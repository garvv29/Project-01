#include <gtest/gtest.h>
#include "SinglyList.h"
#include <stdexcept>

class SinglyListInsertTest : public ::testing::Test {
protected:
    SinglyList<int> list;

    void SetUp() override {
        for(int i = 1; i <= 5; i++)
            list.append(i);
    }
};

TEST_F(SinglyListInsertTest, InsertAtBeginning)
{
    list.insert(0,100);
    EXPECT_EQ(list.size(),6);
    EXPECT_EQ(list[0],100);
    EXPECT_EQ(list[1],1);
    EXPECT_EQ(list[2],2);
    EXPECT_EQ(list[3],3);
    EXPECT_EQ(list[4],4);
    EXPECT_EQ(list[5],5);
}

TEST_F(SinglyListInsertTest, InsertAtMiddle)
{
    list.insert(2,99);
    EXPECT_EQ(list.size(),6);
    EXPECT_EQ(list[0],1);
    EXPECT_EQ(list[1],2);
    EXPECT_EQ(list[2],99);
    EXPECT_EQ(list[3],3);
    EXPECT_EQ(list[4],4);
    EXPECT_EQ(list[5],5);
}

TEST_F(SinglyListInsertTest, InsertAtEnd)
{
    list.insert(list.size(),200);
    EXPECT_EQ(list.size(),6);
    EXPECT_EQ(list[5],200);
}

TEST(SinglyListInsertStandalone, InsertIntoEmptyList)
{
    SinglyList<int> list;
    list.insert(0,10);
    EXPECT_EQ(list.size(),1);
    EXPECT_EQ(list[0],10);
}

TEST(SinglyListInsertStandalone, InsertNegativeIndexThrows)
{
    SinglyList<int> list;
    EXPECT_THROW(list.insert(-1,5),std::out_of_range);
}

TEST(SinglyListInsertStandalone, InsertPastEndThrows)
{
    SinglyList<int> list;
    list.append(10);
    EXPECT_THROW(list.insert(2,5),std::out_of_range);
}

TEST(SinglyListInsertStandalone, InsertLargeDataset)
{
    SinglyList<int> list;
    for(int i=0;i<1000;i++)list.append(i);
    list.insert(500,-1);
    EXPECT_EQ(list.size(),1001);
    EXPECT_EQ(list[500],-1);
    for(int i=0;i<500;i++)
        EXPECT_EQ(list[i],i);
    for(int i=501;i<1001;i++)
        EXPECT_EQ(list[i],i-1);
}
// --- CONSTRUCTOR TESTS ---

TEST(SinglyListComprehensive, DefaultConstructor)
{
    SinglyList<int> list;

    EXPECT_EQ(list.size(),0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(SinglyListComprehensive, IteratorConstructor)
{
    int arr[] = {10,20,30,40};
    SinglyList<int> list(arr,arr+4);
    EXPECT_EQ(list.size(),4);
    EXPECT_EQ(list[0],10);
    EXPECT_EQ(list[1],20);
    EXPECT_EQ(list[2],30);
    EXPECT_EQ(list[3],40);
}

//RULE OF THREE

TEST(SinglyListComprehensive, CopyConstructorDeepCopy)
{
    SinglyList<int> original;
    original.append(1);
    original.append(2);
    original.append(3);
    SinglyList<int> copy(original);
    EXPECT_EQ(copy.size(),3);
    EXPECT_EQ(copy[0],1);
    original[0]=100;
    EXPECT_EQ(copy[0],1);
    EXPECT_EQ(original[0],100);
}

TEST(SinglyListComprehensive, AssignmentOperator)
{
    SinglyList<int> list1;
    list1.append(10);
    list1.append(20);
    SinglyList<int> list2;
    list2.append(1);
    list2=list1;
    EXPECT_EQ(list2.size(),2);
    EXPECT_EQ(list2[0],10);
    EXPECT_EQ(list2[1],20);
    list1[1]=999;
    EXPECT_EQ(list2[1],20);
}

//ELEMENT ACCESS

TEST(SinglyListComprehensive, OperatorBrackets)
{
    SinglyList<int> list;
    list.append(10);
    list.append(20);
    list[0]=15;
    EXPECT_EQ(list[0],15);
}

TEST(SinglyListComprehensive, GetMethod)
{
    SinglyList<int> list;
    list.append(100);
    int value;
    EXPECT_TRUE(list.get(0,value));
    EXPECT_EQ(value,100);
    EXPECT_FALSE(list.get(5,value));
}

//APPEND & INSERT FRONT

TEST(SinglyListComprehensive, AppendElements)
{
    SinglyList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    EXPECT_EQ(list.size(),3);
    EXPECT_EQ(list[2],3);
}

TEST(SinglyListComprehensive, InsertFront)
{
    SinglyList<int> list;
    list.append(2);
    list.append(3);
    list.insertFront(1);
    EXPECT_EQ(list.size(),3);
    EXPECT_EQ(list[0],1);
    EXPECT_EQ(list[1],2);
    EXPECT_EQ(list[2],3);
}

//REMOVAL

TEST(SinglyListComprehensive, RemoveFront)
{
    SinglyList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);
    list.removeFront();
    EXPECT_EQ(list.size(),2);
    EXPECT_EQ(list[0],20);
    EXPECT_EQ(list[1],30);
}

TEST(SinglyListComprehensive, RemoveMiddle)
{
    SinglyList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);
    list.remove(1);
    EXPECT_EQ(list.size(),2);
    EXPECT_EQ(list[0],10);
    EXPECT_EQ(list[1],30);
}

TEST(SinglyListComprehensive, RemoveLastElement)
{
    SinglyList<int> list;
    list.append(10);
    list.append(20);
    list.remove(1);
    EXPECT_EQ(list.size(),1);
    EXPECT_EQ(list[0],10);
}

TEST(SinglyListComprehensive, RemoveOnlyElement)
{
    SinglyList<int> list;
    list.append(100);
    list.remove(0);
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(),0);
}

TEST(SinglyListComprehensive, RemoveInvalidIndexThrows)
{
    SinglyList<int> list;
    EXPECT_THROW(list.remove(0),std::out_of_range);
    list.append(1);
    EXPECT_THROW(list.remove(1),std::out_of_range);
}

TEST(SinglyListComprehensive, RemoveFrontFromEmptyThrows)
{
    SinglyList<int> list;
    EXPECT_THROW(list.removeFront(),std::out_of_range);
}

//SEARCH

TEST(SinglyListComprehensive, SearchExistingElement)
{
    SinglyList<int> list;
    list.append(5);
    list.append(10);
    list.append(15);
    EXPECT_EQ(list.search(5),0);
    EXPECT_EQ(list.search(10),1);
    EXPECT_EQ(list.search(15),2);
}

TEST(SinglyListComprehensive, SearchMissingElement)
{
    SinglyList<int> list;
    list.append(5);
    list.append(10);
    EXPECT_EQ(list.search(100),-1);
}

//CLEAR

TEST(SinglyListComprehensive, ClearList)
{
    SinglyList<int> list;

    list.append(1);
    list.append(2);
    list.append(3);

    list.clear();

    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(),0);
}

// OPERATOR [] EXCEPTIONS

TEST(SinglyListComprehensive, BracketsOutOfRangeThrows)
{
    SinglyList<int> list;

    EXPECT_THROW(list[0],std::out_of_range);

    list.append(10);

    EXPECT_THROW(list[1],std::out_of_range);
}