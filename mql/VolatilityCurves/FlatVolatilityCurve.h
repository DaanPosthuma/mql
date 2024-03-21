#pragma once

#include "VolatilityCurve.h"

namespace mql::volatility_curves {

  using mql::DateTime;
  using mql::Volatility;

  class FlatVolatilityCurve {
  public:
    FlatVolatilityCurve(Volatility vol) : mVol(vol) {}

    [[nodiscard]] Volatility getVolatility(DateTime time) const noexcept {
      return mVol;
    }

  private:
    Volatility mVol;
  };

}

