#pragma once

#include "VolatilityCurve.h"

namespace mql::volatility_curves {

  using mql::DateTime;
  using mql::Volatility;

  template <template <class> class StorageT = std::shared_ptr>
  class PolymorphicVolatilityCurve {
  public:

    explicit PolymorphicVolatilityCurve(VolatilityCurve auto&& volatilityCurve)
      : mVolatilityCurveHolder(new VolatilityCurveHolder<std::decay_t<decltype(volatilityCurve)>>(std::move(volatilityCurve)))
    {}

    PolymorphicVolatilityCurve(PolymorphicVolatilityCurve const& other) = default;
    PolymorphicVolatilityCurve(PolymorphicVolatilityCurve&& other) = default;
    PolymorphicVolatilityCurve& operator=(PolymorphicVolatilityCurve const& other) = default;
    PolymorphicVolatilityCurve& operator=(PolymorphicVolatilityCurve&& other) = default;

    [[nodiscard]] Volatility getVolatility(DateTime dateTime) const {
      return mVolatilityCurveHolder->getVolatility(dateTime);
    }

  private:
    class VolatilityCurveHolderBase {
    public:
      virtual ~VolatilityCurveHolderBase() = default;
      virtual Volatility getVolatility(DateTime dateTime) const = 0;
    };

    template <VolatilityCurve VolatilityCurveT>
    class VolatilityCurveHolder : public VolatilityCurveHolderBase {
    public:
      VolatilityCurveHolder(VolatilityCurveT&& volatilityCurve) noexcept : mVolatilityCurve(std::move(volatilityCurve)) {}

      virtual Volatility getVolatility(DateTime dateTime) const override {
        return mVolatilityCurve.getVolatility(dateTime);
      }

    private:
      VolatilityCurveT mVolatilityCurve;
    };

    StorageT<VolatilityCurveHolderBase> mVolatilityCurveHolder;
  };

}

