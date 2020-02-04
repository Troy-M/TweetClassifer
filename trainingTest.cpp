#include "DSString.h"
#include "Tweet.h"
#include "WordCounts.h"
#include "training.h"
#include "catch.hpp"

TEST_CASE("Filter word should filter out empty words", "[training]")
{
    DSString * test = new DSString("");
    REQUIRE(!filter_tweet(test));
}

TEST_CASE("Filter word should filter out non ascii words", "[training]")
{
    DSString * test = new DSString("´åß∂ƒ˚∆˙åß∂˚¬∆ƒ˙åß∂˚¬∆˙ƒ");
    REQUIRE(!filter_tweet(test));
}

TEST_CASE("Filter word should filter out links", "[training]")
{
    DSString * test = new DSString("http://google.com");
    REQUIRE(!filter_tweet(test));
}

TEST_CASE("Filter word should filter out short words", "[training]")
{
    DSString * test = new DSString("i");
    REQUIRE(!filter_tweet(test));
}

TEST_CASE("Filter word should filter out garbage", "[training]")
{
    DSString * test = new DSString("&quot; &amp");
    
    REQUIRE(!filter_tweet(test));
    REQUIRE(*test == " ");
}

TEST_CASE("Filter word should allow good tweets", "[training]")
{
    DSString * test = new DSString("hello");
    REQUIRE(filter_tweet(test));
}