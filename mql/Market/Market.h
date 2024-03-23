#pragma once

#include <unordered_map>
#include <string>
#include "CurrencyPair.h"

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

  template <template <class> class KeyTypeMapping, class... Components>
  class Market : private MarketComponentHolder<typename KeyTypeMapping<Components>::KeyT, Components>... {
  public:
    
    template <class ComponentT>
    auto const& get(KeyTypeMapping<ComponentT>::KeyT const& key) const {
      return MarketComponentHolder<KeyTypeMapping<ComponentT>::KeyT, ComponentT>::get(key);
    }

    template <class ComponentT>
    auto& get(KeyTypeMapping<ComponentT>::KeyT const& key) {
      return MarketComponentHolder<KeyTypeMapping<ComponentT>::KeyT, ComponentT>::get(key);
    }
    
    template <class ComponentT>
    void set(KeyTypeMapping<ComponentT>::KeyT const& key, ComponentT component) {
      MarketComponentHolder<KeyTypeMapping<ComponentT>::KeyT, ComponentT>::set(key, std::move(component));
    }

  };

  inline namespace fx_market {

    template <class ValueT>
    struct KeyTypeMapping;

    template <>
    struct KeyTypeMapping<mql::Spot> {
      using KeyT = mql::CurrencyPair;
    };

    template <>
    struct KeyTypeMapping<mql::volatility_surfaces::FXVolatilitySurface<mql::volatility_curves::FlatVolatilityCurve>> {
      using KeyT = mql::CurrencyPair;
    };

    using SpotT = mql::Spot;
    using VolCurveT = mql::volatility_curves::FlatVolatilityCurve;
    using VolSurfT = mql::volatility_surfaces::FXVolatilitySurface<VolCurveT>;

    class FXMarket : private Market<KeyTypeMapping,
      SpotT,
      VolSurfT> {
    public:

      [[nodiscard]] SpotT const& GetSpot(KeyTypeMapping<SpotT>::KeyT const& key) const { return get<mql::Spot>(key); }
      [[nodiscard]] VolSurfT const& GetVolatilitySurface(KeyTypeMapping<VolSurfT>::KeyT const& key) const { return get<VolSurfT>(key); }

      [[nodiscard]] SpotT& GetSpot(KeyTypeMapping<SpotT>::KeyT const& key) { return get<mql::Spot>(key); }
      [[nodiscard]] VolSurfT& GetVolatilitySurface(KeyTypeMapping<VolSurfT>::KeyT const& key) { return get<VolSurfT>(key); }

      void SetSpot(KeyTypeMapping<SpotT>::KeyT const& key, SpotT spot) { return set<SpotT>(key, spot); }
      void SetVolatilitySurface(KeyTypeMapping<VolSurfT>::KeyT const& key, VolSurfT volatilitySurface) { return set<VolSurfT>(key, volatilitySurface); }

    };
  }
  
}

