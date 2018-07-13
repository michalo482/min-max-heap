#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "double_ended_priority_queue.h"

template <typename T>
class min_max_heap : double_ended_priority_queue<T> {

	static std::function<bool(T, T)> min_comparator_ = [](const auto& a, const auto& b) { return a < b; };
	static std::function<bool(T, T)> max_comparator_ = [](const auto& a, const auto& b) { return a > b; };
	std::vector<T> elements_;

public:

	min_max_heap(const std::initializer_list<T>& elements = {}) : elements_{elements} {
		for (auto i = parent(static_cast<int>(elements.size()) - 1); i >= 0; --i) {
			heapify_down(i);
		}
	}

	void push(const T& element) override {
		elements_.push_back(element);
		heapify_up(elements_.size() - 1);
	}

	T pop_min() override {

		if (elements_.empty()) {
			throw std::runtime_error{"Cannot pop from an empty heap"};
		}

		const auto min_element = elements_[0];
		std::swap(elements_[0], elements_[elements_.size() - 1]);
		elements_.pop_back();
		heapify_down(0);

		return min_element;
	}

	T pop_max() override {

		if (elements_.empty()) {
			throw std::runtime_error{"Cannot pop from an empty heap"};
		}

		if (elements_.size() == 1) {
			const auto max_element = elements_[0];
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

	const T& peek_min() const override {

		if (elements_.empty()) {
			throw std::exception{"Cannot peek from an empty heap"};
		}

		return elements_[0];
	}

	const T& peek_max() const override {

		if (elements_.empty()) {
			throw std::exception{"Cannot peek from an empty heap"};
		}

		if (elements_.size() == 1) {
			const auto max_element = elements_[0];
			elements_.pop_back();
			return max_element;
		}

		const auto max_index = elements_[left_child(0)] > elements_[right_child(0)]
			? left_child(0)
			: right_child(0);

		return elements_[max_index];
	}

	size_t size() const override {
		return elements_.size();
	}

private:

	static int is_min_level(const int index) {
		return static_cast<int>(log2(index + 1)) % 2 == 0;
	}

	static int left_child(const int index) {
		return 2 * index + 1;
	}

	static int right_child(const int index) {
		return 2 * index + 2;
	}

	static int parent(const int index) {
		return (index - 1) / 2;
	}

	static bool has_parent(const int index) {
		return index > 0;
	}

	bool has_left_child(const int index) const {
		return left_child(index) < elements_.size();
	}

	bool has_right_child(const int index) const {
		return right_child(index) < elements_.size();
	}

	std::vector<int> get_children(const int i) const {

		std::vector<int> children;

		if (has_left_child(i)) {
			children.push_back(left_child(i));

			if (has_right_child(i)) {
				children.push_back(right_child(i));
			}
		}

		return children;
	}

	std::vector<int> get_descendants(const int i) const {

		std::vector<int> descendants;

		for (const auto child : get_children(i)) {
			descendants.push_back(child);

			for (const auto grandchild : get_children(child)) {
				descendants.push_back(grandchild);
			}
		}

		return descendants;
	}

	void heapify_down(const int i) {

		if (is_min_level(i)) {
			return heapify_down(i, min_comparator_);
		}

		return heapify_down(i, max_comparator_);
	}

	void heapify_down(const int index, const std::function<bool(T, T)> comparator) {

		const auto decendants = get_descendants(index);

		if (decendants.empty()) return;

		const auto target_index = *std::min_element(
			decendants.begin(), decendants.end(), [](const auto j, const auto k) {
				return comparator(elements_[j], elements_[k]);
			});

		if (target_index > right_child(index)) {

			if (comparator(elements_[target_index], elements_[index])) {
				std::swap(elements_[target_index], elements_[index]);

				if (!comparator(elements_[target_index], elements_[parent(target_index)])) {
					std::swap(elements_[target_index], elements_[parent(target_index)]);
				}

				heapify_down(target_index, comparator);
			}
		} else if (elements_[target_index] < elements_[index]) {
			std::swap(elements_[target_index], elements_[index]);
		}
	}

	void heapify_up(const int i) {

		if (!has_parent(i)) return;

		if (is_min_level(i)) {
			if (elements_[i] > elements_[parent(i)]) {
				std::swap(elements_[i], elements_[parent(i)]);
				heapify_up(elements_[parent(i)], std::max<T>);
			} else {
				heapify_up(i, std::min<T>);
			}
		} else {
			if (elements_[i] < elements_[parent(i)]) {
				std::swap(elements_[i], elements_[parent(i)]);
				heapify_up(elements_[parent(i)], min_comparator_);
			} else {
				heapify_up(elements_[i], max_comparator_);
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
