#include <stdio.h>
#ifndef MISC_H
#define MISC_H

/*function declaration.*/
void myFunc(void);

// Aquí se va a llamar socket(), bind(), y listen(). Asume IPv4 de momento.
int initialize_listening_socket(FILE *, int, int);

void *serve(void *);

#endif