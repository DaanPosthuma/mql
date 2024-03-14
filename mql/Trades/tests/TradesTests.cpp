#include "Trades/Cashflow.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace mql::literals;
  using mql::trades::Cashflow;
  using mql::CurrencyAmountDateTime;
  using mql::DateTime;
  using namespace std::chrono;

  TEST_CASE("Test cashflow trade") {

    auto const cashflow = Cashflow(CurrencyAmountDateTime(50.0_usd, DateTime(January / 1 / 2024)));
    auto const [currency, amount, paymentDateTime] = cashflow.GetCurrencyAmountDateTime();
    REQUIRE(currency == "USD"_ccy);
    REQUIRE(amount == 50.0);
    REQUIRE(paymentDateTime == DateTime(January / 1 / 2024));

  }

}
