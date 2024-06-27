#pragma once
#include "array.h"
#include "random.h"

#include <vector>
#include <cstdint>

template <typename T>
class sorting
{
public:
  array<T> arr;

  ~sorting()
  {
    arr.ptr = NULL;
  }

  void 
  presort(int input)
  {
    switch(input)
    {
      case '1':
      {
        quicksort(0, arr.size/3);
      } break;

      case '2':
      {
        quicksort(0, (arr.size * 2)/3);
      } break;

      case '3':
      {
        auto size = arr.size - 1;
        for(int32_t i = size / 2 - 1; i >= 0; i--)
          prepare_heap(i, size);
      } break;
    }
  }

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

          size_t j;
          for(j = i + shell_gap; j < arr.size && tmp > arr.ptr[j]; j += shell_gap)
            arr.ptr[j - shell_gap] = arr.ptr[j];

          arr.ptr[j - shell_gap] = tmp;
      }
    }
  }

  void
  heap_sort()
  {
    const size_t size = arr.size - 1;
    for(int32_t i = size / 2 - 1; i >= 0; i--)
      prepare_heap(i, size);

    for(size_t i = size; i > 0; i--)
    {
      arr.swap(0, i);

      // fix heap
      prepare_heap(0, i);
    }
  }

  void
  quicksort_start()
  {
    quicksort(0, arr.size - 1);
  }

private:

  void
  quicksort(size_t l, size_t r)
  {
    if(l >= r)
      return;

    int32_t i = qpart(l, r);
    quicksort(l, i);
    quicksort(i + 1, r);
  }

  int32_t
  qpart(int32_t l, int32_t r)
  {
    T pivot = arr.ptr[l];
    int32_t r_ = r;

    while(true)
    {
      while(arr.ptr[l] < pivot && l < (int32_t) arr.size) l++;
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
    gap_div_num = 3;
  }

  void
  prepare_heap(size_t n_root, size_t size)
  {
    size_t largest = n_root;
    size_t l = 2 * n_root + 1;
    size_t r = 2 * n_root + 2;

    if(l < size && arr.ptr[l] > arr.ptr[largest])
      largest = l;

    if(r < size && arr.ptr[r] > arr.ptr[largest])
      largest = r;

    if(largest != n_root)
    {
      arr.swap(largest, n_root);
      prepare_heap(largest, size);
    }
  }

  size_t shell_gap;
  size_t gap_div_num;
  size_t _pivot;
};
