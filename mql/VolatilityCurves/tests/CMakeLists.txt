include(CTest)
include(Catch)

add_executable(VolatilityCurvesTests VolatilityCurvesTests.cpp)
target_link_libraries(VolatilityCurvesTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(VolatilityCurvesTests)
