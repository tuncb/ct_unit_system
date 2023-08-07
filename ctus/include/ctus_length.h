#pragma once
#include "ctus.h"
#include <ratio>

namespace ctus::length
{
using meter_t = Unit<std::ratio<1, 1>{}, 0.0, Dimension<1, 0, 0>{}>;
constexpr const auto meter = meter_t{};
constexpr ValueWithUnit<double, meter> operator"" _m(long double value)
{
  return {static_cast<double>(value)};
}

CTUS_CREATE_NEW_UNIT(kilometer, km, meter, std::kilo);
CTUS_CREATE_NEW_UNIT(centimeter, cm, meter, std::centi);
CTUS_CREATE_NEW_UNIT(millimeter, mm, meter, std::milli);

} // namespace ctus::length