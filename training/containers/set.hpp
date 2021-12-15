#ifndef _STL_SET_H
#define _STL_SET_H 1

#include <bits/concept_check.h>
#include "../utils/rb_tree.hpp"

namespace std _GLIBCXX_VISIBILITY(default) {
  template <typename _Key, typename _Compare = std::less<_Key>,
            typename _Alloc = std::allocator<_Key>>
  class set {
   public:
    typedef _Key key_type;
    typedef _Key value_type;
    typedef _Compare key_compare;
    typedef _Compare value_compare;
    typedef _Alloc allocator_type;

   private:
    typedef
        typename __gnu_cxx::__alloc_traits<_Alloc>::template rebind<_Key>::other
            _Key_alloc_type;

    typedef _Rb_tree<key_type, value_type, _Identity<value_type>, key_compare,
                     _Key_alloc_type>
        _Rep_type;
    _Rep_type _M_t;  // Red-black tree representing set.

    typedef __gnu_cxx::__alloc_traits<_Key_alloc_type> _Alloc_traits;

   public:
    typedef typename _Alloc_traits::pointer pointer;
    typedef typename _Alloc_traits::const_pointer const_pointer;
    typedef typename _Alloc_traits::reference reference;
    typedef typename _Alloc_traits::const_reference const_reference;
    typedef typename _Rep_type::const_iterator iterator;
    typedef typename _Rep_type::const_iterator const_iterator;
    typedef typename _Rep_type::const_reverse_iterator reverse_iterator;
    typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
    typedef typename _Rep_type::size_type size_type;
    typedef typename _Rep_type::difference_type difference_type;

    // allocation/deallocation
    set() : _M_t() {}

    explicit set(const _Compare& __comp,
                 const allocator_type& __a = allocator_type())
        : _M_t(__comp, _Key_alloc_type(__a)) {}

    template <typename _InputIterator>
    set(_InputIterator __first, _InputIterator __last) : _M_t() {
      _M_t._M_insert_unique(__first, __last);
    }

    template <typename _InputIterator>
    set(_InputIterator __first, _InputIterator __last, const _Compare& __comp,
        const allocator_type& __a = allocator_type())
        : _M_t(__comp, _Key_alloc_type(__a)) {
      _M_t._M_insert_unique(__first, __last);
    }

    set(const set& __x) : _M_t(__x._M_t) {}
    set& operator=(const set& __x) {
      _M_t = __x._M_t;
      return *this;
    }
    // accessors:

    key_compare key_comp() const { return _M_t.key_comp(); }
    value_compare value_comp() const { return _M_t.key_comp(); }
    allocator_type get_allocator() const {
      return allocator_type(_M_t.get_allocator());
    }

    iterator begin() const _GLIBCXX_NOEXCEPT { return _M_t.begin(); }

    iterator end() const _GLIBCXX_NOEXCEPT { return _M_t.end(); }

    reverse_iterator rbegin() const _GLIBCXX_NOEXCEPT { return _M_t.rbegin(); }

    reverse_iterator rend() const _GLIBCXX_NOEXCEPT { return _M_t.rend(); }

    ///  Returns true if the %set is empty.
    bool empty() const _GLIBCXX_NOEXCEPT { return _M_t.empty(); }

    ///  Returns the size of the %set.
    size_type size() const _GLIBCXX_NOEXCEPT { return _M_t.size(); }

    ///  Returns the maximum size of the %set.
    size_type max_size() const _GLIBCXX_NOEXCEPT { return _M_t.max_size(); }

    void swap(set& __x)
        _GLIBCXX_NOEXCEPT_IF(__is_nothrow_swappable<_Compare>::value) {
      _M_t.swap(__x._M_t);
    }

    // insert/erase
    std::pair<iterator, bool> insert(const value_type& __x) {
      std::pair<typename _Rep_type::iterator, bool> __p =
          _M_t._M_insert_unique(__x);
      return std::pair<iterator, bool>(__p.first, __p.second);
    }

     /*
     *  Insertion requires logarithmic time (if the hint is not taken).
     */
    iterator insert(const_iterator __position, const value_type& __x) {
      return _M_t._M_insert_unique_(__position, __x);
    }

    template <typename _InputIterator>
    void insert(_InputIterator __first, _InputIterator __last) {
      _M_t._M_insert_unique(__first, __last);
    }

    void erase(iterator __position) { _M_t.erase(__position); }

    size_type erase(const key_type& __x) { return _M_t.erase(__x); }

    void erase(iterator __first, iterator __last) {
      _M_t.erase(__first, __last);
    }

    void clear() _GLIBCXX_NOEXCEPT { _M_t.clear(); }

    // set operations:
    size_type count(const key_type& __x) const {
      return _M_t.find(__x) == _M_t.end() ? 0 : 1;
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

    /**
     *    std::make_pair(c.lower_bound(val),
     *                   c.upper_bound(val))
     */
    std::pair<iterator, iterator> equal_range(const key_type& __x) {
      return _M_t.equal_range(__x);
    }

    std::pair<const_iterator, const_iterator> equal_range(
        const key_type& __x) const {
      return _M_t.equal_range(__x);
    }

    template <typename _K1, typename _C1, typename _A1>
    friend bool operator==(const set<_K1, _C1, _A1>&,
                           const set<_K1, _C1, _A1>&);

    template <typename _K1, typename _C1, typename _A1>
    friend bool operator<(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);
  };

  template <typename _Key, typename _Compare, typename _Alloc>
  inline bool operator==(const set<_Key, _Compare, _Alloc>& __x,
                         const set<_Key, _Compare, _Alloc>& __y) {
    return __x._M_t == __y._M_t;
  }

  template <typename _Key, typename _Compare, typename _Alloc>
  inline bool operator<(const set<_Key, _Compare, _Alloc>& __x,
                        const set<_Key, _Compare, _Alloc>& __y) {
    return __x._M_t < __y._M_t;
  }

  ///  Returns !(x == y).
  template <typename _Key, typename _Compare, typename _Alloc>
  inline bool operator!=(const set<_Key, _Compare, _Alloc>& __x,
                         const set<_Key, _Compare, _Alloc>& __y) {
    return !(__x == __y);
  }

  ///  Returns y < x.
  template <typename _Key, typename _Compare, typename _Alloc>
  inline bool operator>(const set<_Key, _Compare, _Alloc>& __x,
                        const set<_Key, _Compare, _Alloc>& __y) {
    return __y < __x;
  }

  ///  Returns !(y < x)
  template <typename _Key, typename _Compare, typename _Alloc>
  inline bool operator<=(const set<_Key, _Compare, _Alloc>& __x,
                         const set<_Key, _Compare, _Alloc>& __y) {
    return !(__y < __x);
  }

  ///  Returns !(x < y)
  template <typename _Key, typename _Compare, typename _Alloc>
  inline bool operator>=(const set<_Key, _Compare, _Alloc>& __x,
                         const set<_Key, _Compare, _Alloc>& __y) {
    return !(__x < __y);
  }

  /// See std::set::swap().
  template <typename _Key, typename _Compare, typename _Alloc>
  inline void swap(set<_Key, _Compare, _Alloc> & __x,
                   set<_Key, _Compare, _Alloc> & __y)
      _GLIBCXX_NOEXCEPT_IF(noexcept(__x.swap(__y))) {
    __x.swap(__y);
  }

}  // namespace )
#endif /* _STL_SET_H */
