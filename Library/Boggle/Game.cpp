#include "Game.h"

#include <Dictionary/IDictionary.h>
#include <Boggle/Grid.h>

namespace
{
    struct PathData
    {
        std::unordered_set<Boggle::GridPosition> visitedPositions{};
        std::string pathSoFar{};
    };

    void RecursiveSearchForWords(
        const Boggle::Game& game,
        std::unordered_set<std::string>& discoveredWords,
        Boggle::GridPosition nextGridPosition,
        PathData pathData = {}
    )
    {
        // If we have run out of time we immediately exit
        if(std::chrono::steady_clock::now() > game.deadline)
        {
            return;
        }

        // First thing we do is say we have now visited this grid position
        pathData.visitedPositions.insert(nextGridPosition);

        auto currentLetter = game.grid[nextGridPosition.x][nextGridPosition.y];

        // We append the current letter to the word
        pathData.pathSoFar += currentLetter;

        // If the current letter is a Q we also append a U
        if(currentLetter == 'q')
        {
            pathData.pathSoFar += 'u';
        }

        // Check if the word so far is in our dictionary
        auto result = game.dictionary.IsValid(pathData.pathSoFar);
        switch (result)
        {
            // If not even a valid prefix we exit immediately
            case IDictionary::LookupResult::InvalidPrefix:
                return;

            // If valid we add it to the dictionary
            case IDictionary::LookupResult::ValidWord:
                discoveredWords.insert(pathData.pathSoFar);
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
            auto iterator = pathData.visitedPositions.find(neighbour);
            if(iterator != pathData.visitedPositions.end())
            {
                // Skip it if we have
                continue;
            }

            RecursiveSearchForWords(
                game,
                discoveredWords,
                neighbour,
                pathData
            );
        }
    }
}

std::unordered_set<std::string> Boggle::DiscoverWords(const Boggle::Game& game)
{
    std::unordered_set<std::string> discoveredWords;

    for(int x = 0; x < game.grid.size(); ++x)
    {
        for(int y = 0; y < game.grid.size(); ++y)
        {
            GridPosition startPosition{x, y};
            RecursiveSearchForWords(
                game,
                discoveredWords,
                startPosition
            );
        }
    }

    return discoveredWords;
}
