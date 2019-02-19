cmake_minimum_required(VERSION 3.5)

project(WLoopCalculator)
set(EXECUTE_FILE_NAME wloop1x1Calc)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GetGitRevisionDescription)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${EXECUTE_FILE_NAME} src/main.cpp)

set_target_properties(${EXECUTE_FILE_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)


