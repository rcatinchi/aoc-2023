#ifndef AOC_UTILS_STRING_CONV_HPP__
#define AOC_UTILS_STRING_CONV_HPP__

#include <charconv>
#include <string_view>

namespace aoc {

template <typename T>
inline T stringTo(std::string_view str)
{
    T value {};
    std::from_chars(str.begin(), str.end(), value);
    return value;
}

} // namespace aoc

#endif // AOC_UTILS_STRING_CONV_HPP__
