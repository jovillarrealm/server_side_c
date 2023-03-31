#include <stdio.h>
#include <stdlib.h> //exit
#include <string.h> //exit
#include <sys/socket.h> // socket()
#include <netinet/in.h> /*SOCK_STREAM, sockaddr_in*/
#include <netinet/ip.h> /* superset of previous, AF_INET */
#include <unistd.h> //read
#include "constants.h"
#include "minsc.h"


/*function definition*/
void myFunc(void)
{
    printf("Body of myFunc function.\n");
}

int initialize_listening_socket(FILE *logs, int http_port, int MAX_CONNECTIONS)
{
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    // socket() is fallible
    if (tcp_socket == -1)
    {
        fprintf(logs, "Error: socket()\n");
        fclose(logs);
        perror("Error al crear el socket");
        exit(1);
    }

    // sockaddr_in es de IPv4
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET, // IPv4
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(http_port), // host to network short
    };

    // sockaddr es una mentira y es mejor simplemente hacer casts desde cosas que si existen.
    // bind() es falible

    if ( bind(tcp_socket, (struct sockaddr *)&server_addr, (socklen_t) sizeof(server_addr)) == -1)
    {
        fprintf(logs, "Error: bind()\n");
        fclose(logs);
        perror("Error al bindear el socket");
        exit(1);
    }

    // listen() es falible

    if (listen(tcp_socket, MAX_CONNECTIONS) == -1)
    {
        fprintf(logs, "Error: listen()\n");
        fclose(logs);
        perror("Error: listen()\n");
        exit(1);
    }
    return tcp_socket;
}

void *serve(void *connection_info)
{
    thread_args thread_info = *(thread_args *)connection_info;
    int client_socket = thread_info.client_socket_fd;
    FILE* log_file = thread_info.log_file;

    char request_string[MAX_REQUEST_LEN];
    int socket_bytes = read(client_socket, request_string, MAX_REQUEST_LEN);
    if (socket_bytes <= 0)
    {
        fprintf(log_file, "Error: read()\n");
        return NULL;
    }
    else{
        //null terminar el request string por sanidad
        request_string[socket_bytes] = '\0';
    }

    //FIXME parser de http
    char response_string[MAX_RESPONSE_LEN];
    return NULL;
}

// Implementar la función para parsear la petición HTTP:
//shamelessly, stolen :3
int parse_request(char *request_string, http_request *request)
{
    printf("parsing request");
    char *method, *path, *version;
    method = strtok(request_string, " ");
    if (method == NULL)
    {
        return BAD_REQUEST;
    }
    path = strtok(NULL, " ");
    if (path == NULL)
    {
        return BAD_REQUEST;
    }
    version = strtok(NULL, "\r\n");
    if (version == NULL)
    {
        return BAD_REQUEST;
    }
    strncpy(request->method, method, 8);
    strncpy(request->path, path, 256);
    strncpy(request->version, version, 16);
    return OK;
}

// Implementar la función para procesar la petición HTTP:

int process_request(http_request *request, char *response)
{
    printf("processing request");
    char file_path[256];
    FILE *file;
    int file_size, status_code;
    if (strcmp(request->method, "GET") != 0)
    {
        status_code = BAD_REQUEST;
        sprintf(response, "HTTP/1.1 %d Bad Request\r\n\r\n", status_code);
        return status_code;
    }
    sprintf(file_path, ".%s", request->path);
    file = fopen(file_path, "rb");
    if (file == NULL)
    {
        status_code = NOT_FOUND;
        sprintf(response, "HTTP/1.1 %d Not Found\r\n\r\n", status_code);
        return status_code;
    }
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n", file_size);
    fread(response + strlen(response), file_size, 1, file);
    fclose(file);
    return OK;
}