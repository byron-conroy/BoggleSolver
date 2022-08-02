#pragma once

#include <trompeloeil.hpp>
#include <catch2/trompeloeil.hpp>

#include <Dictionary/IDictionary.h>

class MockDictionary : public trompeloeil::mock_interface<IDictionary>
{
public:
    IMPLEMENT_MOCK1(IsValid);
};
