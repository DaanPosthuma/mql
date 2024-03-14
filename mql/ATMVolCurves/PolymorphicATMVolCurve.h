#pragma once

#include "ATMVolCurve.h"

namespace mql::atm_vol_curves {

  using mql::DateTime;
  using mql::Volatility;

  template <template <class> class StorageT = std::shared_ptr>
  class PolymorphicATMVolCurve {
  public:

    explicit PolymorphicATMVolCurve(ATMVolCurve auto&& curve)
      : mATMVolCurveHolder(new ATMVolCurveHolder<std::decay_t<decltype(curve)>>(std::move(curve)))
    {}

    PolymorphicATMVolCurve(PolymorphicATMVolCurve const& other) = default;
    PolymorphicATMVolCurve(PolymorphicATMVolCurve&& other) = default;
    PolymorphicATMVolCurve& operator=(PolymorphicATMVolCurve const& other) = default;
    PolymorphicATMVolCurve& operator=(PolymorphicATMVolCurve&& other) = default;

    Volatility getATMVol(DateTime dateTime) const {
      return mATMVolCurveHolder->getATMVol(dateTime);
    }

  private:
    class ATMVolCurveHolderBase {
    public:
      virtual ~ATMVolCurveHolderBase() = default;
      virtual Volatility getATMVol(DateTime dateTime) const = 0;
    };

    template <ATMVolCurve ATMVolCurveT>
    class ATMVolCurveHolder : public ATMVolCurveHolderBase {
    public:
      ATMVolCurveHolder(ATMVolCurveT&& curve) noexcept : mATMVolCurve(std::move(curve)) {}

      virtual Volatility getATMVol(DateTime dateTime) const override {
        return mATMVolCurve.getATMVol(dateTime);
      }

    private:
      ATMVolCurveT mATMVolCurve;
    };

    StorageT<ATMVolCurveHolderBase> mATMVolCurveHolder;
  };

  static_assert(ATMVolCurve<PolymorphicATMVolCurve<>>);

}

