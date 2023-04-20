#include <stdio.h>

void swap( int * ptr1, int * ptr2 ) { 
  int tmp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = tmp;
}

void qsort( int * left, int * right ) {

  int *ptr=NULL, *last=NULL, *middle=NULL;

  if( left >= right )
    return;

  middle = left+(right-left)/2;
  swap(left, middle); 
  last = left;

  for( ptr=left+1; ptr<=right; ptr++ ) { 
    if( *ptr < *left ) { 
      swap(++last, ptr);
    }
  }

  swap( left, last );

  qsort( left, last-1);
  qsort( last+1, right);
	     
} 

#define ARRAY_SIZE 7
int array[ARRAY_SIZE] = { 5, -6, 32, 9, 13, -1, 12};

main() { 

  int i;

  printf( "----- before qsort -----\n");
  for( i=0; i<ARRAY_SIZE; i++ ) {
    printf( "%d\t", array[i] );
  }
  printf("\n");

  qsort( array, array+ARRAY_SIZE-1);


  printf( "----- after qsort -----\n");
  for( i=0; i<ARRAY_SIZE; i++ ) {
    printf( "%d\t", array[i] );
  }
  printf("\n");

}
