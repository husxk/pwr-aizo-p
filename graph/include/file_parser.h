#pragma once
#include <fstream>
#include <vector>

#include "random.h"
#include "edge_descr.h"

#define FILENAME_LENGTH 1024

static constexpr size_t
READ_BUFFER_SIZE = 255;

class file_parser
{
  char filename [FILENAME_LENGTH];
  size_t V, E;
  std::vector<edge_descr> input;

  size_t
  get_random_V(int);

public:

  file_parser()
  {
  }

  void get_filename();
  void parse_file();

  void print_data();

  void
  clear()
  {
     this->V = 0;
     this->E = 0;
     input.clear();
  }

  size_t
  get_V()
  {
     return this->V;
  }

  size_t
  get_E()
  {
     return this->E;
  }

  std::vector<edge_descr>
  get_input()
  {
     return this->input;
  }

  size_t
  get_size();

  void
  generate_graph(size_t);
};
