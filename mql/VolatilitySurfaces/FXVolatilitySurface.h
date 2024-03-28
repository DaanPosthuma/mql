#pragma once

#include "Strike.h"
#include "Volatility.h"
#include "VolatilityCurves/VolatilityCurve.h"
#include "DiscountCurves/DiscountCurve.h"
#include <functional>

namespace mql::volatility_surfaces {

  using mql::volatility_curves::VolatilityCurve;
  using mql::discount_curves::DiscountCurve;
  using mql::DateTime;

  template <VolatilityCurve VolatilityCurveT, 
            DiscountCurve DiscountCurveDomesticT, 
            DiscountCurve DiscountCurveForeignT>
  class FXVolatilitySurface {
  public:
    FXVolatilitySurface(VolatilityCurveT atmVolCurve, 
                        DiscountCurveDomesticT const& discountCurveDomestic, 
                        DiscountCurveForeignT const& discountCurveForeign) noexcept : 
      mATMVolCurve(std::move(atmVolCurve)), 
      mDiscountCurveFor(discountCurveForeign), 
      mDiscountCurveDom(discountCurveDomestic) {}

    [[nodiscard]] Volatility getVolatility(DateTime dateTime, Strike strike) const noexcept {
      (void)strike;
      return mATMVolCurve.getVolatility(dateTime);
    }

  private:
    VolatilityCurveT mATMVolCurve;
    std::reference_wrapper<const DiscountCurveForeignT> mDiscountCurveFor;
    std::reference_wrapper<const DiscountCurveDomesticT> mDiscountCurveDom;
  };

}
