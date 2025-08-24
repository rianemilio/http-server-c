#include "server.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void start_server(int port) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    socklen_t client_addr_len = sizeof(struct sockaddr_in);

    // 1. Cria o soquete (AF_INET = IPv4, SOCK_STREAM = TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        die("Falha ao criar soquete");
    }

    // Configura o endereço do servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Escuta em qualquer interface de rede
    server_addr.sin_port = htons(port);       // Converte a porta para o formato de rede

    // 2. Vincula (bind) o soquete à porta
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        die("Falha no bind");
    }

    // 3. Escuta (listen) por conexões (até 10 na fila de espera)
    if (listen(server_fd, 10) < 0) {
        die("Falha no listen");
    }

    printf("Servidor escutando na porta %d...\n", port);

    // 4. Loop principal para aceitar conexões
    while (1) {
        // accept() bloqueia a execução até uma nova conexão chegar
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("Falha no accept");
            continue; // Em caso de erro, apenas continua
        }

        printf("Nova conexão aceita!\n");

        // A lógica de tratamento da requisição virá aqui.
        
        // Por agora, apenas fecha a conexão.
        close(client_fd);
    }

    // Fecha o soquete principal ao encerrar (não alcançado no loop)
    close(server_fd);
}
