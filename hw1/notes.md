### `floating.c` assignment

To read a line in a file I would use `fgets`

To use `fgets` I pass it three args:

1. a char array that will be used to store the line
2. an int to tell it the max num characters to read. It will stop at a newline
   or the char limit, whichever is reached first.
3. and a FILE object to read from


