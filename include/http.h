#ifndef HTTP_H
#define HTTP_H

// Lê a requisição do cliente, faz o parse e lida com ela.
void handle_connection(int client_fd);

#endif // HTTP_H
