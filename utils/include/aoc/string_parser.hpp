#ifndef AOC_UTILS_STRING_PARSER_HPP__
#define AOC_UTILS_STRING_PARSER_HPP__

#include <string_view>
#include <vector>

namespace aoc {

inline std::vector<std::string_view> split(std::string_view str, char delimiter)
{
    using namespace std::string_view_literals;
    constexpr std::string_view digits { "0123456789"sv };

    str.remove_prefix(str.find_first_not_of(delimiter));

    std::vector<std::string_view> result;
    size_t numEnd { 0 };
    do
    {
        numEnd = str.find(delimiter);

        result.push_back(str.substr(0, numEnd));

        str.remove_prefix(numEnd);
        str.remove_prefix(str.find_first_not_of(delimiter));
    }
    while (numEnd != std::string_view::npos);

    return result;
}

} // namespace aoc

#endif // AOC_UTILS_STRING_PARSER_HPP__
