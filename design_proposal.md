# Project 01 – Design Proposal
## Project Objective

The objective of this project is to design a reusable and memory-safe Data Structure Library consisting of DynamicArray, LinkedList, and HashMap implementations.

The proposed design supports explicit memory ownership. For the Design choices i evaluated multiple alternatives for each data structure and selected the one with best tradeoff keeping in mind that later on we will be using these data structures in our upcoming projects like redis lite and ensuring that the selected approach best satisfies the upcoming project requirements.


# Section 1 – Public API
The proposed design extends the suggested interface with several modifications and utility operations 

### 1. DynamicArray 
Methods - 
```cpp
DynamicArray() //construct empty array
void append(int value) //append element
void insert(int index, int value) //insert at position
void remove(int index) //remove element
bool get(int index, int& value) const //returns value
void set(int index, int value) // modify value at given index
void reserve(int newCapacity) //preallocate storage 
void popBack() //remove last element
void clear() //remove all elements
int size() const //return element count
int capacity() const //return allocated capacity
bool isEmpty() const //check whether empty 
~DynamicArray() //destructor
DynamicArray(const DynamicArray&) //copy constructor
DynamicArray& operator=(const DynamicArray&) //assignment operator
```
- The get() method returns the requested element through a reference parameter and uses a boolean return value to indicate success, avoiding ambiguous sentinel values for invalid indices.  
- The reserve() method enables preallocation of storage when the expected number of elements is known, reducing the number of reallocations during repeated insertions.  
- A dedicated set() method separates modification from insertion operations.  
- Utility functions such as `popBack()`,` clear()`,` capacity()`, and `isEmpty()` improve the usability and completeness of the Data Structure.

---

### 2. LinkedList 
The LinkedList is implemented as a singly linked structure while maintaining both head and tail pointers along with the current node count. This allows constant time insertion at both ends while minimizing per node memory overhead .
Methods - 

```cpp
LinkedList() //construct empty linkedlist
void insertFront(int value) //insert at front
void insertBack(int value) //insert at end 
void insert(int index, int value) //insert at position
void removeFront() //remove first node
void remove(int index) //remove node from a specific position
int search(int value) const //search element
void clear() //delete all nodes
void print() const //display all contents
int size() const //return node count
bool isEmpty() const //check whether empty
~LinkedList() //destructor
LinkedList(const LinkedList&) //copy constructor
LinkedList& operator=(const LinkedList&) //assignment operator
```
- The insertBack() method uses the tail pointer to achieve O(1) insertion at the end of the list, improving time complexity for common use cases.
- The search() method returns the index of the found element or -1 if not found, providing more useful information than a simple boolean result.
- Utility functions such as `remove()`,` clear()`, and `isEmpty()` improve the usability and completeness of the Data Structure.

---

## HashMap
Separate chaining using linked lists is selected as the collision handling strategy because it naturally supports dynamic growth, simplifies deletion
Methods - 

```cpp
HashMap() //construct empty hashmap with zero elements and initial bucket array
void set(string key, string value) //insert or update key-value pair 
bool get(string key, string& value) const //retrieve associated value 
bool exists(string key) const //check key existence 
void remove(string key) //remove key-value pair 
void clear() //remove all entries 
int size() const //return stored pair count 
double loadFactor() const //return current load factor 
int collisionCount() const //return current collision count 
void rehash() //resize bucket table 
~HashMap() //destructor 
HashMap(const HashMap&) //copy constructor 
HashMap& operator=(const HashMap&) //assignment operator

```
- The `get()` method returns the associated value through a reference parameter and uses a boolean return value to indicate success, avoiding ambiguous sentinel values for missing keys.
- The `rehash()` method allows manual resizing of the bucket table which can be useful for avoiding collisions and improving overall performance.
- The `collisionCount()` function provides useful diagnostic information for benchmarking and evaluation of hash quality.
- The `clear()` method removes all entries from the HashMap, freeing associated memory and resetting the internal state.  

# Section 2 - Memory Layout
- Handdrawn diagrams of the memory layout for each data structure are made seperately.

## DynamicArray

### Rule of Three:
- Destructor : Deletes the dynamically allocated array and sets the pointer to nullptr.
- Copy Constructor : Allocates new memory and performs a deep copy by copying each element from the source array to the new array.
- Assignment Operator : Releases existing memory, allocates new memory , copies elements from the source array(Deep Copy), and returns a reference to the current object.
- Shallow copy was not used because both objects would point to the same memory causing double deletion and shared modification issues.

## LinkedList

### Rule of Three:
- Destructor : Traverses the list from head to nullptr and deletes each node.
- Copy Constructor : Creates a new list by traversing the source list and inserting copies of each node's value into the new list.
- Assignment Operator : Deletes the existing list then performs a deep copy of the source list by inserting copies of each node's value.
- Shallow copy was not used because both lists would share the same nodes leading to double deletion and shared modification issues.

## Hashmap

### Rule of Three:
- Destructor : Traverses each bucket and deletes all nodes in the collision chains, then deletes the bucket array.
- Copy Constructor : Allocates a new bucket array and deep copy each key-value pair from the source Hashmap .
- Assignment Operator : Deletes the existing HashMap, allocates a new bucket array & deep copy each key-value pair from the source HashMap.
- Shallow copy was not used because both HashMaps would share the same bucket array and linked lists, leading to double deletion and shared modification issues.

# Section 3 – Complexity Estimates

## 1. DynamicArray

### append()

* **Best Case:** O(1)
* **Average Case:** O(1) amortized
* **Worst Case:** O(n)

**Why:** If free capacity exists, the element is inserted directly at the end. When the array becomes full, a larger array is allocated and all existing elements are copied. Since resizing occurs only occasionally due to capacity doubling, the average cost per insertion remains O(1).

---

### insert(index)

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Inserting at the end requires no shifting. For other positions, all subsequent elements must be shifted one position to the right.

---

### remove(index)

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Removing the last element requires no shifting. Removing an element from any other position requires shifting all following elements left by one position.

---

### get(index)

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The required memory address is calculated directly using the index without traversing the array.

---

### set(index)

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The element is updated directly at the calculated memory location.

---

### popBack()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The last element is removed by simply decreasing the stored size.

---

### clear()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The array releases its allocated memory and resets its metadata.

---

### reserve()

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** If the requested capacity is already available, no action is required. Otherwise, a larger array is allocated and all existing elements are copied.

---

### size(), capacity(), isEmpty()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** These functions simply return values stored as member variables.

---

## 2. LinkedList

### insertFront()

* **Best / Average / Worst:** O(1)

**Why:** Only the head pointer needs to be updated.

---

### insertBack()

* **Best / Average / Worst:** O(1)

**Why:** The maintained tail pointer allows direct insertion without traversal.

---

### insert(index)

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Insertion at the front is constant time. Otherwise, traversal is required to reach the target position.

---

### removeFront()

* **Best / Average / Worst:** O(1)

**Why:** The head pointer is updated to the next node.

---

### remove(index)

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Removing the first node is constant time, while removing nodes at arbitrary positions requires traversal.

---

### search()

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** The best case occurs when the element is the first node. Otherwise, nodes are visited sequentially until the element is found or the list ends.

---

### clear()

* **Best / Average / Worst:** O(n)

**Why:** Every allocated node must be visited and deleted individually.

---

### print()

* **Best / Average / Worst:** O(n)

**Why:** Every node must be traversed to display its value.

---

### size(), isEmpty()

* **Best / Average / Worst:** O(1)

**Why:** The current node count is maintained as a member variable.

---

## 3. HashMap

### set()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(n)

**Why:** The hash function directly computes the bucket index. Worst-case complexity occurs when all keys hash into the same bucket.

---

### get()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(n)

**Why:** Lookup usually accesses a short collision chain. In the worst case, every key belongs to the same bucket.

---

### exists()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(n)

**Why:** This operation performs the same lookup process as `get()`.

---

### remove()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(n)

**Why:** Deletion is efficient when collision chains are short but may require traversing an entire chain in the worst case.

---

### clear()

* **Best / Average / Worst:** O(n)

**Why:** Every key-value pair stored in the HashMap must be deleted.

---

### size(), loadFactor(), collisionCount()

* **Best / Average / Worst:** O(1)

**Why:** These operations return values maintained as member variables.

---

### rehash()

* **Best / Average / Worst:** O(n)

**Why:** Every existing key-value pair must be hashed again and inserted into the new bucket array.

---

**Note:** The average-case complexity of the HashMap assumes a well-distributed hash function and a maintained load factor below the rehash threshold.

# Section 4 – Design Decisions

### DynamicArray

* Selected **lazy allocation (initial capacity = 0)** to avoid unnecessary heap allocation for unused containers.
* Capacity doubles whenever the array becomes full, providing **amortized O(1)** append operations.
* The array shrinks when utilization falls below **25%**, improving memory utilization while avoiding excessive reallocations.
* Added `reserve()` to allow preallocation when the expected size is known, reducing repeated resizing operations.
* Rejected a **fixed increment growth strategy** because it results in frequent reallocations and poorer performance for large datasets.

---

### LinkedList

* Selected a **singly linked representation** to reduce per-node memory overhead.
* Maintained both **head and tail pointers**, allowing **O(1)** insertion at both the front and back of the list.
* Stored the current node count as a member variable so that `size()` executes in **O(1)**.
* Modified `search()` to return the **index of the element** instead of a boolean value, providing more useful information.
* Considered a **doubly linked list**, but rejected it because backward traversal is not required and the additional pointer increases both memory usage and implementation complexity.

---

### HashMap

* Selected **separate chaining using linked lists** for collision handling because it simplifies deletion and integrates naturally with the LinkedList implementation.
* Configured the HashMap to **rehash when the load factor reaches 0.70**, maintaining efficient average-case lookup performance.
* Added `collisionCount()` to support benchmarking and evaluation of hash distribution during testing.
* Implemented `get()` using a **reference parameter and boolean return value**, avoiding ambiguous sentinel values for missing keys.
* Considered **linear probing**, but rejected it due to clustering and more complex deletion.
* Considered **Red-Black Tree buckets**, but rejected them because the additional balancing logic and implementation complexity were not justified for the expected workload.

---

### Memory Management

* All three data structures implement the **Rule of Three**.
* Copy operations perform **deep copies**, ensuring independent ownership of dynamically allocated memory.
* Each object exclusively owns its allocated resources, preventing memory leaks, dangling pointers, double deletion, and unintended aliasing.

---