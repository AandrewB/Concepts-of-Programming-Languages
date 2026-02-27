#include "shape_io.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "string_utils.h"

/**
   @param f file
   @pre f is open - checked with assertion
   @return size of file in bytes
   @post file pointer is at the beginning of the file
 */
size_t get_file_size (FILE* f)
{
  assert (f != NULL && "f is not open in get_file_size");
  fseek (f, 0L, SEEK_END);
  size_t sz = ftell(f);
  rewind(f);
  return sz;
}  

shape construct_circle (char** tokens, int num_tokens)
{
  assert (tokens != NULL && "null tokens argument in construct_circle");
  assert (num_tokens >= 0 && "negative num_tokens arguent in construct_circle");
  assert (num_tokens == 2 && "invalid num_tokens for a circle");
  double radius = get_double (tokens[1]);
  return create_circle (radius);
}

shape construct_rectangle (char** tokens, int num_tokens)
{
  assert (tokens != NULL && "null tokens argument in construct_rectangle");
  assert (num_tokens >= 0 &&
	  "negative num_tokens arguent in construct_rectangle");
  assert (num_tokens == 3 && "invalid num_tokens for a rectangle");
  double length = get_double (tokens[1]);
  double width = get_double (tokens[2]);
  return create_rect(length, width);
}

shape construct_triangle (char** tokens, int num_tokens)
{
  assert (tokens != NULL && "null tokens argument in construct_triangle");
  assert (num_tokens >= 0 &&
	  "negative num_tokens arguent in construct_triangle");
  assert (num_tokens == 4 && "invalid num_tokens for a triangle");
  double side1 = get_double (tokens[1]);
  double side2 = get_double (tokens[2]);
  double side3 = get_double (tokens[3]);
  return create_tri(side1, side2, side3);
}

shape create_shape_from_line (const char* line)
{
  assert (line != NULL && "null line argument in create_shape_from_line");
  shape sh;
  int num_tokens;
  char** tokens = split (line, ' ', &num_tokens);
  assert (((num_tokens == 2) || (num_tokens == 3) || (num_tokens == 4))
	  && "format error in file");
  char* name = tokens[0];
  assert (name != NULL && "format error in file");
  if (strcmp(name, "circle") == 0)
    sh = construct_circle (tokens, num_tokens);
  else if (strcmp (name, "rectangle") == 0)
    sh = construct_rectangle(tokens, num_tokens);
  else 
    sh = construct_triangle(tokens, num_tokens);
  return sh;
}

bst read_bst_from_file (const char* filename)
{
  assert (filename != NULL && "null filename argument in read_bst_from_file");
  FILE* f = fopen (filename, "r");
  assert (f != NULL && "error opening file");
  size_t file_size = get_file_size(f);
  char buffer[file_size+1];
  size_t amount_read = fread (buffer, sizeof(char), file_size, f);
  assert (amount_read == file_size && "error reading from file");
  buffer[file_size] = '\0';
  bst t = create_bst();
  int num_lines;
  char** lines = split (buffer, '\n', &num_lines);
  for (int i = 0; i < num_lines; i++)
  {
    shape sh = create_shape_from_line (lines[i]);
    insert_in_bst (&t, sh);
  }
  fclose(f);
  delete_str_array (lines, num_lines);
  return t;
}
