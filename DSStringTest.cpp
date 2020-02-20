#include "DSString.h"
#include "catch.hpp"
#include <vector>
#include <cstring>
using namespace std;

TEST_CASE("DSString class", "[DSString")
{
    DSString test = "test";

    SECTION("Creation from char should work")
    {
        REQUIRE(!strcmp(test.c_str(), "test"));
    }

    SECTION("Creation from DSString should work")
    {
        DSString test2 = test;

        REQUIRE(!strcmp(test.c_str(), test2.c_str()));
    }

    SECTION("Assignment operator from DSString should work")
    {
        DSString test2 = "test2";

        test2 = test;

        REQUIRE(!strcmp(test.c_str(), test2.c_str()));
    }

    SECTION("Assignment operator from char should work")
    {
        const char *test2 = "test2";

        test = test2;

        REQUIRE(!strcmp(test.c_str(), test2));
    }

    SECTION("+ operator should work")
    {
        DSString test2 = "test2";

        DSString test3 = test + test2;

        REQUIRE(!strcmp(test3.c_str(), "testtest2"));
    }

    SECTION("+ operator should work on empty string")
    {
        DSString test2 = "";

        DSString test3 = test + test2;

        REQUIRE(!strcmp(test3.c_str(), "test"));
    }

    SECTION("== operator should work")
    {
        DSString test2 = "test2";
        DSString test3 = "test";

        REQUIRE(!(test == test2));
        REQUIRE((test == test3));
    }

    SECTION("== operator should work on empty strings")
    {
        DSString test2 = "test2";
        DSString test3 = "";

        REQUIRE(!(test2 == test3));
        REQUIRE((test3 == test3));
    }

    SECTION("length function should work")
    {
        REQUIRE(test.length() == 4);
    }

    SECTION("length function should work on empty string")
    {
        DSString test2 = "";
        REQUIRE(test2.length() == 0);
    }

    SECTION("split function should work")
    {
        DSString toSplit = "test test test";
        vector<DSString *> parts = toSplit.split(' ');

        REQUIRE(parts.size() == 3);
        REQUIRE(test == *parts[0]);
        REQUIRE(test == *parts[1]);
        REQUIRE(test == *parts[2]);
    }

    SECTION("split should return when no match is found")
    {
        DSString toSplit = "test test test";
        vector<DSString *> parts = toSplit.split(',');

        REQUIRE(parts.size() == 1);
        REQUIRE(toSplit == *parts[0]);
    }

    SECTION("split should work with a splice")
    {
        DSString toSplit = "t,t";
        DSString answer = "t";

        vector<DSString *> parts = toSplit.split(',');

        REQUIRE(parts.size() == 2);
        REQUIRE(answer == *parts[0]);
        REQUIRE(answer == *parts[1]);
    }

    SECTION("substring should work")
    {
        DSString substring = "test test test";
        DSString output = substring.substring(0, 4);

        REQUIRE(test == output);
    }

    SECTION("substring should not return past the string")
    {
        DSString output = test.substring(0, 6);

        REQUIRE(test == output);
    }

    SECTION("substring may return empty")
    {
        DSString output = test.substring(7, 6);
        DSString compare = "";

        REQUIRE(compare == output);
    }

    SECTION("tolower should work")
    {
        DSString toLower = "TEST";
        toLower.toLower();

        REQUIRE(test == toLower);
    }

    SECTION("tolower should not damage lowercase strings")
    {
        DSString toLower = "TeSt";
        toLower.toLower();

        REQUIRE(test == toLower);
    }

    SECTION("isASCII should work on non ascii string ")
    {
        DSString checkASCII = "‰ÔØ";

        REQUIRE(!checkASCII.isASCII());
    }

    SECTION("isASCII should work on ascii string ")
    {
        REQUIRE(test.isASCII());
    }

    SECTION("includes should work ")
    {
        REQUIRE(test.includes("t"));
    }

    SECTION("includes should work on entire string")
    {
        REQUIRE(test.includes("test"));
    }

    SECTION("includes should work on different strings")
    {
        REQUIRE(!test.includes("z"));
    }

    SECTION("includes should work across spaces")
    {
        DSString includes = "test very";

        REQUIRE(includes.includes("very"));
    }

    SECTION("filter should work")
    {
        DSString toFilter = "test";
        toFilter.filter("t");

        REQUIRE(toFilter == "es");
    }

    SECTION("filter should work with space")
    {
        DSString toFilter = "'test'";
        toFilter.filter("'");

        REQUIRE(toFilter == "test");
    }

    SECTION("filter should work with no occurances")
    {
        DSString toFilter = "test";
        toFilter.filter("\"");

        REQUIRE(toFilter == "test");
    }

    SECTION("atoi should work")
    {
        DSString toATOI = "4";

        REQUIRE(toATOI.atoi() == 4);
    }
}
