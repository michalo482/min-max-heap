#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "empty_heap_exception.h"
#include "double_ended_priority_queue.h"

/**
 * \brief An heap data structure used to efficiently process the minimum and maximum elements in a collection.
 * \tparam T The type of the elements in the collection.
 */
template <typename T>
class min_max_heap : double_ended_priority_queue<T> {

	/** \brief The internal collection used to represent elements in the heap. */
	std::vector<T> elements_;

public:

	/** \brief Initializes an empty min-max heap using default construction. */
	min_max_heap() = default;

	/**
	 * \brief Initializes a min-max heap with a collection of elements.
	 * \param elements The collection of elements to initially build the min-max heap from.
	 */
	min_max_heap(const std::initializer_list<T>& elements) : elements_{elements} {
		for (auto i = parent(static_cast<int>(elements.size()) - 1); i >= 0; --i) {
			heapify_down(i);
		}
	}

	/**
	 * \brief Adds an element onto the heap.
	 * \param element The element to add onto the heap.
	 */
	void add(const T& element) override {
		elements_.push_back(element);
		heapify_up(static_cast<int>(elements_.size()) - 1);
	}

	/**
	 * \brief Removes the minimum element from the heap.
	 * \return The minimum element removed from the heap.
	 */
	T remove_min() override {

		if (elements_.empty()) throw empty_heap_exception{};

		const auto min_element = elements_[0];
		std::swap(elements_[0], elements_[elements_.size() - 1]);
		elements_.pop_back();
		heapify_down(0);

		return min_element;
	}

	/**
	 * \brief Removes the maximum element from the heap.
	 * \return The maximum element removed from the heap.
	 */
	T remove_max() override {

		if (elements_.empty()) throw empty_heap_exception{};

		if (elements_.size() <= 2) {
			const auto max_element = elements_[elements_.size() - 1];
			elements_.pop_back();
			return max_element;
		}

		const auto max_index = elements_[left_child(0)] > elements_[right_child(0)]
			? left_child(0)
			: right_child(0);

		const auto max_element = elements_[max_index];
		std::swap(elements_[max_index], elements_[elements_.size() - 1]);
		elements_.pop_back();
		heapify_down(max_index);

		return max_element;
	}

	/**
	 * \brief Gets the minimum element in the heap.
	 * \return A constant reference to the minimum element in the heap.
	 */
	const T& min() const override {

		return elements_.empty()
			? throw empty_heap_exception{}
			: elements_[0];
	}

	/**
	 * \brief Gets the maximum element from the heap.
	 * \return A constant reference to the maximum element from the heap.
	 */
	const T& max() const override {

		if (elements_.empty()) throw empty_heap_exception{};
		if (elements_.size() <= 2) return elements_[elements_.size() - 1];

		const auto max_index = elements_[left_child(0)] > elements_[right_child(0)]
			? left_child(0)
			: right_child(0);

		return elements_[max_index];
	}

	/**
	 * \brief Gets the number of elements in the heap.
	 * \return The number of elements in the heap.
	 */
	size_t size() const override {
		return elements_.size();
	}

private:

	/**
	 * \brief Determines if an element in the heap is on a minimum level.
	 * \param index The index of the element in the heap.
	 * \return \c true \c if the index is on a minimum level, otherwise \c false. \c
	 */
	static bool min_level(const int index) {
		return static_cast<int>(log2(index + 1)) % 2 == 0;
	}

	/**
	 * \brief Gets the index of the left child of an element in the heap.
	 * \param index The index of the element in the heap to get the left child for.
	 * \return The index of the left child.
	 */
	static int left_child(const int index) {
		return 2 * index + 1;
	}

	/**
	 * \brief Gets the index of the right child of an element in the heap.
	 * \param index The index of the element in the heap to get the right child for.
	 * \return The index of the right child.
	 */
	static int right_child(const int index) {
		return 2 * index + 2;
	}

	/**
	 * \brief Gets the index of the parent element in the heap.
	 * \param index The index of the child element to get the parent for.
	 * \return The index of the parent element.
	 */
	static int parent(const int index) {
		return (index - 1) / 2;
	}

	/**
	 * \brief Determines if an element in the heap has a parent element.
	 * \param index The index of the element in the heap to check if a parent exists.
	 * \return \c true \c if the element has a parent, otherwise \c false. \c
	 */
	static bool has_parent(const int index) {
		return index > 0;
	}

	/**
	 * \brief Determines if an element in the heap has a left child.
	 * \param index The index of the element in the heap to check if a left child exists.
	 * \return \c true \c if a left child exists, otherwise \c false. \c
	 */
	bool has_left_child(const int index) const {
		return left_child(index) < static_cast<int>(elements_.size());
	}

	/**
	 * \brief Determines if an element in the heap has a right child.
	 * \param index The index of the element in the heap to check if a right child exists.
	 * \return \c true \c if a right child exists, otherwise \c false. \c
	 */
	bool has_right_child(const int index) const {
		return right_child(index) < static_cast<int>(elements_.size());
	}

	/**
	 * \brief Gets the children for an element in the heap.
	 * \param index The index of the element in the heap to get the children for.
	 * \return A list of indices for child elements in the heap.
	 */
	std::vector<int> get_children(const int index) const {

		std::vector<int> children;

		if (has_left_child(index)) {
			children.push_back(left_child(index));

			if (has_right_child(index)) {
				children.push_back(right_child(index));
			}
		}

		return children;
	}

	/**
	 * \brief Gets the children and grandchildren for an element in the heap.
	 * \param index The index of the element in the heap to get descendants for.
	 * \return A list of indices for child and grandchild elements in the heap.
	 */
	std::vector<int> get_descendants(const int index) const {

		std::vector<int> descendants;

		for (const auto child : get_children(index)) {
			descendants.push_back(child);

			for (const auto grandchild : get_children(child)) {
				descendants.push_back(grandchild);
			}
		}

		return descendants;
	}

	/**
	 * \brief Restores the min-max heap starting at a specified index and moving down the heap.
	 * \param index The index to begin processing.
	 */
	void heapify_down(const int index) {

		if (min_level(index)) {
			return heapify_down(index, std::less<T>());
		}

		return heapify_down(index, std::greater<T>());
	}

	/**
	 * \brief Restores the min-max heap property starting at a specified index and moving down the heap..
	 * \param index The index to begin processing.
	 * \param comparator The min/max comparison function used to ensure heap ordering at a specific level.
	 */
	void heapify_down(const int index, const std::function<bool(T, T)>& comparator) {

		const auto decendants = get_descendants(index);

		if (decendants.empty()) return;

		const auto extremum_element = *std::min_element(
			decendants.begin(), decendants.end(), [&](const auto j, const auto k) {
				return comparator(elements_[j], elements_[k]);
			});

		if (extremum_element > right_child(index)) {
			if (comparator(elements_[extremum_element], elements_[index])) {
				std::swap(elements_[extremum_element], elements_[index]);

				if (!comparator(elements_[extremum_element], elements_[parent(extremum_element)])) {
					std::swap(elements_[extremum_element], elements_[parent(extremum_element)]);
				}

				heapify_down(extremum_element, comparator);
			}
		} else if (comparator(elements_[extremum_element], elements_[index])) {
			std::swap(elements_[extremum_element], elements_[index]);
		}
	}

	/**
	 * \brief Restores the min-max heap property starting at a specified index and moving up the heap.
	 * \param index The index of the element to being processing.
	 */
	void heapify_up(const int index) {

		if (!has_parent(index)) return;

		if (min_level(index)) {
			if (elements_[index] > elements_[parent(index)]) {
				std::swap(elements_[index], elements_[parent(index)]);
				heapify_up(parent(index), std::greater<T>());
			} else {
				heapify_up(index, std::less<T>());
			}
		} else {
			if (elements_[index] < elements_[parent(index)]) {
				std::swap(elements_[index], elements_[parent(index)]);
				heapify_up(parent(index), std::less<T>());
			} else {
				heapify_up(index, std::greater<T>());
			}
		}
	}

	/**
	 * \brief Restores the min-max heap property starting at a specified index and moving up the heap.
	 * \param index The index of the element to begin processing.
	 * \param comparator The min/max comparison function used to ensure heap ordering at the specified level.
	 */
	void heapify_up(const int index, const std::function<bool(T, T)>& comparator) {

		if (has_parent(index) && has_parent(parent(index))) {
			const auto grandparent = parent(parent(index));

			if (comparator(elements_[index], elements_[grandparent])) {
				std::swap(elements_[index], elements_[grandparent]);
				heapify_up(grandparent, comparator);
			}
		}
	}
};
