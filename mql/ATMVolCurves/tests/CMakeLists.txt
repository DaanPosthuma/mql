include(CTest)
include(Catch)

add_executable(ATMVolCurvesTests ATMVolCurvesTests.cpp)
target_link_libraries(ATMVolCurvesTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(ATMVolCurvesTests)
