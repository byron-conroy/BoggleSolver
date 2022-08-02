#pragma once

#include <random>

#include <Boggle/IRandomCharacterSequence.h>

class UniformCharacterSequence : public IRandomCharacterSequence
{
public:
    explicit UniformCharacterSequence(unsigned int seed = std::random_device{}());
    char GetNext() final;
private:
    std::default_random_engine randomEngine;
    std::uniform_int_distribution<int> distribution;
};
