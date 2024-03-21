#pragma once

#include "CurrencyAmountDateTime.h"
#include "Trades/Cashflow.h"

namespace mql::pricers {

  CurrencyAmountDateTime priceCashflow(mql::trades::Cashflow const& cashflow) {
    return CurrencyAmountDateTime(cashflow.GetCurrencyAmount(), cashflow.GetPaymentDateTime());
  }

}
