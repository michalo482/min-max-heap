#define CATCH_CONFIG_MAIN

#include <vector>

#include "catch.hpp"

#include "min_max_heap.hpp"

TEST_CASE("Initialization", "[MinMaxHeap]") {

	SECTION("Initializing a min-max heap with no elements") {
		const MinMaxHeap<int> heap;

		SECTION("The heap has a size of zero") {
			REQUIRE(heap.Size() == 0);
		}
	}

	SECTION("Initializing a min-max heap with one element") {
		const auto value = 0;
		const MinMaxHeap<int> heap{value};

		SECTION("The size of the heap is one") {
			REQUIRE(heap.Size() == 1);
		}

		SECTION("The minimum element in the heap is the element initially added to the heap") {
			REQUIRE(heap.Min() == value);
		}

		SECTION("The maximum element in the heap is the element initially added to the heap") {
			REQUIRE(heap.Max() == value);
		}
	}

	SECTION("Initializing a min-max heap with a monotonically increasing collection of elements") {
		const MinMaxHeap<int> heap{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(heap.Size() == 10);
		}

		SECTION("The minimum element in the heap equals the smallest element in the collection the heap was constructed with") {
			REQUIRE(heap.Min() == 0);
		}

		SECTION("The maximum element in the heap equals the largest element in the collection the heap was constructed with") {
			REQUIRE(heap.Max() == 9);
		}
	}

	SECTION("Initializing a min-max heap with a monotonically decreasing collection of elements") {
		const MinMaxHeap<int> heap{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(heap.Size() == 10);
		}

		SECTION("The minimum element in the heap equals the smallest element in the collection the heap was constructed with") {
			REQUIRE(heap.Min() == 0);
		}

		SECTION("The maximum element in the heap equals the largest element in the collection the heap was constructed with") {
			REQUIRE(heap.Max() == 9);
		}
	}

	SECTION("Initializing a min-max heap with a random collection of elements") {
		const MinMaxHeap<int> heap{6, 8, 4, 10, 12, 5, 1, 14, 9, 2, 13, 3, 0, 7, 11};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(heap.Size() == 15);
		}

		SECTION("The minimum element in the heap equals to the smallest element in the collection the heap was constructed with") {
			REQUIRE(heap.Min() == 0);
		}

		SECTION("The maximum element in the heap equals to the largest element in the collection the heap was constructed with") {
			REQUIRE(heap.Max() == 14);
		}
	}

	SECTION("Initializing a min-max heap with a collection of duplicate elements") {
		const MinMaxHeap<int> heap{7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(heap.Size() == 10);
		}

		SECTION("The minimum element in the heap equals to the smallest element in the collection the heap was constructed with") {
			REQUIRE(heap.Min() == 7);
		}

		SECTION("The maximum element in the heap equals to the largest element in the collection the heap was constructed with") {
			REQUIRE(heap.Max() == 7);
		}
	}
}

TEST_CASE("Add", "[MinMaxHeap]") {
	MinMaxHeap<int> heap{9, 6, 1, 4, 8, 3, 2, 7, 5};

	SECTION("Adding a element to the heap which is smaller than its current minimum") {
		auto value = 0;
		heap.Add(value);

		SECTION("The heap size is increased by one") {
			REQUIRE(heap.Size() == 10);
		}

		SECTION("The minimum element in the heap equals the newly introduced element") {
			REQUIRE(heap.Min() == 0);
		}

		SECTION("The maximum element remains unchanged") {
			REQUIRE(heap.Max() == 9);
		}
	}

	SECTION("Adding a element to the heap which is greater than its current maximum") {
		heap.Add(10);

		SECTION("The heap size is increased by one") {
			REQUIRE(heap.Size() == 10);
		}

		SECTION("The minimum element remains unchanged") {
			REQUIRE(heap.Min() == 1);
		}

		SECTION("The maximum element in the heap equals the newly introduced element") {
			REQUIRE(heap.Max() == 10);
		}
	}
}

TEST_CASE("Remove", "[MinMaxHeap]") {
	MinMaxHeap<int> heap{9, 6, 1, 4, 8, 3, 2, 7, 5, 0};

	SECTION("Removing the minimum element") {
		const auto min_value = heap.RemoveMin();

		SECTION("The heap size is decreased by one") {
			REQUIRE(heap.Size() == 9);
		}

		SECTION("The element removed from the heap equals the smallest element in the initial collection") {
			REQUIRE(min_value == 0);
		}

		SECTION("The heap minimum equals the next smallest element") {
			REQUIRE(heap.Min() == 1);
		}

		SECTION("The maximum remains unchanged") {
			REQUIRE(heap.Max() == 9);
		}
	}

	SECTION("Removing the maximum element") {
		const auto max_value = heap.RemoveMax();

		SECTION("The heap size is decreased by one") {
			REQUIRE(heap.Size() == 9);
		}

		SECTION("The element removed from the heap equals the largest element in the initial collection") {
			REQUIRE(max_value == 9);
		}

		SECTION("The minimum remains unchanged") {
			REQUIRE(heap.Min() == 0);
		}

		SECTION("The heap maximum equals the next largest element") {
			REQUIRE(heap.Max() == 8);
		}
	}

	SECTION("Removing all elements from the heap") {

		SECTION("Elements removed by continuously extracting the minimum are in the correct order") {
			for (auto i = 0; i < 10; ++i) {
				REQUIRE(heap.RemoveMin() == i);
			}
		}

		SECTION("Elements removed by continuously extracting the maximum are in the correct order") {
			for (auto i = 9; i >= 0; --i) {
				REQUIRE(heap.RemoveMax() == i);
			}
		}
	}
}
