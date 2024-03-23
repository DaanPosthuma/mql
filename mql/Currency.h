#pragma once

#include <ostream>

namespace mql {

  class CurrencyPair;

  class Currency {
  public:
    constexpr explicit Currency(std::string currency) noexcept : mCurrency(currency) {}
  private:
    friend std::ostream& operator<<(std::ostream& ostr, Currency currency);
    friend bool operator==(Currency lhs, Currency rhs);
    friend class CurrencyPair;
    friend struct std::hash<mql::Currency>;

    std::string mCurrency;

  };

  inline bool operator==(Currency lhs, Currency rhs) {
    return lhs.mCurrency == rhs.mCurrency;
  }

  inline std::ostream& operator<<(std::ostream& ostr, Currency currency) {
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
    std::size_t operator()(mql::Currency currency) const {
      return std::hash<std::string>{}(currency.mCurrency);
    }
  };

}
