#include "server.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PORT 8080

int main(int argc, char *argv[]) {
    int port;

    if (argc < 2) {
        // Se nenhuma porta for fornecida, usa a porta padrão
        port = DEFAULT_PORT;
        printf("Nenhuma porta especificada. Usando a porta padrão %d.\n", port);
    } else {
        // Converte o argumento para um inteiro
        port = atoi(argv[1]);
        if (port == 0) {
            fprintf(stderr, "Porta inválida: %s\n", argv[1]);
            return 1;
        }
    }

    start_server(port);

    return 0;
}
