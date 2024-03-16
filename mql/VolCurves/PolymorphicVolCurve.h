#pragma once

#include "VolCurve.h"

namespace mql::vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  template <template <class> class StorageT = std::shared_ptr>
  class PolymorphicVolCurve {
  public:

    explicit PolymorphicVolCurve(VolCurve auto&& curve)
      : mVolCurveHolder(new VolCurveHolder<std::decay_t<decltype(curve)>>(std::move(curve)))
    {}

    PolymorphicVolCurve(PolymorphicVolCurve const& other) = default;
    PolymorphicVolCurve(PolymorphicVolCurve&& other) = default;
    PolymorphicVolCurve& operator=(PolymorphicVolCurve const& other) = default;
    PolymorphicVolCurve& operator=(PolymorphicVolCurve&& other) = default;

    Volatility getVol(DateTime dateTime) const {
      return mVolCurveHolder->getVol(dateTime);
    }

  private:
    class VolCurveHolderBase {
    public:
      virtual ~VolCurveHolderBase() = default;
      virtual Volatility getVol(DateTime dateTime) const = 0;
    };

    template <VolCurve VolCurveT>
    class VolCurveHolder : public VolCurveHolderBase {
    public:
      VolCurveHolder(VolCurveT&& curve) noexcept : mVolCurve(std::move(curve)) {}

      virtual Volatility getVol(DateTime dateTime) const override {
        return mVolCurve.getVol(dateTime);
      }

    private:
      VolCurveT mVolCurve;
    };

    StorageT<VolCurveHolderBase> mVolCurveHolder;
  };

  static_assert(VolCurve<PolymorphicVolCurve<>>);

}

