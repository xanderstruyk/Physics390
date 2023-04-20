#include <stdio.h>

main() {
  int foo=1,bar=22;
  printf("foo: %d\tfoo address: %u\n", foo, &foo);
  printf("bar: %d\tbar address: %u\n", bar, &bar);
  unsigned fooaddr = (unsigned)&foo; 
  unsigned baraddr = (unsigned)&bar; 
  printf("foo addr - bar addr: %d\n", ( fooaddr - baraddr));
}
