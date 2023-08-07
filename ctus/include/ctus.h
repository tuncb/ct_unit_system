#pragma once
#include <ratio>
#include <type_traits>

namespace ctus
{

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

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

template <std::ratio RatioValue, Unit UnitValue>
using CreateUnit =
    Unit<std::ratio_multiply<decltype(RatioValue), decltype(UnitValue.si_ratio())>{}, 0.0, decltype(UnitValue.dim()){}>;

template <Numeric T, std::ratio RatioValue> constexpr auto evaluate() -> T
{
  return static_cast<T>(RatioValue.num) / static_cast<T>(RatioValue.den);
}

template <Numeric T, std::ratio RatioValue> constexpr auto evaluate_inverse() -> T
{
  return static_cast<T>(RatioValue.den) / static_cast<T>(RatioValue.num);
}

template <Numeric T, Unit UnitValue> struct ValueWithUnit
{
  T value;
  static constexpr auto unit()
  {
    return UnitValue;
  }

  template <Unit OtherUnit> constexpr auto to() const
  {
    static_assert(std::is_same_v<decltype(OtherUnit.dim()), decltype(UnitValue.dim())>);
    auto si_value = (value - unit().si_start()) * evaluate<T, unit().si_ratio()>();
    auto new_value = (si_value + OtherUnit.si_start()) * evaluate_inverse<T, OtherUnit.si_ratio()>();
    return ValueWithUnit<T, OtherUnit>{new_value};
  };

  auto operator<=>(const ValueWithUnit<T, UnitValue> &) const = default;
};

template <Numeric T, Unit UnitValue>
constexpr ValueWithUnit<T, UnitValue> operator+(const ValueWithUnit<T, UnitValue> &lhs,
                                                const ValueWithUnit<T, UnitValue> &rhs)
{
  return {lhs.value + rhs.value};
}

template <Numeric T, Unit UnitValue>
constexpr ValueWithUnit<T, UnitValue> operator-(const ValueWithUnit<T, UnitValue> &lhs,
                                                const ValueWithUnit<T, UnitValue> &rhs)
{
  return {lhs.value - rhs.value};
}

template <Numeric T, Numeric TValue, Unit UnitValue>
constexpr ValueWithUnit<T, UnitValue> operator*(TValue value, const ValueWithUnit<T, UnitValue> &rhs)
  requires std::convertible_to<TValue, T>
{
  return {value * rhs.value};
}

#define CTUS_CREATE_NEW_UNIT(new_unit, short_name, base_unit, ratio)                                                   \
  using new_unit##_t = CreateUnit<ratio{}, base_unit>;                                                                 \
  constexpr const auto new_unit = new_unit##_t{};                                                                      \
  constexpr ValueWithUnit<double, new_unit> operator"" _##short_name##(long double value)                              \
  {                                                                                                                    \
    return {static_cast<double>(value)};                                                                               \
  }

} // namespace ctus