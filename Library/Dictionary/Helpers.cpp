#include "Helpers.h"

#include <fstream>

std::unordered_set<std::string> DictionaryHelpers::LoadWordsFromFile(const std::filesystem::path& filePath)
{
    std::unordered_set<std::string> words;

    // Bad file, throw exception
    if(!std::filesystem::is_regular_file(filePath))
    {
        std::string errorMessage = "Invalid dictionary file: " + filePath.string();
        throw std::runtime_error(errorMessage);
    }

    // Otherwise we open the file
    std::ifstream file(filePath.string().c_str());
    if(!file.is_open())
    {
        std::string errorMessage = "Unable to open dictionary file: " + filePath.string();
        throw std::runtime_error(errorMessage);
    }

    // Then we read it 1 line at a time
    std::string line;
    while (std::getline(file, line))
    {
        words.insert(line);
    }
    file.close();

    return words;
}
