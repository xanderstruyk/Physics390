#!/bin/sh

# with object file
gcc -I include/ -c  src/hello.c -o obj/hello.o
gcc -I include/ -c  src/hi.c -o obj/hi.o
gcc -I include/ src/main.c -o main.exe obj/hello.o obj/hi.o


# with library
#gcc -I include/ -c  src/hello.c -o obj/hello.o
#gcc -I include/ -c  src/hi.c -o obj/hi.o
#ar r lib/libhello.a obj/hello.o
#gcc -I include/ src/main.c -o main.exe -L./lib -lhello
