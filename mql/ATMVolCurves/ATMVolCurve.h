#pragma once

#include "DateTime.h"
#include "Volatility.h"

#include <concepts>

namespace mql::ATMVolCurves {

  using mql::DateTime;
  using mql::Volatility;

  template <typename T>
  concept ATMVolCurve = requires(T a, DateTime dateTime)
  {
    { a.getATMVol(dateTime) } -> std::same_as<Volatility>;
  };

}

