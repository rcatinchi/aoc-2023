#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"
#include "aoc/string_parser.hpp"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iterator>
#include <map>
#include <numeric>
#include <span>
#include <vector>

int64_t getResultOfPartOne(std::span<std::string> input)
{
    int64_t result {};

    for (std::string_view line : input)
    {
        std::vector<std::vector<int64_t>> data;

        auto &dataset = data.emplace_back();
        std::ranges::transform(aoc::split(line, ' '), std::back_inserter(dataset), aoc::stringTo<int64_t>);

        for (;;)
        {
            auto &diff = data.emplace_back();
            auto prev = data.end() - 2;
            std::adjacent_difference(prev->begin(), prev->end(), std::back_inserter(diff));
            diff.erase(diff.begin());

            if (std::ranges::all_of(diff, [](auto val) { return val == 0; }))
            {
                break;
            }
        }

        for (auto it { data.rbegin() + 1 }; it != data.rend(); it++)
        {
            it->emplace_back(it->back() + std::prev(it)->back());
        }

        result += data.begin()->back();
    }

    return result;
}

int64_t getResultOfPartTwo(std::span<std::string> input)
{
    int64_t result {};

    for (std::string_view line : input)
    {
        std::vector<std::vector<int64_t>> data;

        auto &dataset = data.emplace_back();
        std::ranges::transform(aoc::split(line, ' '), std::back_inserter(dataset), aoc::stringTo<int64_t>);

        for (;;)
        {
            auto &diff = data.emplace_back();
            auto prev = data.end() - 2;
            std::adjacent_difference(prev->begin(), prev->end(), std::back_inserter(diff));
            diff.erase(diff.begin());

            if (std::ranges::all_of(diff, [](auto val) { return val == 0; }))
            {
                break;
            }
        }

        for (auto it { data.rbegin() + 1 }; it != data.rend(); it++)
        {
            it->insert(it->begin(), it->front() - std::prev(it)->front());
        }

        result += data.begin()->front();
    }

    return result;
}

int main()
{
    auto input = aoc::readInput(std::filesystem::current_path() / "input.txt");

    aoc::println("Result Part One: ", getResultOfPartOne(input));
    aoc::println("Result Part Two: ", getResultOfPartTwo(input));

    return 0;
}
