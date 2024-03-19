#include <stdio.h>


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
  while(true)
  {
    const int option = menu();

    switch(option)
    {
      case '6':
      {
        return 1;
      } break;
    }
  }
}
