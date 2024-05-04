#pragma once

void
get_random(uint8_t* dest, size_t size)
{
  std::ifstream file("/dev/radnom");

  if(!file.good())
  {
    printf("Bad filename! Try again!\n");
    file.close();
    return;
  }

  file.read((char*)dest, size);
  file.close();
}
