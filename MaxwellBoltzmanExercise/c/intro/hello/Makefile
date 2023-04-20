
SRC=$(shell echo *.c)
EXE=$(patsubst  %.c, %.exe, $(SRC)) 

all : main.exe

obj/%.o : src/%.c	
	gcc -I include -c $< -o $@

lib/libhello.a : obj/hello.o
	ar r $@ $< 

main.exe : obj/main.o lib/libhello.a
	gcc -I include obj/main.o -o $@ -Llib -lhello



clean : 
	rm -f *.exe obj/*.o src/*~ *~ lib/*
