#pragma once

#include "Currency.h"
#include "Amount.h"
#include "DateTime.h"
#include "CurrencyAmount.h"
#include <ostream>
#include <tuple>

namespace mql {

  class CurrencyAmountDateTime {
  public:
    Currency currency;
    Amount amount;
    DateTime dateTime;

    constexpr explicit CurrencyAmountDateTime(Currency currency, Amount amount, DateTime dateTime) noexcept : currency(currency), amount(amount), dateTime(dateTime) {}
    constexpr explicit CurrencyAmountDateTime(CurrencyAmount currencyAmount, DateTime dateTime) noexcept : currency(currencyAmount.currency), amount(currencyAmount.amount), dateTime(dateTime) {}

    static constexpr size_t tuple_size = 3;

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

    template<>
    struct tuple_element<2> {
      using type = decltype(dateTime);
    };

    template<std::size_t N>
    auto get() const {
      if constexpr (N == 0)
        return currency;
      else if constexpr (N == 1)
        return amount;
      else if constexpr (N == 2)
        return dateTime;
    }

  private:
    friend std::ostream& operator<<(std::ostream& ostr, CurrencyAmountDateTime cadt) noexcept;
    friend bool operator==(CurrencyAmountDateTime lhs, CurrencyAmountDateTime rhs) noexcept;

    auto tie() const noexcept {
      return std::tie(currency, amount, dateTime);
    }
  };

  inline bool operator==(CurrencyAmountDateTime lhs, CurrencyAmountDateTime rhs) noexcept {
    return lhs.tie() == rhs.tie();
  }

  inline CurrencyAmountDateTime operator+(CurrencyAmountDateTime lhs, CurrencyAmountDateTime rhs) {
    if (lhs.currency != rhs.currency) throw std::logic_error("Currencies not the same");
    if (lhs.dateTime != rhs.dateTime) throw std::logic_error("Dates not the same");
    return CurrencyAmountDateTime(lhs.currency, lhs.amount + rhs.amount, lhs.dateTime);
  }

  inline CurrencyAmountDateTime operator-(CurrencyAmountDateTime lhs, CurrencyAmountDateTime rhs) {
    if (lhs.currency != rhs.currency) throw std::logic_error("Currencies not the same");
    if (lhs.dateTime != rhs.dateTime) throw std::logic_error("Dates not the same");
    return CurrencyAmountDateTime(lhs.currency, lhs.amount - rhs.amount, lhs.dateTime);
  }

  inline std::ostream& operator<<(std::ostream& ostr, CurrencyAmountDateTime cadt) noexcept {
    ostr << "CurrencyAmountDateTime(" << cadt.currency << ", " << cadt.amount << ", " << cadt.dateTime << ")";
    return ostr;
  }

}
