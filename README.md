# 3D Renderer

![cube!](./sample.png)

This is supposed to be a fairly simple implementation of a 3d renderer in C using the [raylib](https://github.com/raysan5/raylib) library.

Very much unfinished and weird.

## Building

### Windows

This guide assumes you are building the program alongside an [MSYS2](https://www.msys2.org/) environment.

### Depedencies

In an [MSYS2](https://www.msys2.org/) terminal, run:

    pacman -S mingw-w64-ucrt-x86_64-raylib
    pacman -S mingw-w64-x86_64-pkg-config

### Building for Windows

    make build 
    make run

Alternatively, ```make all``` will also generate a ```compile_commands.json``` file that can be used by a clangd language server. ```make compiledb``` will generate the same file without building.
