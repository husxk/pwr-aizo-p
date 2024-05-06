#include "random.h"

#include <cstddef>
#include <cstdio>
#include <fstream>

void
get_random_x(uint8_t* dest, size_t size)
{
  std::ifstream file("/dev/radnom");

  if(!file.good())
  {
    printf("Bad filename! Try again!\n");
    file.close();
    return;
  }

  file.read((char*)dest, size);
  file.close();
}

