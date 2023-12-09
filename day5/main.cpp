#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"
#include "aoc/string_parser.hpp"

#include <algorithm>
#include <ranges>
#include <span>

struct Seed
{
    int64_t start;
    int64_t length;
};

struct Range
{
    int64_t destination;
    int64_t source;
    int64_t length;
};

enum class Stage
{
    Seed,
    Soil,
    Fertilizer,
    Water,
    Light,
    Temperature,
    Humidity,
    Location
};

int64_t getResultOfPartOne(std::span<std::string> input)
{
    constexpr std::string_view seedsHeader { "seeds: " };
    constexpr std::string_view digits { "0123456789" };

    int64_t result {};

    auto processSeeds = [](std::span<int64_t> seeds, const std::span<Range> ranges)
    {
        for (auto &seed : seeds)
        {
            for (const auto &range : ranges)
            {
                if ((range.source <= seed) && (seed < (range.source + range.length)))
                {
                    seed += (range.destination - range.source);
                    break;
                }
            }
        }
    };

    auto processStage = [&](std::string_view line, std::span<int64_t> seeds, std::vector<Range> &ranges)
    {
        if (line.find_first_of(digits) != std::string_view::npos)
        {
            const auto rangeStr { aoc::split(line, ' ') };
            ranges.emplace_back(aoc::stringTo<int64_t>(rangeStr[0]), aoc::stringTo<int64_t>(rangeStr[1]),
                                aoc::stringTo<int64_t>(rangeStr[2]));
        }

        if (line.find(':') != std::string_view::npos)
        {
            processSeeds(seeds, ranges);
            return true;
        }

        return false;
    };

    Stage stage { Stage::Seed };
    std::vector<int64_t> seeds;
    std::vector<Range> ranges;
    for (std::string_view line : input)
    {
        switch (stage)
        {
            case Stage::Seed:
            {
                if (seeds.empty())
                {
                    const auto seedsStr { aoc::split(line.substr(seedsHeader.size()), ' ') };
                    std::ranges::transform(seedsStr, std::back_inserter(seeds),
                                           [](auto str) { return aoc::stringTo<int64_t>(str); });
                }

                if (line.find("seed-to-soil") != std::string_view::npos)
                {
                    stage = Stage::Soil;
                }
                break;
            }
            case Stage::Soil:
            {
                if (processStage(line, seeds, ranges))
                {
                    ranges.clear();
                    stage = Stage::Fertilizer;
                }
                break;
            }
            case Stage::Fertilizer:
            {
                if (processStage(line, seeds, ranges))
                {
                    ranges.clear();
                    stage = Stage::Water;
                }
                break;
            }
            case Stage::Water:
            {
                if (processStage(line, seeds, ranges))
                {
                    ranges.clear();
                    stage = Stage::Light;
                }
                break;
            }
            case Stage::Light:
            {
                if (processStage(line, seeds, ranges))
                {
                    ranges.clear();
                    stage = Stage::Temperature;
                }
                break;
            }
            case Stage::Temperature:
            {
                if (processStage(line, seeds, ranges))
                {
                    ranges.clear();
                    stage = Stage::Humidity;
                }
                break;
            }
            case Stage::Humidity:
            {
                if (processStage(line, seeds, ranges))
                {
                    ranges.clear();
                    stage = Stage::Location;
                }
                break;
            }
            case Stage::Location:
            {
                processStage(line, seeds, ranges);
                break;
            }
        }
    }

    processSeeds(seeds, ranges);
    result = std::ranges::min(seeds);

    return result;
}

int64_t getResultOfPartTwo(std::span<std::string> input)
{
    constexpr std::string_view seedsHeader { "seeds: " };
    constexpr std::string_view digits { "0123456789" };

    int64_t result {};

    struct SeedRange
    {
        int64_t start;
        int64_t length;
    };
    struct MapRange
    {
        int64_t destination;
        int64_t source;
        int64_t length;
    };

    std::vector<SeedRange> seedRanges;
    std::array<std::vector<MapRange>, 7> mapRanges;
    bool firstRangeHeaderPassed { false };
    size_t mapRangeIndex { 0 };

    for (std::string_view line : input)
    {
        if (line.find(seedsHeader) != std::string_view::npos)
        {
            const auto seedsStr { aoc::split(line.substr(seedsHeader.size()), ' ') };

            for (size_t i { 0 }; i < seedsStr.size(); i += 2)
            {
                seedRanges.emplace_back(aoc::stringTo<int64_t>(seedsStr[i]), aoc::stringTo<int64_t>(seedsStr[i + 1]));
            }
        }
        else if (firstRangeHeaderPassed == false)
        {
            firstRangeHeaderPassed = (line.find(':') != std::string_view::npos);
        }
        else
        {
            if (line.find(':') != std::string_view::npos)
            {
                mapRangeIndex++;
                continue;
            }
            if (line.find_first_of(digits) != std::string_view::npos)
            {
                const auto rangeStr { aoc::split(line, ' ') };
                mapRanges[mapRangeIndex].emplace_back(aoc::stringTo<int64_t>(rangeStr[0]),
                                                      aoc::stringTo<int64_t>(rangeStr[1]),
                                                      aoc::stringTo<int64_t>(rangeStr[2]));
            }
        }
    }

    for (; result <= std::numeric_limits<int64_t>::max(); result++)
    {
        int64_t location { result };

        for (const auto &ranges : mapRanges | std::views::reverse)
        {
            for (const auto &range : ranges)
            {
                if ((range.destination <= location) && (location < (range.destination + range.length)))
                {
                    location += (range.source - range.destination);
                    break;
                }
            }
        }

        for (const auto &seedRange : seedRanges)
        {
            if ((seedRange.start <= location) && (location < (seedRange.start + seedRange.length)))
            {
                return result;
            }
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
