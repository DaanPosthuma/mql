add_library (mql mql.cpp "Strike.h")
target_include_directories(mql PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory (ATMVolCurves)
add_subdirectory (VolSurfaces)
