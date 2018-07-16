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

		const min_max_heap<int> h{6, 8, 4, 5, 1, 9, 2, 3, 0, 7};

		SECTION("The size of the heap equals to the number of elements in the collection the heap was constructed with") {
			REQUIRE(h.size() == 10);
		}

		SECTION("The minimum element in the heap equals to the smallest element in the collection the heap was constructed with") {
			REQUIRE(h.min() == 0);
		}

		SECTION("The maximum element in the heap equals to the largest element in the collection the heap was constructed with") {
			REQUIRE(h.max() == 9);
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