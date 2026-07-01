# Project 01 - Data Structure Library

Project 01 is a small C++17 data structure library built around a few core containers that were written from scratch and tested with GoogleTest. The repository includes a dynamic array, a singly linked list, a hash map with separate chaining, and a lightweight Redis-style command line interface that uses the hash map as its storage layer.

The goal of the project is simple: keep the code reusable, easy to reason about, and honest about memory ownership. The data structures manage their own allocations, support copy and assignment, and are exercised through a fairly broad test suite.

## What is inside

- DynamicArray: a manually managed resizable array with iterator support, safe element access, insertion/removal helpers, reserve, and shrink-to-size behavior.
- SinglyList: a singly linked list with append, insert, remove, search, indexed access, and deep copy semantics.
- HashMap: a templated hash map that uses separate chaining with SinglyList buckets and supports insert, get, remove, rehash, collisions, and custom hash functors.
- Redis Lite: a small interactive CLI that sits on top of HashMap and understands commands like SET, GET, DEL, EXISTS, COUNT, CLEAR, STATS, PRINT, DEBUG, HELP, and EXIT.

## Repository layout

```text
include/
  DynamicArray.h / DynamicArray.tpp
  SinglyList.h / SinglyList.tpp
  HashMap.h / HashMap.tpp
  headers/Redis
src/
  main.cpp
tests/
  dynamicarray/
  linkedlist/
  hashmap/
  redis/
docs/
  design_proposal/
  daily_journals/
  build_logs/
```

## Build requirements

- C++17 compiler
- CMake 3.10 or newer
- Ninja
- GoogleTest is fetched automatically by CMake during configure
- On this workspace, the preset expects the MSYS2 UCRT64 toolchain at C:/msys64/ucrt64/bin/gcc.exe and g++.exe

## How to build

Use the provided preset from the repository root:

```bash
cmake --build .
```

## How to test

The CMake project defines four test executables:

- datest for DynamicArray tests
- sltest for SinglyList tests
- hmtest for HashMap tests
- redistest for Redis Lite tests

After building, run the test suite with CTest or launch the executables directly from the build folder.

```bash
ctest 
```

## Redis Lite commands

The Redis shell in include/headers/Redis accepts one command per line.

```text
SET name Garv
GET name
DEL name
EXISTS name
COUNT
CLEAR
STATS
PRINT
DEBUG
HELP
EXIT
```

Values can contain spaces after the key. For example:

```text
SET quote Hello World From Redis Lite
GET quote
```

## Quick example

```cpp
#include "HashMap.h"

int main()
{
    HashMap<int, int> map;
    map.insert(1, 2);
    map.insert(2, 3);

    int value = 0;
    if (map.get(1, value))
    {
        std::cout << value << std::endl;
    }
}
```

## Notes

- The project is organized as template-heavy headers, so most implementation details live in the .tpp files.
- The codebase includes design notes and old build logs under docs/ that document the evolution of the data structures.
- main.cpp is a minimal demo entry point that exercises the hash map directly.
