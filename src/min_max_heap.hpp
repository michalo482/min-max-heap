#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

template <typename T>
class MinMaxHeap {

public:
	MinMaxHeap() noexcept = default;
	MinMaxHeap(std::initializer_list<T> data)
		: MinMaxHeap{std::cbegin(data), std::cend(data)} {}

	template <typename TIterator>
	MinMaxHeap(const TIterator& begin, const TIterator& end) : data_(begin, end) {
		for (auto i = ParentIndex(static_cast<int>(end - begin) - 1); i >= 0; --i) {
			HeapifyDown(i);
		}
	}

	void Add(T value) {
		data_.push_back(std::move(value));
		HeapifyUp(Size() - 1);
	}

	T RemoveMin() {
		assert(!data_.empty());
		const auto min_value = data_[0];
		std::swap(data_[0], data_[Size() - 1]);
		data_.pop_back();
		HeapifyDown(0);
		return min_value;
	}

	T RemoveMax() {
		assert(!data_.empty());
		if (data_.size() <= 2) {
			const auto max_value = data_[Size() - 1];
			data_.pop_back();
			return max_value;
		}
		const auto left_child = data_[kRootLeftChildIndex];
		const auto right_child = data_[kRootRightChildIndex];
		const auto max_index = left_child > right_child ? kRootLeftChildIndex : kRootRightChildIndex;
		const auto max_value = data_[max_index];
		std::swap(data_[max_index], data_[Size() - 1]);
		data_.pop_back();
		HeapifyDown(max_index);
		return max_value;
	}

	[[nodiscard]] const T& Min() const noexcept {
		assert(!data_.empty());
		return data_[0];
	}

	[[nodiscard]] const T& Max() const noexcept {
		assert(!data_.empty());
		if (data_.size() <= 2) {
			return data_[Size() - 1];
		}
		const auto left_child = data_[kRootLeftChildIndex];
		const auto right_child = data_[kRootRightChildIndex];
		const auto max_index = left_child > right_child ? kRootLeftChildIndex : kRootRightChildIndex;
		return data_[max_index];
	}

	[[nodiscard]] int Size() const noexcept { return static_cast<int>(data_.size()); }

private:
	static bool IsMinLevel(const int index) { return static_cast<int>(std::log2(index + 1)) % 2 == 0; }

	static constexpr int LeftChildIndex(const int index) noexcept { return 2 * index + 1; }
	static constexpr int RightChildIndex(const int index) noexcept { return 2 * index + 2; }
	static constexpr int ParentIndex(const int index) noexcept { return (index - 1) / 2; }

	static constexpr bool HasParent(const int index) noexcept { return index > 0; }
	[[nodiscard]] bool HasLeftChild(const int index) const noexcept { return LeftChildIndex(index) < Size(); }
	[[nodiscard]] bool HasRightChild(const int index) const noexcept { return RightChildIndex(index) < Size(); }

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

	void HeapifyDown(const int i) {
		return IsMinLevel(i) ? HeapifyDown(i, kLessComparator) : HeapifyDown(i, kGreaterComparator);
	}

	template <typename Comparator>
	void HeapifyDown(const int i, const Comparator& comparator) {

		const auto descendants = GetDescendants(i);
		if (descendants.empty()) return;

		const auto extremum = *std::min_element(
			std::cbegin(descendants), std::cend(descendants), [this, &comparator](const auto j, const auto k) {
				return comparator(data_[j], data_[k]);
			});

		if (extremum > RightChildIndex(i)) {
			if (comparator(data_[extremum], data_[i])) {
				std::swap(data_[extremum], data_[i]);

				if (!comparator(data_[extremum], data_[ParentIndex(extremum)])) {
					std::swap(data_[extremum], data_[ParentIndex(extremum)]);
				}

				HeapifyDown(extremum, comparator);
			}
		} else if (comparator(data_[extremum], data_[i])) {
			std::swap(data_[extremum], data_[i]);
		}
	}

	void HeapifyUp(const int index) {

		if (!HasParent(index)) return;

		if (IsMinLevel(index)) {
			if (data_[index] > data_[ParentIndex(index)]) {
				std::swap(data_[index], data_[ParentIndex(index)]);
				HeapifyUp(ParentIndex(index), kGreaterComparator);
			} else {
				HeapifyUp(index, kLessComparator);
			}
		} else {
			if (data_[index] < data_[ParentIndex(index)]) {
				std::swap(data_[index], data_[ParentIndex(index)]);
				HeapifyUp(ParentIndex(index), kLessComparator);
			} else {
				HeapifyUp(index, kGreaterComparator);
			}
		}
	}

	template <typename Comparator>
	void HeapifyUp(const int index, const Comparator& comparator) {

		if (HasParent(index) && HasParent(ParentIndex(index))) {
			const auto grandparent = ParentIndex(ParentIndex(index));

			if (comparator(data_[index], data_[grandparent])) {
				std::swap(data_[index], data_[grandparent]);
				HeapifyUp(grandparent, comparator);
			}
		}
	}

	static constexpr auto kRootLeftChildIndex = LeftChildIndex(0);
	static constexpr auto kRootRightChildIndex = RightChildIndex(0);
	static constexpr auto kLessComparator = std::less<T>{};
	static constexpr auto kGreaterComparator = std::greater<T>{};
	std::vector<T> data_;
};
