#pragma once

#include "Spot.h"
#include "CurrencyAmountDateTime.h"
#include "Trades/FXForward.h"

namespace mql::pricers {

  
  auto DiscountCashflow(CurrencyAmountDateTime from, DateTime to) {
    from.dateTime = to;
    return from;
  }

  auto DiscountAndSpotConvertCashflow(CurrencyAmountDateTime from, Currency ccyTo, Spot spot) {
    auto const [spotRate, spotDate] = spot;
    auto const [ccyFrom, amountAtSpotDate, _] = DiscountCashflow(from, spot.date);

    return CurrencyAmountDateTime(ccyTo, Amount(amountAtSpotDate * spotRate), spotDate);
  }

  CurrencyAmountDateTime priceFXForward(mql::trades::FXForward const& fxForward, mql::Spot spot) {
    
    auto const ccySell = fxForward.GetCurrencyAmountSell().currency;

    auto const cashflowBuy = CurrencyAmountDateTime(fxForward.GetCurrencyAmountBuy(), fxForward.GetPaymentDateTime());
    auto const cashflowSell = CurrencyAmountDateTime(fxForward.GetCurrencyAmountSell(), fxForward.GetPaymentDateTime());
    auto const a = DiscountAndSpotConvertCashflow(cashflowBuy, ccySell, spot);
    auto const b = DiscountCashflow(cashflowSell, spot.date);

    return a - b;
  }

}
