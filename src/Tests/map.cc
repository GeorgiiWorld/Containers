#include <map>

#include "main.h"

TEST(Map, Constructor_1) {
  myn::map<int, int> my_map;
  std::map<int, int> fact;
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Constructor_2) {
  myn::map<double, std::string> my_map{{1.1, "a"}, {2.2, "b"}, {3.3, "c"},
                                       {4.4, "d"}, {5.5, "e"}, {6.6, "f"},
                                       {7.7, "g"}, {8.8, "h"}};
  std::map<double, std::string> fact{{1.1, "a"}, {2.2, "b"}, {3.3, "c"},
                                     {4.4, "d"}, {5.5, "e"}, {6.6, "f"},
                                     {7.7, "g"}, {8.8, "h"}};
  myn::map<double, std::string>::iterator iter = my_map.begin();
  std::map<double, std::string>::iterator iter_fact = fact.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Copy_Constructor_1) {
  myn::map<double, std::string> my_map1{{1.1, "a"}, {2.2, "b"}, {3.3, "c"},
                                        {4.4, "d"}, {5.5, "e"}, {6.6, "f"},
                                        {7.7, "g"}, {8.8, "h"}};
  myn::map<double, std::string> my_map2(my_map1);
  std::map<double, std::string> fact{{1.1, "a"}, {2.2, "b"}, {3.3, "c"},
                                     {4.4, "d"}, {5.5, "e"}, {6.6, "f"},
                                     {7.7, "g"}, {8.8, "h"}};
  myn::map<double, std::string>::iterator iter1 = my_map1.begin();
  myn::map<double, std::string>::iterator iter2 = my_map2.begin();
  std::map<double, std::string>::iterator iter_fact = fact.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter1, ++iter2, ++iter_fact) {
    EXPECT_EQ(iter1->first, iter_fact->first);
    EXPECT_EQ(iter1->second, iter_fact->second);
    EXPECT_EQ(iter2->first, iter_fact->first);
    EXPECT_EQ(iter2->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact.size());
  EXPECT_EQ(my_map2.size(), fact.size());
}

TEST(Map, Move_Constructor_1) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  myn::map<double, std::string> my_map2(std::move(my_map1));
  std::map<double, std::string> fact1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                      {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                      {6.6, "f"}, {7.7, "g"}};
  std::map<double, std::string> fact2(std::move(fact1));
  myn::map<double, std::string>::iterator iter = my_map1.begin();
  std::map<double, std::string>::iterator iter_fact = fact1.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact1.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact1.size());
  iter = my_map2.begin();
  iter_fact = fact2.begin();
  iter_fact_end = fact2.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map2.size(), fact2.size());
}

TEST(Map, Move_Constructor_2) {
  myn::map<double, std::string> my_map1;
  myn::map<double, std::string> my_map2(std::move(my_map1));
  std::map<double, std::string> fact1;
  std::map<double, std::string> fact2(std::move(fact1));
  myn::map<double, std::string>::iterator iter = my_map1.begin();
  std::map<double, std::string>::iterator iter_fact = fact1.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact1.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact1.size());
  iter = my_map2.begin();
  iter_fact = fact2.begin();
  iter_fact_end = fact2.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map2.size(), fact2.size());
}

TEST(Map, OperatorEqual_1) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  myn::map<double, std::string> my_map2 = std::move(my_map1);
  std::map<double, std::string> fact1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                      {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                      {6.6, "f"}, {7.7, "g"}};
  std::map<double, std::string> fact2 = std::move(fact1);
  myn::map<double, std::string>::iterator iter = my_map1.begin();
  std::map<double, std::string>::iterator iter_fact = fact1.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact1.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact1.size());
  iter = my_map2.begin();
  iter_fact = fact2.begin();
  iter_fact_end = fact2.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map2.size(), fact2.size());
}

TEST(Map, OperatorEqual_2) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  myn::map<double, std::string> my_map2{
      {100, "e"}, {95.5, "h"}, {34.4, "a"}, {294, "d"}};
  my_map2 = std::move(my_map1);
  std::map<double, std::string> fact1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                      {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                      {6.6, "f"}, {7.7, "g"}};
  std::map<double, std::string> fact2{
      {100, "e"}, {95.5, "h"}, {34.4, "a"}, {294, "d"}};
  fact2 = std::move(fact1);
  myn::map<double, std::string>::iterator iter = my_map1.begin();
  std::map<double, std::string>::iterator iter_fact = fact1.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact1.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact1.size());
  iter = my_map2.begin();
  iter_fact = fact2.begin();
  iter_fact_end = fact2.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map2.size(), fact2.size());
}

TEST(Map, MapIterator_1) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  std::map<int, int> fact{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                          {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, MapIterator_2) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  std::map<int, int> fact{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                          {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  myn::map<int, int>::iterator iter = my_map.end();
  std::map<int, int>::iterator iter_fact = fact.end();
  --iter;
  --iter_fact;
  std::map<int, int>::iterator iter_fact_begin = fact.begin();
  for (; iter_fact != iter_fact_begin; --iter, --iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(iter->first, iter_fact->first);
  EXPECT_EQ(iter->second, iter_fact->second);
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, At_1) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  EXPECT_EQ(my_map.at(7), 4);
  my_map.at(7) = 6;
  EXPECT_EQ(my_map.at(7), 6);
}

TEST(Map, At_2) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  EXPECT_ANY_THROW(my_map.at(8) = 6;);
}

TEST(Map, Operator_Square_Brackets_1) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  EXPECT_EQ(my_map[7], 4);
  my_map[7] = 6;
  EXPECT_EQ(my_map[7], 6);
}

TEST(Map, Operator_Square_Brackets_2) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  EXPECT_EQ(my_map[8], 0);
  my_map[8] = 6;
  EXPECT_EQ(my_map[8], 6);
}

TEST(Map, Empty_1) {
  myn::map<int, int> my_map;
  EXPECT_EQ(my_map.empty(), true);
}

TEST(Map, Empty_2) {
  myn::map<int, int> my_map{{3, 4}};
  EXPECT_EQ(my_map.empty(), false);
}

TEST(Map, Size_1) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  EXPECT_EQ(my_map.size(), 8);
}

TEST(Map, Size_2) {
  myn::map<int, int> my_map;
  EXPECT_EQ(my_map.size(), 0);
}

TEST(Map, Clear_1) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  my_map.clear();
  EXPECT_EQ(my_map.size(), 0);
}

TEST(Map, Clear_2) {
  myn::map<int, int> my_map;
  my_map.clear();
  EXPECT_EQ(my_map.size(), 0);
}

TEST(Map, Insert_1) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  std::map<int, int> fact{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                          {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  my_map.insert({55, 44});
  fact.insert({55, 44});
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Insert_2) {
  myn::map<int, int> my_map;
  std::map<int, int> fact;
  my_map.insert({99, 44});
  fact.insert({99, 44});
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Insert_3) {
  myn::map<int, int> my_map;
  std::map<int, int> fact;
  my_map.insert({99, 44});
  fact.insert({99, 44});
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
  my_map.insert({3, 2});
  fact.insert({3, 2});
  iter = my_map.begin();
  iter_fact = fact.begin();
  iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Insert_4) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  std::map<int, int> fact{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                          {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  my_map.insert({55, 44});
  fact.insert({55, 44});
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Insert_5) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  std::map<int, int> fact{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                          {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  my_map.insert({99, 44});
  fact.insert({99, 44});
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Insert_Or_Assign_1) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  std::map<int, int> fact{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                          {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  my_map.insert_or_assign(99, 44);
  fact.insert_or_assign(99, 44);
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Insert_Or_Assign_2) {
  myn::map<int, int> my_map;
  std::map<int, int> fact;
  my_map.insert_or_assign(99, 44);
  fact.insert_or_assign(99, 44);
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Insert_Or_Assign_3) {
  myn::map<int, int> my_map;
  std::map<int, int> fact;
  my_map.insert_or_assign(99, 44);
  fact.insert_or_assign(99, 44);
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Insert_Or_Assign_4) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  std::map<int, int> fact{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                          {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  my_map.insert_or_assign(55, 44);
  fact.insert_or_assign(55, 44);
  myn::map<int, int>::iterator iter = my_map.begin();
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Erase_1) {
  myn::map<int, int> my_map{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                            {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  std::map<int, int> fact{{5, 0}, {1, 1},  {99, 2}, {-104, 3},
                          {7, 4}, {19, 5}, {2, 6},  {49, 7}};
  myn::map<int, int>::iterator iter = my_map.begin();
  ++iter;
  ++iter;
  my_map.erase(iter);

  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  ++iter_fact;
  ++iter_fact;
  fact.erase(iter_fact);

  iter = my_map.begin();
  iter_fact = fact.begin();
  iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Erase_2) {
  myn::map<int, int> my_map{{5, 0}, {1, 1}};
  std::map<int, int> fact{{5, 0}, {1, 1}};
  myn::map<int, int>::iterator iter = my_map.begin();
  my_map.erase(iter);
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  fact.erase(iter_fact);

  iter = my_map.begin();
  iter_fact = fact.begin();
  iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Erase_3) {
  myn::map<int, int> my_map{{5, 0}};
  std::map<int, int> fact{{5, 0}};
  myn::map<int, int>::iterator iter = my_map.begin();
  my_map.erase(iter);
  std::map<int, int>::iterator iter_fact = fact.begin();
  std::map<int, int>::iterator iter_fact_end = fact.end();
  fact.erase(iter_fact);

  iter = my_map.begin();
  iter_fact = fact.begin();
  iter_fact_end = fact.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map.size(), fact.size());
}

TEST(Map, Erase_4) {
  myn::map<int, int> my_map;
  std::map<int, int> fact;
  myn::map<int, int>::iterator iter = my_map.begin();
  EXPECT_ANY_THROW(my_map.erase(iter));
}

TEST(Map, Swap_1) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  myn::map<double, std::string> my_map2{
      {0, "i"}, {4.4, "j"}, {6.6, "k"}, {10.10, "l"}};
  std::map<double, std::string> fact1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                      {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                      {6.6, "f"}, {7.7, "g"}};
  std::map<double, std::string> fact2{
      {0, "i"}, {4.4, "j"}, {6.6, "k"}, {10.10, "l"}};
  my_map1.swap(my_map2);
  fact1.swap(fact2);
  myn::map<double, std::string>::iterator iter = my_map1.begin();
  std::map<double, std::string>::iterator iter_fact = fact1.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact1.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact1.size());
  iter = my_map2.begin();
  iter_fact = fact2.begin();
  iter_fact_end = fact2.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map2.size(), fact2.size());
}

TEST(Map, Merge_1) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  myn::map<double, std::string> my_map2{
      {0, "i"}, {4.4, "j"}, {6.6, "k"}, {10.10, "l"}};
  std::map<double, std::string> fact1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                      {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                      {6.6, "f"}, {7.7, "g"}};
  std::map<double, std::string> fact2{
      {0, "i"}, {4.4, "j"}, {6.6, "k"}, {10.10, "l"}};
  my_map1.merge(my_map2);
  fact1.merge(fact2);
  myn::map<double, std::string>::iterator iter = my_map1.begin();
  std::map<double, std::string>::iterator iter_fact = fact1.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact1.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact1.size());
}

TEST(Map, Merge_2) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  myn::map<double, std::string> my_map2{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  std::map<double, std::string> fact1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                      {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                      {6.6, "f"}, {7.7, "g"}};
  std::map<double, std::string> fact2{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                      {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                      {6.6, "f"}, {7.7, "g"}};
  my_map1.merge(my_map2);
  fact1.merge(fact2);
  myn::map<double, std::string>::iterator iter = my_map1.begin();
  std::map<double, std::string>::iterator iter_fact = fact1.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact1.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact1.size());
  iter = my_map2.begin();
  iter_fact = fact2.begin();
  iter_fact_end = fact2.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map2.size(), fact2.size());
}

TEST(Map, Merge_3) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  myn::map<double, std::string> my_map2;
  std::map<double, std::string> fact1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                      {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                      {6.6, "f"}, {7.7, "g"}};
  std::map<double, std::string> fact2;
  my_map1.merge(my_map2);
  fact1.merge(fact2);
  myn::map<double, std::string>::iterator iter = my_map1.begin();
  std::map<double, std::string>::iterator iter_fact = fact1.begin();
  std::map<double, std::string>::iterator iter_fact_end = fact1.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map1.size(), fact1.size());
  iter = my_map2.begin();
  iter_fact = fact2.begin();
  iter_fact_end = fact2.end();
  for (; iter_fact != iter_fact_end; ++iter, ++iter_fact) {
    EXPECT_EQ(iter->first, iter_fact->first);
    EXPECT_EQ(iter->second, iter_fact->second);
  }
  EXPECT_EQ(my_map2.size(), fact2.size());
}

TEST(Map, Contains_1) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  EXPECT_EQ(my_map1.contains(8.8), true);
}

TEST(Map, Contains_2) {
  myn::map<double, std::string> my_map1{{5.5, "e"}, {8.8, "h"}, {1.1, "a"},
                                        {4.4, "d"}, {2.2, "b"}, {3.3, "c"},
                                        {6.6, "f"}, {7.7, "g"}};
  EXPECT_EQ(my_map1.contains(190), false);
}

TEST(Map, Contains_3) {
  myn::map<double, std::string> my_map1;
  EXPECT_EQ(my_map1.contains(190), false);
}

TEST(Map, Emplace_1) {
  myn::map<double, std::string> my_map{
      {0, "i"}, {4.4, "j"}, {6.6, "k"}, {10.10, "l"}};
  EXPECT_EQ(my_map.at(4.4), "j");

  my_map.insert_many(std::make_pair(8.8, "h"), std::make_pair(1.1, "a"),
                     std::make_pair(4.4, "d"), std::make_pair(2.2, "b"),
                     std::make_pair(3.3, "y"));
  EXPECT_EQ(my_map.at(4.4), "j");
  EXPECT_EQ(my_map.at(8.8), "h");
  EXPECT_EQ(my_map.at(2.2), "b");
  EXPECT_ANY_THROW(my_map.at(9.9););
}
