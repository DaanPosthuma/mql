#pragma once

#include <iostream>

namespace mql {

  class DiscountFactor {
  public:
    explicit DiscountFactor(double discountFactor) : mDiscountFactor(discountFactor) {}

  private:
    friend bool operator == (DiscountFactor lhs, DiscountFactor rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& ostr, DiscountFactor discountFactor) noexcept;

    double mDiscountFactor;
    // could add dates ...
  };

  inline bool operator == (DiscountFactor lhs, DiscountFactor rhs) noexcept {
    return lhs.mDiscountFactor == rhs.mDiscountFactor;
  }

  inline std::ostream& operator<<(std::ostream& ostr, DiscountFactor discountFactor) noexcept {
    ostr << "df(" << discountFactor.mDiscountFactor << ")";
    return ostr;
  }

}
