# Proyecto de Sistemas Operativos

Este proyecto implementa un sistema distribuido para monitorear servicios y generar alertas en caso de problemas.

## Estructura del Proyecto

El sistema consta de tres componentes:
1. **Servidor (`servidor.c`)**:  
   Recibe logs enviados por el agente, analiza el estado de los servicios y genera alertas si detecta problemas.

2. **Agente (`agente.c`)**:  
   Monitorea los logs de servicios en ejecución y los envía al servidor.

3. **Prueba de Estrés (`prueba_stress.c`)**:  
   Genera actividad intensa en un servicio para evaluar el desempeño del sistema.

## Requisitos

- Compilador `gcc`.
- Servicios opcionales: `nginx` y `ssh` (pueden ser simulados).
- [Twilio API](https://www.twilio.com/) (opcional para alertas SMS).

## Cómo compilar

Usa el archivo `Makefile` para compilar el proyecto:

```bash
make
