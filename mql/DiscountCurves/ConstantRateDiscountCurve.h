#pragma once

#include "DiscountCurve.h"
#include "Rate.h"
#include <math.h>

namespace mql::discount_curves {

  using mql::DateTime;

  class ConstantRateDiscountCurve {
  public:
    ConstantRateDiscountCurve(Rate rate) : mRate(rate) {}

    [[nodiscard]] DiscountFactor computeDiscountFactor(DateTime from, DateTime to) const noexcept {
      (void)from;
      (void)to;
      int nbds = 200;
      int ndays = 360;
      double time = static_cast<double>(nbds) / ndays;
      return DiscountFactor(std::exp(-static_cast<double>(mRate)*time), from, to);
    }

  private:
    Rate mRate;
  };

}

