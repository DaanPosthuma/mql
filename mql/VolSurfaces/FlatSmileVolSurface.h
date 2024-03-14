#pragma once

#include "../Strike.h"
#include "../ATMVolCurves/ATMVolCurve.h"

namespace mql::VolSurfaces {

    using mql::ATMVolCurves::ATMVolCurve;
    using mql::DateTime;
    
    template <ATMVolCurve ATMVolCurveT>
    class FlatSmileVolatilitySurface {
    public:
        FlatSmileVolatilitySurface(ATMVolCurveT atmVolCurve) : mATMVolCurve(std::move(atmVolCurve)) {}

        Volatility getVolatility(DateTime dateTime, Strike strike) const {
            return mATMVolCurve.getATMVol(dateTime);
        }

    private:
        ATMVolCurveT mATMVolCurve;
    };

}
