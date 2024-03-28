#pragma once

#include <iostream>

namespace mql {

  class DiscountFactor {
  public:
    double discountFactor;
    DateTime from;
    DateTime to;

    explicit DiscountFactor(double discountFactor, DateTime from, DateTime to) : discountFactor(discountFactor), from(from), to(to) {}

    //explicit operator double() const noexcept { return mDiscountFactor; } // actually need utility function to discount cashflows instead, no need to expose double

  private:
    friend bool operator == (DiscountFactor lhs, DiscountFactor rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& ostr, DiscountFactor discountFactor) noexcept;

    auto tie() const noexcept {
      return std::tie(discountFactor, from, to);
    }

  };

  inline bool operator == (DiscountFactor lhs, DiscountFactor rhs) noexcept {
    return lhs.tie() == rhs.tie();
  }

  inline std::ostream& operator<<(std::ostream& ostr, DiscountFactor discountFactor) noexcept {
    ostr << "df(" << discountFactor.discountFactor << ")";
    return ostr;
  }

}
