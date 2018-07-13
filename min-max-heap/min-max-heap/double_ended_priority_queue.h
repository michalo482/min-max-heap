#pragma once

/**
 * \brief Defines the interface for a double-ended priority queue.
 * \detail A double-ended priority queue defines the interface for a data structure
 *		   which allows for efficient removal of both the minimum and maximum elements.
 * \tparam T The type of the elements in the collection.
 */
template <typename T>
class double_ended_priority_queue {

public:

	/** \brief Initializes a double-ended priority queue. */
	double_ended_priority_queue() = default;

	/**
	 * \brief Initializes a double-ended priority queue using copy construction.
	 * \param q The double-ended priority queue to copy.
	 */
	double_ended_priority_queue(const double_ended_priority_queue& q) = default;

	/**
	 * \brief Initializes a double-ended priority queue using move construction.
	 * \param q The double-ended priority queue to move.
	 */
	double_ended_priority_queue(double_ended_priority_queue&& q) noexcept = default;

	/**
	 * \brief Initializes a double-ended priority queue using copy assignment.
	 * \param q The double-ended priority queue to copy.
	 * \return A reference to the initialized double-ended priority queue.
	 */
	double_ended_priority_queue& operator=(const double_ended_priority_queue& q) = default;

	/**
	 * \brief Initializes a double-ended priority queue using move assignment.
	 * \param q The double-ended priority queue to move.
	 * \return A reference to the initialized double-ended priority queue.
	 */
	double_ended_priority_queue& operator=(double_ended_priority_queue&& q) noexcept = default;

	/** \brief Destroys the double-ended priority queue. */
	virtual ~double_ended_priority_queue() = default;

	/** \brief Pushes an element onto the double-ended priority queue. */
	virtual void push() const = 0;

	/**
	 * \brief Removes the minimum element from the double-ended priority queue.
	 * \return The minimum element in the priority queue.
	 */
	virtual T pop_min() const = 0;


	/**
	 * \brief Removes the maximum element from the double-ended priority queue.
	 * \return The maximum element in the double-ended priority queue.
	 */
	virtual T pop_max() const = 0;


	/**
	 * \brief Gets the minimum element in the double-ended priority queue.
	 * \return A constant reference to the minimum element in the double-ended priority queue.
	 */
	virtual const T& peek_min() const = 0;

	/**
	 * \brief Gets the maximum element in the double-ended priority queue.
	 * \return A constant reference to the maximum element in the double-ended priority queue.
	 */
	virtual const T& peek_max() const = 0;

	/**
	 * \brief Gets the number of elements in the double-ended priority queue.
	 * \return The number of elements in the double-ended priority queue.
	 */
	virtual size_t size() const = 0;
};
