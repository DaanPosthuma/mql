#include "Trades/Cashflow.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace mql::literals;
  using mql::trades::Cashflow;
  using mql::DateTime;
  using namespace std::chrono;

  TEST_CASE("Test cashflow trade") {

    auto const cashflow = Cashflow(50.0_usd, DateTime(January / 10 / 1984));
    //auto const [currency, amount] = cashflow.GetCurrencyAmount();
    //REQUIRE(.GetAmount());

  }

}
