include(CTest)
include(Catch)

add_executable(VolSurfacesTests VolSurfacesTests.cpp)
target_link_libraries(VolSurfacesTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(VolSurfacesTests)
