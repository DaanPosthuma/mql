#pragma once

#include "Market/Market.h"
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

  template <typename T>
  concept SpotMarket = requires(T market, CurrencyPair currencyPair)
  {
    { market.getSpot(currencyPair) } -> std::same_as<Spot>;
  };

  CurrencyAmountDateTime priceFXForward(mql::trades::FXForward const& fxForward, const SpotMarket auto& market) {
    
    auto const ccyBuy = fxForward.getCurrencyAmountBuy().currency;
    auto const ccySell = fxForward.getCurrencyAmountSell().currency;
    auto const spot = market.getSpot(CurrencyPair(ccyBuy, ccySell));

    auto const cashflowBuy = CurrencyAmountDateTime(fxForward.getCurrencyAmountBuy(), fxForward.getPaymentDateTime());
    auto const cashflowSell = CurrencyAmountDateTime(fxForward.getCurrencyAmountSell(), fxForward.getPaymentDateTime());
    auto const a = DiscountAndSpotConvertCashflow(cashflowBuy, ccySell, spot);
    auto const b = DiscountCashflow(cashflowSell, spot.date);

    return a - b;
  }

}
