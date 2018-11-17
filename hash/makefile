CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror

build: hash.c hash.h main.c pruebas_catedra.c testing.c testing.h
	$(CC) $(CFLAGS) hash.c main.c pruebas_catedra.c testing.c -o pruebas
	
run: build
	./pruebas
