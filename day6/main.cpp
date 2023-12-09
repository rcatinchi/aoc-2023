#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"
#include "aoc/string_parser.hpp"

#include <span>

struct Race
{
    int64_t time;
    int64_t distance;
};

int64_t getResultOfPartOne(std::span<std::string> input)
{
    constexpr std::string_view timeHeader { "Time:" };
    constexpr std::string_view distanceHeader { "Distance:" };

    int64_t result {};

    std::vector<Race> races;
    for (std::string_view line : input)
    {
        if (line.find(timeHeader) != std::string_view::npos)
        {
            const auto times = aoc::split(line.substr(timeHeader.size()), ' ');
            races = std::vector<Race>(times.size());
            for (size_t i { 0 }; i < races.size(); i++)
            {
                races[i].time = aoc::stringTo<int64_t>(times[i]);
            }
        }

        if (line.find(distanceHeader) != std::string_view::npos)
        {
            const auto distances = aoc::split(line.substr(distanceHeader.size()), ' ');
            for (size_t i { 0 }; i < races.size(); i++)
            {
                races[i].distance = aoc::stringTo<int64_t>(distances[i]);
            }
        }
    }

    for (const auto &race : races)
    {
        int64_t winCount {};
        for (int64_t holdTime { 0 }; holdTime < race.time; holdTime++)
        {
            int64_t travelTime { race.time - holdTime };
            int64_t speed { holdTime };

            int64_t travelDistance { speed * travelTime };
            if (travelDistance > race.distance)
            {
                winCount++;
            }
        }

        if (result == 0)
        {
            result = winCount;
        }
        else
        {
            result *= winCount;
        }
    }

    return result;
}

int64_t getResultOfPartTwo(std::span<std::string> input)
{
    constexpr std::string_view timeHeader { "Time:" };
    constexpr std::string_view distanceHeader { "Distance:" };

    int64_t result {};

    Race race;
    for (auto &line : input)
    {
        std::erase(line, ' ');
        if (line.find(timeHeader) != std::string_view::npos)
        {
            race.time = aoc::stringTo<int64_t>(std::string_view(line).substr(timeHeader.size()));
        }

        if (line.find(distanceHeader) != std::string_view::npos)
        {
            race.distance = aoc::stringTo<int64_t>(std::string_view(line).substr(distanceHeader.size()));
        }
    }

    for (int64_t holdTime { 0 }; holdTime < race.time; holdTime++)
    {
        int64_t travelTime { race.time - holdTime };
        int64_t speed { holdTime };

        int64_t travelDistance { speed * travelTime };
        if (travelDistance > race.distance)
        {
            result++;
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
