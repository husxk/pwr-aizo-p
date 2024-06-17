#pragma once
#include <cstdio>
#include <cstring>

#include "containers.h"
#include "edge_descr.h"

class algorithms
{
  uint8_t  V;
  uint8_t  E;
  nbor_matrix matrix;
  nbor_matrix matrix_res;

  v_list list;
  v_list list_res;

  uint8_t* lookup;
  uint8_t* p;
  uint8_t* d;
  uint8_t* k;

  void
  res_dijkstra(uint8_t start, uint8_t end, const char* str)
  {
      printf("\n%s results for %hhu to %hhu:\n", str, start, end);
     for(int i = end; d[i] != start; i = p[i])
       printf("%hhu => %hhu\n", i, p[i]);
     printf("Total: %hhu\n", d[end]);
  }

public:

   algorithms()
   {
     lookup = nullptr;
     p = nullptr;
     d = nullptr;
     k = nullptr;
   }

   ~algorithms()
   {
     if(lookup != nullptr)
       delete[] lookup;

     if(p != nullptr)
       delete[] p;

     if(d != nullptr)
       delete[] d;
     
     if(k != nullptr)
       delete[] k;
   }

   void set(size_t, size_t, const std::vector<edge_descr>&);
   void print();
   void print_res();

   void
  reset_mst()
  {
     if(lookup == nullptr)
       return;

     printf("\nV:%hhu\n", V);
     memset(lookup, 0, V);
  }

   void
  reset_pdk()
  {
     if(p == nullptr || d == nullptr || k == nullptr)
       return;

     memset(p, -1, V);
     memset(d, -1, V);
     memset(k,  0, E);
  }

   void
  clear_data()
  {
     matrix_res.clear_data();
     list_res.clear_data();
  }

   void
   clear()
   {
     reset_mst();
     reset_pdk();
     clear_data();
     matrix.clear_data();
     list.clear_data();
   }

   void
   prim_matrix()
   {
     lookup[0] = 1;
     for(size_t i = 0; i < V; i++)
     {
       edge m;
       for(int j = 0; j < V; j++)
       {
         if(lookup[j] == 0)
           continue;
         m.check(matrix.min(j, lookup));
       }

       if((int8_t)m.end == -1)
         continue;

       lookup[m.end] = 1;
       matrix_res.add_edge(m);
     }
   }

   void
  prim_list()
  {
     lookup[0] = 1;
     for(size_t i = 0; i < V; i++)
     {
       edge m;
       for(int j = 0; j < V; j++)
       {
         if(lookup[j] == 0)
           continue;
         m.check(list.min(j, lookup));
       }

       if((int8_t)m.end == -1)
         continue;

       lookup[m.end] = 1;
       list_res.add_edge(m);
     }
  }

   void
  prim()
  {
     clear_data();
     reset_mst();
     prim_matrix();
     reset_mst();
     prim_list();
  }

   void
  kruskal_matrix()
  {
     for(uint8_t i = 0; i < V; i++)
       lookup[i] = i;

     edge_list* min_edges = matrix.get_min_edges_list();

     for(uint8_t i = 0; i < E; i++)
     {
       edge* data = min_edges->data;

       // check if current edge is between vertices in the same group
       if(lookup[data->start] != lookup[data->end])
       {
         uint8_t to_overwrite = lookup[data->end];
         for(int8_t j = 0; j < V; j++)
           if(lookup[j] == to_overwrite)
             lookup[j] = lookup[data->start];

         matrix_res.add_edge(*data);
       }
       min_edges = min_edges->pop_front();
     }
  }

   void
  kruskal_list()
  {
     for(uint8_t i = 0; i < V; i++)
       lookup[i] = i;

     edge_list* min_edges = list.get_min_edges_list();

     for(uint8_t i = 0; i < E; i++)
     {
       edge* data = min_edges->data;
       uint8_t to_overwrite = lookup[data->end];

       // check if current edge is between vertices in the same group
       if(lookup[data->start] != lookup[data->end])
       {
         for(int8_t j = 0; j < V; j++)
           if(lookup[j] == to_overwrite)
             lookup[j] = lookup[data->start];

         list_res.add_edge(*data);
       }
       min_edges = min_edges->pop_front();
     }

   }

   void
  kruskal()
  {
     clear_data();
     reset_mst();
     kruskal_matrix();
     reset_mst();
     kruskal_list();
  }

#define START 0
#define END 4

   void
  dijkstra_matrix(uint8_t start)
  {
     lookup[start] = 1;
     d[start] = 0;
     p[start] = 0;

     for(int i = 0; i < E; i++)
     {
       edge_i e = matrix.edge_dijkstra((uint8_t*)lookup, k);
       k[e.i] = 1;

       if(d[e.e.end] > d[e.e.start] + e.e.weight)
       {
         d[e.e.end] = d[e.e.start] + e.e.weight;
         p[e.e.end] = e.e.start;
       }
       lookup[e.e.end] = 1;
     }
  }

   void
  dijkstra_list(uint8_t start)
  {
     lookup[start] = 1;
     d[start] = 0;
     p[start] = start;

     for(int i = 0; i < E; i++)
     {
       edge_i e = list.edge_dijkstra((uint8_t*)lookup, k);
       k[e.i]   = 1;

       if(d[e.e.end] > d[e.e.start] + e.e.weight)
       {
         d[e.e.end] = d[e.e.start] + e.e.weight;
         p[e.e.end] = e.e.start;
       }
       lookup[e.e.end] = 1;
     }

  }

   void
  dijkstra(uint8_t start = START, uint8_t end = END)
  {
     clear_data();
     reset_pdk();
     reset_mst();
     dijkstra_matrix(start);
     res_dijkstra(start, end, "Matrix");

     reset_pdk();
     reset_mst();
     dijkstra_list(start);
     res_dijkstra(start, end, "List");
  }

   void
  bellman_matrix(uint8_t start)
  {
     lookup[start] = 1;
     d[start] = 0;
     p[start] = start;
     matrix.bellman(d, p, lookup);
  }

   void
  bellman_list(uint8_t start)
  {
     lookup[start] = 1;
     d[start] = 0;
     p[start] = start;
     list.bellman(d, p, lookup, E);
  }

   void
  bellman(uint8_t start = START, uint8_t end = END)
  {
     clear_data();
     reset_pdk();
     reset_mst();
     bellman_matrix(start);
     res_dijkstra(start, end, "Matrix");

     clear_data();
     reset_pdk();
     reset_mst();
     bellman_list(start);
     res_dijkstra(start, end, "List");


  }

};
