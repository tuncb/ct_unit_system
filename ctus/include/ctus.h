#pragma once
#include <ratio>
#include <tuple>

namespace ctus
{

  using Length = int;
using Mass = int;
using Time = int;

template <Length L, Mass M, Time T> struct Dimension
{
  static constexpr Length length()
  {
    return L;
  }

  static constexpr Mass mass()
  {
    return M;
  }

  static constexpr Time time()
  {
    return T;
  }
};

template <std::ratio SIRatio, double SIStart, Dimension Dim> struct Unit
{
  static constexpr auto si_ratio()
  {
    return SIRatio;
  }
  static constexpr double si_start()
  {
    return SIStart;
  }
  static constexpr auto dim()
  {
    return Dim;
  }
};

using second = Unit<std::ratio<1, 1>{}, 0.0, Dimension<0, 0, 1>{}>;
using kilogram = Unit<std::ratio<1, 1>{}, 0.0, Dimension<0, 1, 0>{}>;

template <std::ratio RatioValue, Unit UnitValue>
using CreateUnit =
    Unit<std::ratio_multiply<decltype(RatioValue), decltype(UnitValue.si_ratio())>{}, 0.0, decltype(UnitValue.dim()){}>;

template <typename T, Unit UnitValue> struct ValueWithUnit
{
  T value;
  static constexpr auto unit()
  {
    return UnitValue;
  }

  template <Unit OtherUnit> constexpr auto to() const
  {
    static_assert(std::is_same_v<decltype(OtherUnit.dim()), decltype(UnitValue.dim())>);
    auto si_value = (value - unit().si_start()) / (unit().si_ratio().num / unit().si_ratio().den);
    auto new_value =
        (si_value + OtherUnit.si_start()) * ((OtherUnit.si_ratio().num / OtherUnit.si_ratio().den));
    return ValueWithUnit<T, OtherUnit>{new_value};
  };
};



constexpr ValueWithUnit<double, second{}> operator"" _s(long double value)
{
  return {static_cast<double>(value)};
}

constexpr ValueWithUnit<double, kilogram{}> operator"" _kg(long double value)
{
  return {static_cast<double>(value)};
}

template <typename T, Unit UnitValue>
constexpr ValueWithUnit<T, UnitValue> operator+(const ValueWithUnit<T, UnitValue> &lhs,
                                                const ValueWithUnit<T, UnitValue> &rhs)
{
  return {lhs.value + rhs.value};
}

template <typename T, Unit UnitValue>
constexpr ValueWithUnit<T, UnitValue> operator-(const ValueWithUnit<T, UnitValue> &lhs,
                                                const ValueWithUnit<T, UnitValue> &rhs)
{
  return {lhs.value - rhs.value};
}

} // namespace ctus