#include <stdio.h>      // FILE
#include <netinet/in.h> /*SOCK_STREAM, sockaddr_in*/
#include <pthread.h>    /*pthreads and shit*/

#include "minsc.h"

#define MAX_CONNECTIONS 10

int main(int argc, char *argv[])
{
    // FIXME de que tal vez hay un montón de casts de sockaddr_in a sock_addr
    if (argc != 4)
    {
        printf("Faltaron parámetros, son 4 en total\n");
    }
    int http_port = atoi(argv[1]);

    char *logs_name = argv[2];
    FILE *logs = fopen(logs_name, "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    char *doc_root_folder = argv[3];

    fprintf(logs, "Inicio de sesión de loggeo, JAAAAAAA\n");

    int server_tcp_socket_in = initialize_listening_port(logs, http_port, MAX_CONNECTIONS);

    struct sockaddr_in client_socket;

    int client_socket;
    while (1)
    {
        //client_socket = accept(server_tcp_socket_in, (struct sockaddr *)&client_socket, (socklen_t)sizeof(client_socket));
        fflush(stdout);

        return 0;
    }
}
