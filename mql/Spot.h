#pragma once

#include "DateTime.h"
#include <ostream>

namespace mql {

  class Spot {
  public:
    double rate;
    DateTime date;

    explicit constexpr Spot(double rate, DateTime date) : rate(rate), date(date) {}

    static constexpr size_t tuple_size = 2;

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

    template<std::size_t N>
    auto get() const {
      if constexpr (N == 0)
        return rate;
      else if constexpr (N == 1)
        return date;
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
