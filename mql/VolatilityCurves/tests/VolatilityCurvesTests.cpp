#include "VolatilityCurves/FlatVolatilityCurve.h"
#include "VolatilityCurves/PiecewiseFlatVolatilityCurve.h"
#include "VolatilityCurves/MultiTypeVolatilityCurve.h"
#include "VolatilityCurves/PolymorphicVolatilityCurve.h"
#include "Volatility.h"
#include <catch2/catch_test_macros.hpp>

using namespace mql::volatility_curves;
using namespace mql::literals;
using namespace std::chrono;

namespace {

  TEST_CASE("Test flat ATM vol curve") {

    auto const curve = FlatVolatilityCurve(0.15_vol);
    REQUIRE(curve.getVolatility(January / 10 / 1984) == 0.15_vol);

  }

  TEST_CASE("Test piecewise flat ATM vol curve") {

    auto const curve = PiecewiseFlatVolatilityCurve({ {January / 10 / 1984, 0.05_vol},
                                                  {February / 10 / 1984, 0.06_vol},
                                                  {March / 10 / 1984, 0.07_vol},
                                                  {April / 10 / 1984, 0.08_vol},
                                                  {May / 10 / 1984, 0.09_vol},
                                                  {January / 10 / 1985, 0.10_vol},
                                                  {January / 10 / 2024, 0.11_vol}
      });

    //REQUIRE(curve.getVol(January / 1 / 1984) == 0.00_vol); // throws
    REQUIRE(curve.getVolatility(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curve.getVolatility(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curve.getVolatility(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curve.getVolatility(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curve.getVolatility(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curve.getVolatility(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curve.getVolatility(January / 10 / 2054) == 0.11_vol);

  }

  TEST_CASE("Multi-curve holder") {

    using MTCurve = MultiTypeVolatilityCurve<FlatVolatilityCurve, PiecewiseFlatVolatilityCurve>;
    static_assert(VolatilityCurve<MTCurve>);
    auto curves = std::vector<MTCurve>();
    curves.emplace_back(FlatVolatilityCurve(0.37_vol));
    curves.emplace_back(PiecewiseFlatVolatilityCurve({ {January / 10 / 1984, 0.05_vol},
                                                   {February / 10 / 1984, 0.06_vol},
                                                   {March / 10 / 1984, 0.07_vol},
                                                   {April / 10 / 1984, 0.08_vol},
                                                   {May / 10 / 1984, 0.09_vol},
                                                   {January / 10 / 1985, 0.10_vol},
                                                   {January / 10 / 2024, 0.11_vol}
      }));


    REQUIRE(curves[0].getVolatility(January / 10 / 1984) == 0.37_vol);

    REQUIRE(curves[1].getVolatility(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getVolatility(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getVolatility(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getVolatility(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getVolatility(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curves[1].getVolatility(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curves[1].getVolatility(January / 10 / 2054) == 0.11_vol);

  }


  TEST_CASE("Polymorphic curve") {

    auto curves = std::vector<PolymorphicVolatilityCurve<std::unique_ptr>>();
    curves.emplace_back(FlatVolatilityCurve(0.37_vol));
    curves.emplace_back(PiecewiseFlatVolatilityCurve({ {January / 10 / 1984, 0.05_vol},
                                                   {February / 10 / 1984, 0.06_vol},
                                                   {March / 10 / 1984, 0.07_vol},
                                                   {April / 10 / 1984, 0.08_vol},
                                                   {May / 10 / 1984, 0.09_vol},
                                                   {January / 10 / 1985, 0.10_vol},
                                                   {January / 10 / 2024, 0.11_vol}
      }));

    REQUIRE(curves[0].getVolatility(January / 10 / 1984) == 0.37_vol);

    REQUIRE(curves[1].getVolatility(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getVolatility(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getVolatility(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getVolatility(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getVolatility(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curves[1].getVolatility(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curves[1].getVolatility(January / 10 / 2054) == 0.11_vol);

  }

  TEST_CASE("All vol curves satisfy vol curve concept") {
    STATIC_REQUIRE(VolatilityCurve<FlatVolatilityCurve>);
    STATIC_REQUIRE(VolatilityCurve<PiecewiseFlatVolatilityCurve>);
    STATIC_REQUIRE(VolatilityCurve<PolymorphicVolatilityCurve<>>);
    STATIC_REQUIRE(VolatilityCurve<MultiTypeVolatilityCurve<FlatVolatilityCurve, PiecewiseFlatVolatilityCurve>>);
  }

}
