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
using mql::Spot;
using mql::volatility_curves::FlatVolatilityCurve;
using mql::volatility_surfaces::FXVolatilitySurface;

namespace {


  TEST_CASE("Market test") {

    mql::FXMarket market;

    auto const pair = "EURUSD"_pair;
    market.setSpot(pair, Spot(1.1, DateTime(January / 1 / 2023), pair));
    market.setVolatilitySurface("EURUSD"_pair, FXVolatilitySurface(FlatVolatilityCurve(0.1_vol)));

    REQUIRE(market.getSpot("EURUSD"_pair).rate == 1.1);
    REQUIRE(market.getVolatilitySurface("EURUSD"_pair).getVolatility(DateTime(January / 1 / 2023), 1.0_K) == 0.1_vol);

  }

}
