#ifndef SECURE_SHELL_H
#define SECURE_SHELL_H

#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

void secure_shell (int s);
void async_read_client (int s, int s1);
void async_read_server   (int s, int s1);
void authenticate_server (int out, int in);

#endif
