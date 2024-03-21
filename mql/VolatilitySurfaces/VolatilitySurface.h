#pragma once

#include "DateTime.h"
#include "Strike.h"
#include "Volatility.h"

#include <concepts>

namespace mql::vol_surfaces {

  using mql::DateTime;
  using mql::Strike;
  using mql::Volatility;

  template <typename T>
  concept VolatilitySurface = requires(T a, DateTime dateTime, Strike strike)
  {
    { a.getVolatility(dateTime, strike) } noexcept  -> std::same_as<Volatility>;
  };

}

