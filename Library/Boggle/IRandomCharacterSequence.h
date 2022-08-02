#pragma once

#include <Base.h>

class IRandomCharacterSequence : public Base
{
public:
    virtual char GetNext() = 0;
};
