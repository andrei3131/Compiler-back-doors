#include "server.h"


int server_init (int port)
{
  int s, s1;
  socklen_t clen;
  struct sockaddr_in serv, client;

  if ((s = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror ("socket:");
        exit (EXIT_FAILURE);
    }

  serv.sin_family = AF_INET;
  serv.sin_port = htons(port);
  serv.sin_addr.s_addr = htonl(INADDR_ANY);

  printf("%s%d\n", "Starting server on port ", port);
  /*Bind the socket to a specific port.*/
  if ((bind (s, (struct sockaddr *) &serv,
             sizeof (struct sockaddr_in))) < 0)
    {
      perror ("bind:");
      exit (EXIT_FAILURE);
    }

  /*The second parameter passed to listen is the backlog.
    Basically it indicates how many connections will be
    queued to be accepted before the server starts rejecting
    connections. In our case it just do not really matter.*/
  if ((listen (s, 10)) < 0)
    {
      perror ("listen:");
      exit (EXIT_FAILURE);
    }

  clen = sizeof (struct sockaddr_in);

  /*The call to the accept system call will make our
   server wait for an incoming connection. Whenever it
   arrives a new socket will be created to interchange
   data with the new client.*/
  if ((s1 = accept (s, (struct sockaddr *) &client, &clen)) < 0)
     {
       perror ("accept:");
       exit (EXIT_FAILURE);
     }

  return s1;
}
