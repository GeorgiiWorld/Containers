#ifndef SRC_INCLUDE_VECTOR_H_
#define SRC_INCLUDE_VECTOR_H_

#include <initializer_list>
#include <memory>

#include "random_access_iterator.h"

namespace myn {
template <class T, class A = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = myn::RandomAccessIterator<T>;
  using const_iterator = myn::constRandomAccessIterator<T>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  vector() : data_(0), size_(0), capacity_(0){};
  explicit vector(size_type n)
      : data_(alloc_.allocate(n)), size_(0), capacity_(n) {
    for (size_type i = 0; i < n; ++i) {
      data_[i] = T();
      ++size_;
    }
  };
  vector(std::initializer_list<value_type> const &items)
      : data_(alloc_.allocate(items.size())),
        size_(items.size()),
        capacity_(items.size()) {
    std::copy(items.begin(), items.end(), data_);
  };
  vector(const vector &v)
      : data_(alloc_.allocate(v.capacity_)),
        size_(v.size_),
        capacity_(v.capacity_) {
    for (size_type i = 0; i < v.size_; ++i) data_[i] = v.data_[i];
  }
  vector(vector &&v) : data_(v.size_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = 0;
    v.size_ = 0;
    v.capacity_ = 0;
  };
  ~vector() { alloc_.deallocate(data_, capacity_); };

  vector operator=(vector &&v) {
    if (this == &v) return *this;
    if (v.size_ <= capacity_) {
      for (size_type i = 0; i < v.size_; ++i) data_[i] = v.data_[i];
      return *this;
    }
    resize(v.size_);
    for (auto i = 0; i < v.size_; ++i) data_[i] = v.data_[i];
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
    return *this;
  };

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Position is out of range");
    return data_[pos];
  };
  reference operator[](size_type pos) { return data_[pos]; };
  const_reference operator[](size_type pos) const { return data_[pos]; };
  const_reference front() {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return data_[0];
  };
  const_reference back() {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return data_[size_];
  };
  T *data() noexcept { return data_; };
  iterator begin() { return iterator(data_); };
  iterator end() { return iterator(data_ + size()); };
  const_iterator cbegin() const { return const_iterator(data_); };
  const_iterator cend() const { return const_iterator(data_ + size()); };

  bool empty() const noexcept { return (cbegin() == cend()) ? true : false; };
  size_type size() const noexcept { return size_; };
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  };
  void reserve(size_type size) {
    if (size <= capacity_) return;
    value_type *ptr = alloc_.allocate(size);
    for (size_type i = 0; i < size_; ++i) alloc_.construct(&ptr[i], data_[i]);
    for (size_type i = 0; i < size_; ++i) alloc_.destroy(&data_[i]);
    alloc_.deallocate(data_, capacity_);
    data_ = ptr;
    capacity_ = size;
  };

  size_type capacity() const noexcept { return capacity_; };
  void shrink_to_fit() {
    if (size_ < capacity_) {
      value_type *new_data = 0;
      if (size_ > 0) {
        new_data = alloc_.allocate(size_);
        std::uninitialized_copy(data_, data_ + size_, new_data);
      }
      alloc_.deallocate(data_, capacity_);
      data_ = new_data;
      capacity_ = size_;
    }
  };
  void clear() noexcept {
    for (size_type i = 0; i < size_; ++i) alloc_.destroy(&data_[i]);
    size_ = 0;
  };

  iterator insert(iterator pos, const_reference value) {
    difference_type index = pos - begin();
    if (size_ == capacity_) {
      size_type new_capacity = capacity_ ? 2 * capacity_ : 1;
      reserve(new_capacity);
    }
    if (index < static_cast<difference_type>(size_)) {
      std::copy_backward(data_ + index, data_ + size_, data_ + size_ + 1);
    }
    data_[index] = value;
    ++size_;
    return iterator(data_ + index);
  };

  void erase(iterator pos) {
    if (pos + 1 != end()) {
      iterator next = pos + 1;
      while (next != end()) {
        *pos = std::move(*next);
        ++pos;
        ++next;
      }
    }
    --size_;
    alloc_.destroy(&data_[size_]);
  };

  void push_back(const_reference value) {
    if (capacity_ == 0) {
      reserve(4);
    } else if (size_ == capacity_) {
      reserve(2 * capacity_);
    }
    alloc_.construct(&data_[size_], value);
    ++size_;
  };
  void pop_back() { resize(size_ - 1); };
  void swap(vector &other) noexcept(
      std::allocator_traits<A>::propagate_on_container_swap::value ||
      std::allocator_traits<A>::is_always_equal::value) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  };

  void resize(size_type newsize) {
    if (newsize == capacity_) return;
    if (newsize < capacity_) {
      for (size_type i = newsize; i < size_; ++i) alloc_.destroy(&data_[i]);
    } else {
      reserve(newsize);
      for (size_type i = size_; i < newsize; ++i) alloc_.construct(&data_[i]);
    }
    size_ = newsize;
  };
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_type numArgs = sizeof...(Args);
    value_type temp[numArgs] = {std::forward<Args>(args)...};
    size_type index = pos - cbegin();
    if (size_ + numArgs > capacity_) {
      reserve(size_ + numArgs);
    }
    if (index < size_) {
      std::copy_backward(begin() + index, end(),
                         end() + difference_type(numArgs));
    }
    std::copy(temp, temp + numArgs, begin() + index);
    size_ += numArgs;
    return begin() + index;
  };

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    size_type numArgs = sizeof...(Args);
    value_type temp[numArgs] = {std::forward<Args>(args)...};
    if (size_ + numArgs > capacity_) {
      reserve(size_ + numArgs);
    }
    std::copy(temp, temp + numArgs, end());
    size_ += numArgs;
  };

 private:
  A alloc_;
  value_type *data_;
  size_type size_;
  size_type capacity_;
};
}  // namespace myn

#endif  // SRC_INCLUDE_VECTOR_H_