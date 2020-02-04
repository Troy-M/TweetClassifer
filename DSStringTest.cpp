#include "DSString.h"
#include "catch.hpp"
#include <vector>
#include <cstring>
using namespace std;

TEST_CASE("Creation from char should work", "[DSString]")
{
    DSString test = "test";
    REQUIRE(!strcmp(test.c_str(), "test"));
}

TEST_CASE("Creation from DSString should work", "[DSString]")
{
    DSString test = "test";
    DSString test2 = test;

    REQUIRE(!strcmp(test.c_str(), test2.c_str()));
}

TEST_CASE("Assignment operator from DSString should work", "[DSString]")
{
    DSString test = "test";
    DSString test2 = "test2";

    test2 = test;

    REQUIRE(!strcmp(test.c_str(), test2.c_str()));
}

TEST_CASE("Assignment operator from char should work", "[DSString]")
{
    DSString test = "test";
    const char *test2 = "test2";

    test = test2;

    REQUIRE(!strcmp(test.c_str(), test2));
}

TEST_CASE("+ operator should work", "[DSString]")
{
    DSString test = "test";
    DSString test2 = "test2";

    DSString test3 = test + test2;
 
    REQUIRE(!strcmp(test3.c_str(), "testtest2"));
}

TEST_CASE("== operator should work", "[DSString]")
{
    DSString test = "test";
    DSString test2 = "test2";
    DSString test3 = "test";

    REQUIRE(!(test == test2));
    REQUIRE((test == test));
}

TEST_CASE("length function should work", "[DSString]")
{
    DSString test = "test";
    REQUIRE(test.length() == 4);
}

TEST_CASE("split function should work", "[DSString]")
{
    DSString test = "test test test";
    vector<DSString *> parts = test.split(' ');

    DSString compare = "test";

    REQUIRE(parts.size() == 3);
    REQUIRE(compare == *parts[0]);
    REQUIRE(compare == *parts[1]);
    REQUIRE(compare == *parts[2]);
}

TEST_CASE("split should return when no match is found", "[DSString]")
{
    DSString test = "test test test";
    vector<DSString *> parts = test.split(',');

    REQUIRE(parts.size() == 1);
    REQUIRE(test == *parts[0]);
}

TEST_CASE("substring should work", "[DSString]")
{
    DSString test = "test test test";
    DSString output = test.substring(0, 4);

    DSString compare = "test";

    REQUIRE(compare == output);
}

TEST_CASE("substring should not return past the string", "[DSString]")
{
    DSString test = "test";
    DSString output = test.substring(0, 6);

    DSString compare = "test";

    REQUIRE(compare == output);
}

TEST_CASE("substring may return empty", "[DSString]")
{
    DSString test = "test";
    DSString output = test.substring(7, 6);

    DSString compare = "";

    REQUIRE(compare == output);
}

TEST_CASE("tolower should work", "[DSString]")
{
    DSString test = "TEST";
    test.toLower();

    DSString compare = "test";

    REQUIRE(compare == test);
}

TEST_CASE("tolower should not damage lowercase strings", "[DSString]")
{
    DSString test = "TeSt";
    test.toLower();

    DSString compare = "test";

    REQUIRE(compare == test);
}

TEST_CASE("isASCII should work on non ascii string ", "[DSString]")
{
    DSString test = "‰ÔØ";

    REQUIRE(!test.isASCII());
}

TEST_CASE("isASCII should work on ascii string ", "[DSString]")
{
    DSString test = "test";
    
    REQUIRE(test.isASCII());
}

TEST_CASE("includes should work ", "[DSString]")
{
    DSString test = "test";
    
    REQUIRE(test.includes("t"));
}

TEST_CASE("includes should work on entire string", "[DSString]")
{
    DSString test = "test";
    
    REQUIRE(test.includes("test"));
}

TEST_CASE("includes should work on different strings", "[DSString]")
{
    DSString test = "test";
    
    REQUIRE(!test.includes("z"));
}

TEST_CASE("includes should work across spaces", "[DSString]")
{
    DSString test = "test very";
    
    REQUIRE(test.includes("very"));
}

TEST_CASE("filter should work", "[DSString]")
{
    DSString test = "test";
    test.filter("t");
    
    REQUIRE(test == "es");
}

TEST_CASE("filter should work with space", "[DSString]")
{
    DSString test = "'test'";
    test.filter("'");
    
    REQUIRE(test == "test");
}

TEST_CASE("filter should work with no occurances", "[DSString]")
{
    DSString test = "test";
    test.filter("\"");
    
    REQUIRE(test == "test");
}

TEST_CASE("atoi should work", "[DSString]")
{
    DSString test = "4";
    
    REQUIRE(test.atoi() == 4);
}





