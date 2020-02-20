#include "DSString.h"
#include "Tweet.h"
#include "WordCounts.h"
#include "training.h"
#include "catch.hpp"

TEST_CASE("Training class", "[Training]")
{
    SECTION("Filter word should filter out empty words")
    {
        DSString * test = new DSString("");
        REQUIRE(!filter_tweet(test));
    }

    SECTION("Filter word should filter out non ascii words")
    {
        DSString * test = new DSString("´åß∂ƒ˚∆˙åß∂˚¬∆ƒ˙åß∂˚¬∆˙ƒ");
        REQUIRE(!filter_tweet(test));
    }

    SECTION("Filter word should filter out links")
    {
        DSString * test = new DSString("http://google.com");
        REQUIRE(!filter_tweet(test));
    }

    SECTION("Filter word should filter out short words")
    {
        DSString * test = new DSString("i");
        REQUIRE(!filter_tweet(test));
    }

    SECTION("Filter word should filter out garbage")
    {
        DSString * test = new DSString("&quot; &amp");
        
        REQUIRE(!filter_tweet(test));
        REQUIRE(*test == " ");
    }

    SECTION("Filter word should allow good tweets")
    {
        DSString * test = new DSString("hello");
        REQUIRE(filter_tweet(test));

        test = new DSString("yay!!!");
        REQUIRE(filter_tweet(test));
    }
    
}

