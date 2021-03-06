#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>

namespace ft {
template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  for (; first1 != last1; ++first1, ++first2)
    if (!bool(*first1 == *first2)) return false;
  return true;
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
           BinaryPredicate p) {
  for (; first1 != last1; ++first1, ++first2)
    if (!bool(p(*first1, *first2))) return false;
  return true;
}

template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (*first1 < *first2) return true;
    if (*first2 < *first1) return false;
  }
  return (first1 == last1) && (first2 != last2);
}

template <class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2, Compare comp) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (comp(*first1, *first2)) return true;
    if (comp(*first2, *first1)) return false;
  }
  return (first1 == last1) && (first2 != last2);
}
};  // namespace ft

namespace ft {

//// Tags

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//// iterator_traits

template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

/// Partial specialization for pointer types.
template <class T>
struct iterator_traits<T*> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

/// Partial specialization for pointer types.
template <class T>
struct iterator_traits<const T*> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

//// other iterators

template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

template <class Iter>
class reverse_iterator
    : public iterator<typename ft::iterator_traits<Iter>::iterator_category,
                      typename ft::iterator_traits<Iter>::value_type,
                      typename ft::iterator_traits<Iter>::difference_type,
                      typename ft::iterator_traits<Iter>::pointer,
                      typename ft::iterator_traits<Iter>::reference> {
 protected:
  Iter _current;
  typedef ft::iterator_traits<Iter> traits_type;

 public:
  typedef Iter iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::pointer pointer;
  typedef typename traits_type::reference reference;

  //// Member functions

  reverse_iterator() : _current() {}
  explicit reverse_iterator(iterator_type x) : _current(x) {}
  template <class U>
  reverse_iterator(const reverse_iterator<U>& other) : _current(other.base()) {}

  template <class U>
  reverse_iterator& operator=(const ft::reverse_iterator<U>& other) {
    _current = other.base();
    return *this;
  }

  virtual ~reverse_iterator() {}

  iterator_type base() const { return _current; }
  reference operator*() const {
    Iter tmp = _current;
    return *--tmp;
  }
  pointer operator->() const { return &(operator*()); }

  reference operator[](difference_type n) const { return *(*this + n); }

  reverse_iterator& operator++() {
    --_current;
    return *this;
  }
  reverse_iterator& operator--() {
    ++_current;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator __tmp = *this;
    --_current;
    return __tmp;
  }
  reverse_iterator operator--(int) {
    reverse_iterator __tmp = *this;
    ++_current;
    return __tmp;
  }
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(_current - n);
  }
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(_current + n);
  }
  reverse_iterator& operator+=(difference_type n) {
    _current -= n;
    return *this;
  }
  reverse_iterator& operator-=(difference_type n) {
    _current += n;
    return *this;
  }
};

//// reverse_iterator_nonmember_functions

template <class Iterator1, class Iterator2>
bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() == rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return !(lhs == rhs);
}

template <class Iterator1, class Iterator2>
bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
  return rhs.base() < lhs.base();
}
template <class Iterator1, class Iterator2>
bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs < rhs;
}
template <class Iterator1, class Iterator2>
bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return !(rhs < lhs);
}
template <class Iterator1, class Iterator2>
bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return !(lhs < rhs);
}

template <class Iter>
ft::reverse_iterator<Iter> operator+(
    typename ft::reverse_iterator<Iter>::difference_type n,
    const ft::reverse_iterator<Iter>& it) {
  return ft::reverse_iterator<Iter>(it.base() - n);
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::difference_type operator-(
    const ft::reverse_iterator<Iterator>& lhs,
    const ft::reverse_iterator<Iterator>& rhs) {
  return rhs.base() - lhs.base();
}

//// Functions

template <class InputIterator, class Distance>
void advance(InputIterator& it, Distance n) {
  while (n > 0) {
    ++it;
    --n;
  }
  while (n < 0) {
    --it;
    ++n;
  }
  return;
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(
    InputIterator first, InputIterator last) {
  typename ft::iterator_traits<InputIterator>::difference_type ret = 0;
  while (first != last) {
    ++first;
    ++ret;
  }
  return (ret);
}

template <typename Container>
struct back_insert_iterator {
  back_insert_iterator(Container& c) : c(&c) {}
  Container* c;

  typedef ft::output_iterator_tag iterator_category;
  typedef void value_type;
  typedef void difference_type;
  typedef void pointer;
  typedef void reference;

  back_insert_iterator& operator*() { return *this; }
  back_insert_iterator& operator++() { return *this; }
  back_insert_iterator operator++(int) { return *this; }
  back_insert_iterator& operator=(const typename Container::value_type& value) {
    c->push_back(value);
    return *this;
  }
};

template <class Container>
back_insert_iterator<Container> back_inserter(Container& c) {
  return back_insert_iterator<Container>(c);
}

template <typename Container>
struct front_insert_iterator {
  front_insert_iterator(Container& c) : c(&c) {}
  Container* c;

  typedef ft::output_iterator_tag iterator_category;
  typedef void value_type;
  typedef void difference_type;
  typedef void pointer;
  typedef void reference;

  front_insert_iterator& operator*() { return *this; }
  front_insert_iterator& operator++() { return *this; }
  front_insert_iterator operator++(int) { return *this; }
  front_insert_iterator& operator=(
      const typename Container::value_type& value) {
    c->push_front(value);
    return *this;
  }
};

template <class Container>
front_insert_iterator<Container> front_inserter(Container& x) {
  return front_insert_iterator<Container>(x);
}

template <typename Container>
struct insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void> {
 protected:
  Container* c;
  typename Container::iterator iter;

 public:
  typedef Container container_type;
  insert_iterator(Container& c) : c(&c) {}
  insert_iterator(Container& c, typename Container::iterator i)
      : c(&c), iter(i) {}
  insert_iterator& operator*() { return *this; }
  insert_iterator& operator++() { return *this; }
  insert_iterator operator++(int) { return *this; }
  insert_iterator& operator=(const typename Container::value_type& value) {
    iter = c->insert(iter, value);
    ++iter;
    return *this;
  }
};

template <class Container, class Iterator>
insert_iterator<Container> inserter(Container& x, Iterator it) {
  return insert_iterator<Container>(x, typename Container::iterator(it));
}
};  // namespace ft

namespace ft {
template <class _T1, class _T2>
struct pair {
  typedef _T1 first_type;
  typedef _T2 second_type;

  _T1 first;
  _T2 second;

  //// constructer
  pair() : first(), second() {}

  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}

  template <class _U1, class _U2>
  pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}

  //// operator=
  pair& operator=(const pair& other) {
    if (this == &other) return *this;
    first = other.first;
    second = other.second;
    return *this;
  }
};

//// Non-member functions

template <class _T1, class _T2>
ft::pair<_T1, _T2> make_pair(_T1 __x, _T2 __y) {
  return pair<_T1, _T2>(__x, __y);
}

/// Two pairs of the same type are equal iff their members are equal.
template <class _T1, class _T2>
bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first == __y.first && __x.second == __y.second;
}

/// <http://gcc.gnu.org/onlinedocs/libstdc++/manual/utilities.html>
template <class _T1, class _T2>
bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first < __y.first ||
         (!(__y.first < __x.first) && __x.second < __y.second);
}

/// Uses @c operator== to find the result.
template <class _T1, class _T2>
bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x == __y);
}

/// Uses @c operator< to find the result.
template <class _T1, class _T2>
bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __y < __x;
}

/// Uses @c operator< to find the result.
template <class _T1, class _T2>
bool operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__y < __x);
}

/// Uses @c operator< to find the result.
template <class _T1, class _T2>
bool operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x < __y);
}
}  // namespace ft

namespace ft {

/// integral_constant
/*
type ??? value_type ?????????????????????????????????

- constexpr operator value_type() const { return value; } // c++11
  ft::is_integral<int>() // 1
  ft::is_integral<int*>() // 0

????????? conversion function???????????????????????????????????????????????????????????????????????????

ft::is_integral<InputIt>::value ????????????????????????

- const value_type operator()() const {
  ft::is_integral<int> F;
  int f = F(); // f==1
*/
template <typename _Tp, _Tp __v>
struct integral_constant {
  static const _Tp value = __v;
  typedef _Tp value_type;
  typedef integral_constant<_Tp, __v> type;
  const value_type operator()() const { return value; }
};

/// The type used as a compile-time boolean with true value.
typedef integral_constant<bool, true> true_type;

/// The type used as a compile-time boolean with false value.
typedef integral_constant<bool, false> false_type;

/// is_same
/*
?????????false_type?????????
????????????????????????true?????????
*/
template <typename, typename>
struct is_same : public false_type {};

template <typename _Tp>
struct is_same<_Tp, _Tp> : public true_type {};

// Const-volatile modifications.

/// remove_const
template <typename T>
struct remove_const {
  typedef T type;
};

template <typename T>
struct remove_const<T const> {
  typedef T type;
};

/// remove_volatile
template <typename T>
struct remove_volatile {
  typedef T type;
};

template <typename T>
struct remove_volatile<T volatile> {
  typedef T type;
};

/// remove_cv
template <typename T>
struct remove_cv {
  typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

/*
???????????????false_type
true????????????????????????
*/
template <typename>
struct __is_integral_helper : public false_type {};

template <>
struct __is_integral_helper<bool> : public true_type {};

template <>
struct __is_integral_helper<char> : public true_type {};

template <>
struct __is_integral_helper<signed char> : public true_type {};

template <>
struct __is_integral_helper<unsigned char> : public true_type {};

template <>
struct __is_integral_helper<wchar_t> : public true_type {};

// template <>
// struct __is_integral_helper<char16_t> : public true_type {};

// template <>
// struct __is_integral_helper<char32_t> : public true_type {};

template <>
struct __is_integral_helper<short> : public true_type {};

template <>
struct __is_integral_helper<unsigned short> : public true_type {};

template <>
struct __is_integral_helper<int> : public true_type {};

/*
template <>
struct __is_integral_helper<int>{
  static const bool value = true;
  typedef int value_type;
  typedef __is_integral_helper<int> type;
  const operator value_type() const { return value; }
  const value_type operator()() const { return value; }
};
*/

template <>
struct __is_integral_helper<unsigned int> : public true_type {};

template <>
struct __is_integral_helper<long> : public true_type {};

template <>
struct __is_integral_helper<unsigned long> : public true_type {};

template <>
struct __is_integral_helper<long long> : public true_type {};

template <>
struct __is_integral_helper<unsigned long long> : public true_type {};

//// is_integral
template <typename T>
struct is_integral
    : public __is_integral_helper<typename remove_cv<T>::type>::type {};

//// enable_if
/*
type ???????????????????????????????????????

bool B ???true???????????????enable_if::type ?????????????????????

  set(InputIt first, InputIt last, const _Compare& comp = _Compare(),
      const allocator_type& a = allocator_type(),
      typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* =
          nullptr)
ft::is_integral< T >::value???true????????????
ft::enable_if< false , > ??????????????????::type??????????????????
5??????????????? typename ft::enable_if---::type
????????????????????????????????????????????????????????????????????????????????????????????????

*/
template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
  typedef T type;
};

//// _KeyOfValue

template <typename _Pair>
struct _Select1st {
  typename _Pair::first_type& operator()(_Pair& __x) const { return __x.first; }

  const typename _Pair::first_type& operator()(const _Pair& __x) const {
    return __x.first;
  }
};

template <typename _Tp>
struct _Identity {
  _Tp& operator()(_Tp& __x) const { return __x; }

  const _Tp& operator()(const _Tp& __x) const { return __x; }
};

// Partial specialization, avoids confusing errors in e.g. std::set<const T>.
template <typename _Tp>
struct _Identity<const _Tp> : _Identity<_Tp> {};

};  // namespace ft

namespace ft {

enum _Rb_tree_color { _S_red = false, _S_black = true };

template <typename _Val>
struct _Rb_tree_node {
  typedef _Rb_tree_node<_Val>* _Link_type;

  _Rb_tree_color _M_color;
  _Link_type _M_parent;
  _Link_type _M_left;
  _Link_type _M_right;
  _Val* _M_value_type;

  // returns pointer to uncle
  /*
       B
      / \
     R   R uncle
    /
   B me
  */
  _Link_type uncle() {
    // If no parent or grandparent, then no uncle
    if (_M_parent == NULL or _M_parent->_M_parent == NULL) return NULL;

    if (_M_parent->isOnLeft())
      // uncle on right
      return _M_parent->_M_parent->_M_right;
    else
      // uncle on left
      return _M_parent->_M_parent->_M_left;
  }

  // check if node is left child of parent
  bool isOnLeft() { return this == _M_parent->_M_left; }

  // returns pointer to sibling
  /*
         B
        / \
    me R   R sibling
  */
  _Link_type sibling() {  // ??????
    // sibling null if no parent
    if (_M_parent == NULL) return NULL;

    if (isOnLeft()) return _M_parent->_M_right;

    return _M_parent->_M_left;
  }

  // moves node down and moves given node in its place
  /*
  before
       R parent
      /
     B me

  after
       R parent
      /
     B nParent
     |
    B me
    "nParent->(left or right) = me" decide in rotate() func.
  */
  void moveDown(_Link_type nParent) {
    if (_M_parent != NULL) {
      if (isOnLeft()) {
        _M_parent->_M_left = nParent;
      } else {
        _M_parent->_M_right = nParent;
      }
    }
    nParent->_M_parent = _M_parent;
    _M_parent = nParent;
  }

  bool hasRedChild() {
    return (_M_left != NULL and _M_left->_M_color == _S_red) or
           (_M_right != NULL and _M_right->_M_color == _S_red);
  }

  /*
               B10
              /   \
            R7     R22
           / \      / \
         B6  B8   B13  B26
         /
        R2

    ---B10.swap(B13)---
               B13
              /   \
            R7     B22
           / \        \
         B6  B8        R26
         /
        R2
  */
  /*
  swap except _Val = pair(const key, val)
  const cannot swap or copy

  header->parent cannot apply
  */
  void swapNode(_Link_type& x) {
    // x????????????
    _Link_type xp = x->_M_parent;
    _Link_type xr = x->_M_right;
    _Link_type xl = x->_M_left;
    _Link_type tp = _M_parent;
    _Link_type tr = _M_right;
    _Link_type tl = _M_left;

    if (xp->_M_left == x)
      xp->_M_left = this;
    else if (xp->_M_right == x)
      xp->_M_right = this;
    if (xl) xl->_M_parent = this;
    if (xr) xr->_M_parent = this;

    // ??????????????????
    if (isOnLeft())
      tp->_M_left = x;
    else
      tp->_M_right = x;
    if (tl) tl->_M_parent = x;
    if (tr) tr->_M_parent = x;

    std::swap(_M_color, x->_M_color);
    std::swap(_M_parent, x->_M_parent);
    std::swap(_M_right, x->_M_right);
    std::swap(_M_left, x->_M_left);
  }
};

template <typename _Val>
static _Rb_tree_node<_Val>* local_Rb_tree_increment(
    _Rb_tree_node<_Val>* x) throw() {
  /*
           DUMMY(R): 0x7ffe5ab13d08
             +       |     right: 7
             |       +     left: 1
     [ROOT] 2(B): 0x1892500
              right: 4
              left: 1
             /       \
   1(B): 0x18924d0     4(R): 0x1892560
     right: 0            right: 6
     left: 0             left: 3
                         /      \
             3(B): 0x1892530     6(B): 0x18925c0
              right: 0             right: 7
              left: 0              left: 5
                                  /       \
                        5(R): 0x1892590    7(R): 0x18925f0
                          right: 0            right: 0
                          left: 0             left: 0
  1. ????????????(4->5)
    ??????????????????????????????????????????
  2. ????????????(5->6)
    ??????????????????????????????????????????????????????
  3. ?????????????????????(7->dummy)
    Dummy???????????????dummy?????????4???????????????
  */

  // size==0
  if (x->_M_right == x) return x;
  if (x->_M_right != 0) {
    x = x->_M_right;
    while (x->_M_left != 0) x = x->_M_left;
  } else {
    _Rb_tree_node<_Val>* y = x->_M_parent;
    while (x == y->_M_right) {
      x = y;
      y = y->_M_parent;
    }
    if (x->_M_right != y) {
      /*
      x->_M_right == y <=> M.size()==1 && x==dummy, return(dummy)

        dummy(R): 0x7ffde6b05688
       | + right: ROOT
       + | left: ROOT
        ROOT(B): 0x9414d0
          right: 0
          left: 0
      */
      x = y;
    }
  }
  return x;
}

template <typename _Val>
_Rb_tree_node<_Val>* _Rb_tree_increment(_Rb_tree_node<_Val>* x) throw() {
  return local_Rb_tree_increment(x);
}

template <typename _Val>
const _Rb_tree_node<_Val>* _Rb_tree_increment(
    const _Rb_tree_node<_Val>* x) throw() {
  return local_Rb_tree_increment(const_cast<_Rb_tree_node<_Val>*>(x));
}

template <typename _Val>
static _Rb_tree_node<_Val>* local_Rb_tree_decrement(
    _Rb_tree_node<_Val>* x) throw() {
  /*
           DUMMY(R): 0x7ffe5ab13d08
             +       |     right: 7
             |       +     left: 1
     [ROOT] 2(B): 0x1892500
              right: 4
              left: 1
             /       \
   1(B): 0x18924d0     4(R): 0x1892560
     right: 0            right: 6
     left: 0             left: 3
                         /      \
             3(B): 0x1892530     6(B): 0x18925c0
              right: 0             right: 7
              left: 0              left: 5
                                  /       \
                        5(R): 0x1892590    7(R): 0x18925f0
                          right: 0            right: 0
                          left: 0             left: 0
  1. ????????????(4->3)
    ??????????????????????????????????????????
  2. ????????????(5->4)
    ??????????????????????????????????????????????????????
  3. ?????????????????????(dummy->7)
    Dummy->right
  */

  // size==0
  if (x->_M_right == x) return x;
  // x == dummy == M.end()
  if (x->_M_color == _S_red && x->_M_parent->_M_parent == x)
    x = x->_M_right;
  else if (x->_M_left != 0) {
    _Rb_tree_node<_Val>* y = x->_M_left;
    while (y->_M_right != 0) {
      y = y->_M_right;
    }
    x = y;
  } else {
    _Rb_tree_node<_Val>* y = x->_M_parent;
    while (x == y->_M_left) {
      x = y;
      y = y->_M_parent;
    }
    x = y;
  }
  return x;
}

template <typename _Val>
_Rb_tree_node<_Val>* _Rb_tree_decrement(_Rb_tree_node<_Val>* x) throw() {
  return local_Rb_tree_decrement(x);
}

template <typename _Val>
const _Rb_tree_node<_Val>* _Rb_tree_decrement(
    const _Rb_tree_node<_Val>* x) throw() {
  return local_Rb_tree_decrement(const_cast<_Rb_tree_node<_Val>*>(x));
}

template <typename _Tp>
struct _Rb_tree_iterator {
  typedef _Tp value_type;
  typedef _Tp& reference;
  typedef _Tp* pointer;

  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef _Rb_tree_iterator<_Tp> _Self;
  typedef typename _Rb_tree_node<_Tp>::_Link_type _Link_type;

  _Rb_tree_iterator() : _M_node() {}
  explicit _Rb_tree_iterator(_Link_type x) : _M_node(x) {}

  reference operator*() const { return *_M_node->_M_value_type; }
  pointer operator->() const { return _M_node->_M_value_type; }

  _Self& operator++() {
    _M_node = _Rb_tree_increment(_M_node);
    return *this;
  }

  _Self operator++(int) {
    _Self tmp = *this;
    _M_node = _Rb_tree_increment(_M_node);
    return tmp;
  }

  _Self& operator--() {
    _M_node = _Rb_tree_decrement(_M_node);
    return *this;
  }

  _Self operator--(int) {
    _Self tmp = *this;
    _M_node = _Rb_tree_decrement(_M_node);
    return tmp;
  }

  bool operator==(const _Self& x) const { return _M_node == x._M_node; }
  bool operator!=(const _Self& x) const { return _M_node != x._M_node; }

  // debug
 public:
  _Rb_tree_color get_color() { return _M_node->_M_color; }
  _Link_type get_link() { return _M_node; }

  // member value /////
  _Link_type _M_node;
};

template <typename _Tp>
struct _Rb_tree_const_iterator {
  typedef _Tp value_type;
  typedef const _Tp& reference;
  typedef const _Tp* pointer;

  typedef _Rb_tree_iterator<_Tp> iterator;

  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef _Rb_tree_const_iterator<_Tp> _Self;
  typedef const _Rb_tree_node<_Tp>* _Link_type;

  _Rb_tree_const_iterator() : _M_node() {}
  explicit _Rb_tree_const_iterator(_Link_type x) : _M_node(x) {}
  _Rb_tree_const_iterator(const iterator& it) : _M_node(it._M_node) {}
  iterator _M_const_cast() const {
    return iterator(const_cast<typename iterator::_Link_type>(_M_node));
  }
  reference operator*() const { return *_M_node->_M_value_type; }
  pointer operator->() const { return _M_node->_M_value_type; }

  _Self& operator++() {
    _M_node = _Rb_tree_increment(_M_node);
    return *this;
  }

  _Self operator++(int) {
    _Self tmp = *this;
    _M_node = _Rb_tree_increment(_M_node);
    return tmp;
  }

  _Self& operator--() {
    _M_node = _Rb_tree_decrement(_M_node);
    return *this;
  }

  _Self operator--(int) {
    _Self tmp = *this;
    _M_node = _Rb_tree_decrement(_M_node);
    return tmp;
  }

  bool operator==(const _Self& x) const { return _M_node == x._M_node; }
  bool operator!=(const _Self& x) const { return _M_node != x._M_node; }

  // member value ////
  _Link_type _M_node;
};

template <typename _Val>
inline bool operator==(const _Rb_tree_iterator<_Val>& __x,
                       const _Rb_tree_const_iterator<_Val>& __y) {
  return __x._M_node == __y._M_node;
}

template <typename _Val>
inline bool operator!=(const _Rb_tree_iterator<_Val>& __x,
                       const _Rb_tree_const_iterator<_Val>& __y) {
  return __x._M_node != __y._M_node;
}

template <typename _Key, typename _Val, typename Compare,
          typename _Alloc = std::allocator<_Val> >
class _Rb_tree {
  // _Alloc?????????<_Val> ??? <Node<_Val> > ??? ???????????????
  typedef typename _Alloc::template rebind<_Rb_tree_node<_Val> >::other
      _Node_allocator;

 protected:
  typedef _Rb_tree_node<_Val>* _Link_type;
  typedef const _Rb_tree_node<_Val>* _Const_Link_type;

 public:
  typedef _Key key_type;
  typedef _Val value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef _Alloc allocator_type;
  typedef Compare key_compare;

  //// member value ////
 private:
  _Link_type _M_header;
  size_type _M_node_count;
  key_compare _M_key_compare;
  _Node_allocator _M_node_alloc;

 public:
  typedef _Rb_tree_iterator<value_type> iterator;
  typedef _Rb_tree_const_iterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 protected:
  key_type _S_key(_Link_type x) const {
    return (*(x->_M_value_type));
  }
  key_type _S_key(_Const_Link_type x) const {
    return (*(x->_M_value_type));
  }
  key_type _S_key(value_type x) const { return (x); }
  key_type _S_key(iterator x) const { return (*x); }
  key_type _S_key(const_iterator x) const { return (*x); }
  _Link_type _M_end() { return _M_header; }
  _Const_Link_type _M_end() const { return _M_header; }
  _Link_type _S_root() { return _M_header->_M_parent; }
  _Const_Link_type _S_root() const { return _M_header->_M_parent; }
  _Link_type& _M_root() { return _M_header->_M_parent; }
  _Const_Link_type _M_root() const { return _M_header->_M_parent; }
  _Link_type _S_mostleft() {
    _Link_type ret = _S_root();
    if (ret == NULL) return _M_header;
    while (ret->_M_left) ret = ret->_M_left;
    return ret;
  }
  _Const_Link_type _S_mostleft() const {
    return (_Const_Link_type)_S_mostleft();
  }
  _Link_type _S_mostright() {
    _Link_type ret = _S_root();
    if (ret == NULL) return _M_header;
    while (ret->_M_right) ret = ret->_M_right;
    return ret;
  }
  _Const_Link_type _S_mostright() const {
    return (_Const_Link_type)_S_mostright();
  }

  void _M_reset() {
    _M_header->_M_color = _S_red;
    _M_header->_M_parent = 0;
    _M_header->_M_left = _M_header;
    _M_header->_M_right = _M_header;
    _M_node_count = 0;
  }

  void _M_move_data(_Rb_tree& __from) {  // from ??????????????????
    _M_header->_M_color = __from._M_header->_M_color;
    _M_root() = __from._M_header->_M_parent;
    _M_header->_M_left = __from._M_header->_M_left;
    _M_header->_M_right = __from._M_header->_M_right;
    _M_root()->_M_parent = _M_header;
    _M_node_count = __from._M_node_count;
    __from._M_reset();
  }

  //// iterator ////////////////

 public:
  iterator begin() { return iterator(_M_header->_M_left); }
  const_iterator begin() const { return const_iterator(_M_header->_M_left); }
  iterator end() { return iterator(_M_header); }
  const_iterator end() const { return const_iterator(_M_header); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  key_compare key_comp() const { return _M_key_compare; }
  allocator_type get_allocator() const { return allocator_type(_M_node_alloc); }
  bool empty() const { return _M_node_count == 0; }
  size_type size() const { return _M_node_count; }
  /*
  vector<char>  : max() / 2
  vector<int>   : max() / 4
  map<int,int>  : max() / 40
  map<int,char> : max() / 40
  map<char,int> : max() / 40
  map<char,char>: max() / 32
  set<int>      : max() / 32
  set<char>     : max() / 32
  */
  size_type max_size() const {
    size_t div = sizeof(_Link_type) * 4 + sizeof(value_type);
    div = (div / 8) * 8;
    return std::numeric_limits<size_type>::max() / div;
    //    return _M_node_alloc.max_size();
  }

 public:
  _Rb_tree() : _M_key_compare(key_compare()), _M_node_alloc(_Node_allocator()) {
    _M_header = _M_create_node(value_type());  // size()==1 ??????????????????
    _M_reset();
  }
  _Rb_tree(const key_compare& key_comp, const _Node_allocator& node_alloc)
      : _M_key_compare(key_comp), _M_node_alloc(node_alloc) {
    _M_header = _M_create_node(value_type());  // size()==1 ??????????????????
    _M_reset();
  }
  _Rb_tree(_Rb_tree const& src) {
    // header????????????
    _M_header = _M_create_node(value_type());  // size()==1 ??????????????????
    _M_reset();
    _M_key_compare = src._M_key_compare;
    _M_node_alloc = src._M_node_alloc;
    if (src._M_root() != 0) {
      _M_root() = _M_copy(src._M_header->_M_parent, _M_header);
      _M_header->_M_left = _S_mostleft();
      _M_header->_M_right = _S_mostright();
    }
  }
  ~_Rb_tree() {
    _M_erase(_S_root());
    ++_M_node_count;
    _M_put_node(_M_header);
  }
  _Rb_tree& operator=(const _Rb_tree& src) {
    if (this == &src) return *this;
    _M_erase(_S_root());

    // header?????????????????????
    _M_reset();
    _M_key_compare = src._M_key_compare;
    _M_node_alloc = src._M_node_alloc;
    // root??????????????????
    if (src._M_node_count) {
      _M_root() = _M_copy(src._M_header->_M_parent, _M_header);
      _M_header->_M_left = _S_mostleft();
      _M_header->_M_right = _S_mostright();
    }
    return *this;
  }

  //// Modifiers

  void clear() {
    _M_erase(_S_root());
    _M_reset();
  }

  // insert???helper4??????

  /*
             DUMMY(R): 0x7ffe5ab13d08
               +       |     right: 7
               |       +     left: 1
       [ROOT] 2(B): 0x1892500
                right: 4
                left: 1
               /       \
     1(B): 0x18924d0     4(R): 0x1892560
       right: 0            right: 6
       left: 0             left: 3
                           /      \
               3(B): 0x1892530     6(B): 0x18925c0
                right: 0             right: 7
                left: 0              left: 5
                                    /       \
                          5(R): 0x1892590    7(R): 0x18925f0
                            right: 0            right: 0
                            left: 0             left: 0


  4.5???????????????????????????
  root=2
  4.5>2

  root=4
  4.5>4

  root=6
  4.5<6

  root=5
  4.5<5

  root=NULL

  (root=5) // ??????????????????????????????
  5->left = 4.5 (NULL->4.5)
  4.5->parent = 5

  (root=6)
  6->left = 5 (5->5)
  5->parent = 6 (6->6)
  ...
  */
 protected:
  _Link_type BSTInsert(_Link_type root, _Link_type pt) {
    /* If the tree is empty, return a new _Link_type */
    if (root == NULL) return pt;

    /* Otherwise, recur down the tree */
    if (_M_key_compare(_S_key(pt), _S_key(root))) {
      root->_M_left = BSTInsert(root->_M_left, pt);
      root->_M_left->_M_parent = root;
    } else if (_M_key_compare(_S_key(root), _S_key(pt))) {
      root->_M_right = BSTInsert(root->_M_right, pt);
      root->_M_right->_M_parent = root;
    }

    /* return the (unchanged) node pointer */
    return root;
  }

  /*
  before                                        after
  ??????????????????root                                    root
              |                                       |
             50(B) x:grand_parent                  70(B):nParent
            /   \                                   /   \
    uncle:20(B)  70(R):nParent                    x:50(R)  88(R)
                /  \                             /   \
            60(B)  88(R)                     20(B)  60(B)

  ?????????????????????????????????
  ?????????????????????
  ?????????????????????????????????
  ????????????????????????
  ??????????????????????????????????????????????????????????????????
  */
  // left rotates the given node
  void leftRotate(_Link_type x) {
    // new parent will be node's right child
    _Link_type nParent = x->_M_right;  // 70

    // update root if current node is root
    if (x == _S_root()) _M_root() = nParent;

    x->moveDown(nParent);  // root->left = 70 and 70->parent = root

    // connect x with new parent's left element
    x->_M_right = nParent->_M_left;  // 50->right = 60
    // connect new parent's left element with node
    // if it is not null
    if (nParent->_M_left != NULL)
      nParent->_M_left->_M_parent = x;  // 50->parent = 70

    // connect new parent with x
    nParent->_M_left = x;  // 70->left = 50
  }

  /*
  before                                        after
  ??????????????????root                                    root
              |                                       |
             50(B) x:grand_parent                  20(B):nParent
            /   \                                   /  \
  nParent:20(R)  70(B):uncle                     16(R)  50(R):x
          /  \                                         /   \
       16(R)  24(B)                                  24(B)  70(B)

  ?????????????????????????????????
  ?????????????????????
  ?????????????????????????????????
  ????????????????????????
  ??????????????????????????????????????????????????????????????????
  */
  void rightRotate(_Link_type x) {
    // new parent will be node's left child
    _Link_type nParent = x->_M_left;  // 20

    // update root if current node is root
    if (x == _S_root()) _M_root() = nParent;

    x->moveDown(nParent);  // root->right = 20 and 20->parent = root

    // connect x with new parent's right element
    x->_M_left = nParent->_M_right;  // 50->left = 24
    // connect new parent's right element with node
    // if it is not null
    if (nParent->_M_right != NULL) nParent->_M_right->_M_parent = x;

    // connect new parent with x
    nParent->_M_right = x;  // 20->right = 50
  }

  void fixRedRed(_Link_type& pt) {
    _Link_type parent_pt = NULL;
    _Link_type grand_parent_pt = NULL;

    while ((pt != _S_root()) && (pt->_M_color != _S_black) &&
           (pt->_M_parent->_M_color ==
            _S_red))  // ???????????????????????????????????????????????????
    {
      parent_pt = pt->_M_parent;
      grand_parent_pt = pt->_M_parent->_M_parent;

      /*
         Case : A
              Parent of pt is left child of Grand-parent of pt.
              pt?????????pt???????????????????????????????????????
                B grand_parent
               /
              R parent
              |
              R
      */
      if (parent_pt == grand_parent_pt->_M_left) {
        _Link_type uncle_pt = grand_parent_pt->_M_right;

        /* Case : 1
        The uncle of pt is also red
        Only Recoloring required

        ??????????????????????????????????????????
                 B grand_parent
                / \
        Parent R   R uncle
               |
               R
        */
        if (uncle_pt != NULL && uncle_pt->_M_color == _S_red) {
          grand_parent_pt->_M_color = _S_red;
          parent_pt->_M_color = _S_black;
          uncle_pt->_M_color = _S_black;
          pt = grand_parent_pt;
        } else {
          /* Case : 2
          pt is right child of its parent
          Left-rotation require
          ????????????pt????????????????????????
                   B grand_parent
                  / \
          Parent R   B uncle
                  \
                   R
          */
          if (pt == parent_pt->_M_right) {
            leftRotate(parent_pt);
            pt = parent_pt;
            parent_pt = pt->_M_parent;
          }

          /* Case : 3
          pt is left child of its parent
          Right-rotation required
                   B grand_parent
                  / \
          Parent R   B uncle
                /
               R

          before ???????????????
                    root
                     |
                    50(B) grandparent
                    /   \
          Parent 20(R)   70(B) uncle
                  /
               16(R)

          after????????????
                    root
                     |
                    20(B)
                    /   \
                 16(R)  50(R)
                           \
                            70(B)
          ?????????????????????
          ?????????????????????????????????
          ???????????????????????? swap(20(B) 50(R))
          ??????????????????????????????????????????????????????????????????
          */
          rightRotate(grand_parent_pt);
          std::swap(parent_pt->_M_color, grand_parent_pt->_M_color);
          pt = parent_pt;
        }
      }

      /* Case : B
      Parent of pt is right child
      of Grand-parent of pt */
      else {
        _Link_type uncle_pt = grand_parent_pt->_M_left;  // null

        /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
        if ((uncle_pt != NULL) && (uncle_pt->_M_color == _S_red)) {
          grand_parent_pt->_M_color = _S_red;
          parent_pt->_M_color = _S_black;
          uncle_pt->_M_color = _S_black;
          pt = grand_parent_pt;
        } else {
          /* Case : 2
          pt is left child of its parent
          Right-rotation required
          */
          if (pt == parent_pt->_M_left) {
            rightRotate(parent_pt);
            pt = parent_pt;
            parent_pt = pt->_M_parent;
          }

          /* Case : 3
          pt is right child of its parent
          Left-rotation required
              head
              root
                \
                 1(B)
                  \
                   2(R)
                    \
                     3(R)
          */
          leftRotate(grand_parent_pt);
          std::swap(parent_pt->_M_color, grand_parent_pt->_M_color);
          pt = parent_pt;
        }
      }
    }

    _M_root()->_M_color = _S_black;
  }

  // delete

  // find node that do not have a left child
  // in the subtree of the given node
  // ???????????????????????????????????????????????????
  _Link_type successor(_Link_type x) {
    _Link_type temp = x;

    while (temp->_M_left != NULL) temp = temp->_M_left;

    return temp;
  }

  // find node that replaces a deleted node in BST
  _Link_type BSTreplace(_Link_type x) {
    // when node have 2 children
    // ?????????2??????????????????RLLLLL
    if (x->_M_left != NULL and x->_M_right != NULL)
      return successor(x->_M_right);

    // when leaf
    if (x->_M_left == NULL and x->_M_right == NULL) return NULL;

    // when single child
    // ?????????1???????????????????????????
    if (x->_M_left != NULL)
      return x->_M_left;
    else
      return x->_M_right;
  }

  // deletes the given node
  void deleteNode(_Link_type v) {
    _Link_type u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack =
        ((u == NULL or u->_M_color == _S_black) and (v->_M_color == _S_black));
    _Link_type parent = v->_M_parent;

    if (u == NULL) {  // v??????
      // u is NULL therefore v is leaf
      if (v == _S_root()) {
        // v is root, making root null
        _M_root() = _M_header;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          /*
               B
              /
            v:B
          */
          fixDoubleBlack(v);
        } else {
          // v is red
          /*
                B
               / \
            v:R  (R)
          */
          if (v->sibling() != NULL)
            // sibling is not null, make it red"
            v->sibling()->_M_color = _S_red;
        }

        // delete v from the tree
        if (v->isOnLeft()) {
          parent->_M_left = NULL;
        } else {
          parent->_M_right = NULL;
        }
      }
      _M_put_node(v);
      return;
    }

    if (v->_M_left == NULL or v->_M_right == NULL) {
      // v has 1 child
      if (v == _S_root()) {
        // v is root, assign the value of u to v, and delete u
        /*
              v
             /
            u

             u
            / \
           NU NU
        */
        _M_root() = u;
        v->swapNode(u);
        u->_M_left = u->_M_right = NULL;
        _M_put_node(v);
      } else {
        // Detach v from tree and move u up
        /*
                 B
                /
             v:R
              /
          u:(B)
        */
        if (v->isOnLeft()) {
          parent->_M_left = u;
        } else {
          parent->_M_right = u;
        }
        _M_put_node(v);
        u->_M_parent = parent;
        if (uvBlack) {
          // u and v both black, fix double black at u
          fixDoubleBlack(u);
        } else {
          // u or v red, color u black
          u->_M_color = _S_black;
        }
      }
      return;
    }

    // v has 2 children, swap values with successor and recurse
    /*
     before del(B10)
             B10:v
            /   \
          R7      R22
         / \      /  \
       B6  B8   B13:u B26
       /
      R2

      after
             B13
            /   \
          R7     B22
         / \        \
       B6  B8        R26
       /
      R2
      */

    if (v == _S_root()) _M_root() = u;
    v->swapNode(u);
    deleteNode(v);
  }

  void fixDoubleBlack(_Link_type x) {
    if (x == _S_root())
      // Reached root
      return;

    _Link_type sibling = x->sibling();
    _Link_type parent = x->_M_parent;
    if (sibling == NULL) {
      // No sibiling, double black pushed up
      fixDoubleBlack(parent);
    } else {
      if (sibling->_M_color == _S_red) {
        // Sibling red
        /*
        before
              B
             / \
          x:B   R

        after
             (R)
             / \
          x:B   (B)
        */
        parent->_M_color = _S_red;
        sibling->_M_color = _S_black;
        if (sibling->isOnLeft()) {
          // left case
          rightRotate(parent);
        } else {
          // right case
          /*
               (B)
               /
             (R)
             /
           x:B
          */
          leftRotate(parent);  // ?????????????????????
        }
        fixDoubleBlack(x);
      } else {
        // Sibling black
        if (sibling->hasRedChild()) {
          // ???????????????????????????????????????
          // v???????????????????????????????????????????????????????????????????????????
          // at least 1 red children
          if (sibling->_M_left != NULL and
              sibling->_M_left->_M_color == _S_red) {  // ?????????
            if (sibling->isOnLeft()) {
              // left left
              sibling->_M_left->_M_color = sibling->_M_color;
              sibling->_M_color = parent->_M_color;
              rightRotate(parent);
            } else {
              // right left
              sibling->_M_left->_M_color = parent->_M_color;
              rightRotate(sibling);
              leftRotate(parent);
            }
          } else {  // ?????????
            if (sibling->isOnLeft()) {
              // left right
              /*
              before
                  R
                 / \
              x:B   B
               /   /
              R   R
              x???del????????????x????????????B0, ???????????????B1?????????????????????

              changeColor
                  R
                 / \
              x:B  (R)
                   /
                 (B)

              leftRotate
                    (R)
                    /  \
                   R    B
                 /
               x:B
              changeColor
                     (R)
                     /  \
            parent:(B)    B
                  /
                x:B
              // x??????????????????????????????B1???????????????
              */
              sibling->_M_right->_M_color = parent->_M_color;
              leftRotate(sibling);
              rightRotate(parent);
            } else {
              // right right
              sibling->_M_right->_M_color = sibling->_M_color;
              sibling->_M_color = parent->_M_color;
              leftRotate(parent);
            }
          }
          parent->_M_color = _S_black;
        } else {
          // 2 black children
          /*
                R
              /  \
            x:B   B
                 / \
                B   B
            x??????????????????x??????B1???????????????B2?????????????????????

              (B)
              /  \
            x:B  (R)
                 / \
                B   B
          */
          sibling->_M_color = _S_red;
          if (parent->_M_color ==
              _S_black)  // parent?????????????????????1???????????????????????????????????????parent?????????
            fixDoubleBlack(parent);
          else
            parent->_M_color = _S_black;
        }
      }
    }
  }

 public:
  ft::pair<iterator, bool> insert(const value_type& x) {
    ft::pair<iterator, bool> ret;
    // key???????????????????????????
    iterator it = lower_bound(_S_key(x));
    if (it != end() && !_M_key_compare(_S_key(x), _S_key(it))) {
      ret.first = it;
      ret.second = false;
      return ret;
    }
    // node??????
    _Link_type pt = _M_create_node(x);
    _Link_type old = pt;
    // insert
    _M_root() = BSTInsert(_S_root(), pt);

    // rebalance?????? pt???????????????
    fixRedRed(pt);

    // root?????????header???
    _M_root()->_M_parent = _M_header;

    // header?????????
    _M_header->_M_left = _S_mostleft();
    _M_header->_M_right = _S_mostright();

    ret.first = (iterator)old;
    ret.second = true;
    return ret;
  }

  // utility function that deletes the node with given value
  size_type erase(const key_type& key) {
    if (_S_root() == NULL)
      // Tree is empty
      return 0;

    iterator v = lower_bound(key);  // {1,3,5} key=4 v=5

    if (v == end() || _M_key_compare(key, _S_key(v))) return 0;

    deleteNode(v.get_link());

    // header?????????
    if (size()) {
      _M_root()->_M_parent = _M_header;
      _M_header->_M_left = _S_mostleft();
      _M_header->_M_right = _S_mostright();
    } else {
      _M_root() = NULL;
      _M_header->_M_left = _M_header;
      _M_header->_M_right = _M_header;
    }

    return 1;
  }

  void swap(_Rb_tree& __t) {
    // ??????????????? size==0 ?????????????????? or reset()??????
    if (_M_root() == 0) {
      if (__t._M_root() != 0) _M_move_data(__t);
    } else if (__t._M_root() == 0)
      __t._M_move_data(*this);
    else {  // ?????????????????????????????????
      std::swap(_M_root(), __t._M_root());
      std::swap(_M_header->_M_left, __t._M_header->_M_left);
      std::swap(_M_header->_M_right, __t._M_header->_M_right);

      _M_root()->_M_parent = _M_end();
      __t._M_root()->_M_parent = __t._M_end();
      std::swap(_M_node_count, __t._M_node_count);
    }
    // No need to swap header's color as it does not change.
    std::swap(_M_key_compare, __t._M_key_compare);
    std::swap(_M_node_alloc, __t._M_node_alloc);
  }

  // helper ////
 protected:
  _Link_type _M_get_node() {
    ++_M_node_count;
    return _M_node_alloc.allocate(1);
  }
  void _M_put_node(_Link_type p) {
    --_M_node_count;
    _Alloc value_alloc;

    value_alloc.destroy(p->_M_value_type);
    value_alloc.deallocate(p->_M_value_type, 1);
    _M_node_alloc.destroy(p);
    _M_node_alloc.deallocate(p, 1);
  }
  void _M_construct_node(_Link_type node, const value_type& x) {
    try {
      node->_M_color = _S_red;
      node->_M_left = NULL;
      node->_M_right = NULL;
      node->_M_parent = NULL;
      _Alloc value_alloc;
      typename _Alloc::pointer p = value_alloc.allocate(1);
      value_alloc.construct(p, x);
      node->_M_value_type = p;
    } catch (...) {
      _M_put_node(node);
      throw;  // throw_exception_again;
    }
  }

  _Link_type _M_create_node(const value_type& x) {
    _Link_type tmp = _M_get_node();
    _M_construct_node(tmp, x);
    return tmp;
  }

  // lower_bound
  /*
           DUMMY(R): 0x7ffe5ab13d08
             +       |     right: 7
             |       +     left: 1
     [ROOT] 2(B): 0x1892500
              right: 4
              left: 1
             /       \
   1(B): 0x18924d0     4(R): 0x1892560
     right: 0            right: 6
     left: 0             left: 3
                         /      \
             3(B): 0x1892530     6(B): 0x18925c0
              right: 0             right: 7
              left: 0              left: 5
                                  /       \
                        5(R): 0x1892590    7(R): 0x18925f0
                          right: 0            right: 0
                          left: 0             left: 0

  x????????????y???1??????????????????
  x????????????nill??????????????????return(y)
  */

  iterator _M_lower_bound(_Link_type x, _Link_type y, const _Key& k) {
    while (x != 0)
      if (!_M_key_compare(_S_key(x), k))
        y = x, x = x->_M_left;
      else
        x = x->_M_right;
    return iterator(y);
  }

  const_iterator _M_lower_bound(_Const_Link_type x, _Const_Link_type y,
                                const _Key& k) const {
    while (x != 0)
      if (!_M_key_compare(_S_key(x), k))
        y = x, x = x->_M_left;
      else
        x = x->_M_right;
    return const_iterator(y);
  }

  iterator _M_upper_bound(_Link_type x, _Link_type y, const _Key& k) {
    while (x != 0)
      if (_M_key_compare(k, _S_key(x)))
        y = x, x = x->_M_left;
      else
        x = x->_M_right;
    return iterator(y);
  }

  const_iterator _M_upper_bound(_Const_Link_type x, _Const_Link_type y,
                                const _Key& k) const {
    while (x != 0)
      if (_M_key_compare(k, _S_key(x)))
        y = x, x = x->_M_left;
      else
        x = x->_M_right;
    return const_iterator(y);
  }
  // all_erase(root)
  /*
         3:root
       /   \
      1     5
     / \   / \
    0   2 4   7
             / \
            6   8
                 \
                  9

    9->8->...->0 ??????????????????
  */
  void _M_erase(_Link_type x) {
    // Erase without rebalancing.
    while (x != 0) {
      _M_erase(x->_M_right);
      _Link_type y = x->_M_left;
      _M_put_node(x);
      x = y;
    }
  }

  // val????????????????????????????????????????????????????????????????????????????????????????????????
  _Link_type _M_clone_node(_Const_Link_type x) {
    _Link_type tmp = _M_create_node(*x->_M_value_type);
    tmp->_M_color = x->_M_color;
    tmp->_M_left = 0;
    tmp->_M_right = 0;
    return tmp;
  }

  /*
        head
         |
         3:root
       /   \
      1     5
     / \   / \
    0   2 4   7
             / \
            6   8
                 \
                  9
  1(x:3 p:header)
  2(x:5 p:3)
  3(x:7 p:5)
  4(x:8 p:7)
  5(x:9 p:8)
  6(x:2 p:1) // 3->left?????????
  */
  _Link_type _M_copy(_Const_Link_type x, _Link_type p) {  // {origin, parent}
    _Link_type top = _M_clone_node(x);
    top->_M_parent = p;

    try {
      if (x->_M_right) top->_M_right = _M_copy(x->_M_right, top);
      p = top;
      x = x->_M_left;  // ???????????????????????????

      while (x != 0) {
        _Link_type y = _M_clone_node(x);
        p->_M_left = y;
        y->_M_parent = p;
        if (x->_M_right) y->_M_right = _M_copy(x->_M_right, y);
        p = y;
        x = x->_M_left;
      }
    } catch (...) {
      _M_erase(top);
      throw;  // throw_exception_again;
    }
    return top;
  }

 public:
  iterator find(const _Key& __k) {
    iterator __j = lower_bound(__k);
    if (__j == end() || _M_key_compare(__k, _S_key(__j)))
      return end();
    else
      return __j;
  }

  const_iterator find(const _Key& __k) const {
    const_iterator __j = lower_bound(__k);
    if (__j == end() || _M_key_compare(__k, _S_key(__j)))
      return end();
    else
      return __j;
  }

  iterator lower_bound(const key_type& k) {
    return _M_lower_bound(_S_root(), _M_end(), k);  // root , header
  }

  const_iterator lower_bound(const key_type& k) const {
    return _M_lower_bound(_S_root(), _M_end(), k);
  }

  iterator upper_bound(const key_type& k) {
    return _M_upper_bound(_S_root(), _M_end(), k);
  }

  const_iterator upper_bound(const key_type& k) const {
    return _M_upper_bound(_S_root(), _M_end(), k);
  }

  ft::pair<iterator, iterator> equal_range(const _Key& __k) {
    _Link_type __x = _S_root();
    _Link_type __y = _M_end();
    while (__x != 0) {
      if (_M_key_compare(_S_key(__x), __k))
        __x = __x->_M_right;
      else if (_M_key_compare(__k, _S_key(__x)))
        __y = __x, __x = __x->_M_left;
      else {  // __x ??? key???????????? __y???__x->_M_parent
        _Link_type __xu(__x);
        _Link_type __yu(__y);
        __y = __x,
        __x = __x->_M_left;  // __y???key???????????? __x???key??????????????????NULL
        __xu = __xu->_M_right;  // __xu???key??????????????????NULL
        /*
        __x : key->left
        __y : key?????????
        __xu : key->right
        __yu : key?????????

        _M_lower_bound(__x, __y, __k) :
        __x==NULL??????__y
        __x?????????????????????????????? == key??????

        _M_upper_bound(__xu, __yu, __k) :
        __xu==NULL??????__yu???
        __xu?????????????????????????????? == key??????

        ????????????
        p.first = M.lower_bound(key);
        p.second = M.upper_bound(key);
                ???????????????????????????
        */
        return ft::pair<iterator, iterator>(_M_lower_bound(__x, __y, __k),
                                            _M_upper_bound(__xu, __yu, __k));
      }
    }
    // ??????????????????
    return ft::pair<iterator, iterator>(iterator(__y), iterator(__y));
  }

  ft::pair<const_iterator, const_iterator> equal_range(
      const key_type& __k) const {
    _Const_Link_type __x = _S_root();
    _Const_Link_type __y = _M_end();
    while (__x != 0) {
      if (_M_key_compare(_S_key(__x), __k))
        __x = __x->_M_right;
      else if (_M_key_compare(__k, _S_key(__x)))
        __y = __x, __x = __x->_M_left;
      else {  // __x ??? key???????????? __y???__x->_M_parent
        _Const_Link_type __xu(__x);
        _Const_Link_type __yu(__y);
        __y = __x,
        __x = __x->_M_left;  // __y???key???????????? __x???key??????????????????NULL
        __xu = __xu->_M_right;  // __xu???key??????????????????NULL
        /*
        p.first = M.lower_bound(key);
        p.second = M.upper_bound(key);
                ???????????????????????????
        */
        return ft::pair<const_iterator, const_iterator>(
            _M_lower_bound(__x, __y, __k), _M_upper_bound(__xu, __yu, __k));
      }
    }
    // ??????????????????
    return ft::pair<const_iterator, const_iterator>(const_iterator(__y),
                                                    const_iterator(__y));
  }

  //// debug

 public:
  void link_debug(_Link_type x) {
    _Link_type right = x->_M_right;
    _Link_type parent = x->_M_parent;
    _Link_type left = x->_M_left;

    std::cout << std::endl;
    std::cout << "par:";
    if (parent)
      std::cout << _S_key(parent) << std::endl;
    else
      std::cout << "NULL" << std::endl;

    std::cout << "left:";
    if (left)
      std::cout << _S_key(left) << std::endl;
    else
      std::cout << "NULL" << std::endl;

    std::cout << "right:";
    if (right)
      std::cout << _S_key(right) << std::endl;
    else
      std::cout << "NULL" << std::endl;
  }

  void debug() {
    // ?????????
    std::cout << "size:" << size() << std::endl;

    _Link_type root = _M_header->_M_parent;
    _Link_type Hlef = _M_header->_M_left;
    _Link_type Hrig = _M_header->_M_right;

    for (iterator it = begin(); it != end(); ++it) {
      // M[key]:val LLRR
      std::cout << "M[" << _S_key(it) << "]:" << it->second;
      // link_debug(it.get_link());
      _Link_type root = _S_root();
      std::string path;
      while (root != NULL) {
        if (_M_key_compare(_S_key(root), _S_key(it))) {
          path += 'r';
          root = root->_M_right;
        } else if (_M_key_compare(_S_key(it), _S_key(root))) {
          path += 'l';
          root = root->_M_left;
        } else
          break;
      }
      if (it.get_color() == _S_red)
        std::cout << " R ";
      else if (it.get_color() == _S_black)
        std::cout << " B ";

      std::cout << path << std::endl;
    }
  }

  void debug2() {
    // ?????????
    std::cout << std::endl;
    for (iterator it = begin(); it != end(); ++it) {
      // M[key]:val LLRR
      std::cout << "M[" << _S_key(it) << "]:";
      //      link_debug(it.get_link());
      _Link_type root = _S_root();
      std::string path;
      while (root != NULL) {
        if (_M_key_compare(_S_key(root), _S_key(it))) {
          path += 'r';
          root = root->_M_right;
        } else if (_M_key_compare(_S_key(it), _S_key(root))) {
          path += 'l';
          root = root->_M_left;
        } else
          break;
      }
      if (it.get_color() == _S_red)
        std::cout << "R ";
      else if (it.get_color() == _S_black)
        std::cout << "B ";

      std::cout << path << std::endl;
    }
  }
};

//// Non-member functions

template <typename _Key, typename _Val, typename Compare,
          typename _Alloc>
inline bool operator==(
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __x,
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __y) {
  return __x.size() == __y.size() &&
         ft::equal(__x.begin(), __x.end(), __y.begin());
}

template <typename _Key, typename _Val, typename Compare,
          typename _Alloc>

inline bool operator<(
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __x,
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __y) {
  return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(),
                                     __y.end());
}

template <typename _Key, typename _Val, typename Compare,
          typename _Alloc>

inline bool operator!=(
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __x,
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __y) {
  return !(__x == __y);
}

template <typename _Key, typename _Val, typename Compare,
          typename _Alloc>

inline bool operator>(
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __x,
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __y) {
  return __y < __x;
}

template <typename _Key, typename _Val, typename Compare,
          typename _Alloc>

inline bool operator<=(
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __x,
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __y) {
  return !(__y < __x);
}

template <typename _Key, typename _Val, typename Compare,
          typename _Alloc>

inline bool operator>=(
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __x,
    const ft::_Rb_tree<_Key, _Val, Compare, _Alloc>& __y) {
  return !(__x < __y);
}
}  // namespace ft

namespace ft {
template <typename _Key, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<_Key> >
class set {
 public:
  typedef _Key key_type;
  typedef _Key value_type;
  typedef _Compare key_compare;
  typedef _Compare value_compare;
  typedef _Alloc allocator_type;

 private:
  typedef _Rb_tree<key_type, value_type, key_compare,
                   allocator_type>
      _Rep_type;

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

  set() : _M_t() {}
  explicit set(const _Compare& comp, const allocator_type& a = allocator_type())
      : _M_t(comp, a) {}

  /*
  insert(begin,end)??????????????????
  */
  template <typename InputIt>
  set(InputIt first, InputIt last, const _Compare& comp = _Compare(),
      const allocator_type& a = allocator_type(),
      typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* =
          NULL)
      : _M_t(comp, a) {
    insert(first, last);
  }

  set(const set& x) : _M_t(x._M_t) {}
  virtual ~set() {}
  set& operator=(const set& x) {
    if (this == &x) return *this;
    _M_t = x._M_t;
    return *this;
  }
  allocator_type get_allocator() const { return _M_t.get_allocator(); }

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
    //    return std::numeric_limits<size_type>::max() / sizeof(value_type);
    return _M_t.max_size();
  }

  //// Modifiers

  void clear() { _M_t.clear(); }  // header????????????

  ft::pair<iterator, bool> insert(const value_type& x) {
    return _M_t.insert(x);
  }

  /*
  position???1?????????????????????????????????????????????????????????????????????????????????
  BSTinsert??????????????????root?????????????????????????????????????????????
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

  void erase(iterator pos) { erase(*pos); }

  size_type erase(const key_type& key) { return _M_t.erase(key); }

  void erase(iterator first, iterator last) {
    if (first == begin() && last == end())
      clear();
    else
      while (first != last)
        erase(first++);  // ???????????????iterator??????????????????????????????????????????
  }

  void swap(set& x) { _M_t.swap(x._M_t); }

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
  template <typename _K1, typename _C1, typename _A1>
  friend bool operator==(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);

  template <typename _K1, typename _C1, typename _A1>
  friend bool operator<(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);
  //// debug

 public:
  void debug() { _M_t.debug(); }
  void debug2() { _M_t.debug2(); }
};

//// Non-member functions
template <typename _Key, typename Compare, typename _Alloc>
inline bool operator==(const ft::set<_Key, Compare, _Alloc>& x,
                       const ft::set<_Key, Compare, _Alloc>& y) {
  return x._M_t == y._M_t;
}

template <typename _Key, typename Compare, typename _Alloc>
inline bool operator<(const ft::set<_Key, Compare, _Alloc>& x,
                      const ft::set<_Key, Compare, _Alloc>& y) {
  return x._M_t < y._M_t;
}

/// Based on operator==
template <typename _Key, typename Compare, typename _Alloc>
inline bool operator!=(const ft::set<_Key, Compare, _Alloc>& x,
                       const ft::set<_Key, Compare, _Alloc>& y) {
  return !(x == y);
}

/// Based on operator<
template <typename _Key, typename Compare, typename _Alloc>
inline bool operator>(const ft::set<_Key, Compare, _Alloc>& x,
                      const ft::set<_Key, Compare, _Alloc>& y) {
  return y < x;
}

/// Based on operator<
template <typename _Key, typename Compare, typename _Alloc>
inline bool operator<=(const ft::set<_Key, Compare, _Alloc>& x,
                       const ft::set<_Key, Compare, _Alloc>& y) {
  return !(y < x);
}

/// Based on operator<
template <typename _Key, typename Compare, typename _Alloc>
inline bool operator>=(const ft::set<_Key, Compare, _Alloc>& x,
                       const ft::set<_Key, Compare, _Alloc>& y) {
  return !(x < y);
}

}  // namespace ft

/// See std::set::swap().
namespace std {
template <typename _Key, typename Compare, typename _Alloc>
void swap(ft::set<_Key, Compare, _Alloc>& x,
          ft::set<_Key, Compare, _Alloc>& y) {
  x.swap(y);
}

}  // namespace std

using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define all(c) begin(c), end(c)
#define PI acos(-1)
#define oo 2e18
constexpr const ll MOD = 998244353;
template <typename T1, typename T2>
bool chmax(T1& a, T2 b) {
  if (a < b) {
    a = b;
    return true;
  } else
    return false;
}
template <typename T1, typename T2>
bool chmin(T1& a, T2 b) {
  if (a > b) {
    a = b;
    return true;
  } else
    return false;
}
ld dist(ld x1, ld x2, ld y1, ld y2) {
  return (sqrtl((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
// https://atcoder.jp/contests/abc228/editorial/2932
// M^(K^N)%MOD????????????????????? K^N%(MOD-1)
ll modpow(ll a, ll n, ll mod) {
  a %= mod;
  if (a == 0) return 0;
  if (n == 0) return 1;
  if (n % 2 == 1)
    return (a * modpow(a, n - 1, mod)) % mod;
  else {
    ll t = modpow(a, n / 2, mod) % mod;
    return (t * t) % mod;
  }
}
ll modinv(ll n, ll mod) { return modpow(n, mod - 2, mod); }
// ?????????mod??????????????????https://atcoder.jp/contests/abc186/tasks/abc186_e
ll modinv2(ll a, ll m) {  // ret = inv(a) mod m
  ll b = m, u = 1, v = 0;
  while (b) {
    ll t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= m;
  if (u < 0) u += m;
  return u;
}
ll dx[] = {0, 1, 0, -1};
ll dy[] = {-1, 0, 1, 0};
bool is_pop(ll hash, ll d) { return (hash >> d) & 1; }
// priority_queue<ll, vector<ll>, greater<ll>> Q;

//    size_t = 18446744073709551615 (1.8*10^19)
// LLONG_MAX = 9223372036854775807 (9.2*10^18)
//   INT_MAX = 2147483647 (2.1*10^9)

int main() {
  ft::set<string> sets;

  ll N;
  cin >> N;
  rep(i, N) {
    string S;
    cin >> S;
    if (sets.count(S)) continue;
    sets.insert(S);
    cout << i + 1 << endl;
  }
}