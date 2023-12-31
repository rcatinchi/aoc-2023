#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"

int getResultOfPartOne(const std::vector<std::string> &input)
{
    int result {};

    for (std::string_view line : input)
    {
        constexpr int maxRedCubes { 12 };
        constexpr int maxGreenCubes { 13 };
        constexpr int maxBlueCubes { 14 };

        const size_t gameStrSize { std::string_view("Game ").size() };
        const size_t semiColonPos { line.find(':') };

        const int gameNumber { aoc::stringTo<int>(line.substr(gameStrSize, semiColonPos - gameStrSize)) };

        line.remove_prefix(semiColonPos + 2);

        bool addToCount { true };
        size_t setSeparatorPos { 0 };
        do
        {
            setSeparatorPos = line.find_first_of(",;");
            std::string_view set { line.substr(0, setSeparatorPos) };

            const size_t spaceSeparatorPos { set.find(' ') };

            const int count { aoc::stringTo<int>(set.substr(0, spaceSeparatorPos)) };
            std::string_view colorStr { set.substr(spaceSeparatorPos + 1) };

            const int maxCount = [&]()
            {
                if (colorStr == "red")
                {
                    return maxRedCubes;
                }
                if (colorStr == "blue")
                {
                    return maxBlueCubes;
                }
                if (colorStr == "green")
                {
                    return maxGreenCubes;
                }

                return 0;
            }();

            if (count > maxCount)
            {
                addToCount = false;
                break;
            }

            line.remove_prefix(setSeparatorPos + 2);
        }
        while (setSeparatorPos != std::string::npos);

        if (addToCount)
        {
            result += gameNumber;
        }
    }

    return result;
}

int getResultOfPartTwo(const std::vector<std::string> &input)
{
    int result {};

    for (std::string_view line : input)
    {
        const size_t semiColonPos { line.find(':') };

        line.remove_prefix(semiColonPos + 2);

        int maxRedCubes {};
        int maxBlueCubes {};
        int maxGreenCubes {};
        size_t setSeparatorPos { 0 };
        do
        {
            setSeparatorPos = line.find_first_of(",;");
            std::string_view set { line.substr(0, setSeparatorPos) };

            const size_t spaceSeparatorPos { set.find(' ') };

            const int count { aoc::stringTo<int>(set.substr(0, spaceSeparatorPos)) };
            std::string_view colorStr { set.substr(spaceSeparatorPos + 1) };

            if (colorStr == "red")
            {
                maxRedCubes = std::max(count, maxRedCubes);
            }
            if (colorStr == "blue")
            {
                maxBlueCubes = std::max(count, maxBlueCubes);
            }
            if (colorStr == "green")
            {
                maxGreenCubes = std::max(count, maxGreenCubes);
            }

            line.remove_prefix(setSeparatorPos + 2);
        }
        while (setSeparatorPos != std::string::npos);

        result += (maxRedCubes * maxBlueCubes * maxGreenCubes);
    }

    return result;
}

int main()
{
    const auto input = aoc::readInput(std::filesystem::current_path() / "input.txt");

    aoc::println("Result Part One: ", getResultOfPartOne(input));
    aoc::println("Result Part Two: ", getResultOfPartTwo(input));

    return 0;
}
