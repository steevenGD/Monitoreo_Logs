# Variables
CC = gcc
CFLAGS = -Wall
TARGETS = Server Agente Prueba

# Reglas
all: $(TARGETS)

server: server.c
	$(CC) $(CFLAGS) Server.c -o Server

agente: agente.c
	$(CC) $(CFLAGS) Agente.c -o Agente

prueba_stress: prueba_stress.c
	$(CC) $(CFLAGS) Prueba.c -o Prueba

clean:
	rm -f $(TARGETS)

