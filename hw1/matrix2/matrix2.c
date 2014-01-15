/*
PROG: matrix2
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000

typedef struct Matrix_s{size_t R, C;int *index;}Matrix;

Matrix* allocate_matrix( size_t R, size_t C ) {
    Matrix *matrix = malloc( sizeof( Matrix ) );
    matrix->R = R;
    matrix->C = C;
    matrix->index = malloc( R * C * sizeof(int) );
	return matrix;
}

void destroy_matrix( Matrix *matrix ) {
    free( matrix->index );
    free( matrix );
}

// %zu is used for reading in a size_t
Matrix* read_matrix( FILE *input ) {
	size_t R, C;
    fscanf( input, "%zu %zu", &R, &C );

    if( R > MAXN || C > MAXN ) {
        printf( "Error: tried to read in a (%zu x %zu) matrix (too large)\n", R, C );
        exit( EXIT_FAILURE );
    }

	Matrix *matrix = allocate_matrix( R, C );

   for( size_t r = 0; r < matrix->R; ++r ) {
       for( size_t c = 0; c < matrix->C; ++c ) {
           fscanf( input, "%d", &matrix->index[c + r * C] );
       }
   }

	return matrix;
}

void print_matrix( FILE *output, Matrix *matrix ) {
	fprintf( output, "%zu %zu\n", matrix->R, matrix->C );
  for( size_t r = 0; r < matrix->R; ++r ) {
    for( size_t c = 0; c < matrix->C - 1; ++c ) {
      fprintf( output, "%d ", matrix->index[c + r * matrix->C] );
    }
    fprintf( output, "%d\n", matrix->index[matrix->C - 1 + r * matrix->C] );
  }
}

Matrix* product_matrix( Matrix *a, Matrix *b ) {
    int R = a->R;
    int C = b->C;
    if ( a->C != b->R ) {
        return allocate_matrix(0, 0);
    } 
    Matrix *product = allocate_matrix( R, C );
    // for each row in a
    for ( size_t r = 0; r < product->R; r++ ) {
        // for each column in b
        for ( size_t c = 0; c < product->C; c++ ) {
            // for each value in a row or b column
            int sum = 0;
            for ( size_t ac = 0; ac < a->C; ac++ ) {
                int ar = a->index[ r *  a->C + ac ];
                int bc = b->index[ ac * b->C + c  ];
                sum += ar * bc;
            }
            product->index[r * product->C + c] = sum;
        }
    }
	return product;
}

int main(void) {
    FILE *fin = fopen( "matrix2.in", "r" );

    if( fin == NULL ) {
        printf( "Error: could not open matrix2.in\n" );
        exit( EXIT_FAILURE );
    }

    Matrix *a = read_matrix( fin );
    Matrix *b = read_matrix( fin );
    fclose( fin );

    Matrix *c = product_matrix( a, b );

    FILE *output = fopen( "matrix2.out", "w" );

    if( output == NULL ) {
        printf( "Error: could not open matrix2.out\n" );
        exit( EXIT_FAILURE );
    }

    print_matrix( output, c );
    fclose( output );

    destroy_matrix( a );
    destroy_matrix( b );
    destroy_matrix( c );

    return 0;
}
