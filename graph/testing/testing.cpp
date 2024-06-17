#include <stdio.h>
#include <stdint.h>
#include <chrono>

#include "array.h"
#include "sorting.h"
#include "file_parser.h"
#include "common.h"


#define SIZE 10000
#define SIZE_ADD 20000
#define TIMES 10

#define NOW() \
        std::chrono::high_resolution_clock::now()

using time_ms = std::chrono::duration<float, std::chrono::milliseconds::period>;

int
main()
{
  auto* parser = new file_parser();
  auto* arr    = new array<float>();
  auto* sort   = new sorting<float>();

  for(int j = 0; j < 7; j++)
  {
    arr->size = SIZE + j * SIZE_ADD;

    auto elapsed = time_ms();

    for(size_t i = 0; i < TIMES; i++)
    {
      parser->parse_file(arr);

      sort->set_array(arr);
      sort->presort('2');


      auto start = NOW();

      sort->insertion_sort();

      auto end = NOW();
      elapsed += time_ms(end - start);

      if(!arr->is_sorted())
      {
        printf("FAIL!\n");
        return 5;
      }
    }

    elapsed /= TIMES;
    printf("\nAVG: %fms\n", elapsed.count());
    printf("SIZE: %zu\n", SIZE + SIZE_ADD * j);
  }
  delete parser;
  delete sort;
  delete arr;
}
