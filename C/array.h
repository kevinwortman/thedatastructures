
#ifndef ARRAY_H
#define ARRAY_H

#include "basics.h"

struct array_t {
  void **elements;
  int length;
};
typedef struct array_t array;

struct array_location_t {
  array* arr;
  int index;
};
typedef struct array_location_t array_location;

array* array_create(int length);
array* array_create_init(int length, void* element);
void array_each(array* arr, unary_function func);
void array_free(array* arr);

bool array_empty(array* arr);
int array_size(array* arr);

bool array_valid_index(array* arr, int i);
void* array_get_index(array* arr, int i);
void* array_set_index(array* arr, int i, void* element);

void* array_get_front(array* arr);
void array_add_front(array* arr, void* element);
void array_remove_front(array* arr);

void* array_get_back(array* arr);
void array_add_back(array* arr, void* element);
void array_remove_back(array* arr);

array_location* array_location_create(array* arr);
void array_location_free(array_location* loc);
bool array_location_valid(array_location* loc);
void* array_location_get(array_location* loc);
void array_location_next(array_location* loc);

void array_location_insert(array_location* loc, void* element);

#endif
