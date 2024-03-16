add_library (mql mql.cpp "Strike.h" "Currency.h" "CurrencyAmount.h" "CurrencyAmountDateTime.h" "Amount.h")
target_include_directories(mql PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory (VolCurves)
add_subdirectory (VolSurfaces)
add_subdirectory (Trades)
add_subdirectory (Pricers)
add_subdirectory (tests)
