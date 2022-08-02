#include "PredictiveDictionary.h"

#include <boost/algorithm/string.hpp>

IDictionary::LookupResult PredictiveDictionary::IsValid(const std::string& word)
{
    const auto iterator = words.lower_bound(word);

    // If we don't find anything return saying it's an invalid prefix
    if(iterator == words.end())
    {
        return IDictionary::LookupResult::InvalidPrefix;
    }

    // If we actually found the word then return saying so
    if(*iterator == word)
    {
        return IDictionary::LookupResult::ValidWord;
    }

    // Otherwise we check if the word we found begins with the word we are looking for
    if(boost::algorithm::starts_with(*iterator, word))
    {
        return IDictionary::LookupResult::ValidPrefix;
    }

    return IDictionary::LookupResult::InvalidPrefix;
}

void PredictiveDictionary::LoadWords(const std::unordered_set<std::string>& words_p)
{
    for(auto& word : words_p)
    {
        words.insert(boost::to_lower_copy(word));
    }
}
