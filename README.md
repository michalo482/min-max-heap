# Mix-Max Heap

This repository aims to provide a fast implementation of the [double-ended priority queue](https://en.wikipedia.org/wiki/Double-ended_priority_queue) through the use of a data structure known as the [Min-Max Heap](https://en.wikipedia.org/wiki/Min-max_heap) which can be used to process the minimum and maximum elements of a collection in constant time. One of the principal use cases for this is in creating bounded priority queues of a fixed length where minimum or maximum elements can be easily purged once the heap has reached capacity.

## Getting Started

This project was created with Visual Studio 2017 and built using MSBuild. Although it was written in pure C++ using only the standard library and the testing framework testing framework Catch, it has still yet to be verified on plaforms other than Windows.

## Usage

Once the project has been built as either a static or dynamic library, it can be used by simply including [`min_max_priority_queue.h`](https://github.com/matthew-rister/min-max-heap/blob/master/min-max-heap/src/min_max_heap.h) which then conforms to the canonical double-ended priority queue interface including

1. `const T& min()`
2. `const T& max()`
2. `void add(const T& value)`
2. `T remove_min()`
3. `T remove_max()`
4. `size()`

For more details see [`double_ended_priority_queue.h`](https://github.com/matthew-rister/min-max-heap/blob/master/min-max-heap/src/double_ended_priority_queue.h)
