#include "shell.h"

int start_shell (int s)
{
  char *name[3];

  dup2 (s, 0);
  dup2 (s, 1);
  dup2 (s, 2);

  name[0] = "/bin/sh";
  name[1] = "-i";
  name[2] = NULL;

  execv (name[0], name);
  exit (1);

  return 0;
}
