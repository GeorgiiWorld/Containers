#include <set>

#include "main.h"

TEST(Set, Constructor_1) {
  myn::set<int> st;
  ASSERT_EQ(st.size(), 0);
  ASSERT_TRUE(st.empty());
}

TEST(Set, Constructor_2) {
  myn::set<int> st{3, 5, 8, 7, 2};
  ASSERT_EQ(st.size(), 5);
  ASSERT_FALSE(st.empty());
}

TEST(Set, Copy_Constructor) {
  myn::set<int> st{3, 5, 8, 7, 2};
  myn::set<int> result(st);
  myn::set<int>::iterator my_it = result.begin();
  EXPECT_EQ(result.size(), st.size());
  EXPECT_EQ(*my_it, 2);
  ++my_it;
  EXPECT_EQ(*my_it, 3);
  EXPECT_FALSE(result.empty());
}

TEST(Set, Move_Constructor) {
  myn::set<int> st{3, 5, 8, 7, 2};
  myn::set<int> result = std::move(st);
  myn::set<int>::iterator my_it = result.begin();
  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(*my_it, 2);
  ++my_it;
  EXPECT_EQ(*my_it, 3);
  EXPECT_FALSE(result.empty());
}

TEST(Set, Clear) {
  myn::set<int> st{3, 5, 8, 7, 2};
  EXPECT_EQ(st.size(), 5);
  EXPECT_FALSE(st.empty());
  st.clear();
  EXPECT_EQ(st.size(), 0);
  EXPECT_TRUE(st.empty());
}

TEST(Set, Insert) {
  myn::set<int> st;
  st.insert(8);
  EXPECT_EQ(st.size(), 1);
  EXPECT_FALSE(st.empty());
  EXPECT_TRUE(st.insert(35).second);
  EXPECT_FALSE(st.insert(35).second);
  myn::set<int>::iterator iter;
  iter = st.insert(588).first;
  EXPECT_EQ(*iter, 588);
}

TEST(Set, Contains) {
  myn::set<int> st{8, 25, 35, 45, 11, 9, 7, 4, 14};
  EXPECT_TRUE(st.contains(45));
  EXPECT_TRUE(st.contains(11));
  EXPECT_TRUE(st.contains(7));
  EXPECT_TRUE(st.contains(9));
  EXPECT_FALSE(st.contains(4555));
  EXPECT_FALSE(st.contains(-5));
  EXPECT_FALSE(st.contains(987));
  EXPECT_FALSE(st.contains(654));
}

TEST(Set, Iterator_1) {
  myn::set<int> st{8, 25, 35, 45, 11, 9, 7, 4, 14};
  myn::set<int>::iterator my_it = st.begin();
  EXPECT_EQ(*my_it, 4);
  ++my_it;
  EXPECT_EQ(*my_it, 7);
  ++my_it;
  EXPECT_EQ(*my_it, 8);
  ++my_it;
  EXPECT_EQ(*my_it, 9);
  ++my_it;
  EXPECT_EQ(*my_it, 11);
  ++my_it;
  EXPECT_EQ(*my_it, 14);
  ++my_it;
  EXPECT_EQ(*my_it, 25);
  ++my_it;
  EXPECT_EQ(*my_it, 35);
  ++my_it;
  EXPECT_EQ(*my_it, 45);
}

TEST(Set, Iterator_2) {
  myn::set<int> st{8, 25, 35, 45, 11, 9, 7, 4, 14};
  myn::set<int>::iterator my_it = st.end();
  --my_it;
  EXPECT_EQ(*my_it, 45);
  --my_it;
  EXPECT_EQ(*my_it, 35);
  --my_it;
  EXPECT_EQ(*my_it, 25);
  --my_it;
  EXPECT_EQ(*my_it, 14);
  --my_it;
  EXPECT_EQ(*my_it, 11);
  --my_it;
  EXPECT_EQ(*my_it, 9);
  --my_it;
  EXPECT_EQ(*my_it, 8);
  --my_it;
  EXPECT_EQ(*my_it, 7);
}

TEST(Set, Find) {
  myn::set<int> st{8, 25, 35, 45, 11, 9, 7, 4, 14};
  myn::set<int>::iterator my_it = st.begin();
  EXPECT_EQ(st.find(4), my_it);
  ++my_it;
  EXPECT_EQ(st.find(7), my_it);
  --my_it;
  EXPECT_EQ(st.find(4), my_it);
  myn::set<int>::iterator iterator_25 = st.find(25);
  EXPECT_EQ(*iterator_25, 25);
}

TEST(Set, Merge) {
  myn::set<int> st{8, 25};
  myn::set<int> add{0, 15, 57, 25};
  st.merge(add);
  myn::set<int>::iterator my_it = st.begin();
  EXPECT_EQ(*my_it, 0);
  EXPECT_EQ(st.find(0), my_it);
  EXPECT_EQ(st.size(), 5);
}

TEST(Set, Erase) {
  myn::set<int> st{4, 6, 7, 3, 1};
  myn::set<int>::iterator iter = st.begin();
  ++iter;  // 3
  st.erase(iter);
  iter = st.begin();
  ++iter;  // 4
  st.erase(iter);
  EXPECT_FALSE(st.contains(3));
  EXPECT_FALSE(st.contains(4));
  EXPECT_TRUE(st.contains(1));
  EXPECT_EQ(st.size(), 3);
}

TEST(Set, Erase_1) {
  myn::set<double> st{4, 4.00001, 8, 3, 1};
  myn::set<double>::iterator iter = st.begin();
  ++iter;
  ++iter;
  st.erase(iter);
  EXPECT_FALSE(st.contains(4));
  EXPECT_TRUE(st.contains(4.00001));
}

TEST(Set, insert_many) {
  myn::set<double> my = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> std = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  auto r = my.insert_many(100, 200, 42, 400);
  // auto r = my.insert_many(42);

  //  auto pr1 = o.insert_many(100);
  //  auto pr2 = o.insert_many(200);
  auto pr3 = std.emplace(42);
  //  auto pr4 = o.insert_many(400);

  EXPECT_EQ(*(r[2].first), *(pr3.first));
  EXPECT_EQ(r[2].second, pr3.second);
}
