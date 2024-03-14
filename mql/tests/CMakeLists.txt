include(CTest)
include(Catch)

add_executable(BasicTests BasicTests.cpp)
target_link_libraries(BasicTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(BasicTests)
