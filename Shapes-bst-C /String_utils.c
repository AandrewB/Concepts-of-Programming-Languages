#include "string_utils.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

/**
   @param s string
   @pre s is not null - checked with assertion
   @param lower - lower index of substring
   @pre lower >= 0 - checked with assertion
   @param upper - upper index of substring
   @pre upper >= -1 - checked with assertion
   @return substring from lower to upper inclusive
*/
   
char* sub_str (const char* s, int lower, int upper)
{
  assert (s != NULL && "null string argument in sub_str");
  assert (lower >= 0 && "invalid lower argument in sub_str");
  assert (upper >= -1 && "invalid upper argument in sub_str");
  char* sub = NULL;
  if (lower <= upper)
  {
    sub = malloc ((upper-lower+2)*sizeof(char));
    strncpy (sub, s+lower, upper-lower+1);
    sub[upper-lower+1] = '\0';
  }
  return sub;
}

char** split (const char* s, char delim, int* num_tokens)
{
  assert (s != NULL && "null string argument in split");
  assert (num_tokens != NULL && "null num_tokens argument in split");
  *num_tokens = 0;
  for (int i = 0; i < strlen(s); i++)
  {
    if (s[i] == delim)
      (*num_tokens)++;
  }
  char** tokens = malloc((*num_tokens+1)*sizeof(char*));
  int arr_index = 0;
  int index = 0;
  int count = 0;
  for (int i = 0; i < strlen(s); i++)
  {
    if (s[i] == delim)
    {
      char* temp = sub_str(s, index, i-1);
      if (temp != NULL)
      {
	tokens[arr_index] = temp;
	arr_index++;
	index = i+1;
	count++;
      }
    }
  }
  if (s[strlen(s)-1] != delim)
  {
    char* temp = sub_str(s, index, strlen(s)-1);
    if (temp != NULL)
    {
      tokens[arr_index] = temp;
      arr_index++;
      count++;
    }
  }
  if (*num_tokens == count)
    tokens = realloc(tokens, (count+1)*sizeof(char*));
  else if (*num_tokens > count)
  {
    tokens = realloc(tokens, (count+1)*sizeof(char*));
    *num_tokens = count;
  }
  else
    *num_tokens = count;
  return tokens;
}

double get_double (const char* s)
{
  assert (s != NULL && "null string argument in convert_to_double");
  char* temp = NULL;
  double x = strtod(s, &temp);
  assert (temp[0] == '\0');
  return x;
}

int get_int (const char* s)
{
  assert (s != NULL && "null string argument in convert_to_int");
  char* temp = NULL;
  int n = strtol(s, &temp, 10);
  assert (temp[0] == '\0');
  return n;
}

void delete_str_array (char** tokens, int num_tokens)
{
  assert (tokens != NULL && "null tokens argument in delete_str_array");
  assert (num_tokens >= 0 && "invalid num_tokens argument in delete_str_array");
  for (int i = 0; i < num_tokens; i++)
    free (tokens[i]);
  free (tokens);
}

