﻿#include "ATMVolCurves/FlatATMVolCurve.h"
#include "VolSurfaces/FlatSmileVolSurface.h"
#include "VolSurfaces/FXVolSurface.h"
#include <catch2/catch_test_macros.hpp>

using namespace mql::ATMVolCurves;
using namespace mql::VolSurfaces;
using namespace mql::Literals;
using namespace std::chrono;

namespace {

  TEST_CASE("Flat vol surface test") {

    auto const curve = FlatATMVolCurve(0.20_vol);
    auto const surface = FXVolatilitySurface(curve);
    REQUIRE(surface.getVolatility(March / 14 / 2024, 1.0_K) == 0.20_vol);

  }

}
