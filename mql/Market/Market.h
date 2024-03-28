#pragma once

#include <unordered_map>
#include <string>
#include "CurrencyPair.h"
#include "Spot.h"
#include "VolatilityCurves/FlatVolatilityCurve.h"
#include "VolatilitySurfaces/FXVolatilitySurface.h"
#include "DiscountCurves/ConstantRateDiscountCurve.h"

namespace mql {

  template<typename T>
  concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
  };

  template <Hashable Key, class Component >
  class MarketComponentHolder {
  public:
    
    Component const& get(Key const& key) const {
      return mStorage.at(key);
    }

    Component& get(Key const& key) {
      return mStorage.at(key);
    }

    void set(Key const& key, Component&& component) {
      mStorage.emplace(key, std::move(component));
    }

  private:
    std::unordered_map<Key, Component> mStorage;
  };

  class FXMarket {
  public:
    
    using Spot = mql::Spot;
    using DiscountCurve = mql::discount_curves::ConstantRateDiscountCurve;
    using VolCurve = mql::volatility_curves::FlatVolatilityCurve;
    using VolSurface = mql::volatility_surfaces::FXVolatilitySurface<VolCurve, DiscountCurve, DiscountCurve>;

    [[nodiscard]] auto const& getSpot(mql::CurrencyPair const& key) const { return mSpots.get(key); }
    [[nodiscard]] auto const& getDiscountCurve(mql::Currency const& key) const { return mDiscountCurves.get(key); }
    [[nodiscard]] auto const& getVolatilitySurface(mql::CurrencyPair const& key) const { return mVolSurfaces.get(key); }

    [[nodiscard]] auto& getSpot(mql::CurrencyPair const& key) { return mSpots.get(key); }
    [[nodiscard]] auto& getDiscountCurve(mql::Currency const& key) { return mDiscountCurves.get(key); }
    [[nodiscard]] auto& getVolatilitySurface(mql::CurrencyPair const& key) { return mVolSurfaces.get(key); }

    void setSpot(mql::CurrencyPair const& key, Spot spot) { return mSpots.set(key, std::move(spot)); }
    void setDiscountCurve(mql::Currency const& key, DiscountCurve discountCurve) { return mDiscountCurves.set(key, std::move(discountCurve)); }
    void setVolatilitySurface(mql::CurrencyPair const& key, VolSurface volatilitySurface) { return mVolSurfaces.set(key, std::move(volatilitySurface)); }

  private:
    
    MarketComponentHolder<mql::CurrencyPair, Spot> mSpots;
    MarketComponentHolder<mql::Currency, DiscountCurve> mDiscountCurves;
    MarketComponentHolder<mql::CurrencyPair, VolSurface> mVolSurfaces;

  };
    
}

