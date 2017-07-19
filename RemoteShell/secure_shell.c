#include "secure_shell.h"
#include "shell.h"

//static char *username = "admin";
//static char *passwd = "admin";

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
        async_read_server (s, sp[1]);
     }
}

void
async_read_server (int out, int in)
{
  fd_set         rfds;
  struct timeval tv;
  int            max = out > in ? out : in;
  int            len, r;
  char           buffer[1024];
  bool authenticated = false;

  max++;

  while (1)
    {
      FD_ZERO(&rfds);
      FD_SET(out,&rfds);
      FD_SET(in,&rfds);

      /* Time out. */
      tv.tv_sec = 1;
      tv.tv_usec = 0;

      if (!authenticated)
        {
          const char *username_prompt = "Username";
          write (out, username_prompt , len);
        }

      if ((r = select (max, &rfds, NULL, NULL, &tv)) < 0)
      	{
      	  perror ("select:");
      	  exit (EXIT_FAILURE);
      	}
      else if (r > 0 && authenticated) /* If there is data to process */
      	{
          // Client
      	  if (FD_ISSET(out, &rfds))
      	    {
      	      memset (buffer, 0, 1024);
      	      if ((len = read (out, buffer, 1024)) <= 0) 	exit (1);
              /*The memfrob() function encrypts the first n
                bytes of the memory area s by exclusive-ORing
                each character with the number 42. The effect
                can be reversed by using memfrob() on the
                encrypted memory area. */
              memfrob (buffer, len);

      	      write (in, buffer, len);
      	    }
      	  if (FD_ISSET(in, &rfds))
      	    {
      	      memset (buffer, 0, 1024);
      	      if ((len = read (in, buffer, 1024)) <= 0) exit (1);

      	      memfrob (buffer, len);
      	      write (out, buffer, len);
      	    }
      	}
    }
}


void
async_read_client (int out, int in)
{
  fd_set         rfds;
  struct timeval tv;
  int            max = out > in ? out : in;
  int            len, r;
  char           buffer[1024];
  bool authenticated = false;

  max++;


  while (1)
    {
      FD_ZERO(&rfds);
      FD_SET(out,&rfds);
      FD_SET(in,&rfds);

      /* Time out. */
      tv.tv_sec = 1;
      tv.tv_usec = 0;

      authenticated = true;
      if ((r = select (max, &rfds, NULL, NULL, &tv)) < 0)
      	{
      	  perror ("select:");
      	  exit (EXIT_FAILURE);
      	}
      else if (r > 0 && authenticated) /* If there is data to process */
      	{
          // Client
      	  if (FD_ISSET(out, &rfds))
      	    {
      	      memset (buffer, 0, 1024);
      	      if ((len = read (out, buffer, 1024)) <= 0) 	exit (1);
              /*The memfrob() function encrypts the first n
                bytes of the memory area s by exclusive-ORing
                each character with the number 42. The effect
                can be reversed by using memfrob() on the
                encrypted memory area. */
              memfrob (buffer, len);

      	      write (in, buffer, len);
      	    }
      	  if (FD_ISSET(in, &rfds))
      	    {
      	      memset (buffer, 0, 1024);
      	      if ((len = read (in, buffer, 1024)) <= 0) exit (1);

      	      memfrob (buffer, len);
      	      write (out, buffer, len);
      	    }
      	}
    }
}


int authenticate (int out, int in, char *buffer, struct timeval tv, fd_set rfds)
{
    // printf("%s\n", "Authentication:");
    //
    // FD_ZERO(&rfds);
    // FD_SET(out,&rfds);
    // FD_SET(in,&rfds);
    //
    // /* Time out. */
    // tv.tv_sec = 1;
    // tv.tv_usec = 0;
    //
    // if ((r = select (max, &rfds, NULL, NULL, &tv)) < 0)
    //   {
    //     perror ("select:");
    //     exit (EXIT_FAILURE);
    //   }
    // else if (r > 0) /* If there is data to process */
    //   {
    //     // Client
    //     if (FD_ISSET(out, &rfds))
    //       {
    //         memset (buffer, 0, 1024);
    //         if ((len = read (out, buffer, 1024)) <= 0) 	exit (1);
    //         memfrob (buffer, len);
    //
    //         write (in, buffer, len);
    //       }
    //     if (FD_ISSET(in, &rfds))
    //       {
    //         memset (buffer, 0, 1024);
    //         if ((len = read (in, buffer, 1024)) <= 0) exit (1);
    //
    //         memfrob (buffer, len);
    //         write (out, buffer, len);
    //       }
    //   }


    return -9999;
}
