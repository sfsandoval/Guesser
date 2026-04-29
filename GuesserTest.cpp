/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

TEST(GuesserTest, GuessMatch)
{
    Guesser guess("Secret");
    ASSERT_TRUE(guess.match("Secret"));
}

TEST(GuesserTest, NotMatch)
{
    Guesser guess("Secret");
    ASSERT_FALSE(guess.match("aaaa"));
}

TEST(GuesserTest, ThreeWrongGuesses)
{
    Guesser guess("Secret");

    ASSERT_FALSE(guess.match("Secrex")); 
    ASSERT_FALSE(guess.match("Secrey")); 
    ASSERT_FALSE(guess.match("Secrez")); 

    ASSERT_FALSE(guess.match("Secret")); 
}

TEST(GuesserTest, BigDistance)
{
    Guesser guess("Secret");

    ASSERT_FALSE(guess.match("zzzzzz")); 
    ASSERT_FALSE(guess.match("Secret"));
}

TEST(GuesserTest, AlwaysFalse)
{
    Guesser guess("Secret");

    guess.match("zzzzzz"); 
    ASSERT_FALSE(guess.match("Secret"));
    ASSERT_FALSE(guess.match("anything"));
}

// tests case sensitivity
TEST(GuesserTest, CaseSensitive)
{
    Guesser guess("Secret");
    ASSERT_FALSE(guess.match("secret"));
}

// if its given an empty string 
TEST(GuesserTest, EmptyString)
{
    Guesser guess("");
    ASSERT_TRUE(guess.match(""));
    ASSERT_FALSE(guess.match("x"));
}

// should reset behavior 
TEST(GuesserTest, ResetsAfterCorrectGuess)
{
    Guesser guess("Secret");

    guess.match("Secrex"); 
    guess.match("Secret"); 

    ASSERT_TRUE(guess.match("Secret"));
}

TEST(GuesserTest, ExactDistance)
{
    Guesser guess("Secret");
    ASSERT_EQ(0, guess.distance("Secret"));
}

TEST(GuesserTest, DistanceOffByOne)
{
    Guesser guess("Secret");
    ASSERT_EQ(1, guess.distance("Secrez"));
}

TEST(GuesserTest, WrongDistance)
{
    Guesser guess("Secret");
    ASSERT_EQ(6, guess.distance("aaaaaa"));
}

// if the guess is longer than secret 
TEST(GuesserTest, GuessLongerThanSecret)
{
    Guesser guess("cat");
    ASSERT_EQ(3, guess.distance("caterpillar"));
}

// if guess is shorter than secret 
TEST(GuesserTest, GuessShorterThanSecret)
{
    Guesser guess("caterpillar");
    ASSERT_EQ(8, guess.distance("cat"));
}

TEST(GuesserTest, DistanceCap)
{
    Guesser guess("abc");
    ASSERT_EQ(3, guess.distance("zzzzzzzzzz"));
}

// constructor 
TEST(GuesserTest, SecretTruncation)
{
    std::string long_secret = "abcdefghijklmnopqrstuvwxyz1234567890";
    Guesser guess(long_secret);

    ASSERT_TRUE(guess.match(long_secret.substr(0, 32)));
}