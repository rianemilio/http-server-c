#ifndef UTILS_H
#define UTILS_H

// Exibe uma mensagem de erro e encerra o programa.
void die(const char *message);

// Retorna o MIME type (Content-Type) com base na extensão do arquivo.
const char* get_mime_type(const char* file_path);

#endif // UTILS_H
