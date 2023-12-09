#ifndef AOC_UTILS_FILESYSTEM_HPP__
#define AOC_UTILS_FILESYSTEM_HPP__

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace aoc {

inline std::vector<std::string> readInput(const std::filesystem::path &path)
{
    std::ifstream fileStream { path.native() };

    if (!fileStream.is_open())
    {
        using namespace std::string_literals;
        throw std::filesystem::filesystem_error("Could not open file "s + path.native(),
                                                std::error_code { errno, std::generic_category() });
    }

    std::vector<std::string> input;
    std::string line;
    while (std::getline(fileStream, line))
    {
        input.push_back(std::move(line));
    }

    return input;
}

} // namespace aoc

#endif // AOC_UTILS_FILESYSTEM_HPP__
