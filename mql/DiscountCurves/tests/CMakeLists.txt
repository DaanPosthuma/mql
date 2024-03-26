include(CTest)
include(Catch)

add_executable(DiscountCurvesTests DiscountCurvesTests.cpp)
target_link_libraries(DiscountCurvesTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(DiscountCurvesTests)
