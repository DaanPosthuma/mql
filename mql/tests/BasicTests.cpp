#include "Currency.h"
#include "Strike.h"
#include "Spot.h"
#include "Volatility.h"
#include "CurrencyAmount.h"
#include "CurrencyAmountDateTime.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace mql::literals;
  using namespace mql;
  using namespace std::chrono;

  TEST_CASE("Test currency literals") {
    REQUIRE(50_usd == CurrencyAmount("USD"_ccy, 50.0));
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

  TEST_CASE("DateTime is trivially copyable") {
    STATIC_REQUIRE(std::is_trivially_copyable<DateTime>());
  }

  TEST_CASE("Strike is trivially copyable") {
    STATIC_REQUIRE(std::is_trivially_copyable<Strike>());
  }

  /*TEST_CASE("Spot is trivially copyable") {
    STATIC_REQUIRE(std::is_trivially_copyable<Spot>());
  }*/ 

  TEST_CASE("Volatility is trivially copyable") {
    STATIC_REQUIRE(std::is_trivially_copyable<Volatility>());
  }

}
