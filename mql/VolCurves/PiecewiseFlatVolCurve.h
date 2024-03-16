#pragma once

#include "VolCurve.h"

#include <map>

namespace mql::vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  class PiecewiseFlatVolCurve {
  public:
    PiecewiseFlatVolCurve(std::map<DateTime, Volatility> termStructure) : mTermStructure(std::move(termStructure)) {}

    Volatility getVol(DateTime time) const {
      if (time < mTermStructure.begin()->first) throw std::exception();
      return std::prev(mTermStructure.upper_bound(time))->second;
    }

  private:
    std::map<DateTime, Volatility> mTermStructure;
  };

  static_assert(VolCurve<FlatVolCurve>);

}

