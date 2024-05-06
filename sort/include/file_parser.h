#pragma once
#include <fstream>

#include "array.h"
#include "random.h"

#define FILENAME_LENGTH 1024

static constexpr size_t
READ_BUFFER_SIZE = 255;

class file_parser
{
private:
  char filename [FILENAME_LENGTH];

public:
  void get_filename();

  template <typename T> void
  parse_format_file(array<T>* ar)
  {
    std::ifstream file;
    file.open(filename);

    if(!file.good())
    {
      printf("Bad filename! Try again!\n");
      file.close();
      return;
    }

    // get length of array
    char buffer[READ_BUFFER_SIZE];
    size_t size = 0;
    memset(buffer, 0, READ_BUFFER_SIZE);

    file.getline(buffer, READ_BUFFER_SIZE);
    sscanf(buffer, "%zu\n", &size);

    if(ar->ptr != NULL)
      delete[] ar->ptr;

    ar->ptr = new T[size];
    ar->size = size;

    size_t i = 0;

    while(!file.eof())
    {
      memset(buffer, 0, READ_BUFFER_SIZE);
      file.getline(buffer, READ_BUFFER_SIZE);
      sscanf(buffer, "%u\n", &ar->ptr[i]);
      i++;
    }

    file.close();
  }

  template <typename T> void
  get_size(array<T>* arr)
  {
    printf("Input size of array: ");
    scanf("%zu", &arr->size);
    getchar(); // skip \n
  }

  template <typename T> void
  parse_file(array<T>* arr)
  {
    if(arr->ptr != NULL)
      delete[] arr->ptr;

    arr->ptr = new T[arr->size];

    get_random_x((uint8_t*)arr->ptr, arr->size * sizeof(T));
  }
};
