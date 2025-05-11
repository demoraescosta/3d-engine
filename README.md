# 3D Renderer

![cube!](./sample.png)

Fairly simple implementation of a 3D renderer in C using [raylib](https://github.com/raysan5/raylib).

## Depedencies

### Required

- [raylib](https://github.com/raysan5/raylib)

## Building for Windows

This guide assumes an [MSYS2](https://www.msys2.org/) environment.

### Installing depedencies for Windows

In an [MSYS2](https://www.msys2.org/) UCRT64 terminal, run:

    pacman -S pkgconf

In a Powershell terminal, run:
    
    make build 
    make run

## Building for Linux

### Debian

You will need to have a working [raylib](https://github.com/raysan5/raylib) installation, consult the ["Working on GNU Linux"](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) section of the raylib wiki for instructions.

In a terminal, run:

    sudo apt install pkgconf
    make build
    make run

Alternatively, ```make all``` will also generate a ```compile_commands.json``` file that can be used by a [clangd](https://clangd.llvm.org/) language server. ```make compiledb``` will generate the same file without building the application. This behaviour requires [compiledb](https://github.com/nickdiego/compiledb).
