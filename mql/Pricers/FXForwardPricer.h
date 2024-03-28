#pragma once

#include "Currency.h"
#include "CurrencyPair.h"
#include "DiscountCurves/DiscountCurve.h"
#include "CurrencyAmountDateTime.h"
#include "Trades/FXForward.h"

namespace mql::pricers {

  using mql::discount_curves::DiscountCurve;
  
  auto DiscountCashflow(CurrencyAmountDateTime const& cashflow, DateTime to, DiscountCurve auto const& curve) {
    return cashflow * curve.computeDiscountFactor(cashflow.dateTime, to);
  }

  auto DiscountAndSpotConvertCashflow(CurrencyAmountDateTime const& cashflow, Currency ccyTo, Spot const& spotFromTo, DiscountCurve auto const& curve) {
    return DiscountCashflow(cashflow, spotFromTo.date, curve) * spotFromTo;
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
