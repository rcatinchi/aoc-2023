add_executable(aoc-2023-1 main.cpp)
target_compile_features(aoc-2023-1 PRIVATE cxx_std_20)
target_compile_options(aoc-2023-1 PRIVATE -Wall)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
