#include <catch2/catch.hpp>

#include <Boggle/Grid.h>

#include <Mocks/MockRandomCharacterSequence.h>

TEST_CASE("Boggle Grid")
{
    using namespace Boggle;

    SECTION("Generate Grid")
    {
        MockRandomCharacterSequence randomCharacterSequence;

        constexpr auto MockChar = 'B';

        /*
         * We expect 16 random characters to be requested
         */
        REQUIRE_CALL(randomCharacterSequence, GetNext()).RETURN(MockChar).TIMES(16);

        auto grid = GenerateGrid(randomCharacterSequence);

        // We expect the values returned from the MockRandomCharacterSequence to be stored in the grid
        for(auto x = 0; x < RegulationGridSize; ++x)
        {
            for(auto y = 0; y < RegulationGridSize; ++y)
            {
                REQUIRE(grid[x][y] == MockChar);
            }
        }
    }

    SECTION("Grid Traversal")
    {
        SECTION("All Neighbours")
        {
            GridPosition position{1, 1};

            const auto neighbours = position.GetNeighbours(RegulationGridSize);

            const std::unordered_set<GridPosition> expectedNeighbours{
                GridPosition{0, 0},
                GridPosition{0, 1},
                GridPosition{0, 2},
                GridPosition{1, 0},
                GridPosition{1, 2},
                GridPosition{2, 0},
                GridPosition{2, 1},
                GridPosition{2, 2}
            };

            REQUIRE(neighbours == expectedNeighbours);
        }

        SECTION("Partial Neighbours")
        {
            SECTION("X Lower Bound")
            {
                GridPosition position{0, 1};

                const auto neighbours = position.GetNeighbours(RegulationGridSize);

                const std::unordered_set<GridPosition> expectedNeighbours{
                    GridPosition{0, 0},
                    GridPosition{0, 2},
                    GridPosition{1, 0},
                    GridPosition{1, 1},
                    GridPosition{1, 2}
                };

                REQUIRE(neighbours == expectedNeighbours);
            }

            SECTION("X Upper Bound")
            {
                GridPosition position{3, 1};

                const auto neighbours = position.GetNeighbours(RegulationGridSize);

                const std::unordered_set<GridPosition> expectedNeighbours{
                    GridPosition{2, 0},
                    GridPosition{2, 1},
                    GridPosition{2, 2},
                    GridPosition{3, 0},
                    GridPosition{3, 2}
                };

                REQUIRE(neighbours == expectedNeighbours);
            }

            SECTION("Y Lower Bound")
            {
                GridPosition position{1, 0};

                const auto neighbours = position.GetNeighbours(RegulationGridSize);

                const std::unordered_set<GridPosition> expectedNeighbours{
                    GridPosition{0, 0},
                    GridPosition{2, 0},
                    GridPosition{0, 1},
                    GridPosition{1, 1},
                    GridPosition{2, 1}
                };

                REQUIRE(neighbours == expectedNeighbours);
            }

            SECTION("Y Upper Bound")
            {
                GridPosition position{1, 3};

                const auto neighbours = position.GetNeighbours(RegulationGridSize);

                const std::unordered_set<GridPosition> expectedNeighbours{
                    GridPosition{0, 2},
                    GridPosition{1, 2},
                    GridPosition{2, 2},
                    GridPosition{0, 3},
                    GridPosition{2, 3}
                };

                REQUIRE(neighbours == expectedNeighbours);
            }
        }
    }
}
