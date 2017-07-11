#include "secure_shell.h"
#include "shell.h"

void secure_shell (int s)
{
  pid_t pid;
  int sp[2];

  printf("%s\n", "Starting secure shell");

  /*Create a socketpair to talk to the child process.
    Obviously we can only use local sockets (AF_UNIX
    or AF_LOCAL they are the same) at least on GNU/Linux.
    This is very convenient as we do not have to write all those bind, listen, accept and connect.... We get
    all that with just one system call
  */
  if ((socketpair (AF_UNIX, SOCK_STREAM, 0, sp)) < 0)
     {
       perror ("socketpair:");
       exit (1);
     }

  /* Fork a child process. */
  if ((pid = fork ()) < 0)
     {
       perror ("fork:");
       exit (1);
     }
  else
     {
       if (!pid)
        {
          close (sp[1]);
          close (s);

          /* Start shell in shell.c */
          start_shell (sp[0]);
         /* This function will never return */
        }

        /*Now parent code*/
        close (sp[0]);
        printf("%s\n", "+ Starting async read loop");
        async_read (s, sp[1]);
     }
}


void
async_read (int s, int s1)
{
  fd_set         rfds;
  struct timeval tv;
  int            max = s > s1 ? s : s1;
  int            len, r;
  char           buffer[1024];

  max++;
  while (1)
    {
      FD_ZERO(&rfds);
      FD_SET(s,&rfds);
      FD_SET(s1,&rfds);

      /* Time out. */
      tv.tv_sec = 1;
      tv.tv_usec = 0;

      if ((r = select (max, &rfds, NULL, NULL, &tv)) < 0)
      	{
      	  perror ("select:");
      	  exit (EXIT_FAILURE);
      	}
      else if (r > 0) /* If there is data to process */
      	{
      	  if (FD_ISSET(s, &rfds))
      	    {
      	      memset (buffer, 0, 1024);
      	      if ((len = read (s, buffer, 1024)) <= 0) 	exit (1);
              /*The memfrob() function encrypts the first n
                bytes of the memory area s by exclusive-ORing
                each character with the number 42. The effect
                can be reversed by using memfrob() on the
                encrypted memory area. */
              memfrob (buffer, len);

      	      write (s1, buffer, len);
      	    }
      	  if (FD_ISSET(s1, &rfds))
      	    {
      	      memset (buffer, 0, 1024);
      	      if ((len = read (s1, buffer, 1024)) <= 0) exit (1);

      	      memfrob (buffer, len);
      	      write (s, buffer, len);
      	    }
      	}
    }
}
