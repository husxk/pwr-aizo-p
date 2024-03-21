#pragma once

#include "array.h"

#define FILENAME_LENGTH  1024

class file_parser
{
private:
  char filename [FILENAME_LENGTH];
  

public:
  void get_filename();
  void parse_format_file(array*);
  void get_size(array*);
  void parse_file(array*);
};
