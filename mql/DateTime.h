#pragma once

#include <chrono>
#include <format>

namespace mql {

  class DateTime {
  public:
    DateTime(std::chrono::year_month_day ymd, std::chrono::hours hours = {}, std::chrono::minutes minutes = {}) : mTimePoint(std::chrono::sys_days(ymd) + hours + minutes) {}
    //DateTime(std::chrono::system_clock::time_point timePoint) : mTimePoint(timePoint) {}

  private:

    friend std::ostream& operator << (std::ostream& ostr, DateTime dateTime);
    friend bool operator < (DateTime lhs, DateTime rhs);

    std::chrono::system_clock::time_point mTimePoint;

  };

  inline std::ostream& operator << (std::ostream& ostr, DateTime dateTime) {
    ostr << std::format("{0:%d/%m/%Y} {0:%R}", dateTime.mTimePoint);
    return ostr;
  }

  inline bool operator < (DateTime lhs, DateTime rhs) {
    return lhs.mTimePoint < rhs.mTimePoint;
  }

}
