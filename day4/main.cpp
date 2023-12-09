#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"

#include <deque>
#include <set>
#include <span>

int getResultOfPartOne(std::span<std::string> input)
{
    int result {};

    for (std::string_view line : input)
    {
        std::string_view winningNumsStr { line.substr(0, line.find('|')).substr(line.find(':') + 1) };
        winningNumsStr.remove_prefix(winningNumsStr.find_first_of("0123456789"));
        winningNumsStr.remove_suffix(winningNumsStr.size() - winningNumsStr.find_last_not_of("0123456789"));

        std::set<int> winningNums;
        size_t numEnd { 0 };
        do
        {
            numEnd = winningNumsStr.find(' ');

            const int num { aoc::stringTo<int>(winningNumsStr.substr(0, numEnd)) };

            winningNums.emplace(num);

            winningNumsStr.remove_prefix(numEnd);
            winningNumsStr.remove_prefix(winningNumsStr.find_first_of("0123456789"));
        }
        while (numEnd != std::string_view::npos);

        std::string_view myNumsStr { line.substr(line.find('|') + 1) };
        myNumsStr.remove_prefix(myNumsStr.find_first_of("0123456789"));

        int points {};
        numEnd = 0;
        do
        {
            numEnd = myNumsStr.find(' ');

            const int num { aoc::stringTo<int>(myNumsStr.substr(0, numEnd)) };

            if (winningNums.find(num) != winningNums.end())
            {
                if (points != 0)
                {
                    points *= 2;
                }
                else
                {
                    points = 1;
                }
            }

            myNumsStr.remove_prefix(numEnd);
            myNumsStr.remove_prefix(myNumsStr.find_first_of("0123456789"));
        }
        while (numEnd != std::string_view::npos);

        result += points;
    }

    return result;
}

int getResultOfPartTwo(std::span<std::string> input)
{
    int result {};
    std::deque<int> copyQueue;

    for (std::string_view line : input)
    {
        std::string_view winningNumsStr { line.substr(0, line.find('|')).substr(line.find(':') + 1) };
        winningNumsStr.remove_prefix(winningNumsStr.find_first_of("0123456789"));
        winningNumsStr.remove_suffix(winningNumsStr.size() - winningNumsStr.find_last_not_of("0123456789"));

        std::set<int> winningNums;
        size_t numEnd { 0 };
        do
        {
            numEnd = winningNumsStr.find(' ');

            const int num { aoc::stringTo<int>(winningNumsStr.substr(0, numEnd)) };

            winningNums.emplace(num);

            winningNumsStr.remove_prefix(numEnd);
            winningNumsStr.remove_prefix(winningNumsStr.find_first_of("0123456789"));
        }
        while (numEnd != std::string_view::npos);

        std::string_view myNumsStr { line.substr(line.find('|') + 1) };
        myNumsStr.remove_prefix(myNumsStr.find_first_of("0123456789"));

        int copyCount {};
        if (!copyQueue.empty())
        {
            copyCount = copyQueue.front();
            copyQueue.pop_front();
        }
        result += (1 + copyCount);

        size_t count { 0 };
        numEnd = 0;
        do
        {
            numEnd = myNumsStr.find(' ');

            const int num { aoc::stringTo<int>(myNumsStr.substr(0, numEnd)) };

            if (winningNums.find(num) != winningNums.end())
            {
                if (count < copyQueue.size())
                {
                    copyQueue[count] += (1 + copyCount);
                }
                else
                {
                    copyQueue.push_back(1 + copyCount);
                }
                count++;
            }

            myNumsStr.remove_prefix(numEnd);
            myNumsStr.remove_prefix(myNumsStr.find_first_of("0123456789"));
        }
        while (numEnd != std::string_view::npos);
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
