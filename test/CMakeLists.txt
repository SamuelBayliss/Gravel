include_directories(${CMAKE_SOURCE_DIR}/src/include)
#SimulateTest SimulateFixture CodegenTest
#add_executable(gravel-testcases Tests ContextTest GenerateFixture ModuleTest StreamTest StateMachineTest)
add_executable(gravel-testcases Tests StateMachineTest)
target_link_libraries(gravel-testcases ${Boost_LIBRARIES})
target_link_libraries(gravel-testcases gravel)

add_subdirectory(pli)