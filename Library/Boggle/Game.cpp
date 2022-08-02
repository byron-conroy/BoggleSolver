#include "Game.h"

#include <Dictionary/IDictionary.h>
#include <Boggle/Grid.h>

namespace
{
    void RecursiveSearchForWords(
        const Boggle::Game& game,
        std::unordered_set<std::string>& discoveredWords,
        std::unordered_set<Boggle::GridPosition>& visitedPositions,
        std::string pathSoFar, // @TODO We might want to reserve space in this string somehow
        Boggle::GridPosition nextGridPosition
    )
    {
        auto currentLetter = game.grid[nextGridPosition.x][nextGridPosition.y];

        // We append the current letter to the word
        pathSoFar += currentLetter;

        // If the current letter is a Q we also append a U
        if(currentLetter == 'q')
        {
            pathSoFar += 'u';
        }

        // Check if the word so far is in our dictionary
        auto result = game.dictionary.IsValid(pathSoFar);
        switch (result)
        {
            // If not even a valid prefix we exit immediately
            case IDictionary::LookupResult::InvalidPrefix:
                return;

            // If valid we add it to the dictionary
            case IDictionary::LookupResult::ValidWord:
                discoveredWords.insert(pathSoFar);
                break;
            // We generally want to keep searching
            default:
                break;
        }

        // For each neighbour
        auto neighbours = nextGridPosition.GetNeighbours(game.grid.size());

        for(auto neighbour : neighbours)
        {
            // Check if we have visited it
            auto iterator = visitedPositions.find(neighbour);
            if(iterator != visitedPositions.end())
            {
                // Skip it if we have
                continue;
            }

            // Otherwise we add it to the set of visited positions and recursively search it
            visitedPositions.insert(neighbour);
            RecursiveSearchForWords(
                game,
                discoveredWords,
                visitedPositions,
                pathSoFar,
                neighbour
            );
        }
    }
}

std::unordered_set<std::string> Boggle::DiscoverWords(const Boggle::Game& game)
{
    std::unordered_set<std::string> discoveredWords;

    for(int x = 0; x < RegulationGridSize; ++x)
    {
        for(int y = 0; y < RegulationGridSize; ++y)
        {
            GridPosition startPosition{x, y};
            std::unordered_set<Boggle::GridPosition> visitedPositions{startPosition};

            RecursiveSearchForWords(
                game,
                discoveredWords,
                visitedPositions,
                {},
                startPosition
            );
        }
    }

    return discoveredWords;
}
