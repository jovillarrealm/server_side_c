#include <stdio.h> // FILE
int MAX_CONNECTIONS = 11;
int MAX_REQUEST_LEN = 4096;
int MAX_RESPONSE_LEN = 4096;
int OK = 200;
int BAD_REQUEST = 400;
int NOT_FOUND = 404;
int BUFSIZE = 4096;

typedef struct
{
    int socket_fd;
    FILE *log_file;
} thread_args;

typedef struct
{
    char method[8];
    char path[257];
    char version[16];
} http_request;