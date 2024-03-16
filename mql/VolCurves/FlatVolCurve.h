#pragma once

#include "VolCurve.h"

namespace mql::vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  class FlatVolCurve {
  public:
    FlatVolCurve(Volatility vol) : mVol(vol) {}

    Volatility getVol(DateTime time) const noexcept {
      return mVol;
    }

  private:
    Volatility mVol;
  };

  static_assert(VolCurve<FlatVolCurve>);

}

