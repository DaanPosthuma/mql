#include "Currency.h"
#include "CurrencyAmount.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace mql::literals;
  using mql::CurrencyAmount;
  using mql::Currency;

  TEST_CASE("Test currency literals") {

    REQUIRE(50.0_usd == CurrencyAmount("USD"_ccy, 50.0));
    REQUIRE(40_usd == CurrencyAmount("USD"_ccy, 40.0));

  }

  TEST_CASE("Test currency amount structured binding") {
    auto const [currency, amount] = 40_usd;
    REQUIRE(currency == Currency("USD"));
    REQUIRE(amount == 40.0);
  }

}
