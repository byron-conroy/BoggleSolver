#pragma once

#include <array>
#include <random>
#include <unordered_set>

#include <Boggle/Grid.h>


class IDictionary;

namespace Boggle
{
    struct Game
    {
        Grid grid;
        IDictionary& dictionary;
    };


    // @TODO Add a time limit parameter
    std::unordered_set<std::string> DiscoverWords(const Game& game);
}


