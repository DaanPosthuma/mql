#pragma once

#include <ostream>

namespace mql {

  class Amount {
  public:
    constexpr Amount(double amount) noexcept : mAmount(amount) {}
  private:
    friend std::ostream& operator<<(std::ostream& ostr, Amount amount);
    friend bool operator==(Amount lhs, Amount rhs);

    double mAmount;

  };

  inline bool operator==(Amount lhs, Amount rhs) {
    return lhs.mAmount == rhs.mAmount;
  }

  inline std::ostream& operator<<(std::ostream& ostr, Amount amount) {
    ostr << "amount(" << amount.mAmount << ")";
    return ostr;
  }

}
