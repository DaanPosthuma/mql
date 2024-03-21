#include "VolatilityCurves/FlatVolatilityCurve.h"
#include "VolatilitySurfaces/FlatSmileVolatilitySurface.h"
#include "VolatilitySurfaces/VolatilitySurface.h"
#include "VolatilitySurfaces/FXVolatilitySurface.h"
#include "VolatilitySurfaces/FlatSmileVolatilitySurface.h"
#include <catch2/catch_test_macros.hpp>

using namespace mql::volatility_curves;
using namespace mql::vol_surfaces;
using namespace mql::literals;
using namespace std::chrono;

namespace {

  TEST_CASE("Flat vol surface test") {
    auto const curve = FlatVolatilityCurve(0.20_vol);
    auto const surface = FXVolatilitySurface(curve);
    REQUIRE(surface.getVolatility(March / 14 / 2024, 1.0_K) == 0.20_vol);
  }

  TEST_CASE("All vol surfaces satisfy vol surface concept") {
    STATIC_REQUIRE(VolatilitySurface<FXVolatilitySurface<FlatVolatilityCurve>>);
    STATIC_REQUIRE(VolatilitySurface<FlatSmileVolatilitySurface<FlatVolatilityCurve>>);
  }

}
