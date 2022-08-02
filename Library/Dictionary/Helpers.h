#pragma once

#include <filesystem>
#include <string>
#include <unordered_set>

namespace DictionaryHelpers
{
    std::unordered_set<std::string> LoadWordsFromFile(const std::filesystem::path& filePath);
}
