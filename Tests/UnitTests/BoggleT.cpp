#include <catch2/catch.hpp>

#include <Boggle/Game.h>

#include <Mocks/MockDictionary.h>

TEST_CASE("Boggle Logic")
{
    MockDictionary mockDictionary;

    using trompeloeil::_;

    SECTION("All Permutations of 4x4")
    {
        // In this case we treat all substrings are valid prefixes
        ALLOW_CALL(mockDictionary, IsValid(_)).RETURN(IDictionary::LookupResult::ValidPrefix);

        Boggle::Grid grid{
            {
                {'a', 'b'},
                {'c', 'd'}
            }
        };

        ALLOW_CALL(mockDictionary, IsValid("abcd")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("abdc")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("acbd")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("acdb")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("adcb")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("adbc")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("bacd")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("badc")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("bcad")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("bcda")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("bdca")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("bdac")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("cbad")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("cbda")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("cabd")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("cadb")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("cdab")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("cdba")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("dbca")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("dbac")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("dcba")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("dcab")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("dacb")).RETURN(IDictionary::LookupResult::ValidWord);
        ALLOW_CALL(mockDictionary, IsValid("dabc")).RETURN(IDictionary::LookupResult::ValidWord);

        const auto words = Boggle::DiscoverWords({grid, mockDictionary});
        const std::unordered_set<std::string> expectedWords{
            "abcd",
            "abdc",
            "acbd",
            "acdb",
            "adcb",
            "adbc",
            "bacd",
            "badc",
            "bcad",
            "bcda",
            "bdca",
            "bdac",
            "cbad",
            "cbda",
            "cabd",
            "cadb",
            "cdab",
            "cdba",
            "dbca",
            "dbac",
            "dcba",
            "dcab",
            "dacb",
            "dabc"
        };

        REQUIRE(words == expectedWords);
    }

    SECTION("Case 1")
    {
        // In this case we treat all substrings as invalid by default
        ALLOW_CALL(mockDictionary, IsValid(_)).RETURN(IDictionary::LookupResult::InvalidPrefix);

        Boggle::Grid grid{
            {
                {'y', 'a', 't', 'r'},
                {'p', 'h', 'n', 'e'},
                {'x', 'c', 'l', 'y'},
                {'s', 'v', 'e', 'q'}
            }
        };

        // We expect it to find the word "any"
        REQUIRE_CALL(mockDictionary, IsValid("a")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("an")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("any")).RETURN(IDictionary::LookupResult::ValidWord);

        // We expect it to find the word "chant"
        REQUIRE_CALL(mockDictionary, IsValid("c")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("ch")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("cha")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("chan")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("chant")).RETURN(IDictionary::LookupResult::ValidWord);

        // We expect it to find the words "path" and "panel"
        REQUIRE_CALL(mockDictionary, IsValid("p")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("pa")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("pat")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("path")).RETURN(IDictionary::LookupResult::ValidWord);
        REQUIRE_CALL(mockDictionary, IsValid("pan")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("pane")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("panel")).RETURN(IDictionary::LookupResult::ValidWord);

        // We expect it to find the word "trench"
        REQUIRE_CALL(mockDictionary, IsValid("t")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("tr")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("tre")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("tren")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("trenc")).RETURN(IDictionary::LookupResult::ValidPrefix);
        REQUIRE_CALL(mockDictionary, IsValid("trench")).RETURN(IDictionary::LookupResult::ValidWord);

        const auto words = Boggle::DiscoverWords({grid, mockDictionary});

        const std::unordered_set<std::string> expectedWords{
            "any",
            "chant",
            "panel",
            "path",
            "trench",
        };

        REQUIRE(words == expectedWords);
    }

    SECTION("Case 2")
    {
        // In this case we treat all substrings as invalid by default
        ALLOW_CALL(mockDictionary, IsValid(_)).RETURN(IDictionary::LookupResult::InvalidPrefix);

        Boggle::Grid grid{
            {
                {'c', 'y', 'i', 'q'},
                {'a', 't', 'z', 'y'},
                {'t', 'y', 'a', 'y'},
                {'y', 'y', 'y', 'h'}
            }
        };

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


}

