#include "VolCurves/FlatVolCurve.h"
#include "VolCurves/PiecewiseFlatVolCurve.h"
#include "VolCurves/MultiTypeVolCurve.h"
#include "VolCurves/PolymorphicVolCurve.h"
#include "Volatility.h"
#include <catch2/catch_test_macros.hpp>

using namespace mql::vol_curves;
using namespace mql::literals;
using namespace std::chrono;

namespace {

  TEST_CASE("Test flat ATM vol curve") {

    auto const curve = FlatVolCurve(0.15_vol);
    REQUIRE(curve.getVol(January / 10 / 1984) == 0.15_vol);

  }

  TEST_CASE("Test piecewise flat ATM vol curve") {

    auto const curve = PiecewiseFlatVolCurve({ {January / 10 / 1984, 0.05_vol},
                                                  {February / 10 / 1984, 0.06_vol},
                                                  {March / 10 / 1984, 0.07_vol},
                                                  {April / 10 / 1984, 0.08_vol},
                                                  {May / 10 / 1984, 0.09_vol},
                                                  {January / 10 / 1985, 0.10_vol},
                                                  {January / 10 / 2024, 0.11_vol}
      });

    //REQUIRE(curve.getVol(January / 1 / 1984) == 0.00_vol); // throws
    REQUIRE(curve.getVol(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curve.getVol(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curve.getVol(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curve.getVol(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curve.getVol(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curve.getVol(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curve.getVol(January / 10 / 2054) == 0.11_vol);

  }

  TEST_CASE("Multi-curve holder") {

    using MTCurve = MultiTypeVolCurve<FlatVolCurve, PiecewiseFlatVolCurve>;
    static_assert(VolCurve<MTCurve>);
    auto curves = std::vector<MTCurve>();
    curves.emplace_back(FlatVolCurve(0.37_vol));
    curves.emplace_back(PiecewiseFlatVolCurve({ {January / 10 / 1984, 0.05_vol},
                                                   {February / 10 / 1984, 0.06_vol},
                                                   {March / 10 / 1984, 0.07_vol},
                                                   {April / 10 / 1984, 0.08_vol},
                                                   {May / 10 / 1984, 0.09_vol},
                                                   {January / 10 / 1985, 0.10_vol},
                                                   {January / 10 / 2024, 0.11_vol}
      }));


    REQUIRE(curves[0].getVol(January / 10 / 1984) == 0.37_vol);

    REQUIRE(curves[1].getVol(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getVol(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getVol(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getVol(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getVol(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curves[1].getVol(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curves[1].getVol(January / 10 / 2054) == 0.11_vol);

  }


  TEST_CASE("Polymorphic curve") {

    auto curves = std::vector<PolymorphicVolCurve<std::unique_ptr>>();
    curves.emplace_back(FlatVolCurve(0.37_vol));
    curves.emplace_back(PiecewiseFlatVolCurve({ {January / 10 / 1984, 0.05_vol},
                                                   {February / 10 / 1984, 0.06_vol},
                                                   {March / 10 / 1984, 0.07_vol},
                                                   {April / 10 / 1984, 0.08_vol},
                                                   {May / 10 / 1984, 0.09_vol},
                                                   {January / 10 / 1985, 0.10_vol},
                                                   {January / 10 / 2024, 0.11_vol}
      }));

    REQUIRE(curves[0].getVol(January / 10 / 1984) == 0.37_vol);

    REQUIRE(curves[1].getVol(January / 10 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getVol(January / 11 / 1984) == 0.05_vol);
    REQUIRE(curves[1].getVol(February / 10 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getVol(February / 11 / 1984) == 0.06_vol);
    REQUIRE(curves[1].getVol(January / 9 / 2024) == 0.10_vol);
    REQUIRE(curves[1].getVol(January / 10 / 2024) == 0.11_vol);
    REQUIRE(curves[1].getVol(January / 10 / 2054) == 0.11_vol);

  }



}
