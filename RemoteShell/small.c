#include <stdio.h>

int x = 1;
int y[1][1];

int main (void)
{
	   y[0][0] = 0;
	      while (y[0][0] < 7 ) {
		             int *p = &y[0][0];

			            *p = x;
				           y[0][0] +=1;
					      }


	        //foo ();a
		 printf("%d\n", y[0][0]);
		    return 0;
		    }
		       
