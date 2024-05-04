#pragma once
#include "array.h"

#include <vector>
#include <cstdint>

template <typename T>
class sorting
{
public:
  array<T> arr;

  void
  insertion_sort()
  {
   for(size_t i = 1; i < arr.size; i ++)
   {
     const T key = arr.ptr[i];
     size_t j  = i;

     do
     {
       if(j == 0 || key > arr.ptr[j - 1])
       {
         arr.ptr[j] = key;
         break;
       }
       else
       {
         arr.ptr[j] = arr.ptr[j - 1];
         j--;
       }
     } while(true);
   }
  }

  // do shallow copy
  void
  set_array(array<T>* other)
  {
    this->arr.ptr  = other->ptr;
    this->arr.size = other->size;
  }

  sorting()
  {
  }

  ~sorting()
  {
  }

  void
  shell_calculate_gaps(int type)
  {
    return type == '1' ? shell_calculate_gaps_knuth() : shell_calculate_gaps_shell();
  }

  void
  shell_sort()
  {
    for(; shell_gap != 0; shell_gap /= gap_div_num)
    {
      for(int i = arr.size - shell_gap - 1; i >= 0; i--)
      {
          T tmp = arr.ptr[i];

          for(size_t j = i + shell_gap; j < arr.size && tmp > arr.ptr[j]; j += shell_gap)
            arr.ptr[j - shell_gap] = arr.ptr[j];

          arr.ptr[i - shell_gap] = tmp;
      }
    }
  }

  void
  heap_sort()
  {
    
  }

  void set_pivot(int i)
  {
    if(i == 0)
      _pivot = 0;
    else if(i == 2)
      _pivot = arr.size - 1;
    else if(i == 3)
    {
    }
  }

  void
  quicksort(size_t l, size_t r)
  {
    if(l >= r)
      return;

    int32_t i = qpart(l, r);
    quicksort(l, i);
    quicksort(i + 1, r);
  }

private:

  int32_t
  qpart(int32_t l, int32_t r)
  {
    T pivot = arr.ptr[_pivot];
    int32_t l_ = l, r_ = r;

    while(true)
    {
      while(arr.ptr[l] < pivot && l < arr.size) l++;
      while(arr.ptr[r] > pivot && r >= 0) r--;

      if(l < r)
      {
        arr.swap(l, r);
        l++;
        r--;
      }
      else
      {
          if(r == r_) r--;
          return r;
      }
    }
  }

  void
  shell_calculate_gaps_shell()
  {
    shell_gap = arr.size / 2;
    gap_div_num = 2;
  }

  void
  shell_calculate_gaps_knuth()
  {
    size_t last = 1;

    while(true)
    {
      shell_gap = 3 * last + 1;

      if(shell_gap > arr.size)
        break;
      last = shell_gap;
    }

    shell_gap /= 9;
    printf("gaps: %zu", shell_gap);
    gap_div_num = 3;
  }

  size_t shell_gap;
  size_t gap_div_num;
  size_t _pivot;
};
