#include <stdio.h>
#include <fstream>
#include <cstring>

#include "file_parser.h"
#include "common.h"

static constexpr size_t
READ_BUFFER_SIZE = 255;

void
file_parser::get_filename()
{
  printf("File name (max length:" TO_STR(FILENAME_LENGTH) " ): ");
  scanf("%s", filename);
  getchar(); // skip \n
}

void
file_parser::parse_format_file(array* ar)
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

  ar->ptr = new ARRAY_SPECIFIER[size];
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

void
file_parser::get_size(array* arr)
{
  printf("Input size of array: ");
  scanf("%zu", &arr->size);
  getchar(); // skip \n
}

void
file_parser::parse_file(array* arr)
{
  if(arr->ptr != NULL)
    delete[] arr->ptr;

  arr->ptr = new ARRAY_SPECIFIER[arr->size];

  std::ifstream file;
  file.open("/dev/random");

  if(!file.good())
  {
    printf("Bad filename! Try again!\n");
    file.close();
    return;
  }

  file.read((char*)arr->ptr, arr->size * sizeof(ARRAY_SPECIFIER));

  file.close();

  return;
}
