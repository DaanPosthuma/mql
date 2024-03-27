#include "Spot.h"
#include "CurrencyPair.h"
#include "Pricers/CashflowPricer.h"
#include "Pricers/FXForwardPricer.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <cassert>

namespace {

  using namespace mql::literals;
  using namespace mql::trades;
  using namespace mql;
  using namespace std::chrono;

  class SingleCurrencyPairMarket {
  public:
    SingleCurrencyPairMarket(Currency currencyBase, Currency currencyTerm, Spot spot) : mSpot(spot), mCurrencyBase(currencyBase), mCurrencyTerm(currencyTerm) {}

    [[nodiscard]] Spot getSpot(CurrencyPair pair) const {
      REQUIRE(pair == CurrencyPair(mCurrencyBase, mCurrencyTerm));
      return mSpot;
    }

  private:
    Currency mCurrencyBase;
    Currency mCurrencyTerm;
    Spot mSpot;

  };

  TEST_CASE("Cashflow pricer returns currency amount at payment date") {
    // Cashflow pricer does not discount to today, it just returns the currency amount at the payment date.
    // The risk engine will discount this to a consistent reporting date
    auto const cashflow = Cashflow(50_usd, January / 1 / 2024);
    auto const price = mql::pricers::priceCashflow(cashflow);
    REQUIRE(price.amount == 50.0);
    REQUIRE(price.currency == "USD"_ccy);
    REQUIRE(price.dateTime == DateTime(January / 1 / 2024));

  }

  TEST_CASE("FX Forward pricer") {
    
    auto const market = SingleCurrencyPairMarket("EUR"_ccy, "USD"_ccy, Spot(1.1, DateTime(January / 1 / 2023)));

    auto const fxForward = FXForward(100_eur, 110_usd, July / 8 / 2024);
    auto const price = mql::pricers::priceFXForward(fxForward, market);
    REQUIRE(price.amount == 0.0);
    REQUIRE(price.currency == "USD"_ccy);
    REQUIRE(price.dateTime == DateTime(January / 1 / 2023));
  }

}
