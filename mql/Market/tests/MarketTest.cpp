#include "Spot.h"
#include "Strike.h"
#include "CurrencyPair.h"
#include "VolatilityCurves/FlatVolatilityCurve.h"
#include "VolatilitySurfaces/FXVolatilitySurface.h"
#include "Market/Market.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <type_traits>

using namespace std::string_literals;
using namespace mql::literals;
using mql::DateTime;
using namespace std::chrono;
using namespace mql;
using namespace mql::fx_market;

namespace {


  TEST_CASE("Market test") {

    mql::FXMarket market;

    market.SetSpot("EURUSD"_pair, Spot(1.1, DateTime(January / 1 / 2023)));
    market.SetVolatilitySurface("EURUSD"_pair, VolSurfT(VolCurveT(0.1_vol)));

    REQUIRE(market.GetSpot("EURUSD"_pair).rate == 1.1);
    REQUIRE(market.GetVolatilitySurface("EURUSD"_pair).getVolatility(DateTime(January / 1 / 2023), 1.0_K) == 0.1_vol);

  }

}
