#include <stdio.h>
#include <stdint.h>
#include <chrono>

#include "file_parser.h"
#include "containers.h"
#include "algorithms.h"

#define STR(X) STR_(X)
#define STR_(X) #X

#define SIZE 10000
#define SIZE_ADD 20000
#define TIMES 1
size_t V = 5;
#define PERCENT 25

#define NOW() \
        std::chrono::high_resolution_clock::now()

using time_ms = std::chrono::duration<float, std::chrono::milliseconds::period>;

int
main()
{
  auto* parser = new file_parser();
  auto* alg    = new algorithms();
  printf("V,time,percent=%zu,times=%zu,KRUSKAL,LIST\n", PERCENT, TIMES);

  for(int i = 0; i < 5;)
  {
    auto elapsed = time_ms();
  
    for(int j = 0; j < TIMES; j++)
    {
      parser->clear();
      alg->clear();
      parser->generate_graph(V, PERCENT);
      alg->set(parser->get_V(), parser->get_E(), parser->get_input());
  
      auto start = NOW();
      alg->kruskal_list();
      auto end = NOW();
  
      elapsed += time_ms(end - start);
     }
  
     elapsed /= TIMES;
     printf("%zu,%f\n",V,elapsed.count());

     i++;
     if(i == 6) V = 255;
     else V *= 2;
//     printf("%zu\n", i);
  }


  delete parser;
  delete alg;
}
