#pragma once

#include <exception>

/** \brief An exception thrown when attempting to perform an invalid operation an empty heap. */
class empty_heap_exception : std::exception {

public:

	/** \copydoc std::exception::what */
	char const* what() const override {
		return "An invalid operation was attempted on an empty heap";
	}
};
