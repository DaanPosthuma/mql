include(CTest)
include(Catch)

add_executable(VolatilitySurfacesTests VolatilitySurfacesTests.cpp)
target_link_libraries(VolatilitySurfacesTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(VolatilitySurfacesTests)
