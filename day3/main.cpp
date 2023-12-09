#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"

int getResultOfPartOne(std::vector<std::string> input)
{
    int result {};

    for (size_t lineNum { 1 }; lineNum < input.size() - 1; lineNum++)
    {
        size_t symbolIndex {};
        do
        {
            symbolIndex = input[lineNum].find_first_of("@#$%&*-+=/");
            if (symbolIndex != std::string_view::npos)
            {
                auto findNumAndReplace = [&](std::string &line)
                {
                    bool success = false;

                    size_t digitPos = line.find_first_of("1234567890", symbolIndex - 1);
                    if (digitPos <= symbolIndex + 1)
                    {
                        size_t numBegin { digitPos };
                        do
                        {
                            if (numBegin == 0)
                            {
                                break;
                            }

                            if (!std::isdigit(line[numBegin - 1]))
                            {
                                break;
                            }

                            numBegin--;
                        }
                        while (numBegin > 0);

                        size_t numEnd { digitPos };
                        do
                        {
                            if (numEnd == line.size())
                            {
                                break;
                            }

                            if (!std::isdigit(line[numEnd]))
                            {
                                break;
                            }

                            numEnd++;
                        }
                        while (numEnd <= line.size());

                        int newNum = aoc::stringTo<int>(line.substr(numBegin, numEnd - numBegin));
                        result += newNum;

                        for (size_t i { numBegin }; i < numEnd; i++)
                        {
                            line[i] = '.';
                        }

                        success = true;
                    }

                    return success;
                };

                while (findNumAndReplace(input[lineNum - 1]))
                    ;
                while (findNumAndReplace(input[lineNum]))
                    ;
                while (findNumAndReplace(input[lineNum + 1]))
                    ;

                input[lineNum][symbolIndex] = '.';
            }
        }
        while (symbolIndex != std::string_view::npos);
    }

    return result;
}

int getResultOfPartTwo(std::vector<std::string> input)
{
    int result {};

    for (size_t lineNum { 1 }; lineNum < input.size() - 1; lineNum++)
    {
        std::string_view currentLine { input[lineNum] };

        size_t symbolIndex {};
        do
        {
            symbolIndex = currentLine.find_first_of("*");
            if (symbolIndex != std::string_view::npos)
            {
                std::vector<int> foundNums;

                auto findNumAndReplace = [&](std::string &line)
                {
                    bool success = false;

                    size_t digitPos = line.find_first_of("1234567890", symbolIndex - 1);
                    if (digitPos <= symbolIndex + 1)
                    {
                        size_t numBegin { digitPos };
                        do
                        {
                            if (numBegin == 0)
                            {
                                break;
                            }

                            if (!std::isdigit(line[numBegin - 1]))
                            {
                                break;
                            }

                            numBegin--;
                        }
                        while (numBegin > 0);

                        size_t numEnd { digitPos };
                        do
                        {
                            if (numEnd == line.size())
                            {
                                break;
                            }

                            if (!std::isdigit(line[numEnd]))
                            {
                                break;
                            }

                            numEnd++;
                        }
                        while (numEnd <= line.size());

                        int newNum = aoc::stringTo<int>(line.substr(numBegin, numEnd - numBegin));
                        foundNums.push_back(newNum);

                        for (size_t i { numBegin }; i < numEnd; i++)
                        {
                            line[i] = '.';
                        }
                        success = true;
                    }

                    return success;
                };

                while (findNumAndReplace(input[lineNum - 1]))
                {
                }
                while (findNumAndReplace(input[lineNum]))
                {
                }
                while (findNumAndReplace(input[lineNum + 1]))
                {
                }

                input[lineNum][symbolIndex] = '.';

                if (foundNums.size() == 2)
                {
                    result += (foundNums[0] * foundNums[1]);
                }
            }
        }
        while (symbolIndex != std::string_view::npos);
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
