#pragma once

#include <ostream>
#include "Currency.h"

namespace mql {

  class CurrencyPair {
  public:
    constexpr explicit CurrencyPair(std::string currencyPair) noexcept : mCurrencyPair(currencyPair) {}
    constexpr CurrencyPair(Currency base, Currency term) noexcept : mCurrencyPair(base.mCurrency + term.mCurrency) {}

  private:
    friend std::ostream& operator<<(std::ostream& ostr, CurrencyPair currencyPair);
    friend bool operator==(CurrencyPair lhs, CurrencyPair rhs);
    friend struct std::hash<mql::CurrencyPair>;

    std::string mCurrencyPair;

  };

  inline bool operator==(CurrencyPair lhs, CurrencyPair rhs) {
    return lhs.mCurrencyPair == rhs.mCurrencyPair;
  }

  inline std::ostream& operator<<(std::ostream& ostr, CurrencyPair currencyPair) {
    ostr << "currencyPair(" << currencyPair.mCurrencyPair << ")";
    return ostr;
  }

  inline namespace literals {

    constexpr CurrencyPair operator""_pair(char const* currencyPair, std::size_t)
    {
      return CurrencyPair(currencyPair);
    }

  }

}

namespace std {

  template <>
  struct hash<mql::CurrencyPair> {
    std::size_t operator()(mql::CurrencyPair pair) const {
      return std::hash<std::string>{}(pair.mCurrencyPair);
    }
  };

}
