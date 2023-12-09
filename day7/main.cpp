#include "aoc/filesystem.hpp"
#include "aoc/print.hpp"
#include "aoc/string_conv.hpp"
#include "aoc/string_parser.hpp"

#include <algorithm>
#include <set>
#include <span>

enum class HandType
{
    HighCard,
    Pair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind
};

std::string_view handTypeToStr(HandType type)
{
    switch (type)
    {
        case HandType::HighCard:
            return "HighCard    ";
        case HandType::Pair:
            return "Pair        ";
        case HandType::TwoPair:
            return "TwoPair     ";
        case HandType::ThreeOfAKind:
            return "ThreeOfAKind";
        case HandType::FullHouse:
            return "FullHouse   ";
        case HandType::FourOfAKind:
            return "FourOfAKind ";
        case HandType::FiveOfAKind:
            return "FiveOfAKind ";
    }

    return "";
}

struct Cards
{
    std::string cards;

    auto operator<=>(const Cards &other) const
    {
        return (this->cards == other.cards) ? std::strong_ordering::equal
               : std::ranges::lexicographical_compare(this->cards, other.cards,
                                                      [](char a, char b)
                                                      {
                                                          constexpr std::string_view cards { "23456789TJQKA" };

                                                          return cards.find(a) > cards.find(b);
                                                      })
                   ? std::strong_ordering::greater
                   : std::strong_ordering::less;
    }
};

struct CardsWithJoker
{
    std::string cards;

    auto operator<=>(const CardsWithJoker &other) const
    {
        return (this->cards == other.cards) ? std::strong_ordering::equal
               : std::ranges::lexicographical_compare(this->cards, other.cards,
                                                      [](char a, char b)
                                                      {
                                                          constexpr std::string_view cards { "J23456789TQKA" };

                                                          return cards.find(a) > cards.find(b);
                                                      })
                   ? std::strong_ordering::greater
                   : std::strong_ordering::less;
    }
};

template <typename CardsType>
struct Game
{
    HandType handType;
    CardsType cards;
    int64_t bid;

    auto operator<=>(const Game &) const = default;
};

bool isFiveOfAKind(std::string_view str) { return std::ranges::count(str, str[0]) == 5; };

bool isFourOfAKind(std::string_view str)
{
    return (std::ranges::count(str, str[0]) == 4) || (std::ranges::count(str, str[1]) == 4);
};

bool isThreeOfAKind(std::string_view str)
{
    return (std::ranges::count(str, str[0]) == 3) || (std::ranges::count(str, str[1]) == 3) ||
           (std::ranges::count(str, str[2]) == 3);
};

bool isFullHouse(std::string_view str)
{
    std::set<char> uniqueChars(str.begin(), str.end());
    return (uniqueChars.size() == 2) && (!isFourOfAKind(str));
};

bool isTwoPair(std::string_view str)
{
    std::set<char> uniqueChars(str.begin(), str.end());
    return (uniqueChars.size() == 3) && (!isThreeOfAKind(str));
};

bool isPair(std::string_view str)
{
    std::set<char> uniqueChars(str.begin(), str.end());
    return (uniqueChars.size() == 4);
};

HandType getHandType(std::string_view str)
{
    if (isFiveOfAKind(str))
    {
        return HandType::FiveOfAKind;
    }
    else if (isFourOfAKind(str))
    {
        return HandType::FourOfAKind;
    }
    else if (isFullHouse(str))
    {
        return HandType::FullHouse;
    }
    else if (isThreeOfAKind(str))
    {
        return HandType::ThreeOfAKind;
    }
    else if (isTwoPair(str))
    {
        return HandType::TwoPair;
    }
    else if (isPair(str))
    {
        return HandType::Pair;
    }
    else
    {
        return HandType::HighCard;
    }
}

int64_t getResultOfPartOne(std::span<std::string> input)
{
    int64_t result {};

    std::vector<Game<Cards>> games;
    for (std::string_view line : input)
    {
        const auto game { aoc::split(line, ' ') };
        games.emplace_back(getHandType(game[0]), Cards { std::string(game[0]) }, aoc::stringTo<int64_t>(game[1]));
    }

    std::ranges::sort(games, std::greater<Game<Cards>>());

    for (size_t i { 0 }; i < games.size(); i++)
    {
        result += (games[i].bid * (games.size() - i));
    }

    return result;
}

int64_t getResultOfPartTwo(std::span<std::string> input)
{
    int64_t result {};

    std::vector<Game<CardsWithJoker>> games;
    for (std::string_view line : input)
    {
        auto game { aoc::split(line, ' ') };

        constexpr std::string_view jokers { "AKQT98765432" };
        HandType bestHandType { HandType::HighCard };
        for (char joker : jokers)
        {
            std::string cardsCopy(game[0]);
            std::ranges::replace_if(
                cardsCopy, [](char c) { return c == 'J'; }, joker);
            const HandType jokerHandType { getHandType(cardsCopy) };
            bestHandType = std::max(bestHandType, jokerHandType);
        }

        games.emplace_back(bestHandType, CardsWithJoker { std::string(game[0]) }, aoc::stringTo<int64_t>(game[1]));
    }

    std::ranges::sort(games, std::greater<Game<CardsWithJoker>>());

    for (size_t i { 0 }; i < games.size(); i++)
    {
        result += (games[i].bid * (games.size() - i));
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
