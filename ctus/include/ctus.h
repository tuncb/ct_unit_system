#pragma once
#include <tuple>

namespace ctus
{
struct meter
{
};

template <typename T, int N> struct UnitAtom
{
};

template <typename... T> struct Unit : std::tuple<T...>
{
};

template <typename T, typename UnitType> struct ValueWithUnit
{
  T value;
};

constexpr ValueWithUnit<double, Unit<UnitAtom<meter, 1>>> operator"" _m(long double value)
{
  return {static_cast<double>(value)};
}

template <typename T, typename UnitType>
constexpr ValueWithUnit<T, UnitType> operator+(const ValueWithUnit<T, UnitType> &lhs,
                                               const ValueWithUnit<T, UnitType> &rhs)
{
  return {lhs.value + rhs.value};
}

template <typename T, typename UnitType>
constexpr ValueWithUnit<T, UnitType> operator-(const ValueWithUnit<T, UnitType> &lhs,
                                               const ValueWithUnit<T, UnitType> &rhs)
{
  return {lhs.value - rhs.value};
}

} // namespace ctus