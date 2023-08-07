#pragma once
#include "ctus.h"
#include <ratio>

namespace ctus::mass
{

using kilogram_t = Unit<std::ratio<1, 1>{}, 0.0, Dimension<0, 1, 0>{}>;
constexpr const auto kilogram = kilogram_t{};
constexpr ValueWithUnit<double, kilogram> operator"" _kg(long double value)
{
  return {static_cast<double>(value)};
}

CTUS_CREATE_NEW_UNIT(gram, gr, kilogram, std::milli);

} // namespace ctus::mass