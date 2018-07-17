# Mix-Max Heap

## Overview

This repository aims to provide a fast implementation of the [double-ended priority queue](https://en.wikipedia.org/wiki/Double-ended_priority_queue) through the use of a data structure known as the [Min-Max Heap](https://en.wikipedia.org/wiki/Min-max_heap) which can be used to process the minimum and maximum elements of a collection in constant time. One of the principal use cases for this is in creating bounded priority queues of a fixed length where minimum or maximum elements can be easily purged once the heap has reached capacity.

## Building

The aim of this repository was to be written in pure C++17 with no runtime dependencies. The only dependency used by this project is the testing framework, [Catch](https://github.com/catchorg/Catch2), which is included in this repository as a single header. This project was built using MSBuild in Visual Studio 2017.7.5 Enterprise Edition. 

## Usage

Once the project has been built as either a static or dynamic library, it can be used by simply including `"min_max_priority_queue.h"` which then conforms to the canonical double-ended priority queue interface including

1. `T min()`
2. `T max()`
2. `void add(const T& value)`
2. `T remove_min()`
3. `T remove_max()`
4. `size()`

For more details see `"double_ended_priority_queue.h"`