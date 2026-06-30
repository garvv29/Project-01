#include <gtest/gtest.h>
#include "HashMap.h"
#include <string>

class HashMapInsertTest : public ::testing::Test {
protected:
    HashMap<int,std::string> map;

    void SetUp() override
    {
        map.insert(1,"One");
        map.insert(2,"Two");
        map.insert(3,"Three");
    }
};

// INSERT TESTS

TEST_F(HashMapInsertTest, InsertNewKey)
{
    map.insert(4,"Four");
    EXPECT_EQ(map.size(),4);
    EXPECT_TRUE(map.exists(4));
    std::string value;
    EXPECT_TRUE(map.get(4,value));
    EXPECT_EQ(value,"Four");
}

TEST_F(HashMapInsertTest, InsertDuplicateKeyUpdatesValue)
{
    map.insert(2,"Updated");
    EXPECT_EQ(map.size(),3);
    std::string value;
    EXPECT_TRUE(map.get(2,value));
    EXPECT_EQ(value,"Updated");
}

TEST(HashMapStandalone, InsertIntoEmptyMap)
{
    HashMap<int,int> map;
    map.insert(10,100);
    EXPECT_EQ(map.size(),1);
    int value;
    EXPECT_TRUE(map.get(10,value));
    EXPECT_EQ(value,100);
}

TEST(HashMapStandalone, InsertManyElements)
{
    HashMap<int,int> map;
    for(int i=0;i<1000;i++)
        map.insert(i,i*10);
    EXPECT_EQ(map.size(),1000);
    int value;
    EXPECT_TRUE(map.get(500,value));
    EXPECT_EQ(value,5000);
}

//CONSTRUCTORS

TEST(HashMapComprehensive, DefaultConstructor)
{
    HashMap<int,int> map;

    EXPECT_EQ(map.size(),0);
    EXPECT_TRUE(map.isEmpty());
}

TEST(HashMapComprehensive, CustomBucketConstructor)
{
    HashMap<int,int> map(32);
    EXPECT_EQ(map.bucketCount(),32);
    EXPECT_TRUE(map.isEmpty());
}

//RULE OF THREE

TEST(HashMapComprehensive, CopyConstructorDeepCopy)
{
    HashMap<int,int> original;
    original.insert(1,10);
    original.insert(2,20);
    HashMap<int,int> copy(original);
    EXPECT_EQ(copy.size(),2);
    original.insert(1,100);
    int value;
    copy.get(1,value);
    EXPECT_EQ(value,10);
    original.get(1,value);
    EXPECT_EQ(value,100);
}

TEST(HashMapComprehensive, AssignmentOperator)
{
    HashMap<int,int> map1;
    map1.insert(1,10);
    map1.insert(2,20);
    HashMap<int,int> map2;
    map2.insert(100,500);
    map2=map1;
    EXPECT_EQ(map2.size(),2);
    int value;
    map2.get(2,value);
    EXPECT_EQ(value,20);
    map1.insert(2,999);
    map2.get(2,value);
    EXPECT_EQ(value,20);
}



//GET
TEST(HashMapComprehensive, GetExistingKey)
{
    HashMap<int,int> map;

    map.insert(5,50);

    int value;

    EXPECT_TRUE(map.get(5,value));
    EXPECT_EQ(value,50);
}

TEST(HashMapComprehensive, GetMissingKey)
{
    HashMap<int,int> map;

    int value;

    EXPECT_FALSE(map.get(100,value));
}

//REMOVE

TEST(HashMapComprehensive, RemoveExistingKey)
{
    HashMap<int,int> map;
    map.insert(1,10);
    map.insert(2,20);
    map.remove(1);
    EXPECT_EQ(map.size(),1);
    EXPECT_FALSE(map.exists(1));
    EXPECT_TRUE(map.exists(2));
}

TEST(HashMapComprehensive, RemoveMissingKey)
{
    HashMap<int,int> map;
    map.insert(1,10);
    map.remove(100);
    EXPECT_EQ(map.size(),1);
}

//EXISTS

TEST(HashMapComprehensive, Exists)
{
    HashMap<int,int> map;

    map.insert(7,70);

    EXPECT_TRUE(map.exists(7));
    EXPECT_FALSE(map.exists(8));
}

//CLEAR

TEST(HashMapComprehensive, Clear)
{
    HashMap<int,int> map;
    for(int i=0;i<10;i++)
        map.insert(i,i);
    map.clear();
    EXPECT_EQ(map.size(),0);
    EXPECT_TRUE(map.isEmpty());
}

//REHASH

TEST(HashMapComprehensive, RehashIncreasesBucketCount)
{
    HashMap<int,int> map(4);

    int oldBuckets=map.bucketCount();

    for(int i=0;i<20;i++)
        map.insert(i,i);

    EXPECT_GT(map.bucketCount(),oldBuckets);

    for(int i=0;i<20;i++)
    {
        int value;
        EXPECT_TRUE(map.get(i,value));
        EXPECT_EQ(value,i);
    }
}

//LOAD FACTOR

TEST(HashMapComprehensive, LoadFactor)
{
    HashMap<int,int> map(10);
    map.insert(1,1);
    map.insert(2,2);
    map.insert(3,3);
    EXPECT_DOUBLE_EQ(map.loadFactor(),0.3);
}

//COLLISIONS

struct BadHash
{
    size_t operator()(int) const
    {
        return 0;
    }
};

TEST(HashMapComprehensive, CollisionHandling)
{
    HashMap<int,int,BadHash> map(8);

    map.insert(1,10);
    map.insert(2,20);
    map.insert(3,30);
    EXPECT_EQ(map.collisions(),2);
    int value;
    EXPECT_TRUE(map.get(1,value));
    EXPECT_EQ(value,10);
    EXPECT_TRUE(map.get(2,value));
    EXPECT_EQ(value,20);
    EXPECT_TRUE(map.get(3,value));
    EXPECT_EQ(value,30);
}

//STRING KEYS

TEST(HashMapComprehensive, StringKeys)
{
    HashMap<std::string,int> map;
    map.insert("Alice",10);
    map.insert("Bob",20);
    int value;
    EXPECT_TRUE(map.get("Alice",value));
    EXPECT_EQ(value,10);
    EXPECT_TRUE(map.get("Bob",value));
    EXPECT_EQ(value,20);
}