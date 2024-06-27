#include <stdio.h>
#include <cstring>

#include "file_parser.h"
#include "common.h"

void
file_parser::get_filename()
{
  printf("File name (max length:" TO_STR(FILENAME_LENGTH) " ): ");
  scanf("%s", filename);
  getchar(); // skip \n
}

void
file_parser::parse_file()
{
  std::ifstream file;
  file.open(filename);

  if(!file.good())
  {
     printf("Bad filename!");
     file.close();
     return;
  }

  // get V E
  char buffer[READ_BUFFER_SIZE];

  file.getline(buffer, READ_BUFFER_SIZE);
  sscanf(buffer, "%zu %zu\n", &E, &V);

  input.reserve(E);

  size_t start, end, weight;

  while(!file.getline(buffer, READ_BUFFER_SIZE).eof())
  {
     sscanf(buffer, "%zu %zu %zu\n", &start, &end, &weight);
     input.emplace_back(start, end, weight);
  }

  file.close();
}

void
file_parser::print_data()
{
  printf("E: %zu, V: %zu\n", E, V);
  for(const auto data : input)
     printf("Start: %zu, End: %zu, Weight %zu\n", data.start, data.end, data.weight);
}

size_t
file_parser::get_size()
{
  printf("\nInput V: ");
  scanf("%zu", &this->V);
  // skip \n
  getchar();

  size_t p;
  printf("\nInput E (int %%): ");
  scanf("%zu", &p);
  // skip \n
  getchar();
  printf("\n");

  this->E = this->V - 1;

  return p;
}

size_t
file_parser::get_random_V(int curr)
{
  int ret = curr;
  for(; ret == curr; ret = rand() % (this->V - 1)); // ret <0;V-1> w/o curr
  return ret;
}

void
file_parser::generate_graph(size_t V, size_t percent)
{
  this->V = V;
  this->E = V - 1;
  this->generate_graph(percent);
}

void
file_parser::generate_graph(size_t percent)
{
  // generate mst
  for(size_t i = 0; i < this->V - 1; i++)
  {
     size_t start = i;
     size_t weight = rand() % 100 + 1; // <1;99>
     size_t end = i + 1;

     input.emplace_back(start, end, weight);
  }
  int64_t count = this-> V * (this->V - 1) * percent / 100;

  // fill with %
  // substract added edges to get correct % of edges
  count -= this->E;
  if(count <= 0)
    return;

  this->E += count;

  for(int64_t i = 0; i < count; i++)
  {
     size_t start  = rand() % (this->V - 1);
     size_t end    = get_random_V(start);
     size_t weight = rand() % 100 + 1;

     input.emplace_back(start, end, weight);
  }

}
