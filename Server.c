#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define ALERT_THRESHOLD 10

void display_dashboard(int log_count1, int log_count2) {
    printf("=== Dashboard ===\n");
    printf("Servicio 1: %d logs\n", log_count1);
    printf("Servicio 2: %d logs\n", log_count2);
    printf("=================\n");
}

void send_alert(const char *message) {
    printf("ALERTA: %s\n", message); // Luego implementaremos Twilio
}

void send_alert_via_twilio(const char *message) {
    char command[512];
    snprintf(command, sizeof(command),
             "curl -X POST https://api.twilio.com/2010-04-01/Accounts/sid/Messages.json "
             "--data-urlencode \"Body=%s\" "
             "--data-urlencode \"From= //\" "
             "--data-urlencode \"To= //\" "
             "-u sid : au",
             message);
    
    int result = system(command);
    if (result == -1) {
        perror("Error enviando alerta con Twilio");
    } else {
        printf("Alerta enviada con éxito: %s\n", message);
    }
}


int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error creando socket");
        return 1;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error en bind");
        return 1;
    }

    if (listen(server_fd, 3) == -1) {
        perror("Error en listen");
        return 1;
    }

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    int log_count1 = 0, log_count2 = 0;
    char buffer[BUFFER_SIZE];
    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            perror("Error aceptando conexión");
            continue;
        }

        while (recv(client_fd, buffer, sizeof(buffer), 0) > 0) {
            printf("%s", buffer);
            if (strstr(buffer, "Servicio 1")) log_count1++;
            if (strstr(buffer, "Servicio 2")) log_count2++;

            if (log_count1 > ALERT_THRESHOLD || log_count2 > ALERT_THRESHOLD) {
                send_alert("Threshold excedido");
            }
        }
        close(client_fd);

        display_dashboard(log_count1, log_count2);
    }

    close(server_fd);
    return 0;
}
