#pragma once

#include <algorithm>
#include <functional>
#include <vector>

template <typename T>
class MinMaxHeap {

public:
	MinMaxHeap() noexcept = default;
	MinMaxHeap(const std::initializer_list<T>& elements) : MinMaxHeap{std::begin(elements), std::end(elements)} {}
	
	template <typename TIterator> 
	MinMaxHeap(const TIterator& begin, const TIterator& end) : elements_{begin, end} {
		for (auto i = ParentIndex(static_cast<int>(end - begin) - 1); i >= 0; --i) {
			HeapifyDown(i);
		}
	}

	void Add(const T& element) {
		elements_.push_back(element);
		HeapifyUp(Size() - 1);
	}

	T RemoveMin() {
		const auto min_element = elements_.at(0);
		std::swap(elements_.at(0), elements_.at(Size() - 1));
		elements_.pop_back();
		HeapifyDown(0);
		return min_element;
	}

	T RemoveMax() {
		
		if (elements_.size() <= 2) {
			const auto max_element = elements_.at(Size() - 1);
			elements_.pop_back();
			return max_element;
		}

		const auto left_child = elements_.at(kRootLeftChildIndex);
		const auto right_child = elements_.at(kRootRightChildIndex);
		const auto max_index = left_child > right_child ? kRootLeftChildIndex : kRootRightChildIndex;
		const auto max_element = elements_.at(max_index);

		std::swap(elements_.at(max_index), elements_.at(Size() - 1));
		elements_.pop_back();
		HeapifyDown(max_index);

		return max_element;
	}

	[[nodiscard]] const T& Min() const { return elements_.at(0); }

	[[nodiscard]] const T& Max() const {
		
		if (elements_.size() <= 2) return elements_.at(elements_.size() - 1);
		
		const auto left_child = elements_.at(kRootLeftChildIndex);
		const auto right_child = elements_.at(kRootRightChildIndex);
		const auto max_index = left_child > right_child ? kRootLeftChildIndex : kRootRightChildIndex;
		
		return elements_.at(max_index);
	}

	[[nodiscard]] int Size() const noexcept { return static_cast<int>(elements_.size()); }

private:
	static bool IsMinLevel(const int index) noexcept { return static_cast<int>(log2(index + 1)) % 2 == 0; }
	static constexpr int LeftChildIndex(const int index) { return 2 * index + 1; }
	static constexpr int RightChildIndex(const int index) { return 2 * index + 2; }
	static constexpr int ParentIndex(const int index) { return (index - 1) / 2; }

	static constexpr bool HasParent(const int index) { return index > 0; }
	[[nodiscard]] bool HasLeftChild(const int index) const { return LeftChildIndex(index) < Size(); }
	[[nodiscard]] bool HasRightChild(const int index) const { return RightChildIndex(index) < Size(); }

	[[nodiscard]] std::vector<int> GetChildren(const int index) const {
		std::vector<int> children;

		if (HasLeftChild(index)) {
			children.push_back(LeftChildIndex(index));

			if (HasRightChild(index)) {
				children.push_back(RightChildIndex(index));
			}
		}

		return children;
	}

	[[nodiscard]] std::vector<int> GetDescendants(const int index) const {
		std::vector<int> descendants;

		for (const auto child : GetChildren(index)) {
			descendants.push_back(child);

			for (const auto grandchild : GetChildren(child)) {
				descendants.push_back(grandchild);
			}
		}

		return descendants;
	}

	void HeapifyDown(const int index) {
		return IsMinLevel(index) ? HeapifyDown(index, std::less<T>()) : HeapifyDown(index, std::greater<T>());
	}

	void HeapifyDown(const int index, const std::function<bool(T, T)>& comparator) {

		const auto descendants = GetDescendants(index);
		if (descendants.empty()) return;

		const auto extremum = *std::min_element(
			std::cbegin(descendants), std::cend(descendants), [&](const auto j, const auto k) {
				return comparator(elements_.at(j), elements_.at(k));
			});

		if (extremum > RightChildIndex(index)) {
			if (comparator(elements_.at(extremum), elements_.at(index))) {
				std::swap(elements_.at(extremum), elements_.at(index));

				if (!comparator(elements_.at(extremum), elements_.at(ParentIndex(extremum)))) {
					std::swap(elements_.at(extremum), elements_.at(ParentIndex(extremum)));
				}

				HeapifyDown(extremum, comparator);
			}
		} else if (comparator(elements_.at(extremum), elements_.at(index))) {
			std::swap(elements_.at(extremum), elements_.at(index));
		}
	}

	void HeapifyUp(const int index) {

		if (!HasParent(index)) return;

		if (IsMinLevel(index)) {
			if (elements_.at(index) > elements_[ParentIndex(index)]) {
				std::swap(elements_.at(index), elements_[ParentIndex(index)]);
				HeapifyUp(ParentIndex(index), std::greater<T>());
			} else {
				HeapifyUp(index, std::less<T>());
			}
		} else {
			if (elements_.at(index) < elements_[ParentIndex(index)]) {
				std::swap(elements_.at(index), elements_[ParentIndex(index)]);
				HeapifyUp(ParentIndex(index), std::less<T>());
			} else {
				HeapifyUp(index, std::greater<T>());
			}
		}
	}

	void HeapifyUp(const int index, const std::function<bool(T, T)>& comparator) {

		if (HasParent(index) && HasParent(ParentIndex(index))) {
			const auto grandparent = ParentIndex(ParentIndex(index));

			if (comparator(elements_.at(index), elements_[grandparent])) {
				std::swap(elements_.at(index), elements_[grandparent]);
				HeapifyUp(grandparent, comparator);
			}
		}
	}

	static constexpr int kRootLeftChildIndex = LeftChildIndex(0);
	static constexpr int kRootRightChildIndex = RightChildIndex(0);
	std::vector<T> elements_;
};
