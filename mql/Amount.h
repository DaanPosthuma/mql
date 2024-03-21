#pragma once

#include <ostream>

namespace mql {

  class Amount {
  public:
    constexpr Amount(double amount) noexcept : mAmount(amount) {}

  private:
    friend std::ostream& operator<<(std::ostream& ostr, Amount amount);
    friend bool operator==(Amount lhs, Amount rhs);
    friend constexpr Amount operator * (Amount amount, double multiplier) noexcept;
    friend constexpr Amount operator + (Amount lhs, Amount rhs) noexcept;
    friend constexpr Amount operator - (Amount lhs, Amount rhs) noexcept;

    static constexpr double EqualityTolerance = 0.000001;

    double mAmount;

  };

  inline bool operator==(Amount lhs, Amount rhs) {
    return std::abs(lhs.mAmount - rhs.mAmount) < Amount::EqualityTolerance;
  }

  constexpr Amount operator * (Amount amount, double multiplier) noexcept {
    return Amount(amount.mAmount * multiplier);
  }

  constexpr Amount operator + (Amount lhs, Amount rhs) noexcept {
    return Amount(lhs.mAmount + rhs.mAmount);
  }

  constexpr Amount operator - (Amount lhs, Amount rhs) noexcept {
    return Amount(lhs.mAmount - rhs.mAmount);
  }

  inline std::ostream& operator<<(std::ostream& ostr, Amount amount) {
    ostr << "amount(" << amount.mAmount << ")";
    return ostr;
  }

}
