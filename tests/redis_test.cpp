#include <gtest/gtest.h>
#include <sstream>
#include <Redis>

class RedisTest : public ::testing::Test
{
protected:
    std::streambuf* oldCin;
    std::streambuf* oldCout;
    std::stringstream input;
    std::stringstream output;
    void SetUp() override
    {
        oldCin = std::cin.rdbuf();
        oldCout = std::cout.rdbuf();
        std::cin.rdbuf(input.rdbuf());
        std::cout.rdbuf(output.rdbuf());
    }

    void TearDown() override
    {
        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);
    }

    std::string Execute(const std::string& commands)
    {
        input.str("");
        input.clear();
        output.str("");
        output.clear();
        input << commands;
        Redis redis;
        redis.run();

        return output.str();
    }
};

// SET / GET

TEST_F(RedisTest, SetAndGet)
{
    std::string result = Execute(
        "SET name Garv\n"
        "GET name\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("Done"), std::string::npos);
    EXPECT_NE(result.find("Garv"), std::string::npos);
}

TEST_F(RedisTest, UpdateExistingKey)
{
    std::string result = Execute(
        "SET age 20\n"
        "SET age 21\n"
        "GET age\n"
        "EXIT\n"
    );
    EXPECT_NE(result.find("21"), std::string::npos);
}

TEST_F(RedisTest, GetMissingKey)
{
    std::string result = Execute(
        "GET abc\n"
        "EXIT\n"
    );
    EXPECT_NE(result.find("Not Found"), std::string::npos);
}

// DELETE

TEST_F(RedisTest, DeleteKey)
{
    std::string result = Execute(
        "SET city Delhi\n"
        "DEL city\n"
        "GET city\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("Deleted"), std::string::npos);
    EXPECT_NE(result.find("Not Found"), std::string::npos);
}

TEST_F(RedisTest, DeleteMissingKey)
{
    std::string result = Execute(
        "DEL xyz\n"
        "EXIT\n"
    );
    EXPECT_NE(result.find("Not found"), std::string::npos);
}

// EXISTS

TEST_F(RedisTest, Exists)
{
    std::string result = Execute(
        "SET a 1\n"
        "EXISTS a\n"
        "EXISTS b\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("True"), std::string::npos);
    EXPECT_NE(result.find("False"), std::string::npos);
}

// COUNT

TEST_F(RedisTest, Count)
{
    std::string result = Execute(
        "SET a 1\n"
        "SET b 2\n"
        "COUNT\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("2"), std::string::npos);
}

// CLEAR

TEST_F(RedisTest, Clear)
{
    std::string result = Execute(
        "SET a 1\n"
        "SET b 2\n"
        "CLEAR\n"
        "COUNT\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("Cleared"), std::string::npos);
    EXPECT_NE(result.find("0"), std::string::npos);
}

// INVALID COMMANDS

TEST_F(RedisTest, InvalidSet)
{
    std::string result = Execute(
        "SET\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("SET <key> <value>"), std::string::npos);
}

TEST_F(RedisTest, InvalidGet)
{
    std::string result = Execute(
        "GET\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("GET <key>"), std::string::npos);
}

TEST_F(RedisTest, UnknownCommand)
{
    std::string result = Execute(
        "HELLO\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("Unknown Command"), std::string::npos);
}

// VALUES WITH SPACES

TEST_F(RedisTest, ValueWithSpaces)
{
    std::string result = Execute(
        "SET quote Hello World From Redis Lite\n"
        "GET quote\n"
        "EXIT\n"
    );

    EXPECT_NE(result.find("Hello World From Redis Lite"), std::string::npos);
}