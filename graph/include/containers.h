#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

#include "edge_descr.h"

struct edge
{
  uint8_t end    = -1;
  uint8_t weight = -1;
  uint8_t start;

  edge()
  {
  }

  edge(const edge_descr& other)
  {
     this->start  = other.start;
     this->end    = other.end;
     this->weight = other.weight;
  }

  edge(uint8_t& start, uint8_t& end, uint8_t& weight)
  {
     this->start   = start;
     this->end     = end;
     this->weight = weight;
   }

  edge(edge&& other)
  {
     this->start  = other.start;
     this->end    = other.end;
     this->weight = other.weight;
   }

  edge(const edge& other)
  {
    this->start  = other.start;
    this->end    = other.end;
    this->weight = other.weight;
   }

  edge(edge* other)
  {
     this->start  = other->start;
     this->end    = other->end;
     this->weight = other->weight;
  }

  edge
  operator=(const edge& other)
  {
     this->start  = other.start;
     this->end    = other.end;
     this->weight = other.weight;
     return *this;
  }

  void
   check(edge&& other)
   {
     if(other.weight < this->weight)
     {
       this->start  = other.start;
       this->end    = other.end;
       this->weight = other.weight;
     }
   }
};

struct edge_i
{
  edge e;
  int8_t i;
};


struct edge_list
{
  edge* data;
  edge_list* next;

  edge_list()
  {
     data = nullptr;
     next = nullptr;
  }

  edge_list(const edge_list& other)
  {
     this->data = new edge(other.data);
     this->next = other.next;
  }

  edge_list(const edge& other)
  {
     this->data = new edge(other);
     this->next = nullptr;
  }

  edge_list(edge&& other)
  {
     this->data = new edge(other);
     this->next = nullptr;
  }

  ~edge_list()
  {
     delete data;
  }

  edge_list
  operator=(edge_list& other)
  {
     this->data = other.data;
     this->next = other.next;
     other.data = nullptr;
     other.next = nullptr;
     return *this;
  }

  void
  swap_data(edge_list* other)
  {
     auto* tmp   = other->data;
     other->data = this->data;
     this->data  = tmp;
  }

  void add_sorted(edge&&);
  void add_sorted(const edge&);
  edge_list* pop_front();
};

class v_list
{
  uint8_t V;
  std::vector<edge> edges;
  v_list* next;

  public:

  v_list()
  {
     next = nullptr;
     V    = -1;
  }

  v_list(const edge_descr& edge)
  {
     this->V    = edge.start;
     this->next = nullptr;
     edges.emplace_back(edge);
  }

  v_list(const edge& edge)
  {
     this->V    = edge.start;
     this->next = nullptr;
     edges.emplace_back(edge);
  }

  ~v_list()
  {
     delete this->next;
  }

  void
  clear_data();

  void
  set(const std::vector<edge_descr>&);

  void
  v_add(const edge_descr&);

  void
  v_add(const edge&);

  void
  e_add(const edge_descr&);

  void
  e_add(const edge&);

  void
  add_edge(const edge&);

  void
  add_edge(const edge_descr&);

  edge_list*
  get_min_edges_list();

  void
  edge_dijkstra(uint8_t*, uint8_t*,uint8_t*);

  void
  print();

  v_list*
  find(uint8_t);

  edge
  min(size_t, uint8_t*);

  void
  bellman(uint8_t*, uint8_t*, uint8_t*, size_t);
};

// 1  -> start
// 0  -> none
// -1 -> end
class nbor_matrix
{
  size_t  V;
  size_t  E;
  int8_t* incidence;
  uint8_t* weights;
  size_t edge_num;

  size_t find_end(size_t, size_t);
  edge find_edge(uint8_t);

public:

  nbor_matrix()
  {
     incidence = nullptr;
     weights   = nullptr;
  }

  void
  set(size_t, size_t, const std::vector<edge_descr>&);

  void
  set(size_t, size_t);

  void
  add_edge(edge& e);

  edge min(size_t, uint8_t*);
  edge_list* get_min_edges_list();
  void  edge_dijkstra(uint8_t*, uint8_t*, uint8_t*);
  void bellman(uint8_t*, uint8_t*, uint8_t*);

  void
  print();

  ~nbor_matrix()
  {
     if(incidence != nullptr)
       delete[] incidence;

     if(weights != nullptr)
       delete[] weights;
  }

  void
  clear_data();

  int8_t
  get_weight(size_t index)
  {
     return weights[index];
   }
  
};
