#pragma once

#include "Currency.h"
#include <ostream>

namespace mql {

  class CurrencyAmount {
  public:
    Currency currency;
    double amount;

    constexpr explicit CurrencyAmount(Currency currency, double amount) noexcept : currency(currency), amount(amount) {}

    // Tuple size specialization
    static constexpr size_t tuple_size = 2;

    // Tuple element specialization
    template<std::size_t N>
    struct tuple_element;

    template<>
    struct tuple_element<0> {
      using type = decltype(currency);
    };

    template<>
    struct tuple_element<1> {
      using type = decltype(amount);
    };

    // Get function
    template<std::size_t N>
    auto get() const {
      if constexpr (N == 0)
        return currency;
      else if constexpr (N == 1)
        return amount;
    }

  private:
    friend std::ostream& operator<<(std::ostream& ostr, CurrencyAmount volatility) noexcept;
    friend bool operator==(CurrencyAmount lhs, CurrencyAmount rhs) noexcept;

    auto tie() const noexcept {
      return std::tie(currency, amount);
    }
  };

  inline bool operator==(CurrencyAmount lhs, CurrencyAmount rhs) noexcept {
    return lhs.tie() == rhs.tie();
  }

  inline std::ostream& operator<<(std::ostream& ostr, CurrencyAmount volatility) noexcept {
    ostr << "CurrencyAmount(" << volatility.currency << volatility.amount << ")";
    return ostr;
  }

  inline namespace literals {

    CurrencyAmount operator""_usd(long double amount) noexcept
    {
      return CurrencyAmount(Currency("USD"), amount);
    }

    CurrencyAmount operator""_usd(unsigned long long amount) noexcept
    {
      return CurrencyAmount(Currency("USD"), static_cast<double>(amount));
    }

  }

}
