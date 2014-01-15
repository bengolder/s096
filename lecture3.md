The loop for matrix multiplication is O(n)

The way that we access memory could spped up the application by as much as 3
times.

Your cpu has a set of registers. The L1 cache is the fastest, small bit of
memory registers
There are also L2, and L3, increasingly slower.
The L caches are much faster than the huge RAM, but are much smaller.

When RAM is accessed, it fetches a little more than what you want.
If you're iterating over a matrix, then it will probably fetch other things
that you want, as long as your matrix is coniguously stored.

Accessing contiguous data is faster than jumping between areas of data that
are farther apart.

So if you transpose matrix b, and then just do a row by row calculation, you
can get a speedup of about 3 times.

This is by no means the fastest matrix multiplication
If you look at the first slides o


__how does one read in a string safely__

Separation of declaration and definition.

Generally C projects are not one file. Separation of definitions into header files.

    // in header (.h)
    void increment( int *a );
    // in source (.c)
    void increment( int *a ) {
        ++*a;
    }

Include guards (in myheader.h )

    #ifndef _MYHEADER_H
    #define _MYHEADER_H

    void increment( int *a );
    // your header stuff

    #endif // _MY_HEADER_H

Let's say we have 

    src/
        main.c
        library/
            lib.h - contains declarations, but 
                    functions are implemented in binary lib file
            lib - binary file with compiled functions


    include/
        lib.h -
    src/
        lib.c - source code
    lib/
        lib.a - binary, for Mac?


### Code Style - so stylish! - be consistent!

if you're editing code, ALWAYS use the convention of the library you are
editing.

    void fill_random( float *a, size_t N ) {
      for( size_t i = 0; i < N; ++i ) {
        int *a; // asterisk is before variabls
      }
    }

    Matrix* constructor ( ... ) {
    } // asterisk is after typename


