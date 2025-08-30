# Servidor HTTP em C

![Linguagem](https://img.shields.io/badge/linguagem-C-blue.svg)

Um servidor web HTTP/1.1 simples, escrito em C puro e sem dependências externas. O projeto foi desenvolvido com o objetivo de estudar os fundamentos de programação de rede com sockets POSIX e a estrutura do protocolo HTTP.

## Sobre o Projeto

Esta é uma implementação didática de um servidor web em C. O projeto foi construído do zero, utilizando apenas bibliotecas nativas do C e da API de sockets POSIX. O objetivo principal é demonstrar de forma clara e organizada como um servidor lida com conexões TCP, recebe e interpreta requisições HTTP, e envia respostas para servir arquivos estáticos.

Este projeto **não é recomendado para uso em produção**, mas serve como uma excelente base de aprendizado.

### Funcionalidades Implementadas

-   **Escrito em C puro:** Utiliza apenas bibliotecas padrão (`stdio.h`, `sys/socket.h`, etc.).
-   **Sem dependências externas:** Não requer nenhuma biblioteca de terceiros para compilar ou executar.
-   **Requisições GET:** Processa e responde a requisições do método `GET`.
-   **Servidor de Arquivos Estáticos:** Serve arquivos (HTML, CSS, JS, imagens) do diretório onde é executado.
-   **Respostas HTTP Corretas:**
    -   `200 OK` para arquivos encontrados.
    -   `404 Not Found` para arquivos não encontrados.
    -   `405 Method Not Allowed` para métodos diferentes de `GET`.
-   **Tipos de Conteúdo (MIME Types):** Identifica e envia o cabeçalho `Content-Type` adequado para os principais tipos de arquivo.
-   **Suporte a UTF-8:** Envia o `charset=UTF-8` em arquivos de texto para garantir a renderização correta de caracteres especiais.

## Estrutura do Projeto

O código é organizado de forma modular para facilitar a manutenção e o entendimento.

```text
http-server/
├── Makefile                # Automatiza a compilação
├── README.md               # Documentação do projeto
├── .gitignore              # Arquivos a serem ignorados pelo Git
├── bin/                    # Diretório para o executável (criado pelo Makefile)
├── include/                # Arquivos de cabeçalho (.h)
│   ├── server.h
│   ├── http.h
│   └── utils.h
└── src/                    # Arquivos de código-fonte (.c)
    ├── main.c
    ├── server.c
    ├── http.c
    └── utils.c
```

## Pré-requisitos

Para compilar e executar o projeto, você precisará de:

-   Um compilador C (como o `gcc`).
-   A ferramenta `make`.

Na maioria dos sistemas baseados em Linux, você pode instalar ambos com o pacote `build-essential`:
```bash
sudo apt-get update
sudo apt-get install build-essential
```

## Como Compilar e Executar

1.  **Clone o repositório:**
    ```bash
    git clone https://github.com/rianemilio/http-server-c.git
    ```

2.  **Acesse o diretório do projeto:**
    ```bash
    cd http-server-c
    ```

3.  **Compile o código:**
    O `Makefile` cuidará de todo o processo de compilação.
    ```bash
    make
    ```
    Isso criará o executável em `bin/http-server`.

4.  **Execute o servidor:**
    Você pode executar o servidor especificando uma porta. Se nenhuma porta for informada, ele usará a porta padrão `8080`.

    *Para rodar na porta 8080 (padrão):*
    ```bash
    ./bin/http-server
    ```

    *Para rodar em uma porta diferente (ex: 3000):*
    ```bash
    ./bin/http-server 3000
    ```

5.  **Acesse no navegador:**
    Abra seu navegador e acesse `http://localhost:8080` (ou a porta que você escolheu).

## Limpeza do Projeto

Para remover todos os arquivos compilados (arquivos objeto e o executável), use o comando:```bash
make clean
```

## Melhorias Futuras

-   [ ] Adicionar suporte a requisições `HEAD`.
-   [ ] Implementar um sistema de logging de requisições.
-   [ ] Suportar concorrência com threads ou `select()` para lidar com múltiplos clientes simultaneamente.
-   [ ] Permitir a configuração do diretório raiz através de um arquivo ou argumento de linha de comando.
