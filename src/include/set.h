#ifndef SRC_INCLUDE_SET_H_
#define SRC_INCLUDE_SET_H_

#include <initializer_list>
#include <memory>

#include "vector.h"

namespace myn {
template <class T>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type data_;
    Node* left_;
    Node* right_;
    Node* parent_;

    Node() : data_(), left_(nullptr), right_(nullptr), parent_(nullptr) {}
    Node(const value_type& value, Node* parentnode = nullptr)
        : data_(value), left_(nullptr), right_(nullptr), parent_(parentnode) {}
  };

 public:
  set() : root_(nullptr), end_(nullptr), size_(0) {}
  ~set() { deleteset(root_); }
  set(std::initializer_list<value_type> const& list);
  set(const set& other) : set() { root_ = copy(other.root_, other.end_); }
  set(set&& other);
  set& operator=(set&& other);
  set& operator=(const set& other);

  typedef class Iterator {
   public:
    friend class set;
    Iterator() : set_{nullptr}, current_{nullptr} {}
    Iterator(Node* iter, const set& obj) : set_{&obj}, current_{iter} {}
    Iterator(const Iterator& iter) : set_(iter.set_), current_(iter.current_) {}
    Iterator(Iterator&& iter) : set_(iter.set_), current_(iter.current_) {
      current_ = nullptr;
      set_ = nullptr;
    }
    ~Iterator() {}

    Iterator& operator=(const Iterator& iter) {
      current_ = iter.current_;
      set_ = iter.set_;
      return *this;
    }
    bool operator==(const Iterator& iter) const {
      return (current_ == iter.current_);
    }
    bool operator!=(const Iterator& iter) const {
      return (current_ != iter.current_);
    }
    reference operator*() { return current_->data_; }
    value_type* operator->() { return &operator*(); }
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);

   private:
    const set* set_;
    Node* current_;
  } iterator;
  typedef const Iterator const_iterator;
  iterator begin() const { return iterator(getLeftmostNode(root_), *this); }
  iterator end() const { return iterator(end_, *this); }
  const_iterator cbegin() const { return begin(); }
  const_iterator cend() const { return iterator(end_, *this); }

  size_type size() noexcept { return size_; }
  size_type max_size() noexcept;
  bool empty() { return (root_ == nullptr) ? true : false; }
  void clear();
  void swap(set& other);
  void merge(set& other);
  iterator find(const key_type& key) const;
  bool contains(const key_type& key) const;
  void erase(iterator pos);
  std::pair<iterator, bool> insert(const value_type& value) {
    return base_insert(value);
  }
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  Node* root_;
  Node* end_;
  std::size_t size_;
  std::allocator<typename set<T>::Node> allocator_;
  using BaseKeyType = typename std::decay<key_type>::type;
  BaseKeyType key_max_{};

  void deleteset(Node*& node);
  void transplant(Node* old, Node* fresh);
  Node* copy(Node* node, Node* end);
  Node* search(Node* node, const key_type key) const;
  Node* getLeftmostNode(Node* node) const;
  Node* getRightmostNode(Node* node) const;

 protected:
  std::pair<iterator, bool> base_insert(const value_type& value,
                                        bool insert = false);
  bool assign_value(typename set<T>::Node* current, const value_type& value,
                    bool insert);
  virtual bool comp_key_less(const key_type& first,
                             const key_type& second) const;
  bool comp_key_eq(const key_type& first, const key_type& second) const;
};

template <class T>
set<T>::set(std::initializer_list<T> const& list) : set() {
  for (const auto& item : list) {
    insert(item);
  }
}
template <class T>
set<T>::set(set&& other)
    : root_(std::move(other.root_)), end_(other.end_), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
  other.end_ = nullptr;
}
template <class T>
set<T>& set<T>::operator=(set&& other) {
  if (this != &other) {
    clear();
    root_ = other.root_;
    size_ = other.size_;
    end_ = other.end_;
    other.root_ = nullptr;
    other.size_ = 0;
    other.end_ = nullptr;
  }
  return *this;
}
template <class T>
set<T>& set<T>::operator=(const set& other) {
  if (this != &other) {
    root_ = copy(other.root_, other.end_);
  }
  return *this;
}

template <class T>
typename set<T>::Iterator& set<T>::Iterator::operator++() {
  if (current_ == nullptr) {
    throw std::invalid_argument("current_ == nullptr (++iter)");
  }
  if (current_->right_ != nullptr) {
    current_ = set_->getLeftmostNode(current_->right_);
  } else {
    Node* this_iter = nullptr;
    do {
      this_iter = current_;
      current_ = current_->parent_;
    } while (current_->parent_ && current_->right_ == this_iter);
  }
  return *this;
}
template <class T>
typename set<T>::Iterator set<T>::Iterator::operator++(int) {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}
template <class T>
typename set<T>::Iterator& set<T>::Iterator::operator--() {
  if (current_ == nullptr) {
    throw std::invalid_argument("current_ == nullptr (--iter)");
  }
  if (current_->left_ != nullptr) {
    current_ = set_->getRightmostNode(current_->left_);
  } else {
    Node* this_iter = nullptr;
    do {
      this_iter = current_;
      current_ = current_->parent_;
    } while (current_->parent_ && current_->left_ == this_iter);
  }
  return *this;
}
template <class T>
typename set<T>::Iterator set<T>::Iterator::operator--(int) {
  Iterator tmp = *this;
  --(*this);
  return tmp;
}

template <class T>
typename set<T>::size_type set<T>::max_size() noexcept {
  return std::allocator_traits<std::allocator<typename set<T>::Node>>::max_size(
      allocator_);
}
template <class T>
void set<T>::clear() {
  deleteset(root_);
  size_ = 0;
}
template <class T>
void set<T>::swap(set& other) {
  if (root_ != other.root_) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(end_, other.end_);
  }
}
template <class T>
void set<T>::merge(set& other) {
  if (root_ != other.root_) {
    for (const auto& value : other) {
      insert(value);
    }
  }
}
template <class T>
typename set<T>::Node* set<T>::copy(typename set<T>::Node* node,
                                    typename set<T>::Node* end) {
  if (node == nullptr || node == end) {
    return end_;
  }
  std::pair<iterator, bool> my_pair = insert(node->data_);
  Node* newNode = my_pair.first.current_;

  if (node->left_ != nullptr) {
    newNode->left_ = copy(node->left_, end);
  }
  if (node->right_ != nullptr) {
    newNode->right_ = copy(node->right_, end);
  }
  return newNode;
}
template <class T>
typename set<T>::iterator set<T>::find(const key_type& key) const {
  iterator iter(search(root_, key), *this);
  return iter;
}
template <class T>
bool set<T>::contains(const key_type& key) const {
  return (search(root_, key) == nullptr) ? false : true;
}

template <class T>
std::pair<typename set<T>::iterator, bool> set<T>::base_insert(const T& value,
                                                               bool insert) {
  std::pair<iterator, bool> return_pair;
  Node* new_node = allocator_.allocate(1);
  allocator_.construct(new_node, value, nullptr);
  return_pair.first.current_ = new_node;
  return_pair.second = true;
  ++size_;
  if (root_ == nullptr) {
    root_ = new_node;
    end_ = allocator_.allocate(1);
    allocator_.construct(end_);
    root_->right_ = end_;
    end_->parent_ = root_;
  } else {
    Node* current = root_;
    Node* parent = nullptr;
    while (current != nullptr && current != end_) {
      parent = current;
      if (comp_key_less(value, current->data_)) {
        current = current->left_;
      } else if (!comp_key_less(value, current->data_) &&
                 !comp_key_eq(value, current->data_)) {
        current = current->right_;
      } else {
        return_pair.first = iterator(current, *this);
        return_pair.second = assign_value(current, value, insert);
        allocator_.destroy(new_node);
        allocator_.deallocate(new_node, 1);
        --size_;
        return return_pair;
      }
    }
    if (comp_key_less(key_max_, value))
      key_max_ = static_cast<BaseKeyType>(value);
    new_node->parent_ = parent;
    if (comp_key_less(value, parent->data_)) {
      parent->left_ = new_node;
      new_node->parent_ = parent;
    } else {
      new_node->right_ = parent->right_;  // move end_
      parent->right_ = new_node;          // insert node
      new_node->parent_ = parent;         // insert parent
      if (comp_key_eq(key_max_, value)) {
        end_->parent_ = new_node;
      }  // update parent on end_
    }
  }
  return return_pair;
}

template <class T>
template <class... Args>
std::vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many(
    Args&&... args) {
  return {insert(std::forward<Args>(args))...};
}

template <class T>
bool set<T>::assign_value(typename set<T>::Node* current, const T& value,
                          bool insert) {
  bool res_insert = false;
  if (insert == true) {
    current->data_ = value;
    res_insert = true;
  }
  return res_insert;
}

template <class T>
bool set<T>::comp_key_less(const key_type& first,
                           const key_type& second) const {
  return (first < second) ? true : false;
}

template <class T>
bool set<T>::comp_key_eq(const key_type& first, const key_type& second) const {
  return (!comp_key_less(first, second) && !comp_key_less(second, first))
             ? true
             : false;
}

template <class T>
void set<T>::erase(typename set<T>::iterator pos) {
  if (pos == end() || pos.current_ == nullptr) {
    throw std::invalid_argument("iter == nullptr (erase)");
  }
  Node* node_to_rm = pos.current_;

  if (node_to_rm->left_ == nullptr) {
    transplant(node_to_rm, node_to_rm->right_);
  } else if (node_to_rm->right_ == nullptr) {
    transplant(node_to_rm, node_to_rm->left_);
  } else {
    iterator min_right(getLeftmostNode(node_to_rm->right_), *this);
    if (min_right.current_->parent_ != node_to_rm) {
      transplant(min_right.current_, min_right.current_->right_);
      min_right.current_->right_ = node_to_rm->right_;
      min_right.current_->right_->parent_ = min_right.current_;
    }
    transplant(node_to_rm, min_right.current_);
    min_right.current_->left_ = node_to_rm->left_;
    min_right.current_->left_->parent_ = min_right.current_;
  }
  allocator_.destroy(node_to_rm);
  allocator_.deallocate(node_to_rm, 1);
  --size_;
}

template <class T>
void set<T>::transplant(typename set<T>::Node* old,
                        typename set<T>::Node* fresh) {
  if (old->parent_ == nullptr) {
    root_ = fresh;
  } else if (old == old->parent_->left_) {
    old->parent_->left_ = fresh;
  } else {
    old->parent_->right_ = fresh;
  }
  if (fresh != nullptr) {
    fresh->parent_ = old->parent_;
  }
}

template <class T>
typename set<T>::Node* set<T>::getLeftmostNode(Node* node) const {
  while (node != nullptr && node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}
template <class T>
typename set<T>::Node* set<T>::getRightmostNode(Node* node) const {
  while (node != nullptr && node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}
template <class T>
typename set<T>::Node* set<T>::search(typename set<T>::Node* node,
                                      const key_type key) const {
  if (node == nullptr) return nullptr;
  if (comp_key_eq(node->data_, key)) return node;

  return (comp_key_less(key, node->data_)) ? search(node->left_, key)
                                           : search(node->right_, key);
}

template <class T>
void set<T>::deleteset(typename set<T>::Node*& node) {
  if (node == nullptr) {
    return;
  }
  if (node->left_ != nullptr) {
    deleteset(node->left_);
  }
  if (node->right_ != nullptr) {
    deleteset(node->right_);
  }
  allocator_.destroy(node);
  allocator_.deallocate(node, 1);
  node = nullptr;
}

};  // namespace myn

#endif  // SRC_INCLUDE_SET_H_