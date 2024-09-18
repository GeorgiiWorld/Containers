#ifndef SRC_INCLUDE_STACK_H_
#define SRC_INCLUDE_STACK_H_

namespace myn {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  stack() noexcept {}

  stack(std::initializer_list<value_type> const& items) noexcept {
    for (const auto item : items) {
      push(item);
    }
  }

  stack(const stack& other) {
    Node* current = other.top_;
    stack temp;
    while (current) {
      temp.push(current->value);
      current = current->next;
    }
    while (!temp.empty()) {
      push(temp.top());
      temp.pop();
    }
  }

  stack(stack&& other) noexcept : top_(other.top_), size_(other.size_) {
    other.top_ = nullptr;
    other.size_ = 0;
  }

  ~stack() { delete_stack(); }

  stack& operator=(const stack& other) {
    if (this != &other) {
      stack temp(other);
      swap(temp);
    }
    return *this;
  }

  stack& operator=(stack&& other) noexcept {
    if (this != &other) {
      delete_stack();
      top_ = other.top_;
      size_ = other.size_;
      other.top_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  const_reference top() const {
    if (empty()) {
      throw std::logic_error("stack is empty");
    }
    return top_->value;
  }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }

  void push(const_reference value) noexcept {
    Node* new_node = new Node(value);
    if (empty()) {
      top_ = new_node;
    } else {
      new_node->next = top_;
      top_ = new_node;
    }
    ++size_;
  }

  void pop() {
    if (empty()) {
      throw std::logic_error("stack is empty");
    }
    Node* old_top = top_;
    top_ = top_->next;
    delete old_top;
    --size_;
  }

  void swap(stack& other) noexcept {
    std::swap(top_, other.top_);
    std::swap(size_, other.size_);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  struct Node {
    value_type value;
    Node* next;

    Node(value_type val) : value(val), next(nullptr) {}
  };

  Node* top_ = nullptr;
  size_type size_ = 0;

  void delete_stack() {
    while (!empty()) {
      pop();
    }
  }
};

}  // namespace myn

#endif  // SRC_INCLUDE_STACK_H_
