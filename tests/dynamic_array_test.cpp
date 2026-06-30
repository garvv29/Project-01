#include <gtest/gtest.h>
#include "DynamicArray.h"
#include <stdexcept>


class DynamicArrayInsertTest : public ::testing::Test {
protected:
    DynamicArray<int> arr;

    void SetUp() override {
        for (int i = 1; i <= 5; i++)
            arr.append(i);
    }
};

//DYNAMIC ARRAY INSERTION

TEST_F(DynamicArrayInsertTest, InsertAtBeginning)
{
    arr.insert(0,100);
    EXPECT_EQ(arr.size(),6);
    EXPECT_EQ(arr[0],100);
    EXPECT_EQ(arr[1],1);
    EXPECT_EQ(arr[2],2);
    EXPECT_EQ(arr[3],3);
    EXPECT_EQ(arr[4],4);
    EXPECT_EQ(arr[5],5);
}

TEST_F(DynamicArrayInsertTest, InsertAtMiddle)
{
    arr.insert(2,99);

    EXPECT_EQ(arr.size(),6);
    EXPECT_EQ(arr[0],1);
    EXPECT_EQ(arr[1],2);
    EXPECT_EQ(arr[2],99);
    EXPECT_EQ(arr[3],3);
    EXPECT_EQ(arr[4],4);
    EXPECT_EQ(arr[5],5);
}

TEST_F(DynamicArrayInsertTest, InsertAtEnd)
{
    arr.insert(arr.size(),200);

    EXPECT_EQ(arr.size(),6);
    EXPECT_EQ(arr[5],200);
}

TEST(DynamicArrayInsert, InsertIntoEmptyArray)
{
    DynamicArray<int> arr;
    arr.insert(0,10);
    EXPECT_EQ(arr.size(),1);
    EXPECT_EQ(arr[0],10);
}

TEST(DynamicArrayInsert, InsertTriggersResize)
{
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.append(1);
    arr.append(2);
    int oldCap = arr.capacity();
    arr.insert(1,99);
    EXPECT_GT(arr.capacity(),oldCap);
    EXPECT_EQ(arr.size(),3);
    EXPECT_EQ(arr[0],1);
    EXPECT_EQ(arr[1],99);
    EXPECT_EQ(arr[2],2);
}

TEST(DynamicArrayInsert, InsertNegativeIndexThrows)
{
    DynamicArray<int> arr;
    EXPECT_THROW(arr.insert(-1,5),std::out_of_range);
}

TEST(DynamicArrayInsert, InsertPastEndThrows)
{
    DynamicArray<int> arr;
    arr.append(10);
    EXPECT_THROW(arr.insert(2,5),std::out_of_range);
}

TEST(DynamicArrayInsert, InsertLargeDataset)
{
    DynamicArray<int> arr;
    for(int i=0;i<1000;i++)
        arr.append(i);
    arr.insert(500,-1);
    EXPECT_EQ(arr.size(),1001);
    EXPECT_EQ(arr[500],-1);
    for(int i=0;i<500;i++)
        EXPECT_EQ(arr[i],i);
    for(int i=501;i<1001;i++)
        EXPECT_EQ(arr[i],i-1);
}

// CONSTRUCTOR TESTS 

TEST(DynamicArrayComprehensive, DefaultConstructor) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.isEmpty());
}

TEST(DynamicArrayComprehensive, CapacityConstructor) {
    DynamicArray<int> arr(50);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_GE(arr.capacity(), 50); 
}

TEST(DynamicArrayComprehensive, FillConstructor) {
    DynamicArray<int> arr(5, 42); 
    EXPECT_EQ(arr.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], 42);
    }
}

//RULE OF THREE: COPY & ASSIGNMENT

TEST(DynamicArrayComprehensive, CopyConstructorDeepCopy) {
    DynamicArray<int> original;
    original.append(1);
    original.append(2);
    original.append(3);
    DynamicArray<int> copy(original); 
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
    original[0] = 99;
    EXPECT_EQ(copy[0], 1); 
    EXPECT_EQ(original[0], 99);
}

TEST(DynamicArrayComprehensive, AssignmentOperator) {
    DynamicArray<int> arr1;
    arr1.append(10);
    arr1.append(20);
    DynamicArray<int> arr2;
    arr2.append(1); 
    arr2 = arr1; 
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[1], 20);
    arr1[1] = 500;
    EXPECT_EQ(arr2[1], 20);
}

//ELEMENT ACCESS & MODIFICATION

TEST(DynamicArrayComprehensive, OperatorBrackets) {
    DynamicArray<int> arr;
    arr.append(10);
    arr.append(20);
    arr[0] = 15; 
    EXPECT_EQ(arr[0], 15);
}

TEST(DynamicArrayComprehensive, GetAndSetMethods) {
    DynamicArray<int> arr;
    arr.append(100);
    arr.set(0, 200);
    int val;
    bool success = arr.get(0, val);
    EXPECT_TRUE(success);
    EXPECT_EQ(val, 200);
}

//REMOVAL & CLEARING

TEST(DynamicArrayComprehensive, RemoveElement) {
    DynamicArray<int> arr;
    arr.append(10);
    arr.append(20);
    arr.append(30);
    arr.remove(1); 
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
}

TEST(DynamicArrayComprehensive, ClearArray) {
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(2);
    int oldCap = arr.capacity();
    arr.clear();
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.isEmpty());
    EXPECT_EQ(arr.capacity(), oldCap); 
}

//MEMORY MANAGEMENT

TEST(DynamicArrayComprehensive, ShrinkToFit) {
    DynamicArray<int> arr;
    arr.reserve(100);
    arr.append(1);
    arr.append(2);
    
    EXPECT_GE(arr.capacity(), 100);
    
    arr.shrinktosize();
    
    EXPECT_EQ(arr.capacity(), 2);
    EXPECT_EQ(arr.size(), 2);
}
