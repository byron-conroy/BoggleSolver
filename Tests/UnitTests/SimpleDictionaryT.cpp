#include <catch2/catch.hpp>

#include <Dictionary/SimpleDictionary.h>

TEST_CASE("SimpleDictionary")
{
    SimpleDictionary dictionary;

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
        REQUIRE(dictionary.IsValid("FIRST") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("SECOND") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("SeCond") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("THIRD") == IDictionary::LookupResult::ValidPrefix);
    }

    SECTION("Unexpected Words")
    {
        REQUIRE(dictionary.IsValid("Some") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("otHer") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("wOrD") == IDictionary::LookupResult::ValidPrefix);
    }
}
