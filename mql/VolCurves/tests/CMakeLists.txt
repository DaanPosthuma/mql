include(CTest)
include(Catch)

add_executable(VolCurvesTests VolCurvesTests.cpp)
target_link_libraries(VolCurvesTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(VolCurvesTests)
