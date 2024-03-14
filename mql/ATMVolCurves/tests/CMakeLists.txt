include(CTest)
include(Catch)

add_executable(ATMVolCurveTests ATMVolCurveTests.cpp)
target_link_libraries(ATMVolCurveTests PRIVATE Catch2::Catch2WithMain mql)

catch_discover_tests(ATMVolCurveTests)
