# Project 01 – Design Proposal
## Project Objective

The objective of this project is to design a reusable, generic and memory-safe Data Structure Library consisting of DynamicArray, LinkedList, and HashMap implementations.

The proposed design supports explicit memory ownership. For the Design choices i evaluated multiple pros and cons for each data structure and selected the efficent ones which fullfil our requirements .The selected designs are intended to serve as reusable building blocks for future projects such as Redis Lite, ensuring that the chosen implementations satisfy both current functional requirements and future use cases.


# Section 1 – Public API
The proposed design extends the suggested interface with several modifications and utility operations 

### 1. DynamicArray 
Methods - 
```cpp
template<typename T>
class DynamicArray {
    private:
        int size_;
        int capacity_;
        T *data;
        void resize(int newCapacity); //internal method to resize the array
    public:
        DynamicArray(int capacity=0) //construct empty array
        template<typename Iterator>
        DynamicArray(Iterator start,Iterator end); //construct from any iterable container
        template<typename Container>
        DynamicArray(const Container& c)
        void append(const T& value) //append element
        void insert(const T& value, int index) //insert at position
        void remove(int index) //remove element
        bool get(int index,T& value) const //returns value safely
        void set(int index,const T& value) // modify value at given index
        void reserve(int newCapacity) //preallocate storage 
        void clear() //remove all elements
        int size() const //return element count
        bool isEmpty() const //check whether empty
        T* begin() //return pointer to first element
        T* end() //return pointer to one past last element
        ~DynamicArray() //destructor
        DynamicArray(const DynamicArray&) //copy constructor
        DynamicArray& operator=(const DynamicArray&) //assignment operator
};
```

- The array doubles its capacity when full and shrinks when utilization falls below 25%, balancing memory efficiency with performance doubling it results in amortized O(1) append operations, while shrinking prevents excessive memory usage.
- The get() method returns the requested element through a reference parameter and uses a boolean return value to indicate success, avoiding ambiguous sentinel values for invalid indices.  
- The reserve() method enables preallocation of storage when the expected number of elements is known, reducing the number of reallocations during repeated insertions.  
- A dedicated set() method separates modification from insertion operations.  
- Utility functions such as ` clear()` and `isEmpty()` improve the usability and completeness of the Data Structure.
- `begin()` and `end()` methods provide iterators for return pointers to start and past to end memory address.
- `DynamicArray(Iterator start,Iterator end) `constructor allows construction from any iterable container.

---

### 2. LinkedList 
The linked list functionality is divided into two distinct data structures: `SinglyLinkedList` for strict memory efficiency, and `DoublyLinkedList` for high-performance bidirectional operations.

### 1. SinglyLinkedList 
The SinglyLinkedList is designed for maximum memory efficiency, making it the ideal choice for scenarios with strict memory constraints or as the underlying collision chain for the HashMap. It maintains both `head` and `tail` pointers along with a node count to guarantee constant-time insertions at both ends without the overhead of bidirectional pointers.

**Methods -** 
```cpp

template<typename T> //used to make the linked list generic ie it can store any type of data in the list
class ForwardList {
    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& value)
        };
        Node* head;
        Node* tail;
        int count;
    public:
        ForwardList(); //construct empty list
        template<typename Iterator>
        ForwardList(Iterator start, Iterator end); //construct from any iterable container
        void insert(const T& value, int index); //insert at position (O(n))
        void remove(int index); //remove node from a specific position (O(n))
        bool get(const T& value,int index) const; //safely retrieve value by index
        int search(const T& value) const; //search element and return index
        void clear(); //delete all nodes
        void print() const; //display all contents 
        int size() const; //return node count (O(1))
        bool isEmpty() const; //check whether empty
        ~ForwardList(); //destructor
        ForwardList(const ForwardList&); //copy constructor
        ForwardList& operator=(const ForwardList&); //assignment operator
};
```
- Wildcard Construction: The template<typename Iterator> constructor allows the list to be safely built from any iterable C++ collection (like vector or raw arrays) without relying on unpredictable container types.
- Safe Retrieval: The get() method returns the requested element through a reference parameter and uses a boolean return value to indicate success, avoiding ambiguous sentinel values for invalid indices.
- Improved Searching: The search() method returns the exact index of the found element or -1 if not found, providing more useful systemic information than a simple boolean result.

### 2 . DoublyLinkedList

The DoublyLinkedList trades a small amount of memory per node (for the prev pointer) to achieve vastly superior deletion speeds. By allowing bidirectional traversal, it eliminates the need for O(n) traversals during tail deletions, making it highly suitable for applications like LRU Caches.

Methods - 
```cpp
template<typename T> //used to make the linked list generic so that it can store any type of data in the list
class LinkedList {
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;
            Node(const T& value)
        };
        Node* head;
        Node* tail;
        int count;
    public:
        LinkedList(); //construct empty list 
        template<typename Iterator>
        LinkedList(Iterator start, Iterator end); //construct from any iterator range
        void insert(const T& value, int index); //insert at position (O(n))
        void remove(int index); //remove node from a specific position (O(n))
        bool get(int index, T& value) const; //safely retrieve value by index
        int search(const T& value) const; //search element and return index
        void clear(); //delete all nodes
        void print() const; //display all contents 
        int size() const; //return node count (O(1))
        bool isEmpty() const; //check whether empty
        ~LinkedList(); //destructor
        LinkedList(const LinkedList&); //copy constructor
        LinkedList& operator=(const LinkedList&); //assignment operator
};
---

## HashMap
It uses separate chaining using linkedlist for collision resolution and DynamicArray to manage the bucket table. It introduces an injectable hashing functor and a configurable load factor, allowing the user to tune memory and performance tradeoffs based on their specific dataset.
Methods - 

```cpp
template<typename Key> struct DefaultHash; //an empty blueprint for hashing 
template<>
struct DefaultHash<string>//default hash blueprint for string keys(DJB2 algorithm)
template<>
struct DefaultHash<int>//default hash blueprint for integer keys (simple modulo with key multiplied with a large prime number)
template<typename Key, typename Value, typename Hash = DefaultHash<Key>> //template to make the hashmap generic and allow custom hash functors.
class HashMap {
    private:
        struct Node {
            Key key; Value value; Node* next;
            Node(const Key& k, const Value& v)
        };
        DynamicArray<Node*> buckets; //It is an array where every slot holds a chain of boxes (Nodes)
        double loadFactor; //threshold to trigger rehashing
        int elementCount; /
        int primeindex; 
        static constexpr int PRIME_SIZES[] //takes some memory - giving O(1) lookup for next prime size 
        int getBucketIndex(const Key& key) const //internal method to compute bucket index using the hash functor
    public:
        HashMap(int initialBucketCount = 13, double loadFactor = 0.75); //construct with bucket count and load factor
        void set(const Key& key, const Value& value); //insert or update key-value pair
        bool get(const Key& key, Value& value) const; //safely retrieve value by key
        bool exists(const Key& key) const; //check if key exists
        void remove(const Key& key); //remove key-value pair
        void clear(); //delete all entries and reset state
        int size() const; //return sstored element count    
        double loadFactor() const; //return current load factor
        void rehash(); //resize bucket table and rehash entries
        ~HashMap(); //destructor
        HashMap(const HashMap&); //copy constructor
        HashMap& operator=(const HashMap&); //assignment operator
}
```
- The `get()` method returns the associated value through a reference parameter and uses a boolean return value to indicate success, avoiding ambiguous sentinel values for missing keys.
- Trades ~100 bytes of memory for a static array of prime numbers. This prevents massive CPU stalls during resizing and naturally scatters keys to avoid collision clustering.
- Uses an injectable functor for custom data types.
- Constructor accepts custom capacities and load factors, allowing systems to explicitly tune the tradeoff between memory footprint and guaranteed O(1) lookup speeds.

# Section 2 - Memory Layout
## DynamicArray
![DynamicArray Memory Layout](DynamicArrayMemoryLayout.jpeg)
### Rule of Three:
- Destructor : Deletes the dynamically allocated array and sets the pointer to nullptr.
- Copy Constructor : Allocates new memory and performs a deep copy by copying each element from the source array to the new array.
- Assignment Operator : Releases existing memory, allocates new memory , copies elements from the source array(Deep Copy), and returns a reference to the current object.
- Shallow copy was not used because both objects would point to the same memory causing double deletion and shared modification issues.

## LinkedList
![LinkedList Memory Layout](LinkedListMemoryLayout.jpeg)
### Rule of Three:
- Destructor : Traverses the list from head to nullptr and deletes each node.
- Copy Constructor : Creates a new list by traversing the source list and inserting copies of each node's value into the new list.
- Assignment Operator : Deletes the existing list then performs a deep copy of the source list by inserting copies of each node's value.
- Shallow copy was not used because both lists would share the same nodes leading to double deletion and shared modification issues.

## Hashmap
![Hashmap Memory Layout](HashmapMemoryLayout.jpeg)
### Rule of Three:
- Destructor : Traverses each bucket and deletes all nodes in the collision chains, then deletes the bucket array.
- Copy Constructor : Allocates a new bucket array and deep copy each key-value pair from the source Hashmap .
- Assignment Operator : Deletes the existing HashMap, allocates a new bucket array & deep copy each key-value pair from the source HashMap.
- Shallow copy was not used because both HashMaps would share the same bucket array and linked lists, leading to double deletion and shared modification issues.

# Section 3 – Complexity Estimates

### 1. DynamicArray

**append(const T& value)**
* **Best / Average Case:** O(1) amortized
* **Worst Case:** O(n)
* **Why:** Occasional resizes require allocating a new underlying array and copying all existing elements, which is an O(n) operation. However, because the capacity scales multiplicatively (e.g., doubling), resizes happen logarithmically rarely, meaning the cost averaged across N appends is O(1) per append.

**insert(const T& value, int index)**
* **Best Case:** O(1) (if inserting at the end)
* **Average / Worst Case:** O(n)
* **Why:** To maintain contiguous memory, every element to the right of the target index must be physically shifted one position to the right to make room for the new value.

**remove(int index)**
* **Best Case:** O(1) (if removing the last element)
* **Average / Worst Case:** O(n)
* **Why:** Similar to insertion, removing an element from the middle of a contiguous array requires shifting all subsequent elements one position to the left to fill the memory gap.

**get(int index, T& value) / set(int index, const T& value) 
* **Best / Average / Worst Case:** O(1)
* **Why:** The index directly calculates the exact memory address without requiring any traversal.

**reserve(int newCapacity)**
* **Best Case:** O(1) (if newCapacity <= current capacity)
* **Worst Case:** O(n)
* **Why:** If a size increase is required, it must allocate a new heap array and sequentially copy all `n` existing elements over to the new memory block.

**clear() / size() / isEmpty()**
* **Best / Average / Worst Case:** O(1)
* **Why:** These operations merely return or reset primitive internal state variables (like integers and pointers) without interacting with the stored data.

---

### 2. LinkedList

**insert(const T& value, int index) / remove(int index)**
* **Best Case:** O(1) (if index is 0)
* **Average / Worst Case:** O(n)
* **Why:** Linked lists do not support random access math. The structure must sequentially follow `next` pointers from the head to locate the specified positional index.

**search(const T& value)**
* **Best Case:** O(1) (if the target is the head node)
* **Average / Worst Case:** O(n)
* **Why:** The structure must sequentially traverse and compare the value of each node until a match is found or the tail is reached.

**clear()**
* **Best / Average / Worst Case:** O(n)
* **Why:** Every single node in the chain represents an independent heap allocation. The algorithm must visit and call `delete` on every node sequentially to prevent memory leaks.

---

### 3. HashMap

**set(const Key& key, const Value& value)**
* **Best / Average Case:** O(1)
* **Worst Case:** O(n)
* **Why:** The injected hash functor computes the bucket index instantly using arithmetic. It achieves O(1) average performance assuming a good hash distribution. The worst case O(n) occurs if an insertion triggers the load factor threshold, forcing a complete `rehash()`, or if severe collision clustering forces traversal of a massive chained list.

**get(const Key& key, Value& value) / exists(const Key& key)**
* **Best / Average Case:** O(1)
* **Worst Case:** O(n)
* **Why:** The hash functor calculates the exact memory bucket instantly. The operation is typically O(1), but degrades to O(n) in the worst case if weak hashing causes severe collisions, forcing the algorithm to linearly traverse a long linked list chain to find the matching key.

**remove(const Key& key)**
* **Best / Average Case:** O(1)
* **Worst Case:** O(n)
* **Why:** Finding the correct bucket is instantaneous via hashing. If the item is at the head of the collision chain, deletion is O(1). If the item is buried deep in a heavily collided chain, it requires O(n) traversal to locate and repair the pointers.

**rehash()**
* **Best / Average / Worst Case:** O(n)
* **Why:** To properly redistribute data, a new bucket array must be allocated. Every single key-value pair currently stored in the map must be visited, have its hash mathematically recalculated against the new prime capacity, and be re-inserted into the new chains.

**clear()**
* **Best / Average / Worst Case:** O(n)
* **Why:** The map must loop through every array bucket and subsequently traverse and `delete` every linked node within every collision chain to properly release all heap memory.

**size() / currentLoadFactor() 
* **Best / Average / Worst Case:** O(1)
* **Why:** These methods perform basic arithmetic or simply return tracked primitive state variables, independent of the volume of data stored in the map.

# Section 4 – Design Decisions

### DynamicArray
* Selected (initial capacity = 0) to avoid unnecessary heap allocation for unused containers.
* Capacity doubles whenever the array becomes full, providing amortized O(1) append operations.
* The array shrinks when utilization falls below 25%, improving memory utilization while avoiding excessive reallocations.
* Added `reserve()` to allow preallocation when the expected size is known, reducing repeated resizing operations.
* Rejected a fixed increment growth strategy because it results in frequent reallocations and poorer performance for large datasets.

---

### LinkedList
* Compile-Time Polymorphism Using template specialization allows the list to default to a memory-efficient Singly Linked structure, while offering a toggle for a Doubly Linked structure at compile time with zero runtime branching overhead.
* Maintained both head and tail pointers, allowing **O(1)** insertion at both the front and back of the list.
* Stored the current node count as a member variable so that `size()` executes in **O(1)**.
* Modified `search()` to return the index of the element instead of a boolean value, providing more useful information.

---

### HashMap
* Static Compile-Time Prime Capacity Array is used instead of Resizing by powers of 2 (e.g., capacity * 2) or calculating prime numbers algorithmically at runtime using a while(!isPrime()) loop because power-of-2 capacities cause severe collision clustering if a user provides a weak hash function, because the modulo operator effectively ignores the higher order bits of the hash. While calculating primes at runtime solves this, it introduces an unacceptable O(n​) CPU stall during the already expensive O(n) rehashing phase. A static prime array resolves both issues, trading ~100 bytes of memory for instantaneous, mathematically safe capacity lookups.
* Selected separate chaining using linked lists for collision handling because it simplifies deletion and integrates naturally with the LinkedList implementation.
* Configured the HashMap to rehash when the load factor reaches 0.75 in default case, maintaining efficient average-case lookup performance while the load factor can be set by passing the required load factor in the constructor.
* Implemented `get()` using a reference parameter and boolean return value, avoiding ambiguous sentinel values for missing keys.
* Considered linear probing, but rejected it due to clustering and more complex deletion.
* Considered*Red-Black Tree buckets, but rejected them because the additional balancing logic and implementation complexity were not justified for the expected performance.

---

### Memory Management

* All three data structures implement the Rule of Three.
* Copy operations perform deep copies, ensuring independent ownership of dynamically allocated memory.
* Each object exclusively owns its allocated resources, preventing memory leaks, dangling pointers, double deletion, and unintended aliasing.

---