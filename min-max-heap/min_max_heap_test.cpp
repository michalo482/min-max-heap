#include "catch.h"

#include "min_max_heap.h"

TEST_CASE("Initialization", "[min_max_priority_queue]") {

	SECTION("Initializing an empty min-max heap contains no elements") {

		const min_max_heap<int> h;

		REQUIRE(h.size() == 0);
	}
}