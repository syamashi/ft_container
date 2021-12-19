#ifndef MAP_HPP
#define MAP_HPP

#include "../utils/rb_tree.hpp"
#include <limits>

namespace ft {
template <typename _Key, typename _Tp, typename Compare = std::less<_Key>,
          typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > >
class map {
 public:
  typedef _Key key_type;
  typedef _Tp mapped_type;
  typedef ft::pair<const _Key, _Tp> value_type;
  typedef Compare key_compare;
  typedef _Alloc allocator_type;

  // Member classes
  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    //    friend class map<_Key, _Tp, Compare, _Alloc>; // forbidden??

   public:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

   public:
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

 private:
  typedef _Rb_tree<key_type, value_type, ft::_Select1st<value_type>, key_compare, allocator_type> _Rep_type;

  /// The actual tree structure.
  _Rep_type _M_t;

 public:
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
  explicit map(const Compare& comp,
               const allocator_type& a = allocator_type())
      : _M_t(comp, a) {}

  /*
  insert(begin,end)をすればいい
  */
  template <typename InputIt>
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const allocator_type& a = allocator_type(),
      typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* =
          NULL)
      : _M_t(comp, a) {
    insert(first, last);
  }

  virtual ~map() {}
  map(const map& x) : _M_t(x._M_t) {}
  map& operator=(const map& x) {
    if (this == &x) return *this;
    _M_t = x._M_t;
    return *this;
  }
  allocator_type get_allocator() const { return _M_t.get_allocator(); }

  //// Element access

  mapped_type& at(const key_type& k) {
    iterator i = lower_bound(k);
    if (i == end() || key_comp()(k, (*i).first))
      std::__throw_out_of_range("map::at");
    return (*i).second;
  }

  const mapped_type& at(const key_type& k) const {
    const_iterator i = lower_bound(k);
    if (i == end() || key_comp()(k, (*i).first))
      std::__throw_out_of_range("map::at");
    return (*i).second;
  }

  /*
  **  If the key does not exist, a pair with that key is created using default
  *values,
  **  which is then returned.
  */
  mapped_type& operator[](const key_type& k) {
    iterator i = insert(value_type(k, mapped_type())).first;
    return i->second;
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
  size_type max_size() const {
    return _M_t.max_size();
  }

  //// Modifiers

  void clear() { _M_t.clear(); }  // header以外削除
  ft::pair<iterator, bool> insert(const value_type& x) {
    return _M_t.insert(x);
  }

  /*
  positionの1個次に挿入される場合、償却時間処理になるのが正しいが、
  BSTinsertの開始位置をroot固定の実装なため適応スキップ。
  */
  iterator insert(iterator position, const value_type& x) {
    (void)position;
    return insert(x).first;
  }

  template <class InputIt>
  void insert(InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
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

  void swap(map& x) { _M_t.swap(x._M_t); }

  //// Lookup

  size_type count(const key_type& x) const {
    if (_M_t.find(x) == _M_t.end())
      return 0;
    else
      return 1;
  }

  iterator find(const key_type& x) { return _M_t.find(x); }

  const_iterator find(const key_type& x) const { return _M_t.find(x); }

  iterator lower_bound(const key_type& x) { return _M_t.lower_bound(x); }

  const_iterator lower_bound(const key_type& x) const {
    return _M_t.lower_bound(x);
  }

  iterator upper_bound(const key_type& x) { return _M_t.upper_bound(x); }

  const_iterator upper_bound(const key_type& x) const {
    return _M_t.upper_bound(x);
  }

  ft::pair<iterator, iterator> equal_range(const key_type& x) {
    return _M_t.equal_range(x);
  }

  ft::pair<const_iterator, const_iterator> equal_range(
      const key_type& x) const {
    return _M_t.equal_range(x);
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
  size_type get_value_type_size() { return sizeof(value_type) ;}
};

//// Non-member functions
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator==(const ft::map<_Key, _Tp, Compare, _Alloc>& x,
                       const ft::map<_Key, _Tp, Compare, _Alloc>& y) {
  return x._M_t == y._M_t;
}

template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator<(const ft::map<_Key, _Tp, Compare, _Alloc>& x,
                      const ft::map<_Key, _Tp, Compare, _Alloc>& y) {
  return x._M_t < y._M_t;
}

/// Based on operator==
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator!=(const ft::map<_Key, _Tp, Compare, _Alloc>& x,
                       const ft::map<_Key, _Tp, Compare, _Alloc>& y) {
  return !(x == y);
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator>(const ft::map<_Key, _Tp, Compare, _Alloc>& x,
                      const ft::map<_Key, _Tp, Compare, _Alloc>& y) {
  return y < x;
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator<=(const ft::map<_Key, _Tp, Compare, _Alloc>& x,
                       const ft::map<_Key, _Tp, Compare, _Alloc>& y) {
  return !(y < x);
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator>=(const ft::map<_Key, _Tp, Compare, _Alloc>& x,
                       const ft::map<_Key, _Tp, Compare, _Alloc>& y) {
  return !(x < y);
}

}  // namespace ft

/// See std::map::swap().
namespace std {
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
void swap(ft::map<_Key, _Tp, Compare, _Alloc>& x,
          ft::map<_Key, _Tp, Compare, _Alloc>& y) {
  x.swap(y);
}

}  // namespace std
#endif
