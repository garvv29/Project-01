#pragma once

#include <iostream>
#include <stdexcept>
#include <DynamicArray.h>
#include <SinglyList.h>

template<typename T>
//hashes based on their memory address treating them as huge integers
struct DefaultHash
{   
    size_t operator()(const T& val)const;
};
//hashes integer using shifts and xor
template<>
struct DefaultHash<int>{
    size_t operator()(int x)const;
};
//hashes using integer hash
template<>
struct DefaultHash<char>{
    size_t operator()(char c)const;
};
//simplified FNV-1A
template<>
struct DefaultHash<std::string>{
    size_t operator()(const std::string& s)const;
};

template<typename Key,typename Value,typename Hash=DefaultHash<Key>>
class HashMap{
    private:
    struct Entry{
        Key key;
        Value value;
        Entry(const Key& k,const Value& v):key(k),value(v){}
        bool operator==(const Entry& other)const{
            return key==other.key;
        }
    };
    DynamicArray<SinglyList<Entry>>buckets;
    int elementcount,bucketcount;
    double threshold;
    Hash hashfun;
    //to find what index to insert the key after hashing in
    size_t BucketIndex(const Key& key)const;
    //load factor calculator
    double loadfactor()const;
    //to perform deepcopy of another map
    void deepcopy(const HashMap& map);
    
    public:
    //constructors -
    //default configurable constructor
    HashMap(int inibucketcount=16,double loadfactor=0.75);
    //copy constructor
    HashMap(const HashMap& map);
    //assignment operator (swap idiom)
    HashMap& operator=(const HashMap& map);
    
    //methods- 
    //to append a key value pair in hashmap
    void insert(const Key& k,const Value& v);
    //to retieve value from key
    bool get(const Key& k,Value& v)const;
    //to remove a key value pair
    void remove(const Key& k);
    //to delete all elements
    void clear();
    //rehash to rehash all keys and insert into larger sized array
    void rehash();
    //to check if key exists in the list
    bool exists(const Key& k)const;
    //return number of elements
    int size() const;
    //return number of buckets
    int bucketCount() const;
    //return loadfactor
    double loadFactor() const;
    //empty or not
    bool isEmpty() const;
    
    //testing- 
    
    //to print bucket array and their no of elements
    void debugPrint() const;
    //to get the number of collisions to check hashfunction and chaining
    int collisions() const;
    //print all elements
    void print()const;
};


#include "HashMap.tpp"