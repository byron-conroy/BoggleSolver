#include "Dictionary.h"

#include <boost/algorithm/string.hpp>

IDictionary::LookupResult Dictionary::IsValid(const std::string& word)
{
    const auto iterator = words.find(word);
    if(iterator != words.end())
    {
        return LookupResult::ValidWord;
    }
    return LookupResult::Invalid;
}

void Dictionary::LoadWords(const std::unordered_set<std::string>& words_p)
{
    for(auto& word : words_p)
    {
        words.insert(boost::to_lower_copy(word));
    }
}
