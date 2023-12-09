add_executable(aoc-2023-day3 main.cpp)
target_compile_features(aoc-2023-day3 PRIVATE cxx_std_20)
target_compile_options(aoc-2023-day3 PRIVATE -Wall)
target_link_libraries(aoc-2023-day3 PRIVATE aoc-utils)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
