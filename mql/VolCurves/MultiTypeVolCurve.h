#pragma once

#include "VolCurve.h"

#include <variant>

namespace mql::vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  template <VolCurve... CurveTypes>
  class MultiTypeVolCurve {
  public:
    explicit MultiTypeVolCurve(VolCurve auto const& curve) : mCurve(curve) {}

    Volatility getVol(DateTime dateTime) const {
      return std::visit([=](auto const& curve) { return curve.getVol(dateTime); }, mCurve);
    }

  private:
    std::variant<CurveTypes...> mCurve;
  };

}
