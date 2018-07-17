#include "catch.h"

#include "min_max_heap.h"

TEST_CASE("Initialization", "[min_max_priority_queue]") {

	SECTION("Initializing a min-max heap with no elements") {

		const min_max_heap<int> h;

		SECTION("The heap has a size of zero") {
			REQUIRE(h.size() == 0);
		}

		SECTION("Attempting to access the minimum element in the heap throws an empty heap exception") {
			REQUIRE_THROWS_AS(h.min(), empty_heap_exception);
		}

		SECTION("Attempting to access the maximum element in the heap throws an empty heap exception") {
			REQUIRE_THROWS_AS(h.max(), empty_heap_exception);
		}
	}

	SECTION("Initializing a min-max heap with one element") {

		const auto element = 0;
		const min_max_heap<int> h{element};

		SECTION("The size of the heap is one") {
			REQUIRE(h.size() == 1);
		}

		SECTION("The minimum element in the heap is the element initially added to the heap") {
			REQUIRE(h.min() == element);
		}

		SECTION("The maximum element in the heap is the element initially added to the heap") {
			REQUIRE(h.max() == element);
		}
	}

	SECTION("Initializing a min-max heap with a monotonically increasing collection of elements") {

		const min_max_heap<int> h{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(h.size() == 10);
		}

		SECTION("The minimum element in the heap equals the smallest element in the collection the heap was constructed with") {
			REQUIRE(h.min() == 0);
		}

		SECTION("The maximum element in the heap equals the largest element in the collection the heap was constructed with") {
			REQUIRE(h.max() == 9);
		}
	}

	SECTION("Initializing a min-max heap with a monotonically decreasing collection of elements") {

		const min_max_heap<int> h{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(h.size() == 10);
		}

		SECTION("The minimum element in the heap equals the smallest element in the collection the heap was constructed with") {
			REQUIRE(h.min() == 0);
		}

		SECTION("The maximum element in the heap equals the largest element in the collection the heap was constructed with") {
			REQUIRE(h.max() == 9);
		}
	}

	SECTION("Initializing a min-max heap with a random collection of elements") {

		const min_max_heap<int> h{6, 8, 4, 10, 12, 5, 1, 14, 9, 2, 13, 3, 0, 7, 11};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(h.size() == 15);
		}

		SECTION("The minimum element in the heap equals to the smallest element in the collection the heap was constructed with") {
			REQUIRE(h.min() == 0);
		}

		SECTION("The maximum element in the heap equals to the largest element in the collection the heap was constructed with") {
			REQUIRE(h.max() == 14);
		}
	}

	SECTION("Initializing a min-max heap with a collection of duplicate elements") {

		const min_max_heap<int> h{7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(h.size() == 10);
		}

		SECTION("The minimum element in the heap equals to the smallest element in the collection the heap was constructed with") {
			REQUIRE(h.min() == 7);
		}

		SECTION("The maximum element in the heap equals to the largest element in the collection the heap was constructed with") {
			REQUIRE(h.max() == 7);
		}
	}
}

TEST_CASE("Add", "[min_max_heap]") {

	min_max_heap<int> h{9, 6, 1, 4, 8, 3, 2, 7, 5};

	SECTION("Adding a element to the heap which is smaller than its current minimum") {

		h.add(0);

		SECTION("The heap size is increased by one") {
			REQUIRE(h.size() == 10);
		}

		SECTION("The minimum element in the heap equals the newly introduced element") {
			REQUIRE(h.min() == 0);
		}

		SECTION("The maximum element remains unchanged") {
			REQUIRE(h.max() == 9);
		}
	}

	SECTION("Adding a element to the heap which is greater than its current maximum") {

		h.add(10);

		SECTION("The heap size is increased by one") {
			REQUIRE(h.size() == 10);
		}

		SECTION("The minimum element remains unchanged") {
			REQUIRE(h.min() == 1);
		}

		SECTION("The maximum element in the heap equals the newly introduced element") {
			REQUIRE(h.max() == 10);
		}
	}
}

TEST_CASE("Remove", "[min_max_heap]") {

	SECTION("Removing the minimum element") {

		min_max_heap<int> h{9, 6, 1, 4, 8, 3, 2, 7, 5, 0};
		const auto min = h.remove_min();

		SECTION("The heap size by one") {
			REQUIRE(h.size() == 9);
		}

		SECTION("The element removed from the heap equals the smallest element in the initial collection") {
			REQUIRE(min == 0);
		}

		SECTION("The heap minimum equals the next smallest element") {
			REQUIRE(h.min() == 1);
		}

		SECTION("The maximum remains unchanged") {
			REQUIRE(h.max() == 9);
		}
	}

	SECTION("Removing the maximum element") {

		min_max_heap<int> h{9, 6, 1, 4, 8, 3, 2, 7, 5, 0};
		const auto max = h.remove_max();

		SECTION("The heap size by one") {
			REQUIRE(h.size() == 9);
		}

		SECTION("The element removed from the heap equals the largest element in the initial collection") {
			REQUIRE(max == 9);
		}

		SECTION("The minimum remains unchanged") {
			REQUIRE(h.min() == 0);
		}

		SECTION("The heap maximum equals the next largest element") {
			REQUIRE(h.max() == 8);
		}
	}

	SECTION("Removing all elements from the heap") {

		min_max_heap<int> h{9, 6, 1, 4, 8, 3, 2, 7, 5, 0};

		SECTION("Elements removed by continuously extracting the minimum are in the correct order") {
			for (auto i = 0; i < 10; ++i) {
				REQUIRE(h.remove_min() == i);
			}
		}

		SECTION("Elements removed by continuously extracting the maximum are in the correct order") {
			for (auto i = 9; i >= 0; --i) {
				REQUIRE(h.remove_max() == i);
			}
		}
	}
}
