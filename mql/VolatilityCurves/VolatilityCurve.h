#pragma once

#include "DateTime.h"
#include "Volatility.h"

#include <concepts>

namespace mql::volatility_curves {

  using mql::DateTime;
  using mql::Volatility;

  template <typename T>
  concept VolatilityCurve = requires(T a, DateTime dateTime)
  {
    { a.getVolatility(dateTime) } -> std::same_as<Volatility>;
  };

}

