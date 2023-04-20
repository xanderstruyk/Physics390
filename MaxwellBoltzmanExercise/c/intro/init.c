#include <stdio.h>

#define foo 1
#define bar 2
#define foobar foo+bar 

main() {
  int a=-2, b=3;

  int c  = b+=5*-++a;

  /* uncomment the below/comment the above to check ... */
/*   int c = (b+=5)*(-(++a)); */
  
  printf( "c: %d\n", c);

}
