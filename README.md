# Mix-Max Heap

This project implements a fast, header-only implementation of a [double-ended priority queue](https://en.wikipedia.org/wiki/Double-ended_priority_queue) through the use of a data structure known as the [Min-Max Heap](https://github.com/matthew-rister/min-max-heap/blob/master/docs/Min-Max%20Heaps%20And%20Generalized%20Priority%20Queues.pdf) which can be used to process the minimum and maximum elements of a collection in constant time. One of the principal use cases for this is in creating bounded priority queues of a fixed length where minimum or maximum elements can be easily purged once the heap has reached capacity.

## Usage

To use, include [`min_max_heap.hpp`](https://github.com/matthew-rister/min-max-heap/blob/master/src/min-max-heap.hpp) which conforms to the canonical double-ended priority queue interface including

1. `const T& Min()`
2. `const T& Max()`
3. `void Add(const T& value)`
4. `T RemoveMin()`
5. `T RemoveMax()`
6. `int Size()`

## Build

To build the project, you must have cmake version 3 installed and a compiler that supports the C++17 language standard. You can then build from your favorite IDE or by running `cmake . && make` from the command line.

## Test

This project uses the [Catch2](https://github.com/catchorg/Catch2) testing library which is included in this repository as a single header-only file. Tests are currently configured to run as part of the main executable after building.
