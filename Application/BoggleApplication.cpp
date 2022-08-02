#include "BoggleApplication.h"

#include <filesystem>
#include <iostream>

#include <boost/program_options.hpp>

#include <Dictionary/PredictiveDictionary.h>
#include <Dictionary/Helpers.h>
#include <Boggle/Game.h>
#include <Boggle/UniformCharacterSequence.h>

void BoggleApplication::Run(int argc, char** argv)
{
    boost::program_options::options_description description("Available Options");

    constexpr auto HELP_OPTION = "help";
    constexpr auto DICTIONARY_OPTION = "dictionary";
    constexpr auto SEED_OPTION = "seed";
    constexpr auto LIMIT_OPTION = "limit";

    description.add_options()
        (HELP_OPTION, "Prints help")
        (DICTIONARY_OPTION, boost::program_options::value<std::string>(), "[optional] Path to text file containing a list of acceptable words, one per line, defaults to ./dict.txt")
        (SEED_OPTION, boost::program_options::value<std::random_device::result_type>(), "[optional] Specify a custom seed to be used for generating the board")
        (LIMIT_OPTION, boost::program_options::value<unsigned int>(), "[optional] The time limit (in seconds)")
        ;

    boost::program_options::variables_map variablesMap;
    try
    {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), variablesMap);
    }
    catch (boost::program_options::unknown_option& exception)
    {
        std::cerr << exception.what() << "\n";
        std::cerr << description << "\n";
        return;
    }

    boost::program_options::notify(variablesMap);

    if (variablesMap.count(HELP_OPTION)) {
        std::cout << description << "\n";
        return;
    }

    // Check if we want to override the time limit
    auto searchLength = std::chrono::seconds(180);
    if (variablesMap.count(LIMIT_OPTION)) {
        searchLength = std::chrono::seconds(variablesMap[LIMIT_OPTION].as<unsigned int>());
    }

    // Check if we want to override the dictionary
    std::filesystem::path dictionaryFile = std::filesystem::current_path().append("./dict.txt");
    if (variablesMap.count(DICTIONARY_OPTION)) {
        dictionaryFile = std::filesystem::path(variablesMap[DICTIONARY_OPTION].as<std::string>());
    }

    // Check if we want to override the seed
    auto seed = std::random_device{}();
    if (variablesMap.count(SEED_OPTION)) {
        seed = variablesMap[SEED_OPTION].as<std::random_device::result_type>();
    }

    // Read the words & create the dictionary
    std::cout << "Reading Dictionary...";
    const auto words = DictionaryHelpers::LoadWordsFromFile(dictionaryFile);
    PredictiveDictionary dictionary{};
    dictionary.LoadWords(words);
    std::cout << "done!" << std::endl;

    // Create the random character generator & the game board
    UniformCharacterSequence uniformCharacterSequence(seed);
    const auto grid = Boggle::GenerateGrid(uniformCharacterSequence);

    // We print out the board we are solving
    std::cout << "Generated the following board using seed " << seed << std::endl;
    for(const auto& row : grid)
    {
        for(const auto& cell : row)
        {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << "Searching the board for " << searchLength.count() << " seconds with a dictionary size of " << words.size() << std::endl;

    const auto startTime = std::chrono::steady_clock::now();

    auto discoveredWords = Boggle::DiscoverWords(
        Boggle::Game{
            grid,
            dictionary,
            std::chrono::steady_clock::now() + searchLength
        }
    );

    const std::chrono::duration<double> duration = std::chrono::steady_clock::now() - startTime;

    int score = 0;

    std::cout << "In " << duration.count() << " seconds found the following words:" << std::endl;
    for(const auto& word : discoveredWords)
    {
        auto wordScore = Boggle::GetWordScore(word);

        if(wordScore == 0)
        {
            continue;
        }

        std::cout << word << ": " << wordScore << " points" << std::endl;
        score += wordScore;
    }

    std::cout << "Total Score: " << score << " points" << std::endl;
}
