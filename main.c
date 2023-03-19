#include <stdio.h>
#include "minsc.h"
// Para ver como se reinicia el build system de 
// meson init --name server_side_c --build --force 
int main()
{
    printf("Hello, World.\n");
    myFunc();
    fflush(stdout);

    return 0;
}
