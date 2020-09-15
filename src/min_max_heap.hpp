#pragma once

#include <algorithm>
#include <functional>
#include <vector>

template <typename T> class MinMaxHeap final {

public:
	MinMaxHeap() = default;

	MinMaxHeap(const std::initializer_list<T>& elements) : MinMaxHeap{std::cbegin(elements), std::cend(elements)} {}

	template <typename ElementIterator> MinMaxHeap(const ElementIterator& begin, const ElementIterator& end)
		: elements_{begin, end} {

		for (auto i = parent(static_cast<int32_t>(end - begin) - 1); i >= 0; --i) {
			heapify_down(i);
		}
	}

	void add(const T& element) {
		elements_.push_back(element);
		heapify_up(static_cast<int32_t>(elements_.size()) - 1);
	}

	T remove_min() {

		const auto min_element = elements_[0];
		std::swap(elements_[0], elements_[elements_.size() - 1]);
		elements_.pop_back();
		heapify_down(0);

		return min_element;
	}

	T remove_max() {

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

	[[nodiscard]] const T& min() const { return elements_[0]; }

	[[nodiscard]] const T& max() const {

		if (elements_.size() <= 2) return elements_[elements_.size() - 1];

		const auto max_index = elements_[left_child(0)] > elements_[right_child(0)]
			? left_child(0)
			: right_child(0);

		return elements_[max_index];
	}

	[[nodiscard]] size_t size() const { return elements_.size(); }

private:
	constexpr static bool min_level(const int32_t index) { return static_cast<int32_t>(log2(index + 1)) % 2 == 0; }
	constexpr static int32_t left_child(const int32_t index) { return 2 * index + 1; }
	constexpr static int32_t right_child(const int32_t index) { return 2 * index + 2; }
	constexpr static int32_t parent(const int32_t index) { return (index - 1) / 2; }

	constexpr static bool has_parent(const int32_t index) { return index > 0; }
	[[nodiscard]] bool has_left_child(const int32_t index) const { return left_child(index) < static_cast<int32_t>(elements_.size()); }
	[[nodiscard]] bool has_right_child(const int32_t index) const { return right_child(index) < static_cast<int32_t>(elements_.size()); }

	[[nodiscard]] std::vector<int32_t> get_children(const int32_t index) const {

		std::vector<int32_t> children;

		if (has_left_child(index)) {
			children.push_back(left_child(index));

			if (has_right_child(index)) {
				children.push_back(right_child(index));
			}
		}

		return children;
	}

	[[nodiscard]] std::vector<int32_t> get_descendants(const int32_t index) const {

		std::vector<int32_t> descendants;

		for (const auto child : get_children(index)) {
			descendants.push_back(child);

			for (const auto grandchild : get_children(child)) {
				descendants.push_back(grandchild);
			}
		}

		return descendants;
	}

	void heapify_down(const int32_t index) {

		if (min_level(index)) {
			return heapify_down(index, std::less<T>());
		}

		return heapify_down(index, std::greater<T>());
	}

	void heapify_down(const int32_t index, const std::function<bool(T, T)>& comparator) {

		const auto descendants = get_descendants(index);

		if (descendants.empty()) return;

		const auto extremum = *std::min_element(
			std::cbegin(descendants), std::cend(descendants), [&](const auto j, const auto k) {
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

	void heapify_up(const int32_t index) {

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

	void heapify_up(const int32_t index, const std::function<bool(T, T)>& comparator) {

		if (has_parent(index) && has_parent(parent(index))) {
			const auto grandparent = parent(parent(index));

			if (comparator(elements_[index], elements_[grandparent])) {
				std::swap(elements_[index], elements_[grandparent]);
				heapify_up(grandparent, comparator);
			}
		}
	}

	std::vector<T> elements_;
};
