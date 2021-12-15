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

 private:
 public:
  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    friend class map<_Key, _Tp, Compare, _Alloc>; // subjectにより、非メンバオーバーロード以外のfriendが禁止。protectedをpublicにするくらい？

   protected:
    Compare comp; // compはmapからもアクセスできるよ

    value_compare(Compare __c) : comp(__c) {}

   public:
    bool operator()(const value_type& __x, const value_type& __y) const {
      return comp(__x.first, __y.first);
    }
  };

 private:
  /// This turns a red-black tree into a [multi]map.
  typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template rebind<
      value_type>::other _Pair_alloc_type;

  typedef _Rb_tree<key_type, value_type, std::_Select1st<value_type>,
                   key_compare, _Pair_alloc_type>
      _Rep_type;

  /// The actual tree structure.
  _Rep_type _M_t;

  typedef __gnu_cxx::__alloc_traits<_Pair_alloc_type> _Alloc_traits;

 public:
  // many of these are specified differently in ISO, but the following are
  // "functionally equivalent"
  typedef typename _Alloc_traits::pointer pointer;
  typedef typename _Alloc_traits::const_pointer const_pointer;
  typedef typename _Alloc_traits::reference reference;
  typedef typename _Alloc_traits::const_reference const_reference;
  typedef typename _Rep_type::iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;
  typedef typename _Rep_type::reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;

  map() : _M_t() {}

  explicit map(const Compare& __comp,
               const allocator_type& __a = allocator_type())
      : _M_t(__comp, _Pair_alloc_type(__a)) {}

  map(const map& __x) : _M_t(__x._M_t) {}

  template <typename _InputIterator>
  map(_InputIterator __first, _InputIterator __last) : _M_t() {
    _M_t._M_insert_unique(__first, __last);
  }

  template <typename _InputIterator>
  map(_InputIterator __first, _InputIterator __last, const Compare& __comp,
      const allocator_type& __a = allocator_type())
      : _M_t(__comp, _Pair_alloc_type(__a)) {
    _M_t._M_insert_unique(__first, __last);
  }

  map& operator=(const map& __x) {
    _M_t = __x._M_t;
    return *this;
  }

  allocator_type get_allocator() const _GLIBCXX_NOEXCEPT { // node_allocator
    return allocator_type(_M_t.get_allocator());
  }

  iterator begin() _GLIBCXX_NOEXCEPT { return _M_t.begin(); }

  const_iterator begin() const _GLIBCXX_NOEXCEPT { return _M_t.begin(); }

  iterator end() _GLIBCXX_NOEXCEPT { return _M_t.end(); }

  const_iterator end() const _GLIBCXX_NOEXCEPT { return _M_t.end(); }

  reverse_iterator rbegin() _GLIBCXX_NOEXCEPT { return _M_t.rbegin(); }

  const_reverse_iterator rbegin() const _GLIBCXX_NOEXCEPT {
    return _M_t.rbegin();
  }

  reverse_iterator rend() _GLIBCXX_NOEXCEPT { return _M_t.rend(); }

  const_reverse_iterator rend() const _GLIBCXX_NOEXCEPT { return _M_t.rend(); }

  bool empty() const _GLIBCXX_NOEXCEPT { return _M_t.empty(); }

  size_type size() const _GLIBCXX_NOEXCEPT { return _M_t.size(); }

  size_type max_size() const _GLIBCXX_NOEXCEPT { return _M_t.max_size(); }

  /*
  **  If the key does not exist, a pair with that key is created using default values,
  **  which is then returned.
  */
  mapped_type& operator[](const key_type& __k) {
    iterator __i = lower_bound(__k);
    if (__i == end() || key_comp()(__k, (*__i).first)) // 見つからなかった場合insert
      __i = insert(__i, value_type(__k, mapped_type())); // __iの1個前に、M[__k] = 0 をいれる
	return (*__i).second;
  }

  /*
  **  @throw  std::out_of_range  If no such data is present.
  */
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

  // modifiers

  /*
  **  @return  A pair, of which the first element is an iterator that
  **           points to the possibly inserted pair, and the second is
  **           a bool that is true if the pair was actually inserted.
  **
  **  M[1] = 1;
  **
  **  1.) sample flase: auto p = M.insert({1, 100}); // false
  **  auto it = p.first;
  **  {it->first, it->second} // {1, 1}
  **  p->second // false
  **
  **  2.) sample true: auto p = M.insert({2, 100}); // true
  **  auto it = p.first;
  **  {it->first, it->second} // {2, 100}
  **  p->second // true
  */

  std::pair<iterator, bool> insert(const value_type& __x) {
    return _M_t._M_insert_unique(__x);
  }

  iterator insert(iterator __position, const value_type& __x) {
    return _M_t._M_insert_unique_(__position, __x);
  }

  template <typename _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last) {
    _M_t._M_insert_unique(__first, __last);
  }

  void erase(iterator __position) { _M_t.erase(__position); }

  /*
  **  @return  The number of elements erased.
  **  M[1] = 1;
  **  auto z = M.erase(0) // 0
  **  z = M.erase(1) // 1
  */
  size_type erase(const key_type& __x) { return _M_t.erase(__x); }

  void erase(iterator __first, iterator __last) { _M_t.erase(__first, __last); }

  void swap(map& __x) { _M_t.swap(__x._M_t); }

  void clear() _GLIBCXX_NOEXCEPT { _M_t.clear(); }

  // observers
  /**
   *  Returns the key comparison object out of which the %map was
   *  constructed.
   */
  key_compare key_comp() const { return _M_t.key_comp(); }

  /**
   *  Returns a value comparison object, built from the key comparison
   *  object out of which the %map was constructed.
   */
  value_compare value_comp() const { return value_compare(_M_t.key_comp()); }

  /*
  **  @return  Iterator pointing to sought-after element, or end() if not
  **           found.
  */
  iterator find(const key_type& __x) { return _M_t.find(__x); }

  const_iterator find(const key_type& __x) const { return _M_t.find(__x); }

  size_type count(const key_type& __x) const {
    return _M_t.find(__x) == _M_t.end() ? 0 : 1;
  }

  iterator lower_bound(const key_type& __x) { return _M_t.lower_bound(__x); }

  const_iterator lower_bound(const key_type& __x) const {
    return _M_t.lower_bound(__x);
  }

  iterator upper_bound(const key_type& __x) { return _M_t.upper_bound(__x); }

  const_iterator upper_bound(const key_type& __x) const {
    return _M_t.upper_bound(__x);
  }

  //@}

  //@{
  /**
   *  @brief Finds a subsequence matching given key.
   *  @param  __x  Key of (key, value) pairs to be located.
   *  @return  Pair of iterators that possibly points to the subsequence
   *           matching given key.
   *
   *  This function is equivalent to
   *  @code
   *    std::make_pair(c.lower_bound(val),
   *                   c.upper_bound(val))
   *  @endcode
   *  (but is faster than making the calls separately).
   *
   *  This function probably only makes sense for multimaps.
   */
  std::pair<iterator, iterator> equal_range(const key_type& __x) {
    return _M_t.equal_range(__x);
  }

  /**
   *    std::make_pair(c.lower_bound(val),
   *                   c.upper_bound(val))
   */
  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& __x) const {
    return _M_t.equal_range(__x);
  }

  template <typename _K1, typename _T1, typename _C1, typename _A1>
  friend bool operator==(const map<_K1, _T1, _C1, _A1>&,
                         const map<_K1, _T1, _C1, _A1>&);

  template <typename _K1, typename _T1, typename _C1, typename _A1>
  friend bool operator<(const map<_K1, _T1, _C1, _A1>&,
                        const map<_K1, _T1, _C1, _A1>&);
};

/**
 *  @brief  Map equality comparison.
 *  @param  __x  A %map.
 *  @param  __y  A %map of the same type as @a x.
 *  @return  True iff the size and elements of the maps are equal.
 *
 *  This is an equivalence relation.  It is linear in the size of the
 *  maps.  Maps are considered equivalent if their sizes are equal,
 *  and if corresponding elements compare equal.
 */
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator==(const map<_Key, _Tp, Compare, _Alloc>& __x,
                       const map<_Key, _Tp, Compare, _Alloc>& __y) {
  return __x._M_t == __y._M_t;
}

/**
 *  @brief  Map ordering relation.
 *  @param  __x  A %map.
 *  @param  __y  A %map of the same type as @a x.
 *  @return  True iff @a x is lexicographically less than @a y.
 *
 *  This is a total ordering relation.  It is linear in the size of the
 *  maps.  The elements must be comparable with @c <.
 *
 *  See std::lexicographical_compare() for how the determination is made.
 */
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator<(const map<_Key, _Tp, Compare, _Alloc>& __x,
                      const map<_Key, _Tp, Compare, _Alloc>& __y) {
  return __x._M_t < __y._M_t;
}

/// Based on operator==
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator!=(const map<_Key, _Tp, Compare, _Alloc>& __x,
                       const map<_Key, _Tp, Compare, _Alloc>& __y) {
  return !(__x == __y);
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator>(const map<_Key, _Tp, Compare, _Alloc>& __x,
                      const map<_Key, _Tp, Compare, _Alloc>& __y) {
  return __y < __x;
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator<=(const map<_Key, _Tp, Compare, _Alloc>& __x,
                       const map<_Key, _Tp, Compare, _Alloc>& __y) {
  return !(__y < __x);
}

/// Based on operator<
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline bool operator>=(const map<_Key, _Tp, Compare, _Alloc>& __x,
                       const map<_Key, _Tp, Compare, _Alloc>& __y) {
  return !(__x < __y);
}

/// See std::map::swap().
template <typename _Key, typename _Tp, typename Compare, typename _Alloc>
inline void swap(map<_Key, _Tp, Compare, _Alloc>& __x,
                 map<_Key, _Tp, Compare, _Alloc>& __y) {
  __x.swap(__y);
}

_GLIBCXX_END_NAMESPACE_CONTAINER

_GLIBCXX_END_NAMESPACE_VERSION
}  // namespace ft

#endif
