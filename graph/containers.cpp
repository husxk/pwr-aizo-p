#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "containers.h"

void
edge_list::add_sorted(edge&& data)
{
  edge_list* tmp = new edge_list(data);

  if(this->data->weight >= tmp->data->weight)
  {
      tmp->next  = this->next;
      this->next = tmp;

      this->swap_data(tmp);
      return;
  }

  edge_list* cur = this->next;
  edge_list* bef = this;

  for(; cur != nullptr; bef = cur, cur = cur->next)
  {
    if(cur->data->weight >= tmp->data->weight)
    {
      tmp->next = cur;
      bef->next = tmp;
      return;
    }
  }

  bef->next = tmp;
}

edge_list*
edge_list::pop_front()
{
  edge_list* tmp = this->next;
  delete this;
  return tmp;
}

v_list*
v_list::find(uint8_t V)
{
  v_list* cur = this;

  if(cur->V == -1)
    return this;

  while(cur != nullptr)
  {
     if(cur->V == V)
       return cur;
     cur = cur->next;
  }
  return nullptr;
}

void
v_list::v_add(const edge_descr& edge)
{
  v_list* cur = this;

  if(cur->V == -1)
  {
     cur->V = edge.start;
     cur->edges.push_back(edge);
     return;
  }

  while(cur->next != nullptr)
    cur = cur->next;
  cur->next = new v_list(edge);
}

void
v_list::e_add(const edge_descr& edge)
{
  this->edges.emplace_back(edge);
  this->V = edge.start;
}

void
v_list::clear_data()
{
  edges.clear();
  delete next;
  V = -1;
}

void
v_list::set(const std::vector<edge_descr>& edges)
{
  clear_data();
  for(const auto& e: edges)
    add_edge(e);
}

void
v_list::add_edge(const edge& e)
{
  v_list* tmp = find(e.start);
  if(tmp == nullptr)
    this->v_add(e);
  else
    tmp->e_add(e);
}

void
v_list::add_edge(const edge_descr& e)
{
  v_list* tmp = find(e.start);
  if(tmp == nullptr)
    this->v_add(e);
  else
    tmp->e_add(e);
}

void
v_list::v_add(const edge& edge)
{
  v_list* cur = this;

  if(cur->V == -1)
  {
     cur->V = edge.start;
     cur->edges.push_back(edge);
     return;
  }

  while(cur->next != nullptr)
    cur = cur->next;
  cur->next = new v_list(edge);
}

void
v_list::e_add(const edge& edge)
{
  this->edges.emplace_back(edge);
  this->V = edge.start;
}

void
v_list::print()
{
  v_list* cur = this;
  while(cur != nullptr)
  {
    printf("%hhu | ", cur->V);
    for(const edge& e : cur->edges)
      printf("%hhu(%hhu) ", e.end, e.weight);
    printf("\n");
    cur = cur->next;
  }
}

edge
v_list::min(size_t x, int8_t* mst)
{
  edge m;

  for(v_list* cur = this; cur->next != nullptr; cur = cur->next)
  {
     for(const edge& e : cur->edges)
     {
       if(e.end == x)
         continue;

       if(mst[e.end] != 0)
         continue;

       if(e.weight <= m.weight)
         m = e;
     }
  }

  return m;
}

void
nbor_matrix::clear_data()
{
  if(incidence != nullptr)
    delete[] incidence;
  incidence = new int8_t[V * E];
  memset(incidence, 0, V * E);

  if(weights != nullptr)
     delete[] weights;
   weights = new uint8_t[V * E];
   memset(weights, -1, V * E);
}

void
nbor_matrix::set(size_t V, size_t E, const std::vector<edge_descr>& edges)
{
  this->V = V;
  this->E = E;
  this->edge_num = 0;

  this->clear_data();

  for(size_t i = 0; i < E; i++)
  {
     incidence[i + edges[i].start * E] =  1;
     incidence[i + edges[i].end   * E] = -1;

     weights[i + edges[i].start * E] = edges[i].weight;
     weights[i + edges[i].end   * E] = edges[i].weight;
  }
}

void
nbor_matrix::set(size_t V, size_t E)
{
  this->V = V;
  this->E = E;
  this->edge_num = 0;

  if(incidence != nullptr)
    delete[] incidence;
  incidence = new int8_t[V * E];
  memset(incidence, 0, V * E);

  if(weights != nullptr)
     delete[] weights;
   weights = new uint8_t[V * E];
   memset(weights, -1, V * E);
}

void
nbor_matrix::print()
{
  printf("\nIncidence matrix:\n");
  for(size_t i = 0; i < V * E; i++)
  {
     printf("%-2hhd ", incidence[i]);
     if(i % E == E - 1)
       printf("\n");
  }

  printf("\nWeights matrix:\n");
  for(size_t i = 0; i < V * E; i++)
  {
     printf("%-2hhd ", (int8_t)weights[i] == -1 ? 0 : weights[i]);
     if(i % E == E - 1)
       printf("\n");
  }
}

size_t
nbor_matrix::find_end(size_t i, size_t x)
{
  for(size_t j = 0; j < V; j++)
  {
     if(j == x)
       continue;

     if(incidence[i + j * E] != 0)
       return j;
  }
  return -1;
}

edge
nbor_matrix::min(size_t x, int8_t* mst)
{
  edge m;
  for(size_t i = 0; i < E; i++)
  {
     const size_t index = i + x * E;

     if(incidence[index] == 0)
       continue;

     const uint8_t end = find_end(i, x);

     if((int8_t)end == -1)
     {
       printf("Shouldnt happen\n");
       exit(1);
     }

     // if found edge is between x and a one already in mst, skip
     if(mst[end] != 0)
       continue;

      if(weights[index] < m.weight)
      {
         m.end    = end;
         m.weight = weights[index];
         m.start  = x;
      }
  }
  return m;
}

edge
nbor_matrix::find_edge(uint8_t i)
{
  uint8_t start = -1, end = -1, weight = -1;
  for(uint8_t j = 0; j < V; j++)
  {
    if(incidence[i + j * E] != 0)
    {
      start = j;
      end = find_end(i, j);
      if((int8_t) end == -1)
      {
        printf("Shouldnt happen\n");
        exit(1);
      }
      weight = weights[i + start * E];
      break;
    }
  }
  return edge(start, end, weight);
}

edge_list*
nbor_matrix::get_min_edges_list()
{
  edge_list* min_list = new edge_list(find_edge(0));

  printf("\nmin_edges:\n");
  for(uint8_t i = 1; i < E; i++)
     min_list->add_sorted(find_edge(i));
  printf("\n");
  return min_list;
}

void
nbor_matrix::add_edge(edge& e)
{
  incidence[edge_num + e.start * E] =  1;
  incidence[edge_num + e.end   * E] = -1;
  weights[edge_num   + e.start * E] =  e.weight;
  weights[edge_num   + e.end   * E] =  e.weight;
  edge_num++;
}
