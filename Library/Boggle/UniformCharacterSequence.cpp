#include "UniformCharacterSequence.h"

#include <random>

namespace
{
    constexpr auto firstChar = 'a';
    constexpr auto lastChar = 'z';
}

char UniformCharacterSequence::GetNext()
{
    return static_cast<char>(distribution(randomEngine));
}

UniformCharacterSequence::UniformCharacterSequence(unsigned int seed) :
    randomEngine(seed),
    distribution(firstChar, lastChar)
{}
