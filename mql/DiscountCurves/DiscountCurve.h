#pragma once

#include "DateTime.h"
#include "DiscountFactor.h"

#include <concepts>

namespace mql::discount_curves {

  using mql::DateTime;
  using mql::DiscountFactor;

  template <typename T>
  concept DiscountCurve = requires(T a, DateTime from, DateTime to)
  {
    { a.computeDiscountFactor(from, to) } -> std::same_as<DiscountFactor>;
  };

}

