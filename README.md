# Mix-Max Heap

This repository aims to provide a fast header only implementation of a [double-ended priority queue](https://en.wikipedia.org/wiki/Double-ended_priority_queue) through the use of a data structure known as the [Min-Max Heap](https://en.wikipedia.org/wiki/Min-max_heap) which can be used to process the minimum and maximum elements of a collection in constant time. One of the principal use cases for this is in creating bounded priority queues of a fixed length where minimum or maximum elements can be easily purged once the heap has reached capacity.

## Usage

To use, include [`min_max_priority_queue.hpp`](https://github.com/matthew-rister/min_max_heap/blob/master/min_max_heap/src/min_max_heap.hpp) which conforms to the canonical double-ended priority queue interface including

1. `const T& min()`
2. `const T& max()`
2. `void add(const T& value)`
2. `T remove_min()`
3. `T remove_max()`
4. `size()`

## Compiling

Building is done using cmake. 