#pragma once

#include "ATMVolCurve.h"

#include <map>

namespace mql::atm_vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  class PiecewiseFlatATMVolCurve {
  public:
    PiecewiseFlatATMVolCurve(std::map<DateTime, Volatility> termStructure) : mTermStructure(std::move(termStructure)) {}

    Volatility getATMVol(DateTime time) const {
      auto const it = std::prev(mTermStructure.upper_bound(time));
      if (it == mTermStructure.end()) throw std::exception();
      return it->second;
    }

  private:
    std::map<DateTime, Volatility> mTermStructure;
  };

  static_assert(ATMVolCurve<FlatATMVolCurve>);

}

