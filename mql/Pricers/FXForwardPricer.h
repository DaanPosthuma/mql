#pragma once

#include "Currency.h"
#include "CurrencyPair.h"
#include "DiscountCurves/DiscountCurve.h"
#include "CurrencyAmountDateTime.h"
#include "Trades/FXForward.h"

namespace mql::pricers {

  using mql::discount_curves::DiscountCurve;
  
  auto DiscountCashflow(CurrencyAmountDateTime from, DateTime to, DiscountCurve auto const& curve) {
    auto df = curve.computeDiscountFactor(from.dateTime, to);
    from.dateTime = to;
    from.amount = from.amount * static_cast<double>(df);
    return from;
  }

  auto DiscountAndSpotConvertCashflow(CurrencyAmountDateTime from, Currency ccyTo, Spot spotFromTo, DiscountCurve auto const& curve) {
    auto const [spotRate, spotDate] = spotFromTo;
    auto const [ccyFrom, amountAtSpotDate, _] = DiscountCashflow(from, spotFromTo.date, curve);

    return CurrencyAmountDateTime(ccyTo, Amount(amountAtSpotDate * spotRate), spotDate);
  }

  template <typename T>
  concept ForwardPricerMarket = requires(T market, CurrencyPair currencyPair, Currency currency, Currency)
  {
    { market.getSpot(currencyPair) } -> std::same_as<Spot>;
    { market.getDiscountCurve(currency) } -> DiscountCurve;
  };

  CurrencyAmountDateTime priceFXForward(mql::trades::FXForward const& fxForward, const ForwardPricerMarket auto& market) {
    
    auto const& ccyBuy = fxForward.getCurrencyAmountBuy().currency;
    auto const& ccySell = fxForward.getCurrencyAmountSell().currency;
    auto const& spotBuySell = market.getSpot(CurrencyPair(ccyBuy, ccySell));
    auto const& curveBuy = market.getDiscountCurve(ccyBuy);
    auto const& curveSell = market.getDiscountCurve(ccySell);

    auto const cashflowBuy = CurrencyAmountDateTime(fxForward.getCurrencyAmountBuy(), fxForward.getPaymentDateTime());
    auto const cashflowSell = CurrencyAmountDateTime(fxForward.getCurrencyAmountSell(), fxForward.getPaymentDateTime());
    auto const a = DiscountAndSpotConvertCashflow(cashflowBuy, ccySell, spotBuySell, curveBuy);
    auto const b = DiscountCashflow(cashflowSell, a.dateTime, curveSell);

    return a - b;
  }

}
