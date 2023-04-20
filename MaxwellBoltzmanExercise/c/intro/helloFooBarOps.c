#include <stdio.h>
#include <math.h>

#define MY_FOO 2022
#define MY_PI  3.14159 

main() {
  int foo   = MY_FOO;
  float bar = MY_PI;
  printf("hello, world.  It's %d and I like %.4f!\n", foo, bar);

  foo++;
  bar *=2;
  printf("hello, world.  It's %d and I like %.4f!\n", foo, bar);
 
  foo /= 3;
  bar = 3*foo;
  printf("hello, world.  It's %d and I like %.4f!\n", foo, bar);
}
