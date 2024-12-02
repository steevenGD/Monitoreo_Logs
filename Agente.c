#include <stdio.h>      // Para imprimir mensajes
#include <stdlib.h>     // Para usar comandos como system()
#include <unistd.h>     // Para funciones de sistema operativo
#include <string.h>     // Para trabajar con cadenas de texto
#include <sys/socket.h> // Para comunicación entre programas (sockets)
#include <arpa/inet.h>  // Para direcciones IP y puertos

#define BUFFER_SIZE 1024 // Tamaño máximo de los mensajes

// Función para monitorear un servicio y enviar sus logs al servidor
void monitor_service(const char *service, const char *priority, int sock_fd) {
    char command[256];
    snprintf(command, sizeof(command), "journalctl -u %s -p %s --since \"1 min ago\"", service, priority);
    
    FILE *fp = popen(command, "r"); // Ejecuta el comando y lee su salida
    if (!fp) {
        perror("Error ejecutando journalctl");
        return;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), fp)) {
        send(sock_fd, buffer, strlen(buffer), 0); // Envía los logs al servidor
    }
    pclose(fp);
}

int main(int argc, char *argv[]) {
    //if (argc < 5) {
    //    fprintf(stderr, "Uso: %s <IP_servidor> <puerto> <servicio1> <servicio2>\n", argv[0]);
    //    return 1;
    //}
    printf("1");
    // Crear socket para conectarse al servidor
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("Error creando socket");
        return 1;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    // Conectarse al servidor
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error conectando al servidor");
        return 1;
    }

    // Monitorear dos servicios y enviar sus logs al servidor
    monitor_service(argv[3], "info", sock_fd); // Prioridad: info
    monitor_service(argv[4], "err", sock_fd);  // Prioridad: errores

    close(sock_fd); // Cerrar la conexión
    return 0;
}
