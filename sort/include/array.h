#pragma once
#include "common.h"

class array
{
public:
  ARRAY_SPECIFIER*  ptr;
  size_t size;

  array(ARRAY_SPECIFIER* ptr, size_t size)
  {
    this->ptr  = ptr;
    this->size = size;
  }

  array()
  {
    this->ptr  = NULL;
    this->size = 0;
  }

  ~array()
  {
    delete[] this->ptr;
  }
};
