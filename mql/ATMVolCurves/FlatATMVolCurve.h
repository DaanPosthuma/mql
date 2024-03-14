#pragma once

#include "ATMVolCurve.h"

namespace mql::atm_vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  class FlatATMVolCurve {
  public:
    FlatATMVolCurve(Volatility vol) : mVol(vol) {}

    Volatility getATMVol(DateTime time) const {
      return mVol;
    }

  private:
    Volatility mVol;
  };

  static_assert(ATMVolCurve<FlatATMVolCurve>);

}

