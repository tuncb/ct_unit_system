#include <iostream>

#include "include/ctus.h"
#include "include/ctus_length.h"

auto test_length()
{
  using namespace ctus;
  using namespace ctus::length;

  constexpr auto len = 10.0_m;

  static_assert(len.unit().si_ratio().num == 1);
  static_assert(len.unit().si_ratio().den == 1);
  static_assert(len.unit().si_start() == 0.0);
  static_assert(len.value == 10.0);

  constexpr auto len_km = len.to<kilometer>();
  static_assert(len_km.value == len.value * 1000.0);
}





int main()
{

}
