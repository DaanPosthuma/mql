#pragma once

#include "DateTime.h"
#include "CurrencyPair.h"
#include <ostream>

namespace mql {

  class Spot {
  public:
    double rate;
    DateTime date;
    CurrencyPair currencyPair;

    explicit constexpr Spot(double rate, DateTime date, CurrencyPair currencyPair) : rate(rate), date(date), currencyPair(currencyPair) {}

    static constexpr size_t tuple_size = 3;

    template<std::size_t N>
    struct tuple_element;

    template<>
    struct tuple_element<0> {
      using type = decltype(rate);
    };

    template<>
    struct tuple_element<1> {
      using type = decltype(date);
    };

    template<>
    struct tuple_element<2> {
      using type = decltype(currencyPair);
    };

    template<std::size_t N>
    auto get() const {
      if constexpr (N == 0)
        return rate;
      else if constexpr (N == 1)
        return date;
      else if constexpr (N == 2)
        return currencyPair;
    }

  private:
    friend std::ostream& operator<<(std::ostream& ostr, Spot spot);
    friend bool operator==(Spot lhs, Spot rhs);

    auto constexpr tie() const noexcept { return std::tie(rate, date); }
  };

  inline bool operator==(Spot lhs, Spot rhs) {
    return lhs.tie()  == rhs.tie();
  }

  inline std::ostream& operator<<(std::ostream& ostr, Spot spot) {
    ostr << "spot(" << spot.rate << ", " << spot.date << ")";
    return ostr;
  }

}
