#ifndef HEAPT_H
#define HEAPT_H

#include <cassert>
#include <vector>

template<class T>
class Heap {
  using Container = std::vector<T>;

public:
  using Index = int64_t;
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

  bool isEmpty() const {
    assert(isStateCorrect());
    return data_.empty();
  }
  size_t size() const {
    assert(isStateCorrect());
    return data_.size();
  }

  Index add(const T& value) {
    data_.push_back(value);
    Index vertex = sieveUp(data_.size() - 1);
    assert(isStateCorrect());
    return vertex;
  }

  Index remove(Index vertex) {
    assert(isCorrectIndex(vertex));
    if (size() == 1) {
      assert(vertex == 0);
      data_.clear();
      assert(isStateCorrect());
      return -1;
    }
    if (static_cast<size_t>(vertex) == data_.size() - 1) {
      data_.resize(data_.size() - 1);
      return -1;
    }
    data(vertex) = std::move(data_.back());
    data_.resize(data_.size() - 1);
    vertex = sieveUp(vertex);
    vertex = sieveDown(vertex);
    assert(isStateCorrect());
    return vertex;
  }

  const T& max() const {
    assert(!isEmpty());
    return data(0);
  }

  const_iterator begin() const {
    return data_.begin();
  }
  const_iterator end() const {
    return data_.end();
  }
  const_iterator cbegin() const {
    return data_.cbegin();
  }
  const_iterator cend() const {
    return data_.cend();
  }
  const T& operator[](Index vertex) const {
    assert(isCorrectIndex(vertex));
    return data_[vertex];
  }

  int64_t height() const {
    return std::log2(size()) + 1;
  }

private:
  static constexpr const Index kUndefinedIndex = -1;

  static bool isDefined(Index vertex) {
    return vertex >= 0;
  }
  static Index leftChildIndex(Index vertex) {
    if (!isDefined(vertex))
      return kUndefinedIndex;
    return 2 * vertex + 1;
  }
  static Index rightChildIndex(Index vertex) {
    if (!isDefined(vertex))
      return kUndefinedIndex;
    return 2 * vertex + 2;
  }
  static Index parentIndex(Index vertex) {
    if (!isDefined(vertex))
      return kUndefinedIndex;
    return (vertex - 1) / 2;
  }
  //  static bool isRoot(Index vertex) {
  //    return vertex == 0;
  //  }

  bool hasParent(Index vertex) const {
    return vertex > 0;
  }
  bool hasLeftChild(Index vertex) const {
    return static_cast<size_t>(leftChildIndex(vertex)) < data_.size();
  }
  bool hasRightChild(Index vertex) const {
    return static_cast<size_t>(rightChildIndex(vertex)) < data_.size();
  }

  bool isCorrectIndex(Index vertex) const {
    return isDefined(vertex) && static_cast<size_t>(vertex) < data_.size();
  }
  bool isCorrectVertex(Index vertex) const {
    return doesParentConditionHold(vertex) &&
           doesLeftChildConditionHold(vertex) &&
           doesRightChildConditionHold(vertex);
  }

  bool doesParentConditionHold(Index vertex) const {
    return !hasParent(vertex) || (data(vertex) <= parent(vertex));
  }
  bool doesLeftChildConditionHold(Index vertex) const {
    return !hasLeftChild(vertex) || (data(vertex) >= leftChild(vertex));
  }
  bool doesRightChildConditionHold(Index vertex) const {
    return !hasRightChild(vertex) || (data(vertex) >= rightChild(vertex));
  }

  const T& data(Index vertex) const {
    return data_[vertex];
  }
  T& data(Index vertex) {
    return data_[vertex];
  }
  const T& parent(Index vertex) const {
    return data_[parentIndex(vertex)];
  }
  T& parent(Index vertex) {
    return data_[parentIndex(vertex)];
  }
  const T& leftChild(Index vertex) const {
    return data_[leftChildIndex(vertex)];
  }
  T& leftChild(Index vertex) {
    return data_[leftChildIndex(vertex)];
  }
  const T& rightChild(Index vertex) const {
    return data_[rightChildIndex(vertex)];
  }
  T& rightChild(Index vertex) {
    return data_[rightChildIndex(vertex)];
  }

  Index sieveUp(Index vertex) {
    if (!doesParentConditionHold(vertex)) {
      std::swap(data(vertex), parent(vertex));
      return sieveUp(parentIndex(vertex));
    }
    return vertex;
  }
  Index sieveDown(Index vertex) {
    Index Max = getMaximumChildIndex(vertex);
    if (Max == -1)
      return vertex;
    if (data(vertex) < data(Max)) {
      std::swap(data(vertex), data(Max));
      return sieveDown(Max);
    }
    return vertex;
  }
  Index getMaximumChildIndex(Index vertex) {
    if (!hasLeftChild(vertex))
      return kUndefinedIndex;
    if (!hasRightChild(vertex))
      return leftChildIndex(vertex);
    if (leftChild(vertex) > rightChild(vertex))
      return leftChildIndex(vertex);
    return rightChildIndex(vertex);
  }

  bool isStateCorrect() const {
    for (size_t index = 0; index < data_.size(); ++index) {
      if (!isCorrectVertex(index))
        return false;
    }
    return true;
  }

  Container data_;
};

#endif // HEAPT_H
