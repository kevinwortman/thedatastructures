
#include <assert.h>
#include <stdlib.h>

#include "array.h"

array* array_create(int length) {
  assert(length >= 0);
  array* arr = (array*) malloc(sizeof(array));
  assert(arr != NULL);
  arr->elements = (void**) malloc(sizeof(void*) * length);
  assert(arr->elements != NULL);
  arr->length = length;
  return arr;
}

array* array_create_init(int length, void* element) {
  array* arr = array_create(length);
  for (int i = 0; i < length; ++i) {
    arr->elements[i] = element;
  }
  return arr;
}

void array_each(array* arr, unary_function func) {
  assert(arr != NULL);
  assert(func != NULL);
  for (int i = 0; i < arr->length; ++i) {
    func(arr->elements[i]);
  }
}

void array_free(array* arr) {
  assert(arr != NULL);
  free(arr);
}

bool array_empty(array* arr) {
  assert(arr != NULL);
  return (arr->length == 0);
}

int array_size(array* arr) {
  assert(arr != NULL);
  return arr->length;
}

bool array_valid_index(array* arr, int i) {
  assert(arr != NULL);
  return (i >= 0) && (i < arr->length);
}

void* array_get_index(array* arr, int i) {
  assert(arr != NULL);
  assert(array_valid_index(arr, i));
  return arr->elements[i];
}

void* array_set_index(array* arr, int i, void* element) {
  assert(arr != NULL);
  assert(array_valid_index(arr, i));
  arr->elements[i] = element;
}

void* array_get_front(array* arr) {
  return array_get_index(arr, 0);
}

void array_add_front(array* arr, void* element) {
  assert(arr != NULL);
  int new_length = arr->length + 1;
  void** new_elements = (void**) malloc(sizeof(void*) * new_length);
  assert(new_elements != NULL);
  new_elements[0] = element;
  for (int i = 0; i < arr->length; ++i) {
    new_elements[i + 1] = arr->elements[i];
  }
  free(arr->elements);
  arr->elements = new_elements;
  arr->length = new_length;
}

void array_remove_front(array* arr) {
  assert(arr != NULL);
  assert(!array_empty(arr));
  int new_length = arr->length - 1;
  void** new_elements = (void**) malloc(sizeof(void*) * new_length);
  for (int i = 1; i < arr->length; ++i) {
    new_elements[i - 1] = arr->elements[i];
  }
  free(arr->elements);
  arr->elements = new_elements;
  arr->length = new_length;
}

/*
void* array_get_back(array* arr);
void array_add_back(array* arr, void* element);
void array_remove_back(array* arr);
*/

array_location* array_location_create(array* arr) {
  assert(arr != NULL);
  array_location* loc = (array_location*) malloc(sizeof(array_location));
  assert(array_location != NULL);
  loc->arr = arr;
  loc->index = 0;
  return loc;
}

void array_location_free(array_location* loc) {
  assert(loc != NULL);
  free(loc);
}

bool array_location_valid(array_location* loc) {
  assert(loc != NULL);
  return array_index_valid(loc->index);
}

void* array_location_get(array_location* loc) {
  assert(loc != NULL);
  assert(array_location_valid(loc));
  return array_get_index(loc->index);
}
 
void array_location_next(array_location* loc) {
  assert(loc != NULL);
  if (array_location_valid(loc)) {
    ++loc->index;
  }
}

/*
void array_location_insert(array_location* loc, void* element);
*/
