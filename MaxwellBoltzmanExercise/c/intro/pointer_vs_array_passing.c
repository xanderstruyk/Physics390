#include <stdio.h>


void print_array_via_pointer(int n, int* pointer) {
  printf("\tsizeof(argument): %d\n", sizeof(pointer));
  for( int i=0; i<n; i++)
    printf( "\ti: %d\tval: %d\n", i, *(pointer+i));
}


//
// C passes arrays by pointer, even it arg is an array
//
void print_array_via_array(int n, int array[]) {
  printf("\tsizeof(argument): %d\n", sizeof(array));
  for( int i=0; i<n; i++)
    printf( "\ti: %d\tval: %d\n", i, *(array+i));
}

//
// now argument is a pointer to an array type
//
void print_array_via_pointer_to_array5(int (*pointer)[5]) {
  printf("\tsizeof(int): %d\n", sizeof(int));
  printf("\tsizeof(argument): %d\n", sizeof(pointer));
  printf("\tsizeof(*argument): %d\n", sizeof(*pointer));
  int n = sizeof(*pointer)/sizeof(int);
  for( int i=0; i<n; i++)
    printf( "\ti: %d\tval: %d\n", i, (*pointer)[i]);
}


void print_array_via_pointer_to_array16(int (*pointer)[16]) {
  printf("\tsizeof(int): %d\n", sizeof(int));
  printf("\tsizeof(argument): %d\n", sizeof(pointer));
  printf("\tsizeof(*argument): %d\n", sizeof(*pointer));
  int n = sizeof(*pointer)/sizeof(int);
  for( int i=0; i<n; i++)
    printf( "\ti: %d\tval: %d (%x)\n", i, (*pointer)[i],(*pointer)[i]);
}

void print_array_via_pointer_to_array3(int (*pointer)[3]) {
  printf("\tsizeof(int): %d\n", sizeof(int));
  printf("\tsizeof(argument): %d\n", sizeof(pointer));
  printf("\tsizeof(*argument): %d\n", sizeof(*pointer));
  int n = sizeof(*pointer)/sizeof(int);
  for( int i=0; i<n; i++)
    printf( "\ti: %d\tval: %d (%x)\n", i, (*pointer)[i],(*pointer)[i]);
}



int main() {

  int array []   = {1,2,3,4,5};
  int * pointer1        = array;        // fine
  int * pointer2        = &(array[0]);  // same as above but explict
  int * pointer3        = &array;       // warning, but OK because the pointer to the array points to
                                        // the first element of the array, like the above
  int * pointer4        = (int*)&array; // cast makes this explicit 


  int (*pointer5)[5]    = &array;       // vs case3 now no warning because pointer type is to the full array


  //
  // dump via normal pointer and explicit point to the 
  // first element
  //
  printf( "\ndumping array via pointer1 ...\n");
  print_array_via_pointer(5,pointer1);
  printf( "\ndumping array via pointer2 ...\n");
  print_array_via_pointer(5,pointer2);
  printf( "\ndumping array via pointer3 ...\n");
  print_array_via_pointer(5,pointer3);
  printf( "\ndumping array via pointer4 ...\n");
  print_array_via_pointer(5,pointer4);


  printf("\n\n");
  printf("--------------------------------------\n");
  printf("\n\n");

  printf( "\ndumping array via 'array' ...\n");
  print_array_via_array(5,array);


  printf("\n\n");
  printf("--------------------------------------\n");
  printf("\n\n");

  //
  // now dump using pointer to the array (w/ correct length 5)
  //
  printf( "\ndumping array via pointer to array5 ...\n");
  print_array_via_pointer_to_array5(pointer5);


  //
  // now dump using pointer to a larger array, compiler warning 
  // but it lets us proceed 
  //
  printf( "\ndumping array via pointer to array16 ...\n");
  print_array_via_pointer_to_array16(pointer5);

  //
  // now dump using pointer to a small array, compiler warning 
  // but it lets us proceed 
  //
  printf( "\ndumping array via pointer to array3 ...\n");
  print_array_via_pointer_to_array3(pointer5);


}
