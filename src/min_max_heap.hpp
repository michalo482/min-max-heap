#pragma once

#include <algorithm>
#include <functional>
#include <vector>

template <typename T>
class MinMaxHeap {

public:
	MinMaxHeap(const std::initializer_list<T>& data = {})
		: MinMaxHeap{std::cbegin(data), std::cend(data)} {}

	template <typename TIterator>
	MinMaxHeap(const TIterator& begin, const TIterator& end) : data_{begin, end} {
		for (auto i = ParentIndex(static_cast<int>(end - begin) - 1); i >= 0; --i) {
			HeapifyDown(i);
		}
	}

	void Add(const T& value) {
		data_.push_back(value);
		HeapifyUp(Size() - 1);
	}

	void Add(T&& value) {
		data_.push_back(std::move(value));
		HeapifyUp(Size() - 1);
	}

	T RemoveMin() {
		const auto min_element = data_.at(0);
		std::swap(data_.at(0), data_.at(data_.size() - 1));
		data_.pop_back();
		HeapifyDown(0);
		return min_element;
	}

	T RemoveMax() {

		if (data_.size() <= 2) {
			const auto max_element = data_.at(data_.size() - 1);
			data_.pop_back();
			return max_element;
		}

		const auto left_child = data_.at(kRootLeftChildIndex);
		const auto right_child = data_.at(kRootRightChildIndex);
		const auto max_index = left_child > right_child ? kRootLeftChildIndex : kRootRightChildIndex;
		const auto max_element = data_.at(max_index);

		std::swap(data_.at(max_index), data_.at(data_.size() - 1));
		data_.pop_back();
		HeapifyDown(max_index);

		return max_element;
	}

	[[nodiscard]] const T& Min() const { return data_.at(0); }

	[[nodiscard]] const T& Max() const {

		if (data_.size() <= 2) return data_.at(data_.size() - 1);

		const auto left_child = data_.at(kRootLeftChildIndex);
		const auto right_child = data_.at(kRootRightChildIndex);
		const auto max_index = left_child > right_child ? kRootLeftChildIndex : kRootRightChildIndex;

		return data_.at(max_index);
	}

	[[nodiscard]] int Size() const noexcept { return static_cast<int>(data_.size()); }

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
				return comparator(data_.at(j), data_.at(k));
			});

		if (extremum > RightChildIndex(index)) {
			if (comparator(data_.at(extremum), data_.at(index))) {
				std::swap(data_.at(extremum), data_.at(index));

				if (!comparator(data_.at(extremum), data_.at(ParentIndex(extremum)))) {
					std::swap(data_.at(extremum), data_.at(ParentIndex(extremum)));
				}

				HeapifyDown(extremum, comparator);
			}
		} else if (comparator(data_.at(extremum), data_.at(index))) {
			std::swap(data_.at(extremum), data_.at(index));
		}
	}

	void HeapifyUp(const int index) {

		if (!HasParent(index)) return;

		if (IsMinLevel(index)) {
			if (data_.at(index) > data_[ParentIndex(index)]) {
				std::swap(data_.at(index), data_[ParentIndex(index)]);
				HeapifyUp(ParentIndex(index), std::greater<T>());
			} else {
				HeapifyUp(index, std::less<T>());
			}
		} else {
			if (data_.at(index) < data_[ParentIndex(index)]) {
				std::swap(data_.at(index), data_[ParentIndex(index)]);
				HeapifyUp(ParentIndex(index), std::less<T>());
			} else {
				HeapifyUp(index, std::greater<T>());
			}
		}
	}

	void HeapifyUp(const int index, const std::function<bool(T, T)>& comparator) {

		if (HasParent(index) && HasParent(ParentIndex(index))) {
			const auto grandparent = ParentIndex(ParentIndex(index));

			if (comparator(data_.at(index), data_[grandparent])) {
				std::swap(data_.at(index), data_[grandparent]);
				HeapifyUp(grandparent, comparator);
			}
		}
	}

	static constexpr int kRootLeftChildIndex = LeftChildIndex(0);
	static constexpr int kRootRightChildIndex = RightChildIndex(0);
	std::vector<T> data_;
};
