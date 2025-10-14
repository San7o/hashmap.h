// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#define HASHMAP_IMPLEMENTATION
#include "hashmap.h"

#include <stdio.h>
#include <assert.h>

// A custom type
typedef struct {
  int a;
  char* b;
} ExampleType;

// Define deep copy and free functions
ExampleType example_deep_copy(ExampleType *type) {
  printf("Deep copy\n"); return *type;
}
void example_free(ExampleType *type) {
  printf("Free\n"); return;
}

// Declare the hashmap
HASHMAP_DECLARE(example,
                hashmap_hash_char,
                char*,
                ExampleType,
                example_deep_copy,
                example_free)

int main(void)
{
  example_map map;
  assert(example_map_init(&map, 1024) == 0);

  ExampleType example = {
    .a = 10,
    .b = "it just works",
  };
  assert(example_map_update(&map, "example", 8, &example) == 0);

  ExampleType *value = example_map_lookup(&map, "example", 8);
  assert(value != NULL);
  assert(value->a == 10);
  assert(value->b == example.b);

  example_map *map_copy = example_map_deep_copy(&map);
  assert(map_copy != NULL);
  
  ExampleType *value_copy = example_map_lookup(map_copy, "example", 8);
  assert(value_copy != NULL);
  assert(value_copy->a == 10);
  assert(value_copy->b == example.b);

  
  assert(example_map_destroy(&map) == 0);
  assert(example_map_destroy(map_copy) == 0);
  return 0;
}
