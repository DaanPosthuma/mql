#pragma once

#include "DateTime.h"
#include "CurrencyAmount.h"

namespace mql::Trades {

  class Cashflow {
  public:
    Cashflow(CurrencyAmount currencyAmount, DateTime paymentDateTime) : mCurrencyAmount(currencyAmount), mPaymentDateTime(paymentDateTime) {}

  private:
    CurrencyAmount mCurrencyAmount;
    DateTime mPaymentDateTime;

  };

}
