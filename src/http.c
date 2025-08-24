#include "http.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define BUFFER_SIZE 8192
#define ROOT_DIR "."

// Função interna (static) para enviar uma resposta de erro (ex: 404)
static void send_error_response(int client_fd, int status_code, const char* status_message) {
    char response[1024];
    // Monta uma resposta HTTP simples com uma pequena página HTML
    sprintf(response, "HTTP/1.1 %d %s\r\nContent-Type: text/html\r\n\r\n"
                      "<html><body><h1>%d %s</h1></body></html>",
                      status_code, status_message, status_code, status_message);
    write(client_fd, response, strlen(response));
}

// Função interna para enviar um arquivo como resposta
static void send_file_response(int client_fd, const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        send_error_response(client_fd, 404, "Not Found");
        return;
    }

    // Calcula o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Obtém o MIME type do arquivo
    const char* mime_type = get_mime_type(file_path);

    // Monta o cabeçalho da resposta 200 OK
    char header[1024];
    if (strncmp(mime_type, "text/", 5) == 0) { // Verifica se é um tipo de texto (text/html, text/css, etc.)
        sprintf(header, "HTTP/1.1 200 OK\r\n"
                        "Content-Type: %s; charset=UTF-8\r\n"
                        "Content-Length: %ld\r\n"
                        "\r\n",
                        mime_type, file_size);
    } else { // Para outros tipos (imagens, etc.), não adiciona o charset
        sprintf(header, "HTTP/1.1 200 OK\r\n"
                        "Content-Type: %s\r\n"
                        "Content-Length: %ld\r\n"
                        "\r\n",
                        mime_type, file_size);
    }
    
    write(client_fd, header, strlen(header));

    // Envia o conteúdo do arquivo em partes (chunks)
    char file_buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(file_buffer, 1, BUFFER_SIZE, file)) > 0) {
        write(client_fd, file_buffer, bytes_read);
    }

    fclose(file);
}

void handle_connection(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_fd, buffer, BUFFER_SIZE - 1);

    char method[16], path[256];
    sscanf(buffer, "%s %s", method, path);

    printf("Método: %s | Caminho: %s\n", method, path);

    // Valida o método. Só aceitamos GET por enquanto.
    if (strcmp(method, "GET") != 0) {
        send_error_response(client_fd, 405, "Method Not Allowed");
        return;
    }

    // Constrói o caminho completo do arquivo
    char file_path[512];
    if (strcmp(path, "/") == 0) {
        // Se o caminho for a raiz, serve o index.html por padrão
        sprintf(file_path, "%s/index.html", ROOT_DIR);
    } else {
        // Caso contrário, junta o diretório raiz com o caminho pedido
        sprintf(file_path, "%s%s", ROOT_DIR, path);
    }
    
    send_file_response(client_fd, file_path);
}
