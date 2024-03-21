#pragma once

#include "DateTime.h"
#include "CurrencyAmount.h"
#include "DateTime.h"

namespace mql::trades {

  class Cashflow {
  public:
    Cashflow(CurrencyAmount currencyAmount, DateTime paymentDateTime) noexcept : mCurrencyAmount(currencyAmount), mPaymentDateTime(paymentDateTime) {}
    
    auto const& GetCurrencyAmount() const noexcept { return mCurrencyAmount; }
    auto const& GetPaymentDateTime() const noexcept { return mPaymentDateTime; }

  private:
    CurrencyAmount mCurrencyAmount;
    DateTime mPaymentDateTime;

  };

}
