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
