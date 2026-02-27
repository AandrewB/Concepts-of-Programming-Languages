#include "shape.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define PI atan(1.0) * 4.0
int key = 1;

shape create_shape_template (const char* n)
{
  shape sh;
  sh.name = malloc ((sizeof(n)+1)*sizeof(char));
  strcpy (sh.name, n);
  sh.key = key;
  key++;
  return sh;
}

shape create_circle (double r)
{
  shape sh = create_shape_template ("circle");
  sh.which_one = CIRCLE;
  assert (r > 0 && "invalid radius argument in create_circle");
  sh.circ = (circle_data){r};
  return sh;
}

shape create_rect (double l, double w)
{
  shape sh = create_shape_template ("rectangle");
  sh.which_one = RECTANGLE;
  assert (l > 0 && w > 0 && "invalid length argment in create_rect");
  sh.rect = (rect_data){l,w};
  return sh;
}

shape create_tri (double a, double b, double c)
{
  shape sh = create_shape_template ("triangle");
  sh.which_one = TRIANGLE;
  assert (a > 0 && b > 0 && c > 0 && "invalid length argument in create_tri");
  assert ((a+b)>c && (b+c)>a && (a+c)>b &&
	  "3 arguments do not form a triangle");
  sh.tri = (tri_data){a,b,c};
  return sh;
}

double get_area (shape sh)
{
  double result = 0;
  if (sh.which_one == CIRCLE)
    result = PI*sh.circ.radius*sh.circ.radius;
  else if (sh.which_one == RECTANGLE)
    result = sh.rect.length*sh.rect.width;
  else
  {
    double a = sh.tri.side1;
    double b = sh.tri.side2;
    double c = sh.tri.side3;
    double s = (a+b+c)/2;
    result = sqrt(s*(s-a)*(s-b)*(s-c));
  }    
  return result;
}

char* to_string (shape sh)
{
  char str[50];
  sprintf(str, "%lf", get_area(sh));
  int size = strlen(sh.name) + strlen (str) + 2;
  char* result = malloc (size*sizeof(char));
  strncpy (result, sh.name, strlen (sh.name));
  result[strlen(sh.name)] = ' ';
  strncpy (result+strlen(sh.name)+1, str, strlen(str));
  return result;
}

void free_shape (shape sh)
{
  free (sh.name);
}

int cmp_shapes (shape sh1, shape sh2)
{
  int result;
  if (sh1.key == sh2.key)
    result = 0;
  else if (get_area(sh1) < get_area(sh2))
    result = -1;
  else
    result = 1;
  return result;
}
