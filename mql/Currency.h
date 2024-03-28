#pragma once

#include <ostream>

namespace mql {

  class CurrencyPair;

  class Currency {
  public:
    constexpr explicit Currency(std::string currency) noexcept : mCurrency(currency) {}
  private:
    friend std::ostream& operator<<(std::ostream& ostr, Currency const& currency);
    friend std::ostream& operator<<(std::ostream& ostr, CurrencyPair const& currencyPair);
    friend bool operator==(Currency const& lhs, Currency const& rhs);
    friend struct std::hash<mql::Currency>;
    friend struct std::hash<mql::CurrencyPair>;
    
    friend class CurrencyPair;

    std::string mCurrency;

  };

  inline bool operator==(Currency const& lhs, Currency const& rhs) {
    return lhs.mCurrency == rhs.mCurrency;
  }

  inline std::ostream& operator<<(std::ostream& ostr, Currency const& currency) {
    ostr << "currency(" << currency.mCurrency << ")";
    return ostr;
  }

  inline namespace literals {

    constexpr Currency operator""_ccy(char const* currency, std::size_t)
    {
      return Currency(currency);
    }

  }

}

namespace std {

  template <>
  struct hash<mql::Currency> {
    std::size_t operator()(mql::Currency const& currency) const {
      unsigned int h = 2166136261;
      for (char c : currency.mCurrency) {
        h = (h * 16777619) ^ c;
      }
      return h;
    }
  };

}
