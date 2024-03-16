#include "VolCurves/FlatVolCurve.h"
#include "VolSurfaces/FlatSmileVolSurface.h"
#include "VolSurfaces/FXVolSurface.h"
#include <catch2/catch_test_macros.hpp>

using namespace mql::vol_curves;
using namespace mql::VolSurfaces;
using namespace mql::literals;
using namespace std::chrono;

namespace {

  TEST_CASE("Flat vol surface test") {

    auto const curve = FlatVolCurve(0.20_vol);
    auto const surface = FXVolatilitySurface(curve);
    REQUIRE(surface.getVolatility(March / 14 / 2024, 1.0_K) == 0.20_vol);

  }

}
