#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(const char *message) {
    perror(message); 
    exit(EXIT_FAILURE);
}

const char* get_mime_type(const char* file_path) {
    if (strstr(file_path, ".html")) return "text/html";
    if (strstr(file_path, ".css")) return "text/css";
    if (strstr(file_path, ".js")) return "application/javascript";
    if (strstr(file_path, ".jpg")) return "image/jpeg";
    if (strstr(file_path, ".jpeg")) return "image/jpeg";
    if (strstr(file_path, ".png")) return "image/png";
    
    // Tipo padrão para outros arquivos
    return "application/octet-stream";
}
