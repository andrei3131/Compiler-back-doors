CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: remote_shell

remote_shell: invisible_shell.o secure_shell.o client.o server.o shell.o main.o
	$(CC) invisible_shell.o secure_shell.o client.o server.o shell.o main.o -o remote_shell_exe

main.o: main.c
			$(CC) $(CFLAGS) main.c -c -o main.o

client.o: client.h client.c
	$(CC) $(CFLAGS) client.c -c -o client.o

server.o: server.h server.c
		$(CC) $(CFLAGS) server.c -c -o server.o

shell.o: shell.h shell.c
		$(CC) $(CFLAGS) shell.c -c -o shell.o

secure_shell.o: secure_shell.h secure_shell.c
				$(CC) $(CFLAGS) secure_shell.c -c -o secure_shell.o

invisible_shell.o: invisible_shell.h invisible_shell.c
				$(CC) $(CFLAGS) invisible_shell.c -c -o invisible_shell.o

clean:
	rm -f $(wildcard *.o)
	rm -f remote_shell
	rm -f remote_shell_exe
