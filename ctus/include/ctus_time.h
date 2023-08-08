#pragma once
#include "ctus.h"
#include <ratio>

namespace ctus::time
{

using second_t = Unit<std::ratio<1, 1>{}, Dimension<0, 0, 1, 0>{}>;
constexpr const auto second = second_t{};
constexpr ValueWithUnit<double, second> operator"" _s(long double value)
{
  return {static_cast<double>(value)};
}

using TimeRatio60 = std::ratio<60, 1>;

CTUS_CREATE_NEW_UNIT(millisecond, ms, second, std::milli);
CTUS_CREATE_NEW_UNIT(minute, min, second, TimeRatio60);
CTUS_CREATE_NEW_UNIT(hour, h, minute, TimeRatio60);

} // namespace ctus::time
