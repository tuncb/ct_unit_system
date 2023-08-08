#include <iostream>

#include "include/ctus.h"
#include "include/ctus_length.h"
#include "include/ctus_mass.h"
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
  static_assert(60 * sec + min.to<second>() == 120.0_s);
}

auto test_mass()
{
  using namespace ctus;
  using namespace ctus::mass;

  constexpr auto kilogram = 1.0_kg;
  constexpr auto gr = 1.0_gr;

  static_assert(kilogram.to<gram>() + gr == 1001.0_gr);
}

auto test_combined_units_mul()
{
  using namespace ctus;
  using namespace ctus::mass;
  using namespace ctus::time;

  constexpr auto kilogram = 1.0_kg;
  constexpr auto min = 1.0_min;

  constexpr auto kilomin = kilogram * min;
  static_assert(kilomin.unit().si_ratio().num == 60);
  static_assert(kilomin.unit().si_ratio().den == 1);
  static_assert(kilomin.unit().si_start() == 0.0);
  static_assert(kilomin.unit().dim().length() == 0);
  static_assert(kilomin.unit().dim().mass() == 1);
  static_assert(kilomin.unit().dim().time() == 1);
}

auto test_combined_units_div()
{
  using namespace ctus;
  using namespace ctus::length;
  using namespace ctus::time;

  constexpr auto kilometer = 100.0_km;
  constexpr auto hr = 1.0_h;

  constexpr auto vel = kilometer / hr;
  static_assert(vel.unit().si_ratio().num == 5);
  static_assert(vel.unit().si_ratio().den == 18);
  static_assert(vel.unit().si_start() == 0.0);
  static_assert(vel.unit().dim().length() == 1);
  static_assert(vel.unit().dim().mass() == 0);
  static_assert(vel.unit().dim().time() == -1);
}

int main()
{
  // for debugging purposes only
  test_length();
  test_time();
}
