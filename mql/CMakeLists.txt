add_library (mql mql.cpp)
target_include_directories(mql PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory (VolatilityCurves)
add_subdirectory (VolatilitySurfaces)
add_subdirectory (Trades)
add_subdirectory (Pricers)
add_subdirectory (tests)
