#include "algorithms.h"

void
algorithms::set(size_t V, size_t E, const std::vector<edge_descr>& edges)
{
  this->V = V;
  this->E = E;

  matrix.set(V, E, edges);
  matrix_res.set(V, E);

  list.set(edges);

  if(lookup != nullptr)
    delete [] lookup;
  lookup = new uint8_t[V];

  for(size_t i = 0; i < V; i++)
    lookup[i] = 0;

   if(d != nullptr)
    delete [] d;
  d = new uint8_t[V];

  for(size_t i = 0; i < V; i++)
    d [i] = -1;

   if(p != nullptr)
    delete [] p;
  p = new uint8_t[V];

  for(size_t i = 0; i < V; i++)
    p [i] = -1;

   if(k != nullptr)
    delete [] k;
  k = new uint8_t[E];

  for(size_t i = 0; i < E; i++)
    k [i] = -1;

}

void
algorithms::print()
{
  printf("\nMatrix:\n");
  matrix.print();
  printf("\nList:\n");
  list.print();
}

void
algorithms::print_res()
{
  printf("\nMatrix:\n");
  matrix_res.print();
  printf("\nList:\n");
  list_res.print();
}
