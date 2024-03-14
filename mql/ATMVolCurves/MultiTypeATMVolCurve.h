#pragma once

#include "ATMVolCurve.h"

#include <variant>

namespace mql::atm_vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  template <ATMVolCurve... CurveTypes>
  class MultiTypeATMVolCurve {
  public:
    explicit MultiTypeATMVolCurve(ATMVolCurve auto const& curve) : mCurve(curve) {}

    Volatility getATMVol(DateTime dateTime) const {
      return std::visit([=](auto const& curve) { return curve.getATMVol(dateTime); }, mCurve);
    }

  private:
    std::variant<CurveTypes...> mCurve;
  };

}
