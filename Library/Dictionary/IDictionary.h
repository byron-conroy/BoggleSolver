#pragma once

#include <string>

#include "Base.h"

class IDictionary : public Base
{
public:
    enum class LookupResult{
        InvalidPrefix,
        ValidPrefix,
        ValidWord
    };

    /*
     * Returns whether a string is a valid word / prefix.
     * All words provided must be lower case.
     */
    virtual LookupResult IsValid(const std::string& word) = 0;
};
