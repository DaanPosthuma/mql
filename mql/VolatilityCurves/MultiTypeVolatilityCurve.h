#pragma once

#include "VolatilityCurve.h"

#include <variant>

namespace mql::volatility_curves {

  using mql::DateTime;
  using mql::Volatility;

  template <VolatilityCurve... CurveTypes>
  class MultiTypeVolatilityCurve {
  public:
    explicit MultiTypeVolatilityCurve(VolatilityCurve auto const& curve) : mCurve(curve) {}

    [[nodiscard]] Volatility getVolatility(DateTime dateTime) const {
      return std::visit([=](auto const& curve) { return curve.getVolatility(dateTime); }, mCurve);
    }

  private:
    std::variant<CurveTypes...> mCurve;

  };

}
