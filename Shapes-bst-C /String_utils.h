#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

/**
   @param s string to be split
   @pre s is not null
   @param delim - delimiter used to split
   @param num_tokens - return parameter holding number of tokens
   @return array of non-null strings
*/
char** split (const char* s, char delim, int* num_tokens);

/**
   @param s string to be converted to double
   @pre s is not null - checked with assertion
   @param x pointer to double being created
   @pre x is not null - checked with assertion
   @return error flag indicating whether an error occurred
   @post *x contains double obtained from s 
*/
double get_double (const char* s);

/**
   @param s string to be converted to int
   @pre s is not null - checked with assertion
   @param n pointer to integer being created
   @pre n is not null - checked with assertion
   @return error flag indicating whether an error occurred
   @post *n contains integer obtained from s
*/
int get_int (const char* s);

/**
   @param a array of strings
   @pre a is not null - checked with assertion
   @param num_strings number of elements in a
   @pre num_strings >= 0 - checked with assertion
   @post all memory allocated to a and its contents has been deallocated
*/
void delete_str_array (char** a, int num_strings);

#endif
