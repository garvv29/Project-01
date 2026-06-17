# Project 01 – Design Proposal
## Project Objective

The objective of this project is to design a reusable and memory-safe Data Structure Library consisting of DynamicArray, LinkedList, and HashMap implementations.

The proposed design supports explicit memory ownership, predictable performance, and maintainability. For the Design choices i evaluated multiple alternatives for each data structure and selected the one with best tradeoff keeping in mind that later on we will be using these data structures in our upcoming projects like redis lite and ensuring that the selected approach best satisfies the upcoming project requirements.


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

# Section 3 – Complexity Estimates

| Data Structure   | Operation          | Best Case | Average Case       | Worst Case | Justification                                                                                                                   |
| ---------------- | ------------------ | --------- | ------------------ | ---------- | ------------------------------------------------------------------------------------------------------------------------------- |
| **DynamicArray** | `append()`         | **O(1)**  | **O(1) amortized** | **O(n)**   | Inserts directly when capacity exists. Resizing requires copying all elements but occurs infrequently due to capacity doubling. |
|                  | `insert(index)`    | **O(1)**  | **O(n)**           | **O(n)**   | Insertion at the end requires no shifting, while insertion elsewhere shifts elements.                                |
|                  | `remove(index)`    | **O(1)**  | **O(n)**           | **O(n)**   | Removing the last element is constant time; removing from other positions requires shifting remaining elements.                 |
|                  | `get(index)`       | **O(1)**  | **O(1)**           | **O(1)**   | The memory address is calculated directly using the index without traversal.                                                    |
|                  | `set(index)`       | **O(1)**  | **O(1)**           | **O(1)**   | Updates the element directly at the computed memory location.                                                                   |
|                  | `popBack()`        | **O(1)**  | **O(1)**           | **O(1)**   | Removes the last element without shifting any data.                                                                             |
|                  | `clear()`          | **O(1)**  | **O(1)**           | **O(1)**   | Resets the container state by updating metadata and releasing allocated memory.                                                 |
|                  | `reserve()`        | **O(1)**  | **O(n)**           | **O(n)**   | If reallocation is required, all existing elements must be copied into the new storage.                                         |
|                  | `size()`           | **O(1)**  | **O(1)**           | **O(1)**   | The current element count is maintained as a member variable.                                                                   |
|                  | `capacity()`       | **O(1)**  | **O(1)**           | **O(1)**   | Returns the stored capacity value directly.                                                                                     |
|                  | `isEmpty()`        | **O(1)**  | **O(1)**           | **O(1)**   | Checks whether the stored size equals zero.                                                                                     |
| **LinkedList**   | `insertFront()`    | **O(1)**  | **O(1)**           | **O(1)**   | Only the head pointer is updated.                                                                                               |
|                  | `insertBack()`     | **O(1)**  | **O(1)**           | **O(1)**   | The maintained tail pointer enables direct insertion at the end.                                                                |
|                  | `insert(index)`    | **O(1)**  | **O(n)**           | **O(n)**   | Insertion at the front is constant time; otherwise traversal to the target position is required.                                |
|                  | `removeFront()`    | **O(1)**  | **O(1)**           | **O(1)**   | Removes the head node by updating a single pointer.                                                                             |
|                  | `remove(index)`    | **O(1)**  | **O(n)**           | **O(n)**   | Removal at the front is constant time; arbitrary positions require traversal.                                                   |
|                  | `search()`         | **O(1)**  | **O(n)**           | **O(n)**   | Best case occurs when the element is at the head, while average and worst cases require sequential traversal.                   |
|                  | `clear()`          | **O(n)**  | **O(n)**           | **O(n)**   | Every allocated node must be visited and deleted.                                                                               |
|                  | `print()`          | **O(n)**  | **O(n)**           | **O(n)**   | Every node is traversed once for output.                                                                                        |
|                  | `size()`           | **O(1)**  | **O(1)**           | **O(1)**   | The node count is maintained as a member variable.                                                                              |
|                  | `isEmpty()`        | **O(1)**  | **O(1)**           | **O(1)**   | Checks whether the stored node count is zero.                                                                                   |
| **HashMap**      | `set()`            | **O(1)**  | **O(1)**           | **O(n)**   | Direct bucket access through hashing; worst case occurs when all keys map to one bucket.                                        |
|                  | `get()`            | **O(1)**  | **O(1)**           | **O(n)**   | Bucket lookup is constant on average, but severe collisions require traversing an entire chain.                                 |
|                  | `exists()`         | **O(1)**  | **O(1)**           | **O(n)**   | Uses the same lookup process as `get()`.                                                                                        |
|                  | `remove()`         | **O(1)**  | **O(1)**           | **O(n)**   | Removal is constant on average but may require traversing a long collision chain.                                               |
|                  | `clear()`          | **O(n)**  | **O(n)**           | **O(n)**   | Every stored key-value pair must be removed and memory released.                                                                |
|                  | `size()`           | **O(1)**  | **O(1)**           | **O(1)**   | Returns the maintained element count.                                                                                           |
|                  | `loadFactor()`     | **O(1)**  | **O(1)**           | **O(1)**   | Computed directly using stored size and bucket count.                                                                           |
|                  | `collisionCount()` | **O(1)**  | **O(1)**           | **O(1)**   | Returns the maintained collision counter.                                                                                       |
|                  | `rehash()`         | **O(n)**  | **O(n)**           | **O(n)**   | Every existing key-value pair must be rehashed and inserted into the new bucket array.    
---                                      

- The average-case complexity of the HashMap assumes a well-distributed hash function and a maintained load factor below the rehash threshold.
- DynamicArray append() is O(1) amortized because the array is resized only occasionally. Although resizing copies all elements, it happens rarely, so the average time for each append operation remains O(1).

---
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