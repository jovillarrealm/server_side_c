#include <stdio.h>      // FILE
#include <netinet/in.h> /*SOCK_STREAM, sockaddr_in*/
#include <pthread.h>    /*pthreads and shit*/
#include <sys/socket.h> // accept, sockaddr
#include <stdlib.h>
#include "minsc.h"
#include "constants.h"


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Faltaron parámetros, son 4 en total\n");
    }
    int http_port = atoi(argv[1]);

    FILE *logs = fopen(argv[2], "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    char *doc_root_folder = argv[3];

    fprintf(logs, "Inicio de sesión de loggeo, JAAAAAAA\n");

    int server_tcp_socket_in = initialize_listening_socket(logs, http_port, MAX_CONNECTIONS);
    struct sockaddr_in client_addr_in;
    int client_socket;
    pthread_t thread_id;
    while (1)
    {
        client_socket = accept(server_tcp_socket_in, (struct sockaddr *)&client_addr_in, (socklen_t *)sizeof(client_addr_in));
        if (client_socket == -1)
        {
            fprintf(logs, "Error: accept()\n");
            perror("Error al aceptar el cliente");
            continue;
        };

        if (pthread_create(&thread_id, NULL, serve, &client_socket) != 0)
        {
            fprintf(logs, "Error: pthread_create()\n");
            perror("Error al crear un hilo para manejar la conexion entrante");
            continue;
        }

        fflush(stdout);

    }
    return 0;
}
