#ifndef MAP_HPP
#define MAP_HPP

#include "../utils/rb_tree.hpp"

namespace ft {
template <typename _Key, typename _Tp, typename Compare = std::less<_Key>,
          typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
class map {
 public:
  typedef _Key key_type;
  typedef _Tp mapped_type;
  typedef std::pair<const _Key, _Tp> value_type;
  typedef Compare key_compare;
  typedef _Alloc allocator_type;

  // Member classes
  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    //    friend class map<_Key, _Tp, Compare, _Alloc>; // forbidden??

   public:
    Compare comp;
    value_compare(Compare __c) : comp(__c) {}

   public:
    bool operator()(const value_type& __x, const value_type& __y) const {
      return comp(__x.first, __y.first);
    }
  };

 private:
  typedef _Rb_tree<key_type, value_type, key_compare, allocator_type> _Rep_type;

  /// The actual tree structure.
  _Rep_type _M_t;

 public:
  // many of these are specified differently in ISO, but the following are
  // "functionally equivalent"
  typedef typename _Alloc::reference reference;
  typedef typename _Alloc::const_reference const_reference;
  typedef typename _Alloc::pointer pointer;
  typedef typename _Alloc::const_pointer const_pointer;
  typedef typename _Rep_type::size_type size_type;              // size_t
  typedef typename _Rep_type::difference_type difference_type;  // ptrdiff_t
  typedef typename _Rep_type::iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;

  //// Member functions

  map() : _M_t() {}
  virtual ~map() {}
  map& operator=(const map& __x) {
    if (this == &__x) return *this;
    _M_t = __x._M_t;
    return *this;
  }
  allocator_type get_allocator() const { return _M_t.get_allocator(); }

  //// Element access

  mapped_type& at(const key_type& __k) {
    iterator __i = lower_bound(__k);
    if (__i == end() || key_comp()(__k, (*__i).first))
      std::__throw_out_of_range(__N("map::at"));
    return (*__i).second;
  }

  const mapped_type& at(const key_type& __k) const {
    const_iterator __i = lower_bound(__k);
    if (__i == end() || key_comp()(__k, (*__i).first))
      std::__throw_out_of_range(__N("map::at"));
    return (*__i).second;
  }

  /*
  **  If the key does not exist, a pair with that key is created using default
  *values,
  **  which is then returned.
  */
  mapped_type& operator[](const key_type& __k) {
    iterator __i = insert(value_type(__k, mapped_type())).first;
    return __i->second;
  }

  //// Iterators

  iterator begin() { return _M_t.begin(); }
  const_iterator begin() const { return _M_t.begin(); }
  iterator end() { return _M_t.end(); }
  const_iterator end() const { return _M_t.end(); }
  reverse_iterator rbegin() { return _M_t.rbegin(); }
  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  reverse_iterator rend() { return _M_t.rend(); }
  const_reverse_iterator rend() const { return _M_t.rend(); }

  //// Capacity

  bool empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }

  //// Modifiers

  void clear() { _M_t.clear(); }  // header以外削除
  std::pair<iterator, bool> insert(const value_type& __x) {
    return _M_t.insert(__x);
  }

  /*
  __positionの1個次に挿入される場合、償却時間処理になるのが正しいが、
  BSTinsertの開始位置をroot固定の実装なため適応スキップ。
  */
  iterator insert(iterator __position, const value_type& __x) {
    (void)__position;
    return insert(__x).first;
  }

  template <class InputIt>
  void insert(InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = nullptr) {
    for (InputIt head = first; head != last; ++head) {
      insert(*head);
    }
  }

  void erase(iterator pos) { erase(pos->first); }

  size_type erase(const key_type& key) { return _M_t.erase(key); }

  void erase(iterator first, iterator last) {
    if (first == begin() && last == end())
      clear();
    else
      while (first != last)
        erase(first++);  // 消す前に次iteratorをとっておかないと動いちゃう
  }

  void swap(map& __x) { _M_t.swap(__x._M_t); }

  //// Lookup

  size_type count(const key_type& __x) const {
    if (_M_t.find(__x) == _M_t.end())
      return 0;
    else
      return 1;
  }

  iterator find(const key_type& __x) { return _M_t.find(__x); }

  const_iterator find(const key_type& __x) const { return _M_t.find(__x); }

  iterator lower_bound(const key_type& __x) { return _M_t.lower_bound(__x); }

  const_iterator lower_bound(const key_type& __x) const {
    return _M_t.lower_bound(__x);
  }

  iterator upper_bound(const key_type& __x) { return _M_t.upper_bound(__x); }

  const_iterator upper_bound(const key_type& __x) const {
    return _M_t.upper_bound(__x);
  }

  std::pair<iterator, iterator> equal_range(const key_type& __x) {
    return _M_t.equal_range(__x);
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& __x) const {
    return _M_t.equal_range(__x);
  }

  //// observers

  key_compare key_comp() const { return _M_t.key_comp(); };
  value_compare value_comp() const { return value_compare(_M_t.key_comp()); }

  //// Non-member functions
  template <typename _K1, typename _T1, typename _C1, typename _A1>
  friend bool operator==(const map<_K1, _T1, _C1, _A1>&,
                         const map<_K1, _T1, _C1, _A1>&);

  template <typename _K1, typename _T1, typename _C1, typename _A1>
  friend bool operator<(const map<_K1, _T1, _C1, _A1>&,
                        const map<_K1, _T1, _C1, _A1>&);
  //// debug

 public:
  void debug() { _M_t.debug(); }
  void debug2() { _M_t.debug2(); }
};

//// Non-member functions
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator==(const ft::map<_Key, _Tp, Compare, _Alloc>& __x,
                       const ft::map<_Key, _Tp, Compare, _Alloc>& __y) {
  return __x._M_t == __y._M_t;
}

template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator<(const ft::map<_Key, _Tp, Compare, _Alloc>& __x,
                      const ft::map<_Key, _Tp, Compare, _Alloc>& __y) {
  return __x._M_t < __y._M_t;
}

/// Based on operator==
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator!=(const ft::map<_Key, _Tp, Compare, _Alloc>& __x,
                       const ft::map<_Key, _Tp, Compare, _Alloc>& __y) {
  return !(__x == __y);
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator>(const ft::map<_Key, _Tp, Compare, _Alloc>& __x,
                      const ft::map<_Key, _Tp, Compare, _Alloc>& __y) {
  return __y < __x;
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator<=(const ft::map<_Key, _Tp, Compare, _Alloc>& __x,
                       const ft::map<_Key, _Tp, Compare, _Alloc>& __y) {
  return !(__y < __x);
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator>=(const ft::map<_Key, _Tp, Compare, _Alloc>& __x,
                       const ft::map<_Key, _Tp, Compare, _Alloc>& __y) {
  return !(__x < __y);
}

}  // namespace ft

/// See std::map::swap().
namespace std {
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
void swap(ft::map<_Key, _Tp, Compare, _Alloc>& __x,
          ft::map<_Key, _Tp, Compare, _Alloc>& __y) {
  __x.swap(__y);
}

}  // namespace std
#endif
