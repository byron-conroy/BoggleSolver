#pragma once

#include <unordered_set>

#include <IDictionary.h>

class Dictionary : public IDictionary
{
public:
    LookupResult IsValid(const std::string& word) final;
    void LoadWords(const std::unordered_set<std::string>& words);
private:
    // @TODO Replace this with a prefix trie
    std::unordered_set<std::string> words;
};
