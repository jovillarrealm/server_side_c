#include <stdio.h>
#include <sys/socket.h> // socket()
#include <netinet/in.h> /*SOCK_STREAM, sockaddr_in*/
#include <netinet/ip.h> /* superset of previous, AF_INET */
#include <unistd.h> //read
#include <stdlib.h> //exit
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
        perror("Error al bindear el socket");
        exit(1);
    }
    return tcp_socket;
}

void *serve(void *client_info)
{
    int client_socket = *(int *)client_info;
    char request_string[MAX_REQUEST_LEN];
    int socket_bytes = read(client_socket, request_string, MAX_REQUEST_LEN);
    if (socket_bytes <= 0)
    {
        close(client_socket);
        return NULL;
    }
    else{
        request_string[socket_bytes] = '\0';
    }

    char response_string[MAX_RESPONSE_LEN];
    return NULL;
}
