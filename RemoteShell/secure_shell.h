#ifndef SECURE_SHELL_H
#define SECURE_SHELL_H

#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

void secure_shell (int s);
void async_read (int s, int s1);

#endif
