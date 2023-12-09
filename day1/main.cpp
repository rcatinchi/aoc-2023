#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"

#include <algorithm>
#include <array>

int getResultOfPartOne(const std::vector<std::string> &input)
{
    int result {};

    for (std::string_view line : input)
    {
        const int firstDigit { aoc::stringTo<int>(line.substr(line.find_first_of("123456789"), 1)) };
        const int lastDigit { aoc::stringTo<int>(line.substr(line.find_last_of("123456789"), 1)) };
        result += firstDigit * 10;
        result += lastDigit;
    }

    return result;
}

int getResultOfPartTwo(const std::vector<std::string> &input)
{
    int result {};

    for (std::string_view line : input)
    {
        struct Digit
        {
            size_t pos { std::string_view::npos };
            int value { -1 };
        };

        Digit firstDigit;
        firstDigit.pos = line.find_first_of("123456789");
        firstDigit.value = aoc::stringTo<int>(line.substr(firstDigit.pos, 1));

        Digit lastDigit;
        lastDigit.pos = line.find_last_of("123456789");
        lastDigit.value = aoc::stringTo<int>(line.substr(lastDigit.pos, 1));

        constexpr std::array<std::string_view, 9> digitsInLetters { "one", "two",   "three", "four", "five",
                                                                    "six", "seven", "eight", "nine" };
        for (size_t i = 0; i < digitsInLetters.size(); i++)
        {
            const auto firstDigitInLettersStr = std::ranges::search(line, digitsInLetters[i]);
            if (!firstDigitInLettersStr.empty())
            {
                size_t pos = std::distance(line.begin(), firstDigitInLettersStr.begin());
                if (pos < firstDigit.pos)
                {
                    firstDigit.pos = pos;
                    firstDigit.value = i + 1;
                }
            }

            const auto lastDigitInLettersStr = std::ranges::find_end(line, digitsInLetters[i]);
            if (!lastDigitInLettersStr.empty())
            {
                size_t pos = std::distance(line.begin(), lastDigitInLettersStr.begin());
                if ((pos > lastDigit.pos) && (lastDigit.pos != std::string_view::npos))
                {
                    lastDigit.pos = pos;
                    lastDigit.value = i + 1;
                }
            }
        }

        result += firstDigit.value * 10;
        result += lastDigit.value;
    }

    return result;
}

int main()
{
    const auto input { aoc::readInput(std::filesystem::current_path() / "input.txt") };

    aoc::println("Result Part One: ", getResultOfPartOne(input));
    aoc::println("Result Part Two: ", getResultOfPartTwo(input));

    return 0;
}
