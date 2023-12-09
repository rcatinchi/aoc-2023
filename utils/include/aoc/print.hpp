#ifndef AOC_UTILS_PRINT_HPP__
#define AOC_UTILS_PRINT_HPP__

#include <iostream>

namespace aoc {

inline void println() { std::cout << '\n'; }

inline void println(auto &&...args)
{
    (std::cout << ... << std::forward<decltype(args)>(args));
    std::cout << '\n';
}

} // namespace aoc

#endif // AOC_UTILS_PRINT_HPP__
