#pragma once

#include <ostream>

namespace mql {

  class Volatility {
  public:
    explicit constexpr Volatility(double volatility) : mVolatility(volatility) {}
  private:
    friend std::ostream& operator<<(std::ostream& ostr, Volatility volatility);
    friend bool operator==(Volatility lhs, Volatility rhs);

    double mVolatility;
  };

  inline bool operator==(Volatility lhs, Volatility rhs) {
    return lhs.mVolatility == rhs.mVolatility;
  }

  inline std::ostream& operator<<(std::ostream& ostr, Volatility volatility) {
    ostr << "vol(" << volatility.mVolatility << ")";
    return ostr;
  }

  inline namespace literals {

    consteval Volatility operator""_vol(long double volatility)
    {
      return Volatility(volatility);
    }

  }

}
