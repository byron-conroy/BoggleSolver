#pragma once

#include <set>
#include <unordered_set>

#include "IDictionary.h"

class PredictiveDictionary : public IDictionary
{
public:
    LookupResult IsValid(const std::string& word) final;
    void LoadWords(const std::unordered_set<std::string>& words);
private:
    std::set<std::string> words;
};
