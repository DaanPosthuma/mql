#include "Currency.h"
#include "CurrencyAmount.h"
#include "CurrencyAmountDateTime.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace mql::literals;
  using mql::CurrencyAmount;
  using mql::CurrencyAmountDateTime;
  using mql::Currency;
  using mql::DateTime;
  using namespace std::chrono;

  TEST_CASE("Test currency literals") {

    REQUIRE(50.0_usd == CurrencyAmount("USD"_ccy, 50.0));
    REQUIRE(40_usd == CurrencyAmount("USD"_ccy, 40.0));

  }

  TEST_CASE("Test currency amount structured binding") {
    auto const [currency, amount] = 40_usd;
    REQUIRE(currency == Currency("USD"));
    REQUIRE(amount == 40.0);
  }

  TEST_CASE("Test currency amount date time structured binding") {
    auto const cadt = CurrencyAmountDateTime(40_usd, January / 1 / 2024);
    auto const [currency, amount, dateTime] = cadt;
    REQUIRE(currency == Currency("USD"));
    REQUIRE(amount == 40.0);
    REQUIRE(dateTime == DateTime(January / 1 / 2024));
  }

}
