#include <stack>

#include "main.h"

TEST(StackTest, Throw) {
  myn::stack<int> stack_int;
  myn::stack<double> stack_double;
  myn::stack<std::string> stack_string;

  EXPECT_EQ(stack_int.size(), 0U);
  EXPECT_THROW(stack_int.top(), std::logic_error);
  EXPECT_THROW(stack_int.pop(), std::logic_error);

  EXPECT_EQ(stack_double.size(), 0U);
  EXPECT_THROW(stack_double.top(), std::logic_error);
  EXPECT_THROW(stack_double.pop(), std::logic_error);

  EXPECT_EQ(stack_string.size(), 0U);
  EXPECT_THROW(stack_string.top(), std::logic_error);
  EXPECT_THROW(stack_string.pop(), std::logic_error);
}

TEST(StackTest, PushAndPop) {
  myn::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.top(), 1);
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(Stack, Constructor_Copy) {
  myn::stack<int> our_stack = {1, 2, 3};
  myn::stack<int> our_copy(our_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  EXPECT_EQ(our_copy.top(), std_copy.top());
}

TEST(Stack, Operator_Copy) {
  myn::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  myn::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = our_stack_int;
  std_stack_empty = std_stack_int;
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Constructor_Move) {
  myn::stack<int> our_stack = {1, 2, 3};
  myn::stack<int> our_move(std::move(our_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  EXPECT_EQ(our_move.top(), std_move.top());
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(Stack, Operator_Move) {
  myn::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  myn::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = std::move(our_stack_int);
  std_stack_empty = std::move(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(StackTest, AssignmentOperator) {
  myn::stack<int> s1;
  s1.push(1);
  s1.push(2);
  myn::stack<int> s2;
  s2 = s1;
  EXPECT_EQ(s1.top(), s2.top());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(StackTest, MoveAssignmentOperator) {
  myn::stack<int> s1;
  s1.push(1);
  s1.push(2);
  myn::stack<int> s2;
  s2 = std::move(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 2);
}

TEST(Test_stack, stack_test_emplace_front) {
  myn::stack<int> s1{1, 2, 3, 4, 5, 6, 7};
  myn::stack<int> stack_2{1, 2, 3, 4, 5, 6, 7, 88};
  int temp_1 = 88;
  s1.insert_many_front(std::move(temp_1));

  for (size_t i = s1.size(); i > 0; i--) {
    // std::cout << "std_stack: " << s1.top() << " "
    //           << "stack: " << stack_2.top() << std::endl;
    ASSERT_EQ(s1.top(), stack_2.top());
    stack_2.pop();
    s1.pop();
  }
}
