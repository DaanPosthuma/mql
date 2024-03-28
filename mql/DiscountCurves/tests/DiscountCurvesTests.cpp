#include "DiscountCurves/DiscountCurve.h"
#include "DiscountCurves/ConstantRateDiscountCurve.h"
#include <catch2/catch_test_macros.hpp>

using namespace std::chrono;
using mql::Rate;
using namespace mql::discount_curves;

namespace {

  TEST_CASE("Test flat discount curve") {
    ConstantRateDiscountCurve discount(Rate(0.0));
    REQUIRE(discount.computeDiscountFactor(January / 1 / 2024, January / 1 / 2025) == DiscountFactor(1.0, January / 1 / 2024, January / 1 / 2025));
  }

  TEST_CASE("All discount curves satisfy discount curve concept") {
    STATIC_REQUIRE(DiscountCurve<ConstantRateDiscountCurve>);
  }

}
