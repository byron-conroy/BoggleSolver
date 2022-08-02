#pragma once

#include <array>
#include <unordered_set>

class IRandomCharacterSequence;

namespace Boggle
{
    constexpr static auto RegulationGridSize = 4;
    using Grid = std::vector<std::vector<char>>;
    Grid GenerateGrid(IRandomCharacterSequence& randomCharacterSequence, size_t GridSize = RegulationGridSize);

    struct GridPosition
    {
        int x;
        int y;

        bool operator==(const GridPosition& rhs) const;

        [[nodiscard]]
        std::unordered_set<GridPosition> GetNeighbours(size_t gridSize) const;
    };
}

namespace std {
    template <> struct hash<Boggle::GridPosition> {
        inline size_t operator()(const Boggle::GridPosition& gridPosition) const {
            std::hash<int> int_hasher;
            return int_hasher(gridPosition.x) ^ int_hasher(gridPosition.y);
        }
    };
}

