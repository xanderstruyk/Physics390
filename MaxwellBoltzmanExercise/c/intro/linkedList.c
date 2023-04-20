#include <stdio.h>
#include "barStruct.h"
#define ARRAY_SIZE 10

main() {
  int i=0;
  MyBarStruct foo[ARRAY_SIZE];

  for( i=0; i<ARRAY_SIZE; i++ ) {
    (foo+i)->bar = i;
    (foo+i)->next = foo+i+1;
  } 
  foo[ARRAY_SIZE-1].next = NULL;

  MyBarStruct* ptr;
  for( ptr = foo; ptr != NULL; ptr = ptr->next ) {
    printf( "bar: %d\n", ptr->bar );
  }
}

