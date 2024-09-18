#include <array>
#include <list>
#include <vector>

#include "main.h"

TEST(vector, shrink) {
  myn::vector<std::string> vec1;
  vec1.push_back("aaa");
  vec1.push_back("bbb");
  vec1.push_back("ccc");

  std::vector<std::string> vec2;
  vec2.push_back("aaa");
  vec2.push_back("bbb");
  vec2.push_back("ccc");

  ASSERT_EQ(vec1.capacity(), vec2.capacity());

  vec1.shrink_to_fit();
  vec2.shrink_to_fit();

  ASSERT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector, constr_copy) {
  myn::vector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);

  myn::vector<int> vec2(vec1);

  ASSERT_EQ(vec2[0], 1);
  ASSERT_EQ(vec2[1], 2);
  ASSERT_EQ(vec2[2], 3);
  ASSERT_EQ(vec1.capacity(), vec2.capacity());
  ASSERT_EQ(vec1.size(), vec2.size());
}

TEST(vector, init_list) {
  myn::vector<int> vec{1, 2, 3};

  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
}

TEST(vector, iterator_1) {
  myn::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);

  auto iter = vec.begin();
  ASSERT_EQ(vec[0], *iter);
  ASSERT_EQ(vec[1], *(++iter));
  int* d = vec.data();
  ASSERT_EQ(*(d + 1), *iter);
}

TEST(vector, empty_true) {
  myn::vector<int> vec;
  ASSERT_TRUE(vec.empty());
}

TEST(vector, empty_false) {
  myn::vector<int> vec;
  vec.push_back(123);
  ASSERT_FALSE(vec.empty());
}

TEST(vector, resize_capacity) {
  myn::vector<int> vec1(0);
  vec1.reserve(5);
  ASSERT_EQ(vec1.capacity(), 5);
  vec1.push_back(123);
  vec1.push_back(456);
  vec1.push_back(789);

  vec1.resize(20);
  ASSERT_EQ(vec1.size(), 20);

  vec1.pop_back();
  ASSERT_EQ(vec1.size(), 19);
}

TEST(vector, at_1) {
  myn::vector<std::string> vec1;
  vec1.push_back("aaaa");

  ASSERT_EQ(vec1[0], "aaaa");
  EXPECT_ANY_THROW({ vec1.at(2); });
}

TEST(vector, at_2) {
  myn::vector<int> vec1(3);
  vec1.push_back(1);
  vec1.push_back(2);

  std::vector<int> vec2(3);
  vec2.push_back(1);
  vec2.push_back(2);

  ASSERT_EQ(vec1.at(3), vec2.at(3));
}

TEST(vector, clear) {
  myn::vector<double> vec;
  vec.push_back(123.123);
  vec.push_back(12.22);

  vec.clear();
  ASSERT_EQ(vec.size(), 0);
}

TEST(vector, swap) {
  myn::vector<int> vec1{1, 2, 3};
  myn::vector<int> vec2{4, 3, 2, 1};

  vec1.swap(vec2);

  ASSERT_EQ(vec1[0], 4);
  ASSERT_EQ(vec1[1], 3);
  ASSERT_EQ(vec1[2], 2);
  ASSERT_EQ(vec1[3], 1);
  ASSERT_EQ(vec1.size(), 4);
}

TEST(vector, erase) {
  myn::vector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);
  vec1.push_back(4);
  std::vector<int> vec2;
  vec2.push_back(1);
  vec2.push_back(2);
  vec2.push_back(3);
  vec2.push_back(4);

  vec1.erase(vec1.begin() + 2);
  vec2.erase(vec2.begin() + 2);

  auto it1 = vec1.begin();
  auto it2 = vec2.begin();
  for (; it1 != vec1.end() && it2 != vec2.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(vector, insert_1) {
  myn::vector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);
  vec1.push_back(4);
  vec1.push_back(5);
  std::vector<int> vec2;
  vec2.push_back(1);
  vec2.push_back(2);
  vec2.push_back(3);
  vec2.push_back(4);
  vec2.push_back(5);

  vec1.insert(vec1.begin(), 100);
  vec1.insert(vec1.end(), 200);
  vec1.insert(vec1.begin() + vec1.size() / 2, 300);

  vec2.insert(vec2.begin(), 100);
  vec2.insert(vec2.end(), 200);
  vec2.insert(vec2.begin() + vec2.size() / 2, 300);

  auto it1 = vec1.begin();
  auto it2 = vec2.begin();
  for (; it1 != vec1.end() && it2 != vec2.end(); ++it1, ++it2)
    ASSERT_EQ(*it1, *it2);
}

TEST(vector, insert_2) {
  myn::vector<double> vec1{1.1, 2.2, 3.3, 4.4, 5.5};
  std::vector<double> vec2{1.1, 2.2, 3.3, 4.4, 5.5};
  vec1.insert(vec1.begin(), 10.10);
  vec2.insert(vec2.begin(), 10.10);
  auto it1 = vec1.begin();
  auto it2 = vec2.begin();
  for (; it1 != vec1.end() && it2 != vec2.end(); ++it1, ++it2)
    ASSERT_EQ(*it1, *it2);
}

TEST(vector, insert_many) {
  myn::vector<int> vec{1, 2, 6};
  vec.insert_many(vec.cbegin() + 2, 3, 4, 5);
  double num = 1;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    ASSERT_EQ(*it, num);
    num += 1;
  }
}
TEST(vector, insert_many_back) {
  myn::vector<int> vec{1, 2, 3};
  vec.insert_many_back(4, 5, 6);
  double num = 1;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    ASSERT_EQ(*it, num);
    num += 1;
  }
}

TEST(list, constr_alloc) {
  myn::list<int> l(10);
  for (auto i = l.begin(); i != l.end(); ++i) ASSERT_EQ(*i, 0);
}

TEST(list, constr_copy) {
  myn::list<int> l1;
  l1.push_back(123);
  l1.push_back(456);
  l1.push_back(789);

  myn::list<int> l2(l1);

  auto i = l2.begin();
  ASSERT_EQ(*i, 123);
  ++i;
  ASSERT_EQ(*i, 456);
  ++i;
  ASSERT_EQ(*i, 789);
}

TEST(list, constr_init_list) {
  myn::list<int> l2{123, 456, 789};

  auto i = l2.begin();
  ASSERT_EQ(*i, 123);
  ++i;
  ASSERT_EQ(*i, 456);
  ++i;
  ASSERT_EQ(*i, 789);
}

TEST(list, constr_move) {
  myn::list<int> l1;
  l1.push_back(123);
  l1.push_back(456);
  l1.push_back(789);

  myn::list<int> l2(std::move(l1));

  auto i = l2.begin();
  ASSERT_EQ(*i, 123);
  ++i;
  ASSERT_EQ(*i, 456);
  ++i;
  ASSERT_EQ(*i, 789);
}

TEST(list, op_eq) {
  myn::list<int> l1;
  l1.push_back(123);
  l1.push_back(456);
  l1.push_back(789);

  myn::list<int> l2 = l1;

  auto i = l2.begin();
  ASSERT_EQ(*i, 123);
  ++i;
  ASSERT_EQ(*i, 456);
  ++i;
  ASSERT_EQ(*i, 789);
}

TEST(list, push_front) {
  myn::list<int> l;
  l.push_front(333);
  l.push_front(333);
  l.push_front(333);
  for (auto i = l.begin(); i != l.end(); ++i) ASSERT_EQ(*i, 333);
}

TEST(list, insert) {
  myn::list<int> l;
  l.push_front(333);
  l.push_front(444);
  l.push_front(555);

  auto pos = l.begin();
  auto res = l.insert(pos, 2);
  ASSERT_EQ(*res, 2);

  pos = ++(l.begin());
  res = l.insert(pos, 3);
  ASSERT_EQ(*res, 3);

  pos = l.end();
  res = l.insert(pos, 3);
  ASSERT_EQ(*res, 3);
}

TEST(list, pop_back) {
  myn::list<std::string> a;
  a.push_back("a");
  a.push_back("a");
  a.push_back("a");
  a.push_back("a");
  a.pop_back();
  a.push_back("b");
  a.pop_back();
  a.push_back("c");
  a.pop_back();
  a.pop_back();
  a.pop_back();
  a.pop_back();

  ASSERT_EQ(a.empty(), 1);
  ASSERT_EQ(a.begin(), a.end());

  a.push_back("aa");
  ASSERT_EQ(a.front(), "aa");
  ASSERT_EQ(a.back(), "aa");
  a.pop_back();
  // std::cout << "front? : " << a.front() << '\n';
  // std::cout << "back? : " << a.back() << '\n';
}

TEST(list, pop_front) {
  myn::list<std::string> a;
  a.push_back("a");
  a.push_back("b");
  a.pop_front();
  a.pop_front();

  // for (auto i = a.begin(); i != a.end(); ++i)
  //   std::cout << *i << '\n';

  a.push_back("a");
  a.push_back("a");
  a.pop_front();
  a.push_back("b");
  a.pop_front();
  a.push_back("c");
  a.pop_front();
  a.pop_front();

  ASSERT_EQ(a.empty(), 1);
  ASSERT_EQ(a.begin(), a.end());

  a.push_back("aa");
  ASSERT_EQ(a.front(), "aa");
  ASSERT_EQ(a.back(), "aa");
  a.pop_front();
}

TEST(list, clear) {
  myn::list<double> d;
  d.push_back(123.123);
  d.push_back(333.123);
  d.push_back(444.123);
  d.push_back(555.123);
  d.push_back(666.123);

  d.clear();
  ASSERT_EQ(d.empty(), 1);
  ASSERT_EQ(d.size(), 0);
  ASSERT_EQ(d.begin(), d.end());
}

TEST(list, empty_true) {
  myn::list<int> a;
  ASSERT_TRUE(a.empty());
}

TEST(list, empty_false) {
  myn::list<int> a;
  a.push_back(123);
  ASSERT_FALSE(a.empty());
}

TEST(list, swap) {
  myn::list<int> a1;
  a1.push_back(111);
  a1.push_back(222);
  a1.push_back(333);

  myn::list<int> a2;
  a2.push_back(4444);
  a2.push_back(5555);
  a2.push_back(6666);
  a2.push_back(7777);

  a1.swap(a2);
  ASSERT_EQ(*(a1.begin()), 4444);
  ASSERT_EQ(*(a2.begin()), 111);
  ASSERT_EQ(a1.size(), 4);
  ASSERT_EQ(a2.size(), 3);
}

TEST(list, erase) {
  myn::list<int> a;
  a.push_back(111);
  a.push_back(222);
  a.push_back(333);
  a.push_back(444);
  a.push_back(555);
  a.push_back(666);
  a.push_back(777);

  auto res = a.erase(--(a.end()));
  ASSERT_EQ(res, a.end());

  auto first = a.begin();
  auto last = a.end();
  --last;

  res = a.erase(first, last);
  ASSERT_EQ(*(a.begin()), 666);
}

TEST(list, reverse) {
  myn::list<int> a;
  a.push_back(111);
  a.push_back(222);
  a.push_back(333);
  a.push_back(444);

  a.reverse();

  auto i = a.begin();
  ASSERT_EQ(*i, 444);
  ++i;
  ASSERT_EQ(*i, 333);
  ++i;
  ASSERT_EQ(*i, 222);
  ++i;
  ASSERT_EQ(*i, 111);
}

TEST(list, splice) {
  myn::list<int> a;
  // std::list<int> a;
  a.push_back(111);
  a.push_back(222);
  a.push_back(333);
  a.push_back(444);

  myn::list<int> b;
  // std::list<int> b;
  b.push_back(10);
  b.push_back(20);
  b.push_back(30);

  auto pos = a.cbegin();
  ++pos;
  a.splice(pos, b);

  auto i = a.begin();
  ASSERT_EQ(*i, 111);
  ++i;
  ASSERT_EQ(*i, 10);
  ++i;
  ASSERT_EQ(*i, 20);
  ++i;
  ASSERT_EQ(*i, 30);
  ++i;
  ASSERT_EQ(*i, 222);
}

TEST(list, unique) {
  myn::list<int> a;
  // std::list<int> a;
  a.push_back(1);
  a.push_back(1);
  a.push_back(1);
  a.push_back(2);
  a.push_back(2);
  a.push_back(2);
  a.push_back(3);
  a.push_back(3);
  a.push_back(4);
  a.push_back(4);
  a.push_back(4);
  a.push_back(4);
  a.push_back(4);

  a.unique();

  auto i = a.begin();
  ASSERT_EQ(*i, 1);
  ++i;
  ASSERT_EQ(*i, 2);
  ++i;
  ASSERT_EQ(*i, 3);
  ++i;
  ASSERT_EQ(*i, 4);
}

TEST(list, sort) {
  myn::list<int> a;
  a.push_back(4);
  a.push_back(1);
  a.push_back(8);
  a.push_back(3);
  a.push_back(2);
  a.push_back(3);
  a.push_back(1);
  a.push_back(0);
  a.push_back(4);
  a.push_back(2);

  a.sort();

  // for (auto i = a.begin(); i != a.end(); ++i)
  //   std::cout << *i << '\n';

  auto i = a.begin();
  ASSERT_EQ(*i, 0);
  ++i;
  ASSERT_EQ(*i, 1);
  ++i;
  ASSERT_EQ(*i, 1);
  ++i;
  ASSERT_EQ(*i, 2);

  ASSERT_EQ(a.back(), 8);
}

TEST(list, merge) {
  // std::list<int> a;
  myn::list<int> a;
  a.push_back(2);
  a.push_back(4);
  a.push_back(6);
  a.push_back(8);
  a.push_back(10);

  // std::list<int> b;
  myn::list<int> b;
  b.push_back(1);
  b.push_back(2);
  b.push_back(5);
  b.push_back(5);
  b.push_back(5);
  b.push_back(8);
  b.push_back(9);
  b.push_back(90);
  b.push_back(91);
  b.push_back(92);

  a.merge(b);

  auto i = a.begin();
  ASSERT_EQ(*i, 1);
  ++i;
  ASSERT_EQ(*i, 2);
  ++i;
  ASSERT_EQ(*i, 2);
  ++i;
  ASSERT_EQ(*i, 4);

  ASSERT_EQ(a.back(), 92);
}

TEST(list, insert_many) {
  myn::list<int> l{1, 2, 3};
  l.insert_many(++l.cbegin(), 7, 6, 5);
  auto it = l.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 7);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
}

TEST(list, insert_many_back) {
  myn::list<int> l{1, 2, 3};
  l.insert_many_back(4, 5, 6, 7, 8, 9);
  int num = 1;
  for (auto it = l.begin(); it != l.end(); ++it) {
    ASSERT_EQ(*it, num);
    num++;
  }
}

TEST(list, insert_many_front) {
  myn::list<int> l{11, 12, 13, 14, 15};
  l.insert_many_front(10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
  int num = 1;
  for (auto it = l.begin(); it != l.end(); ++it) {
    ASSERT_EQ(*it, num);
    num++;
  }
}

TEST(stack, base) {
  myn::stack<int> s;
  s.push(123);
  s.push(456);
  s.push(789);
  s.pop();

  s.pop();
  s.pop();

  s.push(35);
  myn::stack<int> s2;
  s2 = std::move(s);
}

TEST(queue, base) {
  myn::queue<int> s;
  s.push(123);
  s.push(456);
  s.push(789);
  s.pop();

  s.pop();
  s.pop();

  s.push(25);
  myn::queue<int> s2;
  s2 = std::move(s);
}

TEST(array, constructor) {
  myn::array<int, 4> arr1{5, 3, 5, 5};
  myn::array<int, 4> arr2(arr1);

  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  for (; it1 != arr1.end() && it2 != arr2.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(array, constructor_2) {
  myn::array<int, 4> arr1{5, 3, 5, 5};
  myn::array<int, 4> arr2(std::move(arr1));
  ASSERT_EQ(arr2.front(), 5);
  ASSERT_EQ(arr2.at(1), 3);
  ASSERT_EQ(arr2.at(2), 5);
  ASSERT_EQ(arr2.at(3), 5);
  ASSERT_EQ(arr1.at(0), 0);
}

TEST(array, op_eq) {
  myn::array<int, 4> arr1{5, 3, 5, 3};
  myn::array<int, 4> arr2;

  arr2 = arr1;
  ASSERT_EQ(arr2[0], 5);
  ASSERT_EQ(arr2[1], 3);
  ASSERT_EQ(arr2[2], 5);
  ASSERT_EQ(arr2[3], 3);
}

TEST(array, iter) {
  myn::array<int, 4> a1{1, 2, 3, 4};
  auto i = a1.begin();
  ASSERT_EQ(*i, 1);
  ++i;
  ASSERT_EQ(*i, 2);
  --i;
  ASSERT_EQ(*i, 1);

  auto j = a1.end();
  --j;
  ASSERT_EQ(*j, 4);
}

TEST(array, empty) {
  myn::array<int, 0> a;
  ASSERT_EQ(a.empty(), true);
}

TEST(array, size) {
  myn::array<int, 1> a;
  ASSERT_EQ(a.size(), 1);
}

TEST(array, max) {
  myn::array<int, 11> a1;
  std::array<int, 11> a2;
  ASSERT_EQ(a1.max_size(), a2.max_size());
}

TEST(array, swap) {
  myn::array<int, 3> arr1{1, 2, 3};
  myn::array<int, 3> arr2{6, 5, 4};

  arr1.swap(arr2);
  int num = 6;
  for (auto it = arr1.begin(); it != arr1.end(); ++it) {
    ASSERT_EQ(*it, num);
    --num;
  }

  num = 1;
  for (auto it = arr2.begin(); it != arr2.end(); ++it) {
    ASSERT_EQ(*it, num);
    ++num;
  }
}

TEST(array, fill) {
  myn::array<int, 10> arr;

  arr.fill(666);

  for (auto it = arr.begin(); it != arr.end(); ++it) ASSERT_EQ(*it, 666);
}

TEST(array, front_back) {
  myn::array<int, 3> arr1{1, 2, 3};
  std::array<int, 3> arr2{1, 2, 3};

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(array, front_error) {
  myn::array<char, 0> arr;
  ASSERT_ANY_THROW(arr.front());
}

TEST(array, back_error) {
  myn::array<double, 0> arr;
  ASSERT_ANY_THROW(arr.back());
}

TEST(array, data) {
  myn::array<int, 4> arr1{1, 2, 3, 4};
  std::array<int, 4> arr2{1, 2, 3, 4};

  auto data1 = arr1.data();
  auto data2 = arr2.data();

  ASSERT_EQ(data1[0], data2[0]);
  ASSERT_EQ(data1[1], data2[1]);
  ASSERT_EQ(data1[2], data2[2]);
  ASSERT_EQ(data1[3], data2[3]);
}
