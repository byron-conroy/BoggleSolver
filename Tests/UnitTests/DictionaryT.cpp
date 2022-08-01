#include <catch2/catch.hpp>

#include <Dictionary.h>

TEST_CASE("Dictionary")
{
    Dictionary dictionary;

    std::unordered_set<std::string> words{
        "first",
        "SeCond",
        "THIRD"
    };

    dictionary.LoadWords(words);

    SECTION("Expected Words")
    {
        // We expect that the lowercase version of our dictionary words should be valid
        REQUIRE(dictionary.IsValid("first") == IDictionary::LookupResult::ValidWord);
        REQUIRE(dictionary.IsValid("second") == IDictionary::LookupResult::ValidWord);
        REQUIRE(dictionary.IsValid("third") == IDictionary::LookupResult::ValidWord);

        // We expect that any versions of the words which contain uppercase characters will be invalid
        REQUIRE(dictionary.IsValid("FIRST") == IDictionary::LookupResult::Invalid);
        REQUIRE(dictionary.IsValid("SECOND") == IDictionary::LookupResult::Invalid);
        REQUIRE(dictionary.IsValid("SeCond") == IDictionary::LookupResult::Invalid);
        REQUIRE(dictionary.IsValid("THIRD") == IDictionary::LookupResult::Invalid);
    }

    SECTION("Unexpected Words")
    {
        REQUIRE(dictionary.IsValid("Some") == IDictionary::LookupResult::Invalid);
        REQUIRE(dictionary.IsValid("otHer") == IDictionary::LookupResult::Invalid);
        REQUIRE(dictionary.IsValid("wOrD") == IDictionary::LookupResult::Invalid);
    }

    // @TODO add test cases for word prefix searching
}
