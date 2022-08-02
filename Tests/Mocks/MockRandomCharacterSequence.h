#pragma once

#include <trompeloeil.hpp>
#include <catch2/trompeloeil.hpp>

#include <Boggle/IRandomCharacterSequence.h>

class MockRandomCharacterSequence : public trompeloeil::mock_interface<IRandomCharacterSequence>
{
public:
    IMPLEMENT_MOCK0(GetNext);
};
