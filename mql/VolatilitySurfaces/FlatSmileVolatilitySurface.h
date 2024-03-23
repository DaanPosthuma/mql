#pragma once

#include "Strike.h"
#include "VolatilityCurves/VolatilityCurve.h"

namespace mql::volatility_surfaces {

    using mql::volatility_curves::VolatilityCurve;
    using mql::DateTime;
    
    template <VolatilityCurve VolatilityCurveT>
    class FlatSmileVolatilitySurface {
    public:
        FlatSmileVolatilitySurface(VolatilityCurveT VolatilityCurve) noexcept : mVolCurve(std::move(VolatilityCurve)) {}

        [[nodiscard]] Volatility getVolatility(DateTime dateTime, Strike strike) const noexcept {
            return mVolCurve.getVolatility(dateTime);
        }

    private:
        VolatilityCurveT mVolCurve;
    };

}
