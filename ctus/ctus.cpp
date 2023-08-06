#include <iostream>

#include "include/ctus.h"

int main()
{
  using namespace ctus;

  auto len1 = 10.0_m;
  auto len2 = 20.0_m;

  auto len3 = len1 + len2;
  auto len4 = len3 - len2;

  std::cout << "Hello World!\n";
}
