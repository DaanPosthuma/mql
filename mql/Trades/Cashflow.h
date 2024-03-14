#pragma once

#include "DateTime.h"
#include "CurrencyAmountDateTime.h"

namespace mql::trades {

  class Cashflow {
  public:
    Cashflow(Currency currency, Amount amount, DateTime paymentDateTime) noexcept : mCurrencyAmountDateTime(currency, amount, paymentDateTime) {}
    Cashflow(CurrencyAmount currencyAmount, DateTime paymentDateTime) noexcept : mCurrencyAmountDateTime(currencyAmount.currency, currencyAmount.amount, paymentDateTime) {}
    Cashflow(CurrencyAmountDateTime currencyAmountDateTime) noexcept : mCurrencyAmountDateTime(currencyAmountDateTime) {}
    auto const& GetCurrencyAmountDateTime() const noexcept { return mCurrencyAmountDateTime; }

  private:
    CurrencyAmountDateTime mCurrencyAmountDateTime;

  };

}
