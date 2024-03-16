#pragma once

#include "../Strike.h"
#include "../Volatility.h"
#include "../VolCurves/VolCurve.h"

namespace mql::VolSurfaces {

    using mql::vol_curves::VolCurve;
    using mql::DateTime;

    template <VolCurve VolCurveT>
    class FXVolatilitySurface {
    public:
        FXVolatilitySurface(VolCurveT VolCurve) noexcept : mVolCurve(std::move(VolCurve)) {}

        Volatility getVolatility(DateTime dateTime, Strike strike) const noexcept {
            return mVolCurve.getVol(dateTime);
        }

    private:
        VolCurveT mVolCurve;
    };

}
