#include <stdio.h>      // FILE
#include <netinet/in.h> /*SOCK_STREAM, sockaddr_in*/
#include <pthread.h>    /*pthreads*/
#include <sys/socket.h> // accept, sockaddr
#include <stdlib.h>     //
#include <unistd.h>     //close

#include "minsc.h"
#include "constants.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Faltaron parámetros, son 4 en total\n");
        exit(1);
    }
    int http_port = atoi(argv[1]);

    FILE *log_file = fopen(argv[2], "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    char *doc_root_folder = argv[3];

    fprintf(log_file, "Inicio de sesión de loggeo\n");

    int tcp_socket_in = initialize_listening_socket(log_file, http_port, MAX_CONNECTIONS);
    struct sockaddr_in client_addr_in;
    int client_socket = -1;
    thread_args connection_info = {.client_socket_fd = client_socket, .log_file = log_file};

    pthread_t thread_id;
    while (1)
    {
        client_socket = accept(tcp_socket_in, (struct sockaddr *)&client_addr_in, (socklen_t *)sizeof(client_addr_in));
        if (client_socket == -1)
        {
            fprintf(log_file, "Error: accept()\n");
            perror("Error al aceptar el cliente");
            continue;
        };

        if (pthread_create(&thread_id, NULL, serve, &connection_info) != 0)
        {
            fprintf(log_file, "Error: pthread_create()\n");
            perror("Error al crear un hilo para manejar la conexion entrante");
            continue;
        }
    }
    // cerrar el socket del servidor
    close(tcp_socket_in);
    return 0;
}
