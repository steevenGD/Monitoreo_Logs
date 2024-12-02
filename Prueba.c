#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void generate_logs(const char *service, int interval, int count) {
    for (int i = 0; i < count; i++) {
        printf("[%s] Log %d: Este es un mensaje de prueba.\n", service, i + 1);
        fflush(stdout);
        sleep(interval); // Espera unos segundos entre logs
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <servicio> <intervalo> <cantidad>\n", argv[0]);
        return 1;
    }

    const char *service = argv[1]; // Nombre del servicio simulado
    int interval = atoi(argv[2]);  // Intervalo entre logs (segundos)
    int count = atoi(argv[3]);     // Cantidad de logs a generar

    printf("Iniciando prueba de estrés para el servicio: %s\n", service);
    generate_logs(service, interval, count);

    printf("Prueba de estrés finalizada.\n");
    return 0;
}
