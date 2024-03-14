#pragma once

#include <ostream>

namespace mql {

  class Strike {
  public:
    explicit constexpr Strike(double strike) : mStrike(strike) {}
  private:
    friend std::ostream& operator<<(std::ostream& ostr, Strike volatility);
    friend bool operator==(Strike lhs, Strike rhs);

    double mStrike;
  };

  inline bool operator==(Strike lhs, Strike rhs) {
    return lhs.mStrike == rhs.mStrike;
  }

  inline std::ostream& operator<<(std::ostream& ostr, Strike volatility) {
    ostr << "strike(" << volatility.mStrike << ")";
    return ostr;
  }

  inline namespace literals {

    constexpr Strike operator""_K(long double strike)
    {
      return Strike(strike);
    }

  }

}
