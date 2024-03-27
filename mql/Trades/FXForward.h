#pragma once

#include "CurrencyAmount.h"
#include "DateTime.h"

namespace mql::trades {

  class FXForward {
  public:
    FXForward(CurrencyAmount currencyAmountBuy, CurrencyAmount currencyAmountSell, DateTime paymentDateTime) noexcept : mCurrencyAmountBuy(currencyAmountBuy), mCurrencyAmountSell(currencyAmountSell), mPaymentDateTime(paymentDateTime) {}

    auto const& getCurrencyAmountBuy() const noexcept { return mCurrencyAmountBuy; }
    auto const& getCurrencyAmountSell() const noexcept { return mCurrencyAmountSell; }
    auto const& getPaymentDateTime() const noexcept { return mPaymentDateTime; }

  private:
    CurrencyAmount mCurrencyAmountBuy;
    CurrencyAmount mCurrencyAmountSell;
    DateTime mPaymentDateTime;

  };

}
