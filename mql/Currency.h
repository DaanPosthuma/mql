#pragma once

#include <ostream>

namespace mql {

  class Currency {
  public:
    constexpr explicit Currency(std::string currency) : mCurrency(currency) {}
  private:
    friend std::ostream& operator<<(std::ostream& ostr, Currency volatility);
    friend bool operator==(Currency lhs, Currency rhs);

    std::string mCurrency;

  };

  inline bool operator==(Currency lhs, Currency rhs) {
    return lhs.mCurrency == rhs.mCurrency;
  }

  inline std::ostream& operator<<(std::ostream& ostr, Currency volatility) {
    ostr << "currency(" << volatility.mCurrency << ")";
    return ostr;
  }

  inline namespace Literals {

    constexpr Currency operator""_ccy(char const* currency, std::size_t)
    {
      return Currency(currency);
    }

  }

}
