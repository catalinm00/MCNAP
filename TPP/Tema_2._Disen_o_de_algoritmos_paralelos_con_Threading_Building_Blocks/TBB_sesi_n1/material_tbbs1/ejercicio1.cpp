
#include <cstdlib>

void Foo( double &f ) { 
  unsigned int u = (unsigned int) f; 
  f = (double) rand_r(&u)/RAND_MAX; 
  f=f*f; 
}

void SerialApplyFoo( double a[], size_t n ) { 
  for(size_t i=0; i<n; ++i ) 
    Foo(a[i]); 
}

int main( ) {
  size_t n = 1000;
  double a[n];
  SerialApplyFoo( a, n );
}


