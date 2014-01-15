#include <iostream>


/*
 * Typically classes are declared in header files, while
 * the methods and functions are fleshed out in .cpp files
 */

class Array {
  // class variables are private by default
  size_t _size;
  double *_elem;
  public:
    Array( size_t theSize );
    ~Array();

    inline size_t size() const { return size; };
    double& operator[]( size_t i );
    void print() const;
};

Array::Array( size_t theSize )
  : _size{theSize},
    _elem{new double[theSize]} 
{
  for( size_t i = 0; i < _size; ++i ) {
    _elem[i] = 0;
  }
}

Array::~Array() {
  delete [] _elem; // [] indicates deletion of array
}


