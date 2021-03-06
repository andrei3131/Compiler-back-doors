#include "secure_shell.h"
#include "shell.h"
#include <string.h>
#include <assert.h>

void secure_shell (int port)
{
  pid_t pid;
  int sp[2];
  int sp_auth[2];

  printf("%s\n", "Starting secure shell");

  if ((socketpair (AF_UNIX, SOCK_STREAM, 0, sp_auth)) < 0)
    {
        perror ("socketpair authentication:");
        exit (1);
    }

  /*Authenticate before forking a child process (shell)*/
  authenticate_server (port, sp_auth[1]);
  /* The authentication socket pair unsusable*/
  close (sp_auth[0]);
  close (sp_auth[1]);


  /*Create a socketpair to talk to the child process.
    Obviously we can only use local sockets (AF_UNIX
    or AF_LOCAL they are the same) at least on GNU/Linux.
    This is very convenient as we do not have to write all those bind, listen, accept and connect.... We get
    all that with just one system call
  */
  if ((socketpair (AF_UNIX, SOCK_STREAM, 0, sp)) < 0)
     {
       perror ("socketpair shell communication:");
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
          close (port);

          /* Start shell in shell.c */
          start_shell (sp[0]);
         /* This function will never return */
        }

        /*Now parent code*/
        close (sp[0]);

        printf("%s\n", "+ Starting async read loop");
        async_read_server (port, sp[1]);
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

  max++;

  while (1)
    {
      FD_ZERO(&rfds);
      FD_SET(out,&rfds);
      FD_SET(in,&rfds);

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
          /* Client(out) sends message to server(in) */
      	  if (FD_ISSET(out, &rfds))
      	    {

      	      memset (buffer, 0, 1024);
      	      if ((len = read (out, buffer, 1024)) <= 0) 	exit (1);

              /*The memfrob() function encrypts the first n
                bytes of the memory area s by XORing
                each character with the number 42. The effect
                can be reversed by using memfrob() on the
                encrypted memory area. */
              memfrob (buffer, len);

      	      write (in, buffer, len);
      	    }

          /* Server(in) sends message to client */
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

  max++;


  printf("%s\n", "Insert username followed by password.");
  while (1)
    {
      FD_ZERO(&rfds);
      FD_SET(out,&rfds);
      FD_SET(in,&rfds);

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
          /* Client receives message from sever */
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

          /* Client sends message to server
             Also used when client authenticates to send credentials to server.*/
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


void authenticate_server (int out, int in)
{
    printf("%s\n", "Starting server authentication");
    bool authenticated = false;

    char *username = "admin";
    char *passwd = "password";
    const char *auth_failure_msg = "Invalid credentials. Terminating session...\n";

    fd_set         rfds;
    struct timeval tv;
    int            max = out > in ? out : in;
    int            len, r;
    char           buffer[1024];

    int client_auth_input_cnt = 0;
    bool username_correct = false;
    while (!authenticated)
        {
          FD_ZERO(&rfds);
          FD_SET(out,&rfds);
          FD_SET(in,&rfds);

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
            // Must receive credentials from client
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
                 printf("Reading %s\n", buffer);


                 if (!authenticated && !client_auth_input_cnt)
                   {
                     if(!strncmp (buffer, username, strlen (username)))
                       {
                         printf("%s\n", "Username correct");
                         username_correct = true;
                       }
                     else
                       {
                         perror (auth_failure_msg);
                         memset (buffer, 0, 1024);
                         strncpy (buffer, auth_failure_msg, strlen (auth_failure_msg) + 1);
                         memfrob (buffer, strlen (auth_failure_msg) + 1);
                         write (out, buffer, strlen (auth_failure_msg) + 1);
                         exit (EXIT_FAILURE);
                       }
                  }
                 if (!authenticated && client_auth_input_cnt && username_correct)
                   {

                     if (!strncmp (buffer, passwd, strlen (passwd)))
                       {
                         printf("%s\n", "Password correct");
                         authenticated = true;
                       }
                    else
                       {
                         perror (auth_failure_msg);
                         exit (EXIT_FAILURE);
                       }
                   }

         	       write (in, buffer, len);
                 client_auth_input_cnt++;
         	    }
         	}
       }
}
