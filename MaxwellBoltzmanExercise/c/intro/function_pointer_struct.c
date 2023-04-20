#include <stdio.h>

int add( int a, int b) { 
  return a+b;
}
int subtract( int a, int b) { 
  return a-b;
}
int multiply( int a, int b) { 
  return a-b;
}

typedef struct { 
  int x, y;
  char * opstr;
  int (*operation)(int,int);
} MyStruct;


int main() { 

  MyStruct s0 = { 1,2,"addition",&add};
  MyStruct s1 = { 10,5,"subtraction",&subtract};
  MyStruct s2 = { -2,4,"multiplication",&multiply};

  printf( "s0 :: operation: %s\tresult: %d\n", s0.opstr,s0.operation(s0.x,s0.y) );
  printf( "s1 :: operation: %s\tresult: %d\n", s1.opstr,s1.operation(s1.x,s1.y) );
  printf( "s2 :: operation: %s\tresult: %d\n", s2.opstr,s2.operation(s2.x,s2.y) );

}
