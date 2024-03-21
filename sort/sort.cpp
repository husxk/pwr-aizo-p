#include <stdio.h>
#include <stdint.h>

#include "array.h"
#include "file_parser.h"

static int
menu()
{
  printf("\nChoose:\n");
  printf("1. Load array from given file\n");
  printf("2. Generate array with random numbers\n");
  printf("3. Show last generated/loaded array\n");
  printf("4. Run sorting algorithm\n");
  printf("5. Show sorted array\n");
  printf("6. Exit\n");
  printf("\nInput:  ");

  const char input = getchar();

  if(input < 49 || input > 54)
  {
    printf("\nWrong input, try again!\n");
    return menu();
  }
  return input;
}

int
main()
{

  auto parser     = new file_parser();
  auto arr        = new array();
  auto arr_sorted = new array();

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

        for(size_t i = 0; i < arr->size; i++)
        {
           printf("%u ", arr->ptr[i]);

           if(i + 1 % 10 == 0)
            printf("\n");
        }
      } break;

      case '6':
      {
        delete arr;
        delete arr_sorted;
        delete parser;
        return 0;
      } break;
    }
  }

}
