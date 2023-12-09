#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"
#include "aoc/string_parser.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <span>

enum class InstructionType
{
    Left,
    Right
};

struct Node
{
    std::string_view left;
    std::string_view right;
};

int64_t getResultOfPartOne(std::span<std::string> input)
{
    int64_t result {};

    std::vector<InstructionType> instructions;
    std::map<std::string_view, Node> nodeMap;
    for (std::string_view line : input)
    {
        if (instructions.empty())
        {
            instructions.reserve(line.size());
            std::ranges::transform(line, std::back_inserter(instructions),
                                   [](char c) { return (c == 'L') ? InstructionType::Left : InstructionType::Right; });
        }
        else if (!line.empty())
        {
            nodeMap.emplace(line.substr(0, 3), Node { line.substr(7, 3), line.substr(12, 3) });
        }
    }

    std::string startStr { nodeMap.begin()->first };
    std::string finishStr { nodeMap.rbegin()->first };

    int64_t stepCount {};
    for (std::string_view currentStr { startStr }; currentStr != finishStr;)
    {
        if (instructions[stepCount % instructions.size()] == InstructionType::Left)
        {
            currentStr = nodeMap.find(currentStr)->second.left;
        }
        else
        {
            currentStr = nodeMap.find(currentStr)->second.right;
        }

        stepCount++;
    }

    result = stepCount;
    return result;
}

int64_t getResultOfPartTwo(std::span<std::string> input)
{
    int64_t result {};

    std::vector<InstructionType> instructions;
    std::map<std::string_view, Node> nodeMap;
    for (std::string_view line : input)
    {
        if (instructions.empty())
        {
            instructions.reserve(line.size());
            std::ranges::transform(line, std::back_inserter(instructions),
                                   [](char c) { return (c == 'L') ? InstructionType::Left : InstructionType::Right; });
        }
        else if (!line.empty())
        {
            nodeMap.emplace(line.substr(0, 3), Node { line.substr(7, 3), line.substr(12, 3) });
        }
    }

    std::vector<std::string_view> currentStrList;
    for (auto &&[key, node] : nodeMap)
    {
        if (key.back() == 'A')
        {
            currentStrList.emplace_back(key);
        }
    }

    std::vector<int64_t> results;
    for (auto &currentStr : currentStrList)
    {
        int64_t stepCount {};
        while (currentStr.back() != 'Z')
        {
            if (instructions[stepCount % instructions.size()] == InstructionType::Left)
            {
                currentStr = nodeMap.find(currentStr)->second.left;
            }
            else
            {
                currentStr = nodeMap.find(currentStr)->second.right;
            }
            stepCount++;
        }

        results.emplace_back(stepCount);
    }

    for (auto val : results)
    {
        if (result == 0)
        {
            result = val;
        }
        else
        {
            result = std::lcm(result, val);
        }
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
