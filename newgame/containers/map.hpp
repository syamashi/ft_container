#ifndef MAP_HPP
#define MAP_HPP

#include "../utils/rb_tree.hpp"

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

  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    // friend class map<_Key, _Tp, Compare, _Alloc>; // forbidden?

    // protected:
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

  map() : _M_t() {}

  /*
  ** Iterators
  */

  iterator begin() { return _M_t.begin(); }
  const_iterator begin() const { return _M_t.begin(); }
  iterator end() { return _M_t.end(); }
  const_iterator end() const { return _M_t.end(); }
  reverse_iterator rbegin() { return _M_t.rbegin(); }
  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  reverse_iterator rend() { return _M_t.rend(); }
  const_reverse_iterator rend() const { return _M_t.rend(); }
  bool empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }

  
  //// Element access

  //// Modifiers

  ft::pair<iterator, bool> insert(const value_type& __x) {
    return _M_t.insert(__x);
  }
  
  //// Lookup
  iterator lower_bound(const key_type& __x) { return _M_t.lower_bound(__x); }

  const_iterator lower_bound(const key_type& __x) const {
    return _M_t.lower_bound(__x);
  }

};

}  // namespace ft

#endif