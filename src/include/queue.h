#ifndef SRC_INCLUDE_QUEUE_H_
#define SRC_INCLUDE_QUEUE_H_

namespace myn {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue() noexcept {}

  queue(std::initializer_list<value_type> const& items) noexcept {
    for (const auto item : items) {
      push(item);
    }
  }

  queue(const queue& q) {
    Node* current = q.head_;
    queue temp;
    while (current) {
      temp.push(current->value);
      current = current->ptr_next_;
    }
    while (!temp.empty()) {
      push(temp.front());
      temp.pop();
    }
  }

  queue(queue&& q) noexcept : head_(q.head_), tail_(q.tail_), size_(q.size_) {
    q.head_ = nullptr;
    q.tail_ = nullptr;
    q.size_ = 0;
  }

  ~queue() { delete_queue(); }

  queue& operator=(const queue& q) {
    if (this != &q) {
      queue temp(q);
      swap(temp);
    }
    return *this;
  }

  queue& operator=(queue&& q) noexcept {
    if (this != &q) {
      delete_queue();
      head_ = q.head_;
      tail_ = q.tail_;
      size_ = q.size_;
      q.head_ = nullptr;
      q.tail_ = nullptr;
      q.size_ = 0;
    }
    return *this;
  }

  const_reference front() const {
    if (empty()) {
      throw std::logic_error("queue is empty");
    }
    return head_->value;
  }

  const_reference back() const {
    if (empty()) {
      throw std::logic_error("queue is empty");
    }
    return tail_->value;
  }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }

  void push(const_reference value) noexcept {
    Node* new_node = new Node(value);
    if (empty()) {
      head_ = new_node;
      tail_ = new_node;
    } else {
      tail_->ptr_next_ = new_node;
      tail_ = new_node;
    }
    ++size_;
  }

  void pop() {
    if (empty()) {
      throw std::logic_error("queue is empty");
    }
    Node* old_H_ead = head_;
    head_ = head_->ptr_next_;
    delete old_H_ead;
    --size_;
  }

  void swap(queue& q) noexcept {
    std::swap(head_, q.head_);
    std::swap(tail_, q.tail_);
    std::swap(size_, q.size_);
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  struct Node {
    value_type value;
    Node* ptr_next_;

    explicit Node(value_type val) noexcept : value(val), ptr_next_(nullptr) {}
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_type size_ = 0;

  void delete_queue() {
    while (!empty()) {
      pop();
    }
  }
};

}  // namespace myn

#endif  // SRC_INCLUDE_QUEUE_H_