


## C Standard Library

What else besides `stdio.h` is interesting in the C standard library

    #include <uchar.h> // for unicode handling
    #include <stdarg.h> // for handling varying numbers of arguments
    #include <stdlib.h> // pseudo random 


## Understanding the & and * operators

    int a  = 5; // the address of a is &a
    int *a_ptr = &a; // *a_ptra is a pointer to an int

You can apply & to any addressable value
lvalue is a locatable value - it has a location in memory.

    return &5; // this does not work

the memory addresses ina 64 bit machine can be larger than 2^32

## C data types

char (8) 
short (16), int (32), long (64), long long (64+), size_t (at least 16)
float (32), double (64), long double (~80)


## Compiling 

C compiles to machine code for the computer on which it was compiled.

1. preprocessing - libraries
2. Object code is produced for each function.
2. linking functions - loads functions into memory. It makes things like
   function pointers. 


## Arrays

You can not have a variable sized array in C. So you might have to have large
bounds. Declared and uninitialized variables have no reliable value. They may
often be 0, but there is no guarantee.

## Strings

Strings always have an extra character until they are printed, the "\0" null
character, which is used to signal the end of the string.

## Header files

They aren't supposed ot have full decalrations of functions.
