#pragma once

#include <cstring>
#include <cstdio>
#include <cstdint>

template <class T>
class array
{
public:
  T*  ptr;
  size_t size, allocated_size;

  void
  copy(const array* another)
  {
    size = another->size;

    if(ptr == NULL)
    {
      ptr            = new T[size];
      allocated_size = size;
    }
    else if(allocated_size < size)
    {
      delete[] ptr;
      ptr            = new T[size];
      allocated_size = size;
    }
    memcpy(ptr, another->ptr, another->size * sizeof(T));
  }

  void
  swap(int32_t l, int32_t r)
  {
    T tmp = ptr[l];
    ptr[l] = ptr[r];
    ptr[r] = tmp;
  }

  bool
  is_sorted() const
  {
    for(size_t i = 0; i < size - 1; i++)
      if(ptr[i] > ptr[i + 1])
        return false;
    return true;
  }

  void
  print()
  {
    printf("\n\n");
    for(size_t i = 0; i < size; i++)
    {
      printf("%u ", ptr[i]);
      if((i + 1) % 10 == 0)
        printf("\n");
    }
  }

  array(T* ptr, size_t size)
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
