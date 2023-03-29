#ifndef CONSTANTS
#define CONSTANTS

extern int MAX_CONNECTIONS;
extern int MAX_REQUEST_LEN;
extern int MAX_RESPONSE_LEN;
extern int OK;
extern int BAD_REQUEST;
extern int NOT_FOUND;
extern int BUFSIZE;
//Lo que vamos a pasar al hilo de cada conección
// FIXME poner declaraciones afuera no parece funcionar pero no se si está bien
typedef struct thread_args;

typedef struct http_request;
// #define TCP_MSG_MAX_LEN 524280 o 65535

#endif