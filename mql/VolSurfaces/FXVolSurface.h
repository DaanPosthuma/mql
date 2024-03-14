#pragma once

#include "../Strike.h"
#include "../Volatility.h"
#include "../ATMVolCurves/ATMVolCurve.h"

namespace mql::VolSurfaces {

    using mql::atm_vol_curves::ATMVolCurve;
    using mql::DateTime;

    template <ATMVolCurve ATMVolCurveT>
    class FXVolatilitySurface {
    public:
        FXVolatilitySurface(ATMVolCurveT atmVolCurve) noexcept : mATMVolCurve(std::move(atmVolCurve)) {}

        Volatility getVolatility(DateTime dateTime, Strike strike) const noexcept {
            return mATMVolCurve.getATMVol(dateTime);
        }

    private:
        ATMVolCurveT mATMVolCurve;
    };

}
