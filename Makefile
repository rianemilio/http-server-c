# --- Compilador e Flags ---
# Define o compilador a ser usado (gcc)
CC = gcc
# Flags de compilacao:
# -Wall: Habilita todos os avisos do compilador
# -Iinclude: Adiciona o diretorio 'include' a lista de busca por arquivos de cabecalho (.h)
# -g: Adiciona informacoes de debug ao executavel
CFLAGS = -Wall -Iinclude -g

# --- Nomes de Arquivos e Diretorios ---
# Diretorio de arquivos de cabecalho
INCLUDE_DIR = include
# Diretorio de arquivos de codigo fonte
SRC_DIR = src
# Diretorio onde o executavel sera colocado
BIN_DIR = bin
# Nome do executavel final
TARGET = $(BIN_DIR)/http-server

# Encontra todos os arquivos .c no diretorio src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
# Gera os nomes dos arquivos objeto (.o) substituindo a extensao .c por .o
OBJECTS = $(SOURCES:.c=.o)

# --- Regras ---
# Regra principal (default). E executada quando voce digita apenas 'make'
all: $(TARGET)

# Regra para criar o executavel final
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR) # Cria o diretorio bin/ se ele nao existir
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) # Junta todos os arquivos .o para criar o executavel

# Regra para compilar cada arquivo .c em um arquivo .o
# $< representa o primeiro pre-requisito (o arquivo .c)
# $@ representa o nome do alvo (o arquivo .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJECTS) # Remove todos os arquivos objeto
	rm -f $(TARGET)  # Remove o executavel

# Declara alvos que nao sao nomes de arquivos
.PHONY: all clean
