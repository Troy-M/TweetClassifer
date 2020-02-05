#include "Tweet.h"
#include "DSString.h"
#include "catch.hpp"
#include <vector>
#include <cstring>
using namespace std;


TEST_CASE("Creation and getters should work", "[Tweet]")
{
    DSString * user = new DSString("test");
    DSString * text = new DSString("test2");
    DSString * id = new DSString("test3");
    
    Tweet tweet(text, user, id);

    REQUIRE(*tweet.GetText() == *text);
    REQUIRE(*tweet.GetUser() == *user);
    REQUIRE(*tweet.GetID() == *id);
}


TEST_CASE("Setters should work", "[Tweet]")
{
    DSString * user = new DSString("test");
    DSString * text = new DSString("test2");
    DSString * id = new DSString("test3");
    
    Tweet tweet(text, user, id);

    tweet.SetClassification(5);

    REQUIRE(tweet.GetClassification() == 5);
}

TEST_CASE("Copy assignment should work", "[Tweet]")
{
    DSString * user = new DSString("test");
    DSString * text = new DSString("test2");
    DSString * id = new DSString("test3");
    
    Tweet tweet(text, user, id);
    tweet.SetClassification(5);

    Tweet tweet2 = tweet;


    REQUIRE(*tweet.GetText() == *text);
    REQUIRE(*tweet.GetUser() == *user);
    REQUIRE(*tweet.GetID() == *id);
    REQUIRE(tweet.GetClassification() == 5);
}

TEST_CASE("Assignment should work", "[Tweet]")
{
    DSString * user = new DSString("test");
    DSString * text = new DSString("test2");
    DSString * id = new DSString("test3");
    
    Tweet tweet(text, user, id);
    tweet.SetClassification(5);


    DSString * user2 = new DSString("test3");
    DSString * text2 = new DSString("test4");
    DSString * id2 = new DSString("test5");

    Tweet tweet2(text2, user2, id2);

    tweet2 = tweet;

    REQUIRE(*tweet.GetText() == *text);
    REQUIRE(*tweet.GetUser() == *user);
    REQUIRE(*tweet.GetID() == *id);
    REQUIRE(tweet.GetClassification() == 5);

    REQUIRE(*tweet2.GetText() == *text);
    REQUIRE(*tweet2.GetUser() == *user);
    REQUIRE(*tweet2.GetID() == *id);
    REQUIRE(tweet2.GetClassification() == 5);
}