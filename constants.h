#ifndef CONSTANTS
#define CONSTANTS

extern int MAX_CONNECTIONS;
extern int MAX_REQUEST_LEN;
extern int MAX_RESPONSE_LEN;
extern int OK;
extern int BAD_REQUEST;
extern int NOT_FOUND;
extern int BUFSIZE;
// FIXME poner declaraciones afuera no parece funcionar pero no se si está bien
//Lo que vamos a pasar al hilo de cada conexión
typedef struct thread_args_tag
{
    int client_socket_fd;
    FILE *log_file;
} thread_args;

typedef struct
{
    char method[8];
    char path[257];
    char version[16];
} http_request;
// #define TCP_MSG_MAX_LEN 524280 o 65535

#endif