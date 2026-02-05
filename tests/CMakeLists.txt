add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE ifcg_core GTest::gtest_main)
add_test(NAME ShaderUnitTests COMMAND tests)