#include <catch2/catch.hpp>

#include <Boggle/Game.h>

#include <Mocks/MockDictionary.h>

TEST_CASE("Boggle Logic")
{

    MockDictionary mockDictionary;

    Boggle::Grid grid{
        {
            {'c', 'y', 'i', 'q'},
            {'a', 't', 'z', 'y'},
            {'t', 'y', 'a', 'y'},
            {'y', 'y', 'y', 'h'}
        }
    };

    using trompeloeil::_;

    // We will allow any string to be checked in the dictionary but we will treat it as invalid by default
    ALLOW_CALL(mockDictionary, IsValid(_)).RETURN(IDictionary::LookupResult::InvalidPrefix);

    // We expect it to find the word "cat"
    REQUIRE_CALL(mockDictionary, IsValid("c")).RETURN(IDictionary::LookupResult::ValidPrefix);
    REQUIRE_CALL(mockDictionary, IsValid("ca")).RETURN(IDictionary::LookupResult::ValidPrefix);
    REQUIRE_CALL(mockDictionary, IsValid("cat")).RETURN(IDictionary::LookupResult::ValidWord);

    // We expect it to find the word "hat"
    REQUIRE_CALL(mockDictionary, IsValid("h")).RETURN(IDictionary::LookupResult::ValidPrefix);
    REQUIRE_CALL(mockDictionary, IsValid("ha")).RETURN(IDictionary::LookupResult::ValidPrefix);
    REQUIRE_CALL(mockDictionary, IsValid("hat")).RETURN(IDictionary::LookupResult::ValidWord);

    // We expect it to find the word "quiz"
    REQUIRE_CALL(mockDictionary, IsValid("qu")).RETURN(IDictionary::LookupResult::ValidPrefix);
    REQUIRE_CALL(mockDictionary, IsValid("qui")).RETURN(IDictionary::LookupResult::ValidPrefix);
    REQUIRE_CALL(mockDictionary, IsValid("quiz")).RETURN(IDictionary::LookupResult::ValidWord);

    const auto words = Boggle::DiscoverWords({grid, mockDictionary});

    const std::unordered_set<std::string> expectedWords{
        "cat",
        "quiz",
        "hat"
    };

    REQUIRE(words == expectedWords);
}

