#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "file_parser.h"
#include "containers.h"
#include "algorithms.h"

static int
menu()
{
  printf("\nChoose:\n");
  printf("1. Load data from file\n");
  printf("2. Generate data\n");
  printf("3. Show graph\n");
  printf("4. Prim\n");
  printf("5. Kruskal\n");
  printf("6. Dijkstra\n");
  printf("7. Ford-Bellman\n");
  printf("8. Exit\n");
  printf("Input: ");

  const char input = getchar();
  getchar(); // skip \n

  if(input < 49 || input > 56)
  {
     printf("Wrong input, try again\n");
     return menu();
  }

  return input;
}

size_t
get_start()
{
  size_t a;
  printf("\nInput v start: ");
  std::cin >> a;
  getchar();
  return a;
}

size_t
get_end()
{
  size_t a;
  printf("\nInput v end: ");
  std::cin >> a;
  getchar();
  return a;
}

int
main()
{
  auto parser = new file_parser();
  auto alg    = new algorithms();

  srand(time(NULL));

  while(true)
  {
     const int option = menu();

     switch(option)
     {
       case '1':
       {
         parser->clear();
         parser->get_filename();
         parser->parse_file();
         alg->set(parser->get_V(), parser->get_E(), parser->get_input());
       } break;

       case '2':
       {
         parser->clear();
         size_t percent = parser->get_size();
         parser->generate_graph(percent);
         alg->set(parser->get_V(), parser->get_E(), parser->get_input());
         alg->print();
       } break;


       case '3':
       {
         alg->print();
       } break;

       case '4':
       {
         alg->prim();
         alg->print_res();
       } break;

       case '5':
       {
         alg->kruskal();
         alg->print_res();
       } break;

       case '6':
       {
         size_t start = get_start();
         size_t end   = get_end();
         alg->dijkstra(start, end);
       } break;

       case '7':
       {
         size_t start = get_start();
         size_t end   = get_end();
         alg->bellman(start, end);
       } break;

       case '8':
       {
         delete parser;
         delete alg;
         return 0;
       }
     }
  }

}
