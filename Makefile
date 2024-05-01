CC = gcc
CFLAGS = #-Wall -Wextra -Werror -std=c11
LIBDIR = lib
LIBS = -llamport -lpthread
LDLIBS = -fPIC -shared

all: build/programa_lamport.out

build/programa_lamport.out: src/programa_lamport.c lib/liblamport.so | build
	$(CC) $(CFLAGS) -o $@ $< $(LIBS) -L$(LIBDIR)

lib/liblamport.so: src/liblamport.c | lib
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $< -lpthread

build:
	mkdir -p build

lib:
	mkdir -p lib

clean:
	rm -rf build lib

