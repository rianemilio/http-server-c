#include "http.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define BUFFER_SIZE 8192

void handle_connection(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    long bytes_read;

    // Lê a requisição do cliente para o buffer
    bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("Falha ao ler do soquete do cliente");
        return;
    }
    if (bytes_read == 0) {
        printf("Cliente desconectou sem enviar dados.\n");
        return;
    }

    printf("--- Requisição Recebida ---\n%s\n---------------------------\n", buffer);

    // Variáveis para guardar o método e o caminho
    char method[16];
    char path[256];

    // Extrai o método e o caminho da primeira linha da requisição
    // Ex: "GET /index.html HTTP/1.1"
    sscanf(buffer, "%s %s", method, path);

    // Exibe as informações extraídas para depuração
    printf("Método: %s\n", method);
    printf("Caminho: %s\n", path);
}
