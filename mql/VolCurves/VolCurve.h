#pragma once

#include "DateTime.h"
#include "Volatility.h"

#include <concepts>

namespace mql::vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  template <typename T>
  concept VolCurve = requires(T a, DateTime dateTime)
  {
    { a.getVol(dateTime) } -> std::same_as<Volatility>;
  };

}

