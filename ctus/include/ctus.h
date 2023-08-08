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
using Temperature = int;

template <Length L, Mass M, Time T, Temperature Temp> struct Dimension
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

  static constexpr Temperature temperature()
  {
    return Temp;
  }
};

template <std::ratio SIRatio, Dimension Dim> struct Unit
{
  static constexpr auto si_ratio()
  {
    return SIRatio;
  }

  static constexpr auto dim()
  {
    return Dim;
  }
};

template <std::ratio RatioValue, Unit UnitValue>
using CreateUnit =
    Unit<std::ratio_multiply<decltype(RatioValue), decltype(UnitValue.si_ratio())>{}, decltype(UnitValue.dim()){}>;

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
    auto si_value = value * evaluate<T, unit().si_ratio()>();
    auto new_value = si_value * evaluate_inverse<T, OtherUnit.si_ratio()>();
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

template <Numeric T, Unit UnitValue1, Unit UnitValue2>
constexpr auto operator*(const ValueWithUnit<T, UnitValue1> &lhs, const ValueWithUnit<T, UnitValue2> &rhs)
{
  constexpr auto dim1 = UnitValue1.dim();
  constexpr auto dim2 = UnitValue2.dim();

  constexpr auto length = dim1.length() + dim2.length();
  constexpr auto mass = dim1.mass() + dim2.mass();
  constexpr auto time = dim1.time() + dim2.time();
  constexpr auto temp = dim1.temperature() + dim2.temperature();

  using DimType = Dimension<length, mass, time, temp>;
  using RatioType = std::ratio_multiply<decltype(UnitValue1.si_ratio()), decltype(UnitValue2.si_ratio())>;
  using UnitType = Unit<RatioType{}, DimType{}>;

  return ValueWithUnit<T, UnitType{}>{lhs.value * rhs.value};
}

template <Numeric T, Unit UnitValue1, Unit UnitValue2>
constexpr auto operator/(const ValueWithUnit<T, UnitValue1> &lhs, const ValueWithUnit<T, UnitValue2> &rhs)
{
  constexpr auto dim1 = UnitValue1.dim();
  constexpr auto dim2 = UnitValue2.dim();

  constexpr auto length = dim1.length() - dim2.length();
  constexpr auto mass = dim1.mass() - dim2.mass();
  constexpr auto time = dim1.time() - dim2.time();
  constexpr auto temp = dim1.temperature() - dim2.temperature();

  using DimType = Dimension<length, mass, time, temp>;
  using RatioType = std::ratio_divide<decltype(UnitValue1.si_ratio()), decltype(UnitValue2.si_ratio())>;
  using UnitType = Unit<RatioType{}, DimType{}>;

  return ValueWithUnit<T, UnitType{}>{lhs.value / rhs.value};
}

#define CTUS_CREATE_NEW_UNIT(new_unit, short_name, base_unit, ratio)                                                   \
  using new_unit##_t = CreateUnit<ratio{}, base_unit>;                                                                 \
  constexpr const auto new_unit = new_unit##_t{};                                                                      \
  constexpr ValueWithUnit<double, new_unit> operator"" _##short_name##(long double value)                              \
  {                                                                                                                    \
    return {static_cast<double>(value)};                                                                               \
  }
} // namespace ctus