#include <iostream>

#include "Dictionary/SimpleDictionary.h"
#include <Boggle/Game.h>
#include <Boggle/UniformCharacterSequence.h>

int main()
{
    SimpleDictionary dictionary{};

    dictionary.LoadWords(
        {
            "first",
            "second",
            "third",
        }
    );

    UniformCharacterSequence uniformCharacterSequence(22);

    auto grid = Boggle::GenerateGrid(uniformCharacterSequence);

    for(const auto& row : grid)
    {
        for(const auto& cell : row)
        {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
}
