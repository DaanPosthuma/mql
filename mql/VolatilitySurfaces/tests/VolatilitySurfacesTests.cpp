#include "VolatilityCurves/FlatVolatilityCurve.h"
#include "VolatilitySurfaces/FlatSmileVolatilitySurface.h"
#include "VolatilitySurfaces/VolatilitySurface.h"
#include "VolatilitySurfaces/FXVolatilitySurface.h"
#include "VolatilitySurfaces/FlatSmileVolatilitySurface.h"
#include "DiscountCurves/ConstantRateDiscountCurve.h"
#include <catch2/catch_test_macros.hpp>

using namespace mql::volatility_curves;
using namespace mql::volatility_surfaces;
using namespace mql::literals;
using namespace std::chrono;
using namespace mql::discount_curves;

namespace {

  TEST_CASE("Flat vol surface test") {
    auto const atmCurve = FlatVolatilityCurve(0.20_vol);
    auto domCurve = ConstantRateDiscountCurve(mql::Rate(0.0));
    auto forCurve = ConstantRateDiscountCurve(mql::Rate(0.0));
    auto const surface = FXVolatilitySurface(atmCurve, forCurve, domCurve);
    REQUIRE(surface.getVolatility(March / 14 / 2024, 1.0_K) == 0.20_vol);
  }

  TEST_CASE("All vol surfaces satisfy vol surface concept") {
    STATIC_REQUIRE(VolatilitySurface<FXVolatilitySurface<FlatVolatilityCurve, ConstantRateDiscountCurve, ConstantRateDiscountCurve>>);
    STATIC_REQUIRE(VolatilitySurface<FlatSmileVolatilitySurface<FlatVolatilityCurve>>);
  }

}
