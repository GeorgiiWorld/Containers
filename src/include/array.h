#ifndef SRC_INCLUDE_ARRAY_H_
#define SRC_INCLUDE_ARRAY_H_

#include <initializer_list>
#include <memory>

#include "random_access_iterator.h"

namespace myn {
template <class T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = myn::RandomAccessIterator<T>;
  using const_iterator = myn::constRandomAccessIterator<T>;
  using size_type = size_t;

  array() : data_{} {}
  array(const std::initializer_list<value_type>& items) {
    std::copy(items.begin(), items.end(), data_);
  }
  array(const array& a) {
    std::copy(std::begin(a.data_), std::end(a.data_), std::begin(data_));
  }
  array(array&& a) noexcept {
    std::move(std::begin(a.data_), std::end(a.data_), std::begin(data_));
    std::fill(std::begin(a.data_), std::end(a.data_),
              value_type{});  // обнуляем данные исходного массива
  }
  ~array() {}
  array& operator=(const array& a) {
    if (this != &a) {
      std::copy(a.data_, a.data_ + N, data_);
    }
    return *this;
  }
  array& operator=(array&& a) {
    if (this != &a) {
      std::move(std::begin(a.data_), std::end(a.data_), std::begin(data_));
      std::fill(std::begin(a.data_), std::end(a.data_),
                value_type{});  // обнуляем данные исходного массива
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) throw std::out_of_range("");
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }

  const_reference front() const {
    if (N == 0) {
      throw std::out_of_range("Array is empty");
    }
    return data_[0];
  }

  const_reference back() const {
    if (N == 0) {
      throw std::out_of_range("Array is empty");
    }
    return data_[N - 1];
  }

  iterator data() { return iterator(data_); }
  const_iterator data() const { return data_; }

  iterator begin() { return iterator(data_); }
  iterator end() { return iterator(data_ + N); }

  const_iterator begin() const { return data_; }
  const_iterator end() const { return data_ + N; }

  bool empty() const noexcept { return begin() == end(); }
  size_type size() const noexcept { return N; }

  size_type max_size() const noexcept { return N; }

  void swap(array& other) { std::swap(data_, other.data_); }

  void fill(const_reference value) {
    std::fill(std::begin(data_), std::end(data_), value);
  }

 private:
  value_type data_[N];
};

}  // namespace myn

#endif  // SRC_INCLUDE_ARRAY_H_