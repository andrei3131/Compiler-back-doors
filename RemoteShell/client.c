#include "client.h"

int client_init (char *ip, int port)
{
  int s;
  struct sockaddr_in serv;

  if ((s = socket (AF_INET, SOCK_STREAM,0 )) < 0)
    {
      perror("socket:");
      exit (EXIT_FAILURE);
    }

  serv.sin_family = AF_INET;
  serv.sin_port = htons(port);
  serv.sin_addr.s_addr = inet_addr(ip);

  printf("Starting client application <%s, %d>\n", ip, port);
  if (connect (s, (struct sockaddr *) &serv, sizeof(serv)) < 0)
     {
       perror("connect:");
       exit (EXIT_FAILURE);
     }

  return s;
}
