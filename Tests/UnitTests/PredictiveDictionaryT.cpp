#include <catch2/catch.hpp>

#include <Dictionary/PredictiveDictionary.h>

TEST_CASE("PredictiveDictionary")
{
    PredictiveDictionary dictionary;

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
        REQUIRE(dictionary.IsValid("FIRST") == IDictionary::LookupResult::InvalidPrefix);
        REQUIRE(dictionary.IsValid("SECOND") == IDictionary::LookupResult::InvalidPrefix);
        REQUIRE(dictionary.IsValid("SeCond") == IDictionary::LookupResult::InvalidPrefix);
        REQUIRE(dictionary.IsValid("THIRD") == IDictionary::LookupResult::InvalidPrefix);
    }

    SECTION("Unexpected Words")
    {
        REQUIRE(dictionary.IsValid("Some") == IDictionary::LookupResult::InvalidPrefix);
        REQUIRE(dictionary.IsValid("otHer") == IDictionary::LookupResult::InvalidPrefix);
        REQUIRE(dictionary.IsValid("wOrD") == IDictionary::LookupResult::InvalidPrefix);
    }

    SECTION("Prefix Checking")
    {
        // For "first"
        REQUIRE(dictionary.IsValid("f") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("fi") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("fir") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("firs") == IDictionary::LookupResult::ValidPrefix);

        // For "second"
        REQUIRE(dictionary.IsValid("s") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("se") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("sec") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("seco") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("secon") == IDictionary::LookupResult::ValidPrefix);

        // For "third"
        REQUIRE(dictionary.IsValid("t") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("th") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("thi") == IDictionary::LookupResult::ValidPrefix);
        REQUIRE(dictionary.IsValid("thir") == IDictionary::LookupResult::ValidPrefix);
    }
}
