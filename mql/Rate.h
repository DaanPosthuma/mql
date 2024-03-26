#pragma once

namespace mql {

  class Rate {
  public:
    explicit Rate(double rate) : mRate(rate) {}

    [[nodiscard]] explicit operator double() const noexcept { return mRate; }

  private:
    double mRate;
  };


}
