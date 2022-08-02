#include "Grid.h"

#include <Boggle/IRandomCharacterSequence.h>

Boggle::Grid Boggle::GenerateGrid(IRandomCharacterSequence& randomCharacterSequence, size_t GridSize)
{
    Grid returnValue(GridSize, std::vector<char>(GridSize, 'a'));

    for(int x = 0; x < RegulationGridSize; ++x)
    {
        for(int y = 0; y < RegulationGridSize; ++y)
        {
            returnValue[x][y] = randomCharacterSequence.GetNext();
        }
    }

    return returnValue;
}

bool Boggle::GridPosition::operator==(const Boggle::GridPosition& rhs) const
{
    return x == rhs.x && y == rhs.y;
}

std::unordered_set<Boggle::GridPosition> Boggle::GridPosition::GetNeighbours(size_t gridSize) const
{
    std::unordered_set<GridPosition> neighbours;
    neighbours.reserve(8); // At most 8 neighbours

    for(int xMod = -1; xMod <= 1; ++xMod)
    {
        for(int yMod = -1; yMod <= 1; ++yMod)
        {
            // Skip the current position (IE no position modification)
            if(xMod == 0 && yMod == 0)
            {
                continue;
            }

            GridPosition possibleNeighbour{x + xMod, y + yMod};

            // If the position is out of bounds we skip it
            if(
                possibleNeighbour.x < 0
                ||
                possibleNeighbour.x >= gridSize
                ||
                possibleNeighbour.y < 0
                ||
                possibleNeighbour.y >= gridSize
            )
            {
                continue;
            }

            // Otherwise it's a valid neighbour so add it
            neighbours.insert(possibleNeighbour);
        }
    }

    return neighbours;
}
