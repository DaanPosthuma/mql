include(CTest)
include(Catch)

add_executable(VolSurfaceTests VolSurfaceTests.cpp)
target_link_libraries(VolSurfaceTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(VolSurfaceTests)
