#pragma once

#include "Trades/Cashflow.h"

namespace mql::pricers {

  CurrencyAmountDateTime priceCashflow(mql::trades::Cashflow const& cashflow) {
    return cashflow.GetCurrencyAmountDateTime();
  }

}
