#include <stdio.h>
#include <stdint.h>

#include "array.h"
#include "file_parser.h"

static void
choose_sort()
{
  printf("\nChoose:\n");
  printf("1. Insertion sort\n");
  printf("2. Shell sort\n");
  printf("3. Quick sort\n");
  printf("4. Heap sort\n");
  printf("5. Exit\n");
  printf("\nInput:  ");

  const char input = getchar();

  if(input < 49 || input > 53)
  {
    printf("\nWrong input, try again!\n");
    return menu();
  }
  return input;
}

template <typename T>
static void
handle_sorting(array<T>* arr, sorting<T>* sort)
{
  const int sort = choose_sort();
  
  if(sort == '5')
    return;

  sort->set_array(arr);

  switch(sort)
  {
    case '1':
    {
      sort->insertion_sort();
    } break;

    case '2':
    {
    }
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
        handle_sorting(arr, sort);
      } break;

      case '5':
      {
        arr_sorted->print();
      } break;

      case '6':
      {
        arr->is_sorted() ?
          printf("Success! Array is sorted!\n") :
          printf("Fail! Array is not sorted!\n");
      } break;

      case '7':
      {
        delete arr;
        delete arr_sorted;
        delete parser;
        return 0;
      } break;
    }
  }

}
