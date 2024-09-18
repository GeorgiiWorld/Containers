#include <queue>

#include "main.h"

TEST(QueueTest, Throw) {
  myn::queue<int> queue_int;
  myn::queue<double> queue_double;
  myn::queue<std::string> queue_string;

  EXPECT_EQ(queue_int.size(), 0U);
  EXPECT_THROW(queue_int.front(), std::logic_error);
  EXPECT_THROW(queue_int.back(), std::logic_error);
  EXPECT_THROW(queue_int.pop(), std::logic_error);

  EXPECT_EQ(queue_double.size(), 0U);
  EXPECT_THROW(queue_double.front(), std::logic_error);
  EXPECT_THROW(queue_double.back(), std::logic_error);
  EXPECT_THROW(queue_double.pop(), std::logic_error);

  EXPECT_EQ(queue_string.size(), 0U);
  EXPECT_THROW(queue_string.front(), std::logic_error);
  EXPECT_THROW(queue_string.back(), std::logic_error);
  EXPECT_THROW(queue_string.pop(), std::logic_error);
}

TEST(QueueTest, DefaultConstructor) {
  myn::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
  myn::queue<int> q{1, 2, 3};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(Queue, Constructor_Copy) {
  myn::queue<int> our_queue = {1, 2, 3};
  myn::queue<int> our_copy(our_queue);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_copy(std_queue);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(Queue, Operator_Copy) {
  myn::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  myn::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = our_queue_int;
  std_queue_empty = std_queue_int;
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Constructor_Move) {
  myn::queue<int> our_queue = {1, 2, 3};
  myn::queue<int> our_move(std::move(our_queue));
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_move(std::move(std_queue));
  EXPECT_EQ(our_move.front(), std_move.front());
  EXPECT_EQ(our_move.back(), std_move.back());
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(Queue, Operator_Move) {
  myn::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  myn::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = std::move(our_queue_int);
  std_queue_empty = std::move(std_queue_int);
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(QueueTest, CopyAssignmentOperator) {
  myn::queue<int> q1{1, 2, 3};
  myn::queue<int> q2;
  q2 = q1;
  EXPECT_EQ(q2.size(), q1.size());
  EXPECT_EQ(q2.front(), q1.front());
  EXPECT_EQ(q2.back(), q1.back());
}

TEST(QueueTest, MoveAssignmentOperator) {
  myn::queue<int> q1{1, 2, 3};
  myn::queue<int> q2;
  q2 = std::move(q1);
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, Push) {
  myn::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);

  q.push(1);
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 1);

  q.push(2);
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 2);

  q.push(3);
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, Pop) {
  myn::queue<int> q{1, 2, 3};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);

  q.pop();
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.back(), 3);

  q.pop();
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 3);
  EXPECT_EQ(q.back(), 3);

  q.pop();
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, Swap) {
  myn::queue<int> q1{1, 2, 3};
  myn::queue<int> q2{4, 5};
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.front(), 1);
  EXPECT_EQ(q1.back(), 3);
  EXPECT_EQ(q2.size(), 2);
  EXPECT_EQ(q2.front(), 4);
  EXPECT_EQ(q2.back(), 5);

  q1.swap(q2);
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 5);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, Emplace_back) {
  myn::queue<int> q1{10, 9, 5, 5, 15, 13, 8};
  myn::queue<int> q2{10, 9, 5, 5, 15, 13, 8, 88};
  int temp_1 = 88;
  q1.insert_many_back(std::move(temp_1));
}

TEST(QueueTest, Emplace_back_2) {
  myn::queue<int> q1{1, 2, 3, 4, 5, 6, 7};
  myn::queue<int> q2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  q1.insert_many_back(8, 9, 10, 11, 12, 13, 14, 15);
  int count = 1;
  for (size_t i = q1.size(); i > 0; i--) {
    ASSERT_EQ(q1.front(), count);
    // std::cout << "std_queue 2: " << q1.back() << " "
    //           << "queue 2: " << q2.back() << std::endl;
    q1.pop();
    count++;
  }
}
