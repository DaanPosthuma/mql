#include "DateTime.h"
#include "Trades/Cashflow.h"
#include "Trades/FXForward.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace mql::literals;
  using namespace mql::trades;
  using mql::DateTime;
  using namespace std::chrono;

  TEST_CASE("Test cashflow") {

    auto const cashflow = Cashflow(50_usd, DateTime(January / 1 / 2024));
    auto const [currency, amount] = cashflow.GetCurrencyAmount();
    REQUIRE(currency == "USD"_ccy);
    REQUIRE(amount == 50.0);
    REQUIRE(cashflow.GetPaymentDateTime() == DateTime(January / 1 / 2024));

  }

  TEST_CASE("Test FX Forward") {

    auto const cashflow = FXForward(50_usd, 40_eur, DateTime(January / 1 / 2024));
    auto const [currencyBuy, amountBuy] = cashflow.GetCurrencyAmountBuy();
    auto const [currencySell, amountSell] = cashflow.GetCurrencyAmountSell();
    REQUIRE(currencyBuy == "USD"_ccy);
    REQUIRE(currencySell == "EUR"_ccy);
    REQUIRE(amountBuy == 50.0);
    REQUIRE(amountSell == 40.0);
    REQUIRE(cashflow.GetPaymentDateTime() == DateTime(January / 1 / 2024));

  }

}
