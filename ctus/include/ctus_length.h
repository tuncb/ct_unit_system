#pragma once
#include <ratio>
#include "ctus.h"

namespace ctus::length
{
using meter_t = Unit<std::ratio<1, 1>{}, 0.0, Dimension<1, 0, 0>{}>;
constexpr const auto meter = meter_t{};
constexpr ValueWithUnit<double, meter> operator"" _m(long double value)
{
  return {static_cast<double>(value)};
}

using kilometer_t = CreateUnit<std::kilo{}, meter>;
constexpr const auto kilometer = kilometer_t{};
constexpr ValueWithUnit<double, kilometer> operator"" _km(long double value)
{
  return {static_cast<double>(value)};
}

using centimeter_t = CreateUnit<std::centi{}, meter>;
constexpr const auto centimeter = centimeter_t{};
constexpr ValueWithUnit<double, centimeter> operator"" _cm(long double value)
{
  return {static_cast<double>(value)};
}

using millimeter_t = CreateUnit<std::milli{}, meter>;
constexpr const auto millimeter = millimeter_t{};
constexpr ValueWithUnit<double, millimeter> operator"" _mm(long double value)
{
  return {static_cast<double>(value)};
}

} // namespace ctus::length