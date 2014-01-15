/*
PROG: floating
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// #include "floating.h"

// define the buffer size for reading floats as 
// the FLT_MAX_10_EXP constant + a few extra
#define FLOAT_BUFFER_SIZE 100

// this will combine a float with an unsigned int in memory
union FloatToUnsigned {
    float f;
    unsigned int bits;
};

// this will convert a float to a signed int in memory
union FloatToSigned {
    float f;
    int bits;
};

int get_bit( int bits, int pos ) {
    int mask = 1 << pos;
    int masked_n = bits & mask;
    int thebit = masked_n >> pos;
    return thebit;
}

int *get_bits( int value, int pos, int num_bits ){
    int *bits = malloc( sizeof( int ) * num_bits );
    int i;
    for ( i = 0; i < num_bits; i++ ) {
        bits[i] = get_bit( value, pos + i );
    }
    return bits;
}

char *ints_to_chars( int *ints, int len ) {
    char buffer[4];
    char *chars = malloc( sizeof( char ) * ( len + 1 )  );
    int i;
    for ( i = 0; i < len; i++ ){
        sprintf( buffer, "%d", ints[i] );
        chars[len - (i + 1)] = buffer[0];
    }
    chars[len] = '\0';
    return chars;
}

void copy_string( char *dest, char *src, int len, int pos ) {
    int i;
    for ( i = 0; i < len; i++ ){
        dest[pos + i] = src[i];
    }
}

int fromBinary(char *s) {
  return (int) strtol(s, NULL, 2);
}

char *int_to_bin( int value ) {
    // 1.01000000000000000000000 * 2^-3
    // 1.11010101010011111110000 * 2^2
    char *bin_string = malloc( sizeof( char ) * 50  );
    // mantissa is 0 - 22
    int *mantissa = get_bits( value, 0, 23 );
    char *mantissa_s = ints_to_chars( mantissa, 23 );
    // exponent is 23 - 30
    int *exponent_a = get_bits( value, 23, 8 );
    char *exponent_s = ints_to_chars( exponent_a, 8 );
    int exp_base = fromBinary( exponent_s );
    int exponent = exp_base - 127;
    char expo[5];
    sprintf( expo, "%d", exponent );
    // sign is 31
    int sign = get_bit( value, 31 );
    int k = 0;
    if ( sign == 0 ) {
    } else {
        bin_string[k] = '-';
        k++;
    }
    bin_string[k] = '1';
    k++;
    bin_string[k] = '.';
    k++;
    copy_string( bin_string, mantissa_s, 23, k );
    copy_string( bin_string, " * 2^", 5, k+23 );
    copy_string( bin_string, expo, 4, k+28 );
    bin_string[k+32] = '\0';
    free( mantissa );
    free( mantissa_s );
    free( exponent_a );
    free( exponent_s);
    return bin_string;
}

int main( void ) {
    char read_buffer[FLOAT_BUFFER_SIZE];
    FILE *file_in = fopen( "floating.in", "r" );
    FILE *file_out = fopen( "floating.out", "w" );

    union FloatToSigned hybrid;

    int line = 0;
    while( fgets( read_buffer, FLOAT_BUFFER_SIZE, file_in ) != NULL ) {
        if (line != 0) {
            // convert to float
            hybrid.f = atof( read_buffer );
            // write to file
            char *binary_string = int_to_bin( hybrid.bits );
            fprintf( file_out, "%s\n", binary_string );
            free( binary_string );
        }
        line++;
    }

    // write to the file_out
    fclose( file_in );
    fclose( file_out );
    return 0;
}


