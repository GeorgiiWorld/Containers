#ifndef SRC_INCLUDE_MAP_H_
#define SRC_INCLUDE_MAP_H_

#include "set.h"

namespace myn {
template <class Key, class T>
class map : public set<std::pair<Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using iterator = typename set<value_type>::iterator;
  using const_iterator = typename set<value_type>::const_iterator;

  using set<value_type>::set;

  mapped_type &at(const key_type &key) {
    if (!contains(key)) {
      throw std::out_of_range("key not found");
    } else {
      mapped_type data{};
      return set<value_type>::find(std::make_pair(key, data))->second;
    }
  }
  mapped_type &operator[](const key_type &key) {
    mapped_type data{};
    if (!contains(key)) {
      insert(key, data);
    }
    return set<value_type>::find(std::make_pair(key, data))->second;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return set<value_type>::base_insert(value);
  }
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    return set<value_type>::base_insert(std::make_pair(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const Key &key,
                                             const mapped_type &obj) {
    return set<value_type>::base_insert(std::make_pair(key, obj), true);
  }

  bool contains(const key_type &key) {
    mapped_type data{};
    return set<value_type>::contains(std::make_pair(key, data));
  }

 private:
  bool comp_key_less(const value_type &first,
                     const value_type &second) const override {
    return (first.first < second.first) ? true : false;
  }
};

};  // namespace myn

#endif  // SRC_INCLUDE_MAP_H_