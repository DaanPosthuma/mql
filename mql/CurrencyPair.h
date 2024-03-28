#pragma once

#include "Currency.h"
#include <ostream>
#include <cassert>


namespace mql {

  class CurrencyPair {
  public:
    Currency foreign;
    Currency domestic;

    constexpr CurrencyPair(Currency const& foreign, Currency const& domestic) noexcept : foreign(foreign), domestic(domestic) {}

  private:
    friend bool operator==(CurrencyPair const& lhs, CurrencyPair const& rhs);
    
    auto tie() const noexcept {
      return std::tie(foreign, domestic);
    }

  };

  inline bool operator==(CurrencyPair const& lhs, CurrencyPair const& rhs) {
    return lhs.tie()  == rhs.tie();
  }

  inline std::ostream& operator<<(std::ostream& ostr, CurrencyPair const& currencyPair) {
    ostr << "currencyPair(" << currencyPair.domestic.mCurrency << currencyPair.foreign.mCurrency << ")";
    return ostr;
  }

  inline namespace literals {

    constexpr CurrencyPair operator""_pair(char const* currencyPair, std::size_t n)
    {
      assert(n == 6);
      return CurrencyPair(Currency(std::string() + currencyPair[0] + currencyPair[1] + currencyPair[2]),
                          Currency(std::string() + currencyPair[3] + currencyPair[4] + currencyPair[5]));
    }

  }

}

namespace std {

  template <>
  struct hash<mql::CurrencyPair> {
    std::size_t operator()(mql::CurrencyPair pair) const {
      unsigned int h = 2166136261;
      for (char c : pair.foreign.mCurrency) {
        h = (h * 16777619) ^ c;
      }
      for (char c : pair.domestic.mCurrency) {
        h = (h * 16777619) ^ c;
      }
      return h;
    }
  };

}
