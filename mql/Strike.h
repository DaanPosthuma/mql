#pragma once

#include <ostream>

namespace mql {

  class Strike {
  public:
    explicit constexpr Strike(double strike) : mStrike(strike) {}
  private:
    friend std::ostream& operator<<(std::ostream& ostr, Strike strike) noexcept;
    friend bool operator==(Strike lhs, Strike rhs) noexcept;

    double mStrike;
  };

  inline bool operator==(Strike lhs, Strike rhs) noexcept {
    return lhs.mStrike == rhs.mStrike;
  }

  inline std::ostream& operator<<(std::ostream& ostr, Strike strike) noexcept {
    ostr << "strike(" << strike.mStrike << ")";
    return ostr;
  }

  inline namespace literals {

    consteval Strike operator""_K(long double strike)
    {
      return Strike(static_cast<double>(strike));
    }

  }

}
