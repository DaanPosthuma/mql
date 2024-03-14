include(CTest)
include(Catch)

add_executable(TradesTests TradesTests.cpp)
target_link_libraries(TradesTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(TradesTests)
