include(CTest)
include(Catch)

add_executable(PricersTest PricersTest.cpp)
target_link_libraries(PricersTest PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(PricersTest)
