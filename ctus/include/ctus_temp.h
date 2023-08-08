#pragma once
#include "ctus.h"
#include <ratio>

namespace ctus::temperature
{
using kelvin_t = Unit<std::ratio<1, 1>{}, Dimension<0, 0, 0, 1>{}>;
constexpr const auto kelvin = kelvin_t{};
constexpr ValueWithUnit<double, kelvin> operator"" _k(long double value)
{
  return {static_cast<double>(value)};
}

} // namespace ctus::temperature