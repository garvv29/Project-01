## Project Objective
The objective of this project is to design a reusable, generic and memory-safe Data Structure Library consisting of DynamicArray, LinkedList, and HashMap implementations.

For the Design choices i evaluated multiple pros and cons for each data structure and selected the efficent ones which fullfil our requirements .The selected designs are intended to serve as reusable building blocks for future projects such as Redis Lite, ensuring that the chosen implementations satisfy both current functional requirements and future use cases.

# Dynamic Array -
* The DynamicArray manages a contiguous block of heap memory manually. Memory is allocated when capacity changes and released when the DynamicArray is destroyed. Existing elements are copied into the new allocation during resizing. 
## Public API - 
```cpp
template<typename T> //generic type parameter for any type of element
class DynamicArray {
    private:
        int size_;
        int capacity_;
        T *data;
        void resize(int newCapacity); //internal method to resize the array
        void copyelements(T* copyto,const T* copyfrom,int count); //internal method to copy elements from one array to another
        void destroy(); //internal method to destroy elements
        void deepcopy(const DynamicArray& other); //internal method to copy elements from another DynamicArray
        void init(); //internal method to initialize the array to reduce redudancy in constructors
        void construct(T* ptr,const T& value); //internal method to construct elements in the array
        T* allocate(int newCapacity); //internal method to allocate memory for the array
        void destoryobj(T* ptr); //internal method to destroy a single element
    public:
    //CONSTRUCTORS
        DynamicArray() //construct empty array
        DynamicArray(int cap) //construct with initial capacity
        DynamicArray(int count,const T& value)//to construct a Dynamic array of the given size with the all of them initialized 
        template<typename Iterator>
        DynamicArray(Iterator start,Iterator end); //construct from any iterable container
        template<typename Ds> //construct from any Data structure that supports iteration
        DynamicArray(const Ds& ds)
        DynamicArray(const DynamicArray&) //copy constructor
    //METHODS
        void append(const T& value) //append element
        void insert(int index,const T& value) //insert at position
        void remove(int index) //remove element
        bool get(int index,T& value) const //returns value safely
        void set(int index,const T& value) // modify value at given index
        void reserve(int newCapacity) //preallocate storage 
        void shrinktosize()//deallocate memory not in use of the array
        T& operator[](int index) //overloaded [] operator for direct access
        void clear() //remove all elements
        int size() const //return element count
        bool isEmpty() const //check whether empty
        T* begin() //return pointer to first element
        T* end() //return pointer to one past last element
    //DESTRUCTOR AND ASSIGNMENT OPERATOR
        void swap(DynamicArray& other) //swap contents with another DynamicArray helper function for assignment operator
        DynamicArray& operator=(const DynamicArray&) //assignment operator
        ~DynamicArray() //destructor
};
```
* It gives amortized O(1) time complexity for appending elements due to the doubling so this happens because array only doubles at powers of 2 which means that the number of operations needed would be n operations to insert n elements and (n-1) operations to copy elements during resizing  giving a total of 2n-1 operations which is for n element so for a single element it is 2n-1/n which is 2 and this can be called O(1) amortized time complexity.
* The DynamicArray class is a template class that can hold any type of element specified by the user.
* Internally the data is stored in a contiguous block of memory by using malloc and free for memory management.
* Internal methods like resize() and copyfrom() are used to manage memory and copy data when needed.
* The public API provides methods for constructing the array in multiple ways, appending and inserting elements, removing elements, accessing and modifying elements safely, reserving capacity, clearing the array, checking size and emptiness.
* The design includes a destructor, copy constructor, and assignment operator to get proper memory management and prevent from memory leaks and support for copying and assignment of DynamicArray instances.
* begin() and end() methods return pointers to the first element and one past the last element respectively, allowing for iteration over the elements in the array.
* `DynamicArray(Iterator start,Iterator end), DynamicArray(const Ds& ds) `constructor allows construction from any iterable Data Structure.

## Internal Representation -

![DynamicArray](DynamicArrayMemoryLayout.jpeg)

### Rule of Three:
- Destructor : Deletes the dynamically allocated array and sets the pointer to nullptr.
- Copy Constructor : Allocates new memory and performs a deep copy by copying each element from the source array to the new array.
- Assignment Operator : Releases existing memory, allocates new memory , copies elements from the source array(Deep Copy), and returns a reference to the current object.
- Shallow copy was not used because both objects would point to the same memory causing double deletion and shared modification issues.

## Time Complexity -
**append(const T& value)**
* **Best / Average Case:** O(1) amortized
* **Worst Case:** O(n)
* **Why:** resizes require allocating a new array and copying all existing elements, which is an O(n) operation although the average time for appending is O(1) due to the doubling strategy that minimizes the number of resizes needed as the array grows.

**insert(const T& value, int index)**
* **Best Case:** O(1) (if inserting at the end)
* **Average / Worst Case:** O(n)
* **Why:** To maintain contiguous memory, every element to the right of the target index must be physically shifted one position to the right to make room for the new value.

**remove(int index)**
* **Best Case:** O(1) (if removing the last element)
* **Average / Worst Case:** O(n)
* **Why:** Similar to insertion, removing an element from the middle of a contiguous array requires shifting all elements one position to the left to fill the memory gap.

**get(int index, T& value) / set(int index, const T& value)**
* **Best / Average / Worst Case:** O(1)
* **Why:** The index directly calculates the exact memory address without requiring any traversal.

**reserve(int newCapacity)**
* **Best Case:** O(1) (if newCapacity <= current capacity)
* **Worst Case:** O(n)
* **Why:** If a size increase is required, it must allocate a new heap array and sequentially copy all `n` existing elements over to the new memory block.

**clear() / size() / isEmpty()**
* **Best / Average / Worst Case:** O(1)
* **Why:** These operations merely return or reset primitive internal state variables (like integers and pointers) without interacting with the stored data.


## Design Decisions -

* Selected (initial capacity = 0) to avoid unnecessary heap allocation for unused containers.
* Capacity doubles whenever the array becomes full, providing amortized O(1) append operations.
* The array shrinks when utilization falls below 25%, improving memory utilization while avoiding excessive reallocations.
* Added `reserve()` to allow preallocation when the expected size is known, reducing repeated resizing operations.
* Rejected a fixed increment because it results in frequent reallocations and poorer performance for large datasets.
* The `get()` method returns a boolean to indicate success and uses a reference parameter to return the value, avoiding ambiguous sentinel values for invalid indices.
* `begin()` and `end()` methods provide iterators for return pointers to start and past to end memory address
* `DynamicArray(Iterator start,Iterator end) `constructor allows construction from any iterable container
