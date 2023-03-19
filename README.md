
# server_side_c

El punto es hacer un servidor en C con HTTP1.1
Aquí es donde:

- Daniel
- Sara
- Jorge

vamos a estar haciendo cosas.

## Inicio

De momento se planea tener en una imagen de ubuntu de AWS, o algo, entonces en vez de lidiar con las mierdas de windows de no ser POSIX compliant con freaking sockets no es algo con lo que quiera lidiar.

### Setup

1. Prender un [WSL de ubuntu.](https://learn.microsoft.com/es-mx/windows/wsl/install) y [WSL en vscode.](https://code.visualstudio.com/docs/remote/wsl)
2. Desde wsl se usa con [Meson.](https://mesonbuild.com/SimpleStart.html)

#### Detalles

|Compilador|Build|Debugger|
|---|---|---|
|gcc|meson|gdb|

Debian, Ubuntu and derivatives:

``` bash
sudo apt install build-essential gdb
sudo apt install meson ninja-build
```

Para instalar gcc y gdb

``` bash
sudo apt install build-essential gdb
```

Para instalar meson y ninja

``` bash
sudo apt install meson ninja-build
```

Para iniciar un projecto en el directorio actual

``` bash
meson init --name server_side_c --build
```

Para compilar y testeo

``` bash
meson compile -C builddir
meson test -C builddir
```

Instalar

``` bash
DESTDIR=/path/to/staging/root/borrardespues meson install -C builddir
```
