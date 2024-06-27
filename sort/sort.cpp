#include <stdio.h>
#include <stdint.h>
#include <chrono>

#include "array.h"
#include "sorting.h"
#include "file_parser.h"

static int
choose_sort()
{
  printf("\nChoose:\n");
  printf("1. Insertion sort\n");
  printf("2. Shell sort\n");
  printf("3. Quick sort\n");
  printf("4. Heap sort\n");
  printf("5. Do presort\n");
  printf("6. Exit\n");
  printf("\nInput:  ");

  const char input = getchar();
  getchar();

  if(input < 49 || input > 54)
  {
    printf("\nWrong input, try again!\n");
    return choose_sort();
  }
  return input;
}

static int
pick_shell_sort()
{
  printf("\nChoose:\n");
  printf("1. Knuth\n");
  printf("2. Shell\n");
  printf("3. Exit\n");
  printf("\nInput:  ");

  const char input = getchar();

  if(input < 49 || input > 51)
  {
    printf("\nWrong input, try again!\n");
    return pick_shell_sort();
  }
  return input;
}

static int
pick_pivot()
{
  printf("\nChoose:\n");
  printf("1. Left\n");
  printf("2. Right\n");
  printf("3. Random\n");
  printf("4. Exit\n");
  printf("\nInput:  ");

  const char input = getchar();

  if(input < 49 || input > 52)
  {
    printf("\nWrong input, try again!\n");
    return pick_pivot();
  }
  return input;
}

static int
handle_presort()
{
  printf("\nChoose:\n");
  printf("1. 33%%\n");
  printf("2. 66%%\n");
  printf("3. Desc\n");
  printf("4. Exit\n");
  printf("\nInput:  ");

  const char input = getchar();
  getchar();

  if(input < 49 || input > 52)
  {
    printf("\nWrong input, try again!\n");
    return handle_presort();
  }
  return input;
}

#define NOW() \
        std::chrono::high_resolution_clock::now()

template <typename T>
static void
handle_sorting(array<T>* arr, array<T>* arr_sort, sorting<T>* sort)
{
  using time_ms = std::chrono::duration<float, std::chrono::milliseconds::period>;

  int sort_ = choose_sort();

  while(sort_ == '5')
  {
    auto input = handle_presort();
    sort->presort(input);

    sort_ = choose_sort();
  }

  if(sort_ == '6')
    return;

  arr_sort->copy(arr);
  sort->set_array(arr_sort);

  switch(sort_)
  {
    case '1':
    {
      auto start = NOW();
      sort->insertion_sort();
      auto end = NOW();
      auto elapsed = time_ms(end - start);

      printf("\nTime: %fms", elapsed.count());
    } break;

    case '2':
    {
      auto shell = pick_shell_sort();
      sort->shell_calculate_gaps(shell);

      auto start = NOW();
      sort->shell_sort();
      auto end = NOW();
      auto elapsed = time_ms(end - start);

      printf("\nTime: %fms", elapsed.count());
    } break;

    case '3':
    {
      auto start = NOW();
      sort->quicksort_start();
      auto end = NOW();
      auto elapsed = time_ms(end - start);

      printf("\nTime: %fms", elapsed.count());
    } break;

    case '4':
    {
      auto start = NOW();
      sort->heap_sort();
      auto end = NOW();
      auto elapsed = time_ms(end - start);

      printf("\nTime: %fms", elapsed.count());
    } break;
  }

}

static int
menu()
{
  printf("\nChoose:\n");
  printf("1. Load array from given file\n");
  printf("2. Generate array with random numbers\n");
  printf("3. Show last generated/loaded array\n");
  printf("4. Run sorting algorithm\n");
  printf("5. Show sorted array\n");
  printf("6. Validate sorted array\n");
  printf("7. Exit\n");
  printf("\nInput:  ");

  const char input = getchar();

  if(input < 49 || input > 55)
  {
    printf("\nWrong input, try again!\n");
    return menu();
  }
  return input;
}

int
main()
{

  auto parser      = new file_parser();
  auto* arr        = new array<uint32_t>();
  auto* arr_sorted = new array<uint32_t>();
  auto* sort       = new sorting<uint32_t>();

  while(true)
  {
    const int option = menu();
    getchar(); // skip \n

    switch(option)
    {
      case '1':
      {
        parser->get_filename();
        parser->parse_format_file(arr);
      } break;

      case '2':
      {
        parser->get_size(arr);
        parser->parse_file(arr);
      } break;

      case '3':
      {
        if(arr->ptr == NULL)
        {
           printf("No loaded array!\n");
           continue;
        }

        arr->print();

     } break;

     case '4':
      {
        handle_sorting(arr, arr_sorted, sort);
      } break;

      case '5':
      {
        arr_sorted->print();
      } break;

      case '6':
      {
        arr_sorted->is_sorted() ?
          printf("Success! Array is sorted!\n") :
          printf("Fail! Array is not sorted!\n");
      } break;

      case '7':
      {
        delete arr;
        delete arr_sorted;
        delete parser;
        delete sort;
        return 0;
      } break;
    }
  }

}
