#include "SimpleDictionary.h"

#include <boost/algorithm/string.hpp>

IDictionary::LookupResult SimpleDictionary::IsValid(const std::string& word)
{
    const auto iterator = words.find(word);
    if(iterator != words.end())
    {
        return LookupResult::ValidWord;
    }

    // Since we have no way to know if the string passed in was a valid prefix we assume it was so the algorithm can continue
    return LookupResult::ValidPrefix;
}

void SimpleDictionary::LoadWords(const std::unordered_set<std::string>& words_p)
{
    for(auto& word : words_p)
    {
        words.insert(boost::to_lower_copy(word));
    }
}
