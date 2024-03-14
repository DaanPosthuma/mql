#pragma once

#include "Currency.h"
#include <ostream>

namespace mql {

  class CurrencyAmount {
  public:
    constexpr CurrencyAmount(Currency currency, double amount) : mCurrency(currency), mAmount(amount) {}

  private:
    friend std::ostream& operator<<(std::ostream& ostr, CurrencyAmount volatility);
    friend bool operator==(CurrencyAmount lhs, CurrencyAmount rhs);

    auto tie() const {
      return std::tie(mCurrency, mAmount);
    }

    Currency mCurrency;
    double mAmount;
  };

  inline bool operator==(CurrencyAmount lhs, CurrencyAmount rhs) {
    return lhs.tie() == rhs.tie();
  }

  inline std::ostream& operator<<(std::ostream& ostr, CurrencyAmount volatility) {
    ostr << "CurrencyAmount(" << volatility.mCurrency << volatility.mAmount << ")";
    return ostr;
  }

  inline namespace Literals {

    CurrencyAmount operator""_usd(long double amount)
    {
      return CurrencyAmount(Currency("USD"), amount);
    }

  }

}
