#pragma once

#include <unordered_set>

#include "IDictionary.h"

// @TODO Create implementation which uses a prefix trie
class SimpleDictionary : public IDictionary
{
public:
    LookupResult IsValid(const std::string& word) final;
    void LoadWords(const std::unordered_set<std::string>& words);
private:
    std::unordered_set<std::string> words;
};
