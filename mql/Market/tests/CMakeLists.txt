include(CTest)
include(Catch)

add_executable(MarketTest MarketTest.cpp)
target_link_libraries(MarketTest PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(MarketTest)
