/*
PROG: matrix
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXN 300

typedef struct Matrix_s {
  size_t R; 
  size_t C;
  int index[MAXN][MAXN];
} Matrix;

// %zu is used for reading in a size_t
// this function initializes a new Matrix
void read_matrix( FILE *input, Matrix *matrix ) {
  // fscanf is used to read 
  // assign the two integers to matrix.R and matrix.C
  // why do we use the -> notation?
  // here the dimensions of the Matrix are set
  fscanf( input, "%zu %zu", &matrix->R, &matrix->C );

  // if either size_t is too big
  if( matrix->R > MAXN || matrix->C > MAXN ) {
    printf( "Error: tried to read in a (%zu x %zu) matrix (too large)\n", matrix->R, matrix->C );
    exit( EXIT_FAILURE );
  }

  // This actually places the values into the matrix
  for( size_t r = 0; r < matrix->R; ++r ) {
    for( size_t c = 0; c < matrix->C; ++c ) {
      fscanf( input, "%d", &matrix->index[r][c] );
    }
  }
}

void print_matrix( FILE *output, Matrix *matrix ) {
	fprintf( output, "%zu %zu\n", matrix->R, matrix->C );
  for( size_t r = 0; r < matrix->R; ++r ) {
    for( size_t c = 0; c < matrix->C - 1; ++c ) {
      fprintf( output, "%d ", matrix->index[r][c] );
    }
    fprintf( output, "%d\n", matrix->index[r][matrix->C - 1] );
  }
}

void product_matrix( Matrix *a, Matrix *b, Matrix *product ) {
    if ( a->C != b->R ) {
        product->R = 0;
        product->C = 0;
    } else {
        product->R = a->R;
        product->C = b->C;
        // for each row in a
        for ( size_t ar = 0; ar < a->R; ar++ ) {
            // for each column in b
            for ( size_t bc = 0; bc < b->C; bc++ ) {
                // for each value in a row or b column
                int value = 0;
                for ( size_t ac = 0; ac < a->C; ac++ ) {
                    value += a->index[ar][ac] * b->index[ac][bc];
                }
                product->index[ar][bc] = value;
            }
        }
    }
}

int main(void) {
  FILE *fin = fopen( "matrix.in", "r" );

  if( fin == NULL ) {
    printf( "Error: could not open matrix.in\n" );
    exit( EXIT_FAILURE );
  }

  Matrix a, b, c;
  read_matrix( fin, &a );
  read_matrix( fin, &b );
  fclose( fin );

  product_matrix( &a, &b, &c );

  FILE *output = fopen( "matrix.out", "w" );

  if( output == NULL ) {
    printf( "Error: could not open matrix.out\n" );
    exit( EXIT_FAILURE );
  }

  print_matrix( output, &c );
  fclose( output );

  return 0;
}
