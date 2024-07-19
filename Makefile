CC = gcc
CFLAGS = -Wall -g $(shell pkg-config --cflags libuv)
LIBS = $(shell pkg-config --libs libuv)

all: file_async_read echo_server

file_async_read: file_async_read.c
	$(CC) $(CFLAGS) -o file_async_read file_async_read.c $(LIBS)

echo_server: echo_server.c
	$(CC) $(CFLAGS) -o echo_server echo_server.c $(LIBS)

run_echo_server: echo_server
	./echo_server

run_file_async_read: file_async_read
	./file_async_read

clean:
	rm -f file_async_read echo_server

.PHONY: all clean