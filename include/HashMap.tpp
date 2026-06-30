#pragma once

    #include <iostream>
    #include <stdexcept>
    #include <HashMap.h>

    //hashes based on their memory address treating them as huge integers
    template<typename T>
    size_t DefaultHash<T>::operator()(const T& val)const{
        std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(&val);
        addr^=(addr>>16); 
        addr*=0x45d9f3b; 
        addr^=(addr>>16);
        return static_cast<size_t> (addr);
    }
    //hashes integer using shifts and xor
    size_t DefaultHash<int>::operator()(int x)const{
        size_t h = static_cast<size_t>(x);
        h^=(h>>16); //xor high bits into low bits
        h*=0x45d9f3b;//large scattering constant (prime)
        h^=(h>>16); //xor again to distribute result;
        return h;
    }
    //hashes using integer hash
    size_t DefaultHash<char>::operator()(char c)const{
        return DefaultHash<int>()(static_cast<int>(c));
    }
    //simplified FNV-1A
    size_t DefaultHash<std::string>::operator()(const std::string& s)const
    {
        size_t hash=2166136261U;
        for(char c:s)
        {
            hash^= static_cast<size_t>(c);//xor char
            hash*=16777619U;//multiply by prime
        }
        return hash;
    }
    
    //to find what index to insert the key after hashing in
    template<typename Key,typename Value,typename Hash>
    size_t HashMap<Key,Value,Hash>::BucketIndex(const Key& key)const{
        return hashfun(key)%bucketcount;
    }

    //load factor calculator
    template<typename Key,typename Value,typename Hash>
    double HashMap<Key,Value,Hash>::loadfactor()const{
        return static_cast<double>(elementcount)/bucketcount;
    }

    //to perform deepcopy of another map
    template<typename Key,typename Value,typename Hash>
    void HashMap<Key,Value,Hash>::deepcopy(const HashMap& map){
        buckets = map.buckets;
        elementcount = map.elementcount;
        threshold = map.threshold;
        bucketcount= map.bucketcount;
        hashfun = map.hashfun;
    }

//constructors -
    //default configurable constructor
    template<typename Key,typename Value,typename Hash>
    HashMap<Key,Value,Hash>::HashMap(int inibucketcount,double loadfactor){
        if(inibucketcount<=0)inibucketcount=16;
        bucketcount=inibucketcount;
        elementcount=0;
        threshold=loadfactor;
        //initializing a dynamic array with the size of bucketcount where each element has an empty singlylist<Entry>
        buckets = DynamicArray<SinglyList<Entry>>(bucketcount,SinglyList<Entry>());
    }

    //copy constructor
    template<typename Key,typename Value,typename Hash>
    HashMap<Key,Value,Hash>::HashMap(const HashMap& map){
        deepcopy(map);
    }

    //assignment operator
    template<typename Key,typename Value,typename Hash>
    HashMap<Key,Value,Hash>& HashMap<Key,Value,Hash>::operator=(const HashMap& map){
        if(this==&map)return *this;
        deepcopy(map);
        return *this;
    }

//methods- 

    //to append a key value pair in hashmap
    template<typename Key,typename Value,typename Hash>
    void HashMap<Key,Value,Hash>::insert(const Key& k,const Value& v){
        size_t index = BucketIndex(k);
        //I
        SinglyList<Entry>& bucket = buckets[index];
        for(int i=0;i<bucket.size();i++){
            if(bucket[i].key==k)
            {
                bucket[i].value = v;
                return;
            }
        }
        bucket.append(Entry(k,v));
        elementcount++;
        if(loadfactor()>threshold)rehash();
    }

    //to retieve value from key
    template<typename Key,typename Value,typename Hash>
    bool HashMap<Key,Value,Hash>::get(const Key& k,Value& v)const {
        size_t index = BucketIndex(k);
        const SinglyList<Entry>& bucket = buckets[index];
        for(int i=0;i<bucket.size();i++)
        {
            if(bucket[i].key==k){
                v = bucket[i].value;
                return true;
            }
        }
        return false;
    }

    //to remove a key value pair
    template<typename Key,typename Value,typename Hash>
    void HashMap<Key,Value,Hash>::remove(const Key& k){
        size_t index = BucketIndex(k);
        SinglyList<Entry>& bucket=buckets[index];
        for(int i=0;i<bucket.size();i++){
            if(bucket[i].key==k)
            {
                bucket.remove(i);
                elementcount--;
                return;
            }
        }   
    }

    //to delete all elements
    template<typename Key,typename Value,typename Hash>
    void HashMap<Key,Value,Hash>::clear(){
        for(int i=0;i<bucketcount;i++)
        {
            buckets[i].clear();
        }
        elementcount=0;
    }

    //rehash to rehash all keys and insert into larger sized array
    template<typename Key,typename Value,typename Hash>
    void HashMap<Key,Value,Hash>::rehash(){
        int oldbc = bucketcount;
        bucketcount*=2;
        DynamicArray<SinglyList<Entry>> newbuckets(bucketcount,SinglyList<Entry>());
        for(int i=0;i<oldbc;i++)
        {
            SinglyList<Entry>& bucket = buckets[i];
            for(int j=0;j<bucket.size();j++){
                Entry entry = bucket[j];
                size_t index = BucketIndex(entry.key);
                newbuckets[index].append(entry);
            }
        }
        buckets=newbuckets;
    }

    //to check if key exists in the list
    template<typename Key,typename Value,typename Hash>
    bool HashMap<Key,Value,Hash>::exists(const Key& k)const{
        size_t index = BucketIndex(k);
        const SinglyList<Entry>& bucket = buckets[index];
        for(int i=0;i<bucket.size();i++){
            if(bucket[i].key==k){
                return true;
            }
        }
        return false;
    }

    //returns number of elements
    template<typename Key,typename Value,typename Hash>
    int HashMap<Key,Value,Hash>::size() const{
        return elementcount;
    }

    //return number of buckets
    template<typename Key,typename Value,typename Hash>
    int HashMap<Key,Value,Hash>::bucketCount() const{
        return bucketcount;
    }

    //returns the loadfactor
    template<typename Key,typename Value,typename Hash>
    double HashMap<Key,Value,Hash>::loadFactor() const{
        return static_cast<double>(elementcount)/ bucketcount;
    }

    //checks if empty
    template<typename Key,typename Value,typename Hash>
    bool HashMap<Key,Value,Hash>::isEmpty() const{
        return elementcount == 0;
    }

//testing- 

    //to print bucket array and their no of elements
    template<typename Key,typename Value,typename Hash>
    void HashMap<Key,Value,Hash>::debugPrint() const{
        for(int i=0;i<bucketcount;i++)
        {
            std::cout<<"Bucket "<<i<< ": "<<buckets[i].size()<<'\n';
        }
    }

    //to get the number of collisions to check hashfunction and chaining
    template<typename Key,typename Value,typename Hash>
    int HashMap<Key,Value,Hash>::collisions() const{
        int c = 0;
        for(int i=0;i<bucketcount;i++)
        {
            if(buckets[i].size() > 1)c += buckets[i].size() - 1;
        }
        return c;
    }

    //to print all elements
    template<typename Key,typename Value,typename Hash>
    void HashMap<Key,Value,Hash>::print() const{
        for(int i=0;i<bucketcount;i++)
        {
            const SinglyList<Entry>& bucket = buckets[i];
            for(int j=0;j<bucket.size();j++){
                std::cout<<bucket[j].key<<" "<<bucket[j].value<<endl;
            }
        }
    }

