#ifndef _SHAPE_H_
#define _SHAPE_H_

enum shape_type {CIRCLE, RECTANGLE, TRIANGLE};

typedef struct circle_data_struct
{
  double radius;
} circle_data;

typedef struct rect_data_struct
{
  double length;
  double width;
} rect_data;

typedef struct tri_data_struct
{
  double side1;
  double side2;
  double side3;
} tri_data;

typedef struct shape_struct
{
  char* name;
  int key;
  enum shape_type which_one;
  union
  {
    circle_data circ;
    rect_data rect;
    tri_data tri;
  };
} shape;

shape create_circle (double r);

shape create_rect (double l, double w);

shape create_tri (double a, double b, double c);

double get_area (shape sh);

char* to_string (shape sh);

void free_shape (shape sh);

int cmp_shapes (shape sh1, shape sh2);

#endif
