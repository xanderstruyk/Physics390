#include <stdio.h>

void addOneToMyInt(int * foo ) { 
  ++*foo;
}

main() {
  int bar = 22;

  printf("bar: %d\n", bar);
  printf("----- calling addOneToMyInt -----\n");
  addOneToMyInt(&bar);
  printf("bar: %d\n", bar);
  printf("----- calling addOneToMyInt -----\n");
  addOneToMyInt(&bar);
  printf("bar: %d\n", bar);
}
