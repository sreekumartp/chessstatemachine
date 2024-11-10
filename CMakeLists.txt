cmake_minimum_required(VERSION 3.10)

# Set the project name
project(chessstatepmachine)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Ensure NDEBUG is not defined in Debug builds
add_compile_options($<$<CONFIG:Debug>:-UNDEBUG>)

# Configure compiler flags for Debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g")


include(CTest)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(FetchContent)

# Download GTest if not present
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
)

# Add GTest to the build
FetchContent_MakeAvailable(googletest)

message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

# Set the cppcheck path
set(CMAKE_CXX_CPPCHECK "cppcheck;--enable=all;--language=c++;--suppress=missingIncludeSystem;--suppress=unusedFunction")

# Include directories if necessary
include_directories(include)
# Specify a directory for cpp files
#file(GLOB SOURCES "src/statemachine.cpp, src/main.cpp")
add_library(libstatemachine src/statemachine.cpp)
add_executable(sm src/main_statemachine.cpp)
target_link_libraries(sm libstatemachine)

# Disable -Werror for Google Test
set_target_properties(gtest PROPERTIES COMPILE_FLAGS "-Wno-error")
set_target_properties(gtest PROPERTIES gtest_death_test_style "threadsafe")

# Enable testing
enable_testing()
# Find GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(test_statemachine test/test_statemachine.cpp src/statemachine.cpp)

# Link the test executable with the main project and GoogleTest
target_link_libraries(test_statemachine ${GTEST_LIBRARIES} gmock_main pthread)

# Add the test to CTest
add_test(NAME GameStateMachineTest COMMAND test_statemachine --gtest_output=json:statemachine_report.json)