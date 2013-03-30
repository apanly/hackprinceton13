#include <aubio.h>
#include "utils_tests.h"

int main ()
{
  uint_t i, window_size = 16; // window size
  utils_init_random();
  cvec_t * complex_vector = new_cvec (window_size); // input buffer
  uint_t rand_times = 4;

  while (rand_times -- ) {
    // fill with random phas and norm
    for ( i = 0; i < complex_vector->length; i++ ) {
      complex_vector->norm[i] = ( 2. / RAND_MAX * random() - 1. );
      complex_vector->phas[i] = ( 2. / RAND_MAX * random() - 1. ) * M_PI;
    }
    // print the vector
    cvec_print(complex_vector);
  }

  // set all vector elements to `0`
  cvec_zeros(complex_vector);
  for ( i = 0; i < complex_vector->length; i++ ) {
    assert( complex_vector->norm[i] == 0. );
    // assert( complex_vector->phas[i] == 0 );
  }
  cvec_print(complex_vector);

  // set all vector elements to `1`
  cvec_ones(complex_vector);
  for ( i = 0; i < complex_vector->length; i++ ) {
    assert( complex_vector->norm[i] == 1. );
    // assert( complex_vector->phas[i] == 0 );
  }
  cvec_print(complex_vector);
  // destroy it
  del_cvec(complex_vector);
  return 0;
}
