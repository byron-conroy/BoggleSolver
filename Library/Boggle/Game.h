#pragma once

#include <array>
#include <chrono>
#include <random>
#include <unordered_set>

#include <Boggle/Grid.h>


class IDictionary;

namespace Boggle
{
    // Represents all information required for a Boggle game
    struct Game
    {
        // Initial grid configuration
        Grid grid;
        // Dictionary to be used
        IDictionary& dictionary;
        // Deadline for when the search must be stopped
        std::chrono::steady_clock::time_point deadline = std::chrono::steady_clock::now() + std::chrono::minutes(3);
    };

    /*
     * Search for words given a Boggle Grid, Dictionary & time up deadline
     */
    std::unordered_set<std::string> DiscoverWords(const Game& game);
}


