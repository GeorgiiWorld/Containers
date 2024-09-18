#ifndef SRC_INCLUDE_LIST_H_
#define SRC_INCLUDE_LIST_H_

namespace myn {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  struct node {
    node() : prev_(nullptr), next_(nullptr){};
    node(const value_type &data, node *prev, node *next)
        : data_(data), prev_(prev), next_(next){};
    node(node *prev, node *next) : prev_(prev), next_(next){};
    value_type data_;
    node *prev_ = nullptr;
    node *next_ = nullptr;
  };
  size_t size_ = 0;
  node *node_ = nullptr;
  node *begin_ = &end_;
  node end_;

  void allocate(size_type n);

 public:
  template <typename value_type>
  class ListIterator {
   public:
    ListIterator(node *node) : current_(node){};

    ListIterator operator++() {
      node *temp = current_->next_;
      current_ = current_->next_;
      return temp;
    }

    ListIterator operator--() {
      node *temp = current_->prev_;
      current_ = current_->prev_;
      return temp;
    }

    reference operator*() { return current_->data_; }

    bool operator==(const ListIterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const ListIterator &other) const {
      return current_ != other.current_;
    }

    node *operator&() { return current_; }

   private:
    node *current_;
  };
  template <typename value_type>
  class ListConstIterator {
   public:
    ListConstIterator(const node *node) : current_(node){};

    ListConstIterator operator++() {
      node *temp = current_->next_;
      current_ = current_->next_;
      return temp;
    }

    ListConstIterator operator--() {
      node *temp = current_->prev_;
      current_ = current_->prev_;
      return temp;
    }

    const_reference operator*() const { return current_->data_; }

    bool operator==(const ListConstIterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const ListConstIterator &other) const {
      return current_ != other.current_;
    }

    const node *operator&() { return current_; }

   private:
    const node *current_;
  };
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

  // construct
  list() : list{list(0)} {};
  list(size_type n) { allocate(n); }
  list(std::initializer_list<value_type> const &items) {
    for (const auto &i : items) push_back(i);
  }
  list(const list &l) {
    node *current = l.begin_;
    for (size_type i = 0; i != l.size_; ++i) {
      push_back(current->data_);
      current = current->next_;
    }
  }
  list(list &&l) {
    push_back(value_type());
    swap(l);
  }
  ~list() {
    node *next;
    node *temp = begin_;
    for (size_type i = 0; i < size_; temp = next, ++i) {
      next = temp->next_;
      delete temp;
    }
  }
  void operator=(list &&l) {
    if (this != &l) {
      push_back(value_type());
      swap(l);
    }
  }

  // // List Iterators
  iterator begin() { return iterator(begin_); }
  iterator end() { return iterator(&end_); }
  const_iterator cbegin() const { return const_iterator(begin_); }
  const_iterator cend() const { return const_iterator(&end_); }

  // // List Element access
  const_reference front() { return begin_->data_; }
  const_reference back() {
    if (end_.prev_ != nullptr)
      return (end_.prev_)->data_;
    else
      return begin_->data_;
  }

  // // List Capacity
  bool empty() { return begin() == end(); }
  size_type size() { return size_; }
  size_type max_size() { return SIZE_MAX / sizeof(*this); }

  // // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    list<T> newList;
    for (auto it = cbegin(); it != pos; ++it) {
      newList.push_back(*it);
    }
    for (auto &&arg : {std::forward<Args>(args)...}) {
      newList.push_back(arg);
    }
    if (pos != cend()) {
      for (auto it = pos; it != cend(); ++it) {
        newList.push_back(*it);
      }
    }
    clear();
    for (auto &item : newList) {
      push_back(item);
    }
    auto it = end();
    for (size_t i = 0; i < sizeof...(Args); ++i) {
      --it;
    }
    return it;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (push_front(std::forward<Args>(args)), ...);
  }

 private:
  iterator change_elements(iterator a, iterator b);
};

template <typename T>
void list<T>::allocate(size_type n) {
  for (size_type i = 0; i < n; ++i) push_back(value_type());
}

template <typename T>
void list<T>::push_back(const_reference value) {
  if (end_.prev_ != nullptr) {
    node *old_last = end_.prev_;
    old_last->next_ = new struct node(value, old_last, &end_);
    end_.prev_ = old_last->next_;
  } else {
    begin_ = node_ = new struct node(value, &end_, &end_);
    end_.next_ = begin_;
    end_.prev_ = begin_;
  }
  ++size_;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  node *old_first = begin_;
  node *new_node = new struct node(value, &end_, old_first);
  old_first->prev_ = new_node;
  begin_ = new_node;
  end_.next_ = new_node;
  ++size_;
}

template <typename T>
void list<T>::clear() {
  for (; !empty();) pop_back();
}

template <typename T>
void list<T>::pop_back() {
  if (!empty()) {
    node *old_last = end_.prev_;
    if (old_last->prev_ != &end_) {
      node *prev_last = old_last->prev_;
      end_.prev_ = prev_last;
      prev_last->next_ = &end_;
    } else {
      end_.prev_ = nullptr;
      end_.next_ = nullptr;
      begin_ = &end_;
    }
    delete old_last;
    --size_;
  }
}

template <typename T>
void list<T>::pop_front() {
  node *old_first = begin_;
  if (old_first->next_ != &end_) {
    node *new_first = old_first->next_;
    begin_ = new_first;
    new_first->prev_ = &end_;
    end_.next_ = new_first;
  } else {
    end_.prev_ = nullptr;
    end_.next_ = nullptr;
    begin_ = &end_;
  }
  delete old_first;
  --size_;
}

template <typename T>
void list<T>::swap(list &other) {
  node *last_this = end_.prev_;
  node *last_other = other.end_.prev_;
  last_this->next_ = &other.end_;
  last_other->next_ = &end_;

  begin_->prev_ = &other.end_;
  other.begin_->prev_ = &end_;

  std::swap(size_, other.size_);
  std::swap(node_, other.node_);
  std::swap(begin_, other.begin_);
  std::swap(end_, other.end_);
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == begin()) {
    push_front(value);
    return begin();
  } else if (pos == end()) {
    push_back(value);
    return --(end());
  } else {
    node *current = &pos;
    node *prev_current = current->prev_;
    node *new_insert = new struct node(value, prev_current, current);
    prev_current->next_ = new_insert;
    current->prev_ = new_insert;
    ++size_;
    return iterator(new_insert);
  }
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
  iterator first = pos;
  iterator last = ++pos;
  return erase(first, last);
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
  node *prev = (&first)->prev_;
  node *next = (&last);
  node *del;

  for (auto i = first; i != last; --size_) {
    del = &i;
    ++i;
    delete del;
  }

  if (&first == begin_) begin_ = next;

  prev->next_ = next;
  next->prev_ = prev;

  return last;
}

template <typename T>
void list<T>::reverse() {
  if (!empty()) {
    node *prev;
    node *next;
    node *new_begin = end_.prev_;
    size_type temp_size = size_;

    for (node *i = begin_; temp_size; --temp_size) {
      prev = i->prev_;
      next = i->next_;

      i->prev_ = next;
      i->next_ = prev;

      i = next;
    }

    begin_ = new_begin;
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (!other.empty()) {
    iterator no_const_iterator = iterator(const_cast<node *>(&pos));
    for (auto i = other.begin(); i != other.end(); ++i) {
      insert(no_const_iterator, *i);
    }
  }
  other.clear();
}

template <typename T>
void list<T>::unique() {
  if (!empty()) {
    iterator end = iterator(end_.prev_);
    node *next;
    for (auto i = begin(); i != end;) {
      next = (&i)->next_;
      if (*i == next->data_)
        i = erase(i);
      else
        ++i;
    }
  }
}

template <typename T>
void list<T>::sort() {
  iterator end = this->end();
  size_type count2 = 0;
  for (; this->begin() != end; --end) {
    bool swapped = false;

    count2 = 0;
    for (node *pos = begin_; pos != (&end)->prev_; pos = pos->next_, ++count2) {
      node *next = pos->next_;
      if (next->data_ < pos->data_) {
        change_elements(iterator(pos), iterator(next));
        pos = next;
        swapped = true;
      }
      if (count2 > size_) {
        throw std::logic_error("экстренный выход");
      }
    }

    if (swapped == false) break;
  }
}

template <typename T>
void list<T>::merge(list &other) {
  auto a = this->begin();
  auto b = other.begin();

  for (; a != this->end() && b != other.end();) {
    if (*b < *a) {
      this->insert(a, *b);
      ++b;
    } else {
      ++a;
    }
  }

  for (; b != other.end(); ++b) this->insert(a, *b);
};

template <typename T>
typename list<T>::iterator list<T>::change_elements(iterator a, iterator b) {
  node *self_a = &a;
  node *neig_a_prev = self_a->prev_;
  node *neig_a_next = self_a->next_;
  node *self_b = &b;
  node *neig_b_prev = self_b->prev_;
  node *neig_b_next = self_b->next_;

  if (neig_a_next == self_b) {
    self_a->prev_ = self_b;
    self_b->next_ = self_a;
    self_b->prev_ = neig_a_prev;
    self_a->next_ = neig_b_next;

    neig_a_prev->next_ = self_b;
    neig_b_next->prev_ = self_a;
  } else {
    std::swap(self_a->next_, self_b->next_);
    std::swap(self_a->prev_, self_b->prev_);
    std::swap(neig_a_prev->next_, neig_b_prev->next_);
    std::swap(neig_a_next->prev_, neig_b_next->prev_);
  }
  if (self_a == begin_) begin_ = self_b;

  return iterator(self_b);
};

}  // namespace myn

#endif  // SRC_INCLUDE_LIST_H_