#pragma once

#include "../Strike.h"
#include "../Volatility.h"
#include "../VolatilityCurves/VolatilityCurve.h"

namespace mql::vol_surfaces {

    using mql::volatility_curves::VolatilityCurve;
    using mql::DateTime;

    template <VolatilityCurve VolatilityCurveT>
    class FXVolatilitySurface {
    public:
        FXVolatilitySurface(VolatilityCurveT VolatilityCurve) noexcept : mVolCurve(std::move(VolatilityCurve)) {}

        [[nodiscard]] Volatility getVolatility(DateTime dateTime, Strike strike) const noexcept {
            return mVolCurve.getVolatility(dateTime);
        }

    private:
        VolatilityCurveT mVolCurve;
    };

}
