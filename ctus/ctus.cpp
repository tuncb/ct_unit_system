#include <iostream>

#include "include/ctus.h"
#include "include/ctus_length.h"
#include "include/ctus_time.h"

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
  static_assert(len_km.value == len.value * 0.001);

  constexpr auto total_len = 5.0_cm + 1.0_m.to<centimeter>();
  static_assert(total_len == 105.0_cm);
}

auto test_time()
{
  using namespace ctus;
  using namespace ctus::time;

  constexpr auto millisec = 1.0_ms;
  constexpr auto sec = 1.0_s;
  constexpr auto min = 1.0_min;
  constexpr auto hour = 1.0_h;

  static_assert(sec + min.to<second>() == 61.0_s);
}

int main()
{
  // for debugging purposes only
  test_length();
  test_time();
}
