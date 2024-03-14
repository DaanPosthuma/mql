#include "Currency.h"
#include "CurrencyAmount.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace mql::Literals;
  using mql::CurrencyAmount;

  TEST_CASE("Test currency literals") {

    REQUIRE(50.0_usd == CurrencyAmount("USD"_ccy, 50.0));

  }

}
