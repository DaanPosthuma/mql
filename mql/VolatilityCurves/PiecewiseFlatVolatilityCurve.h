#pragma once

#include "VolatilityCurve.h"

#include <map>

namespace mql::volatility_curves {

  using mql::DateTime;
  using mql::Volatility;

  class PiecewiseFlatVolatilityCurve {
  public:
    PiecewiseFlatVolatilityCurve(std::map<DateTime, Volatility> termStructure) : mTermStructure(std::move(termStructure)) {}

    [[nodiscard]] Volatility getVolatility(DateTime time) const {
      if (time < mTermStructure.begin()->first) throw std::exception();
      return std::prev(mTermStructure.upper_bound(time))->second;
    }

  private:
    std::map<DateTime, Volatility> mTermStructure;
  };

}

