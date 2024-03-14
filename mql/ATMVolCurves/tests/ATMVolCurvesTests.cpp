#include "ATMVolCurves/FlatATMVolCurve.h"
#include "ATMVolCurves/PiecewiseFlatATMVolCurve.h"
#include "ATMVolCurves/MultiTypeATMVolCurve.h"
#include "ATMVolCurves/PolymorphicATMVolCurve.h"
#include "Volatility.h"
#include <catch2/catch_test_macros.hpp>

using namespace mql::ATMVolCurves;
using namespace mql::Literals;
using namespace std::chrono;

namespace {

  TEST_CASE("Test flat ATM vol curve") {

    auto const curve = FlatATMVolCurve(0.15_vol);
    REQUIRE(curve.getATMVol(January / 10 / 1984) == 0.15_vol);

  }

  TEST_CASE("Test piecewise flat ATM vol curve") {

    auto const curve = PiecewiseFlatATMVolCurve({ {January / 10 / 1984, 0.05_vol},
                                                  {February / 10 / 1984, 0.06_vol},
                                                  {March / 10 / 1984, 0.07_vol},
                                                  {April / 10 / 1984, 0.08_vol},
                                                  {May / 10 / 1984, 0.09_vol},
                                                  {January / 10 / 1985, 0.10_vol},
                                                  {January / 10 / 2024, 0.11_vol}
      });

    REQUIRE(curve.getATMVol(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curve.getATMVol(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curve.getATMVol(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curve.getATMVol(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curve.getATMVol(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curve.getATMVol(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curve.getATMVol(January / 10 / 2054) == 0.11_vol);

  }

  TEST_CASE("Multi-curve holder") {

    using MTCurve = MultiTypeATMVolCurve<FlatATMVolCurve, PiecewiseFlatATMVolCurve>;
    auto curves = std::vector<MTCurve>();
    curves.emplace_back(FlatATMVolCurve(0.37_vol));
    curves.emplace_back(PiecewiseFlatATMVolCurve({ {January / 10 / 1984, 0.05_vol},
                                                   {February / 10 / 1984, 0.06_vol},
                                                   {March / 10 / 1984, 0.07_vol},
                                                   {April / 10 / 1984, 0.08_vol},
                                                   {May / 10 / 1984, 0.09_vol},
                                                   {January / 10 / 1985, 0.10_vol},
                                                   {January / 10 / 2024, 0.11_vol}
      }));


    REQUIRE(curves[0].getATMVol(January / 10 / 1984) == 0.37_vol);

    REQUIRE(curves[1].getATMVol(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getATMVol(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getATMVol(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getATMVol(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getATMVol(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curves[1].getATMVol(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curves[1].getATMVol(January / 10 / 2054) == 0.11_vol);

  }


  TEST_CASE("Polymorphic curve") {

    auto curves = std::vector<PolymorphicATMVolCurve<std::unique_ptr>>();
    curves.emplace_back(FlatATMVolCurve(0.37_vol));
    curves.emplace_back(PiecewiseFlatATMVolCurve({ {January / 10 / 1984, 0.05_vol},
                                                   {February / 10 / 1984, 0.06_vol},
                                                   {March / 10 / 1984, 0.07_vol},
                                                   {April / 10 / 1984, 0.08_vol},
                                                   {May / 10 / 1984, 0.09_vol},
                                                   {January / 10 / 1985, 0.10_vol},
                                                   {January / 10 / 2024, 0.11_vol}
      }));

    REQUIRE(curves[0].getATMVol(January / 10 / 1984) == 0.37_vol);

    REQUIRE(curves[1].getATMVol(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getATMVol(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getATMVol(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getATMVol(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getATMVol(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curves[1].getATMVol(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curves[1].getATMVol(January / 10 / 2054) == 0.11_vol);

  }



}
