#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "double_ended_priority_queue.hpp"

template <typename T>
class MinMaxHeap final : public DoubleEndedPriorityQueue<T> {

public:

	MinMaxHeap() = default;

	MinMaxHeap(const std::initializer_list<T>& elements)
		: MinMaxHeap{elements.begin(), elements.end()} {}

	template <typename InputIterator>
	MinMaxHeap(const InputIterator& begin, const InputIterator& end)
		: elements_{begin, end} {

		static_assert(std::is_convertible<typename std::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value);
		static_assert(std::is_same<typename std::iterator_traits<InputIterator>::value_type, T>::value);

		for (auto i = parent(static_cast<int>(end - begin) - 1); i >= 0; --i) {
			heapify_down(i);
		}
	}

	void add(const T& element) override {

		elements_.push_back(element);
		heapify_up(static_cast<int>(elements_.size()) - 1);
	}

	T remove_min() override {

		const auto min_element = elements_[0];
		std::swap(elements_[0], elements_[elements_.size() - 1]);
		elements_.pop_back();
		heapify_down(0);

		return min_element;
	}

	T remove_max() override {

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

	const T& min() const override {
		return elements_[0];
	}

	const T& max() const override {

		if (elements_.size() <= 2) return elements_[elements_.size() - 1];

		const auto max_index = elements_[left_child(0)] > elements_[right_child(0)]
			? left_child(0)
			: right_child(0);

		return elements_[max_index];
	}

	size_t size() const override { return elements_.size(); }

private:

	std::vector<T> elements_;

	constexpr static bool min_level(const int index) { return static_cast<int>(log2(index + 1)) % 2 == 0; }
	constexpr static int left_child(const int index) { return 2 * index + 1; }
	constexpr static int right_child(const int index) { return 2 * index + 2; }
	constexpr static int parent(const int index) { return (index - 1) / 2; }

	constexpr static bool has_parent(const int index) { return index > 0; }
	bool has_left_child(const int index) const { return left_child(index) < static_cast<int>(elements_.size()); }
	bool has_right_child(const int index) const { return right_child(index) < static_cast<int>(elements_.size()); }

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

	void heapify_down(const int index) {

		if (min_level(index)) {
			return heapify_down(index, std::less<T>());
		}

		return heapify_down(index, std::greater<T>());
	}

	void heapify_down(const int index, const std::function<bool(T, T)>& comparator) {

		const auto descendants = get_descendants(index);

		if (descendants.empty()) return;

		const auto extremum = *std::min_element(
			descendants.begin(), descendants.end(), [&](const auto j, const auto k) {
				return comparator(elements_[j], elements_[k]);
			});

		if (extremum > right_child(index)) {
			if (comparator(elements_[extremum], elements_[index])) {
				std::swap(elements_[extremum], elements_[index]);

				if (!comparator(elements_[extremum], elements_[parent(extremum)])) {
					std::swap(elements_[extremum], elements_[parent(extremum)]);
				}

				heapify_down(extremum, comparator);
			}
		}
		else if (comparator(elements_[extremum], elements_[index])) {
			std::swap(elements_[extremum], elements_[index]);
		}
	}

	void heapify_up(const int index) {

		if (!has_parent(index)) return;

		if (min_level(index)) {
			if (elements_[index] > elements_[parent(index)]) {
				std::swap(elements_[index], elements_[parent(index)]);
				heapify_up(parent(index), std::greater<T>());
			}
			else {
				heapify_up(index, std::less<T>());
			}
		}
		else {
			if (elements_[index] < elements_[parent(index)]) {
				std::swap(elements_[index], elements_[parent(index)]);
				heapify_up(parent(index), std::less<T>());
			}
			else {
				heapify_up(index, std::greater<T>());
			}
		}
	}

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
