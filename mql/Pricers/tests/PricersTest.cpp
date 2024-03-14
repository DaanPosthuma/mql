#include "Pricers/CashflowPricer.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace mql::literals;
  using mql::trades::Cashflow;
  using mql::DateTime;
  using namespace std::chrono;

  TEST_CASE("Cashflow pricer returns currency amount at payment date") {
    // Cashflow pricer does not discount to today, it just returns the currency amount at the payment date.
    // The risk engine will discount this to a consistent reporting date
    auto const cashflow = Cashflow(50.0_usd, January / 10 / 2024);
    auto const price = mql::pricers::priceCashflow(cashflow);
    REQUIRE(price.amount == 50.0);
    REQUIRE(price.currency == "USD"_ccy);
    REQUIRE(price.dateTime == DateTime(January / 10 / 2024));

  }

}
