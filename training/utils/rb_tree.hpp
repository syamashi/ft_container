#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>

#include "../containers/stack.hpp"
#include "alloc_traits.hpp"
#include "iterator.hpp"

namespace ft {

enum _Rb_tree_color { _S_red = false, _S_black = true };

struct _Rb_tree_node_base {
  typedef _Rb_tree_node_base* _Base_ptr;
  typedef const _Rb_tree_node_base* _Const_Base_ptr;

  _Rb_tree_color _M_color;
  _Base_ptr _M_parent;
  _Base_ptr _M_left;
  _Base_ptr _M_right;

  // 静的メンバ関数。thisは渡されない。メンバ変数、メンバ関数にもアクセスできない。
  // 呼び方は_Rb_tree_node_base::_S_minimum(__x)

  static _Base_ptr _S_minimum(_Base_ptr __x) {
    while (__x->_M_left != 0) __x = __x->_M_left;
    return __x;
  }

  static _Const_Base_ptr _S_minimum(_Const_Base_ptr __x) {
    while (__x->_M_left != 0) __x = __x->_M_left;
    return __x;
  }

  static _Base_ptr _S_maximum(_Base_ptr __x) {
    while (__x->_M_right != 0) __x = __x->_M_right;
    return __x;
  }

  static _Const_Base_ptr _S_maximum(_Const_Base_ptr __x) {
    while (__x->_M_right != 0) __x = __x->_M_right;
    return __x;
  }

  /*
  ** debug [ Black or Red : right or left ]
  ** exaple R:rrr
  */

  void node_base_debug() {
    ft::stack<char> st;

    _Base_ptr now = this;
    int turn = 0;
    while (1) {
      //      std::cout << "now:" << now << std::endl;
      //      std::cout << "color:" << now->_M_color << std::endl;
      //      std::cout << "par:" << now->_M_parent << std::endl;
      //      std::cout << "right:" << now->_M_right << std::endl;
      //      std::cout << "left:" << now->_M_left << std::endl;
      //      std::cout << std::endl;

      // size==0
      if (!now->_M_parent) break;
      // now == dummy
      if (now->_M_parent->_M_right == _S_maximum(now) &&
          now->_M_parent->_M_left == _S_minimum(now))
        break;

      if (now->_M_parent->_M_right == now)
        st.push('r');
      else if (now->_M_parent->_M_left == now)
        st.push('l');
      now = now->_M_parent;
    }

    if (_M_color == _S_red) std::cout << "R:";
    if (_M_color == _S_black) std::cout << "B:";
    while (!st.empty()) {
      std::cout << st.top();
      st.pop();
    }
    std::cout << std::endl;
  }
};

// Helper type offering value initialization guarantee on the compare functor.
template <typename _Key_compare>
struct _Rb_tree_key_compare {
  _Key_compare _M_key_compare;

  _Rb_tree_key_compare() : _M_key_compare() {}
  _Rb_tree_key_compare(const _Key_compare& __comp) : _M_key_compare(__comp) {}
};

// Helper type to manage default initialization of node count and header.

// left = begin();
// this = end();
struct _Rb_tree_header {
  _Rb_tree_node_base _M_header;
  size_t _M_node_count;  // Keeps track of size of tree.

  _Rb_tree_header() {
    _M_header._M_color = _S_red;
    _M_reset();
  }

  void _M_move_data(_Rb_tree_header& __from) {
    _M_header._M_color = __from._M_header._M_color;
    _M_header._M_parent = __from._M_header._M_parent;
    _M_header._M_left = __from._M_header._M_left;
    _M_header._M_right = __from._M_header._M_right;
    _M_header._M_parent->_M_parent = &_M_header;  // 親の親が自分
    _M_node_count = __from._M_node_count;
    __from._M_reset();
  }

  void _M_reset() {
    _M_header._M_parent = 0;
    _M_header._M_left = &_M_header;
    _M_header._M_right = &_M_header;
    _M_node_count = 0;
  }
};

template <typename _Val>  // pair<key, val>
struct _Rb_tree_node : public _Rb_tree_node_base {
  typedef _Rb_tree_node<_Val>* _Link_type;

  _Val _M_value_field;

  void _node_debug() {
    std::cout << "first:" << _M_value_field.first
              << " second:" << _M_value_field.second << std::endl;
  }

  _Val* _M_valptr() {
    return &_M_value_field;
  }  // == std::__addressof(_M_value_field)
  const _Val* _M_valptr() const { return &_M_value_field; }
};

_Rb_tree_node_base* _Rb_tree_increment(_Rb_tree_node_base* __x) throw();

const _Rb_tree_node_base* _Rb_tree_increment(
    const _Rb_tree_node_base* __x) throw();

_Rb_tree_node_base* _Rb_tree_decrement(_Rb_tree_node_base* __x) throw();

const _Rb_tree_node_base* _Rb_tree_decrement(
    const _Rb_tree_node_base* __x) throw();

/*
iteratorに必要なもの
  _Base_ptr _M_node; だけ持ってる。

*/

template <typename _Tp>  // _Tp = pair
struct _Rb_tree_iterator {
  typedef _Tp value_type;
  typedef _Tp& reference;
  typedef _Tp* pointer;

  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef _Rb_tree_iterator<_Tp> _Self;
  typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
  typedef _Rb_tree_node<_Tp>* _Link_type;

  _Rb_tree_iterator() : _M_node() {}
  explicit _Rb_tree_iterator(_Base_ptr __x) : _M_node(__x) {}

  // _Base_ptr _M_node ;
  // _Base_ptr <= _Link_type ( _M_valptr() がとれるようになるだけ )
  reference operator*() const {
    return *static_cast<_Link_type>(_M_node)->_M_valptr();
  }
  pointer operator->() const {
    return static_cast<_Link_type>(_M_node)->_M_valptr();
  }

  _Self& operator++() {
    _M_node = _Rb_tree_increment(_M_node);
    return *this;
  }

  _Self operator++(int) {
    _Self __tmp = *this;
    _M_node = _Rb_tree_increment(_M_node);
    return __tmp;
  }

  _Self& operator--() {
    _M_node = _Rb_tree_decrement(_M_node);
    return *this;
  }

  _Self operator--(int) {
    _Self __tmp = *this;
    _M_node = _Rb_tree_decrement(_M_node);
    return __tmp;
  }

  bool operator==(const _Self& __x) const { return _M_node == __x._M_node; }
  bool operator!=(const _Self& __x) const { return _M_node != __x._M_node; }

  _Base_ptr _M_node;

  /*
  ** debug
  */

  void iterator_debug() { _M_node->node_base_debug(); }
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
  typedef _Rb_tree_node_base::_Const_Base_ptr _Base_ptr;
  typedef const _Rb_tree_node<_Tp>* _Link_type;

  _Rb_tree_const_iterator() : _M_node() {}

  explicit _Rb_tree_const_iterator(_Base_ptr __x) : _M_node(__x) {}

  _Rb_tree_const_iterator(const iterator& __it) : _M_node(__it._M_node) {}

  iterator _M_const_cast() const {
    return iterator(const_cast<typename iterator::_Base_ptr>(_M_node));
  }

  reference operator*() const {
    return *static_cast<_Link_type>(_M_node)->_M_valptr();
  }

  pointer operator->() const {
    return static_cast<_Link_type>(_M_node)->_M_valptr();
  }

  _Self& operator++() {
    _M_node = _Rb_tree_increment(_M_node);
    return *this;
  }

  _Self operator++(int) {
    _Self __tmp = *this;
    _M_node = _Rb_tree_increment(_M_node);
    return __tmp;
  }

  _Self& operator--() {
    _M_node = _Rb_tree_decrement(_M_node);
    return *this;
  }

  _Self operator--(int) {
    _Self __tmp = *this;
    _M_node = _Rb_tree_decrement(_M_node);
    return __tmp;
  }

  bool operator==(const _Self& __x) const { return _M_node == __x._M_node; }

  bool operator!=(const _Self& __x) const { return _M_node != __x._M_node; }

  _Base_ptr _M_node;
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

/*
** _Rb_tree
** _Val = pair{key, val}
*/

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc = std::allocator<_Val>>
class _Rb_tree {
  // _Allocの引数<_Val> を <Node<_Val>> に 置き換える
  typedef typename _Alloc::template rebind<_Rb_tree_node<_Val>>::other
      _Node_allocator;

  typedef ft::__alloc_traits<_Node_allocator> _Alloc_traits;

 protected:
  typedef _Rb_tree_node_base* _Base_ptr;
  typedef const _Rb_tree_node_base* _Const_Base_ptr;
  typedef _Rb_tree_node<_Val>* _Link_type;
  typedef const _Rb_tree_node<_Val>* _Const_Link_type;

 private:
  // Functor recycling a pool of nodes and using allocation once the pool is
  // empty.
  // __t._M_root() == _M_impl._M_header._M_parent
  // __t._M_rightmost() == _M_impl._M_header._M_right
  //
  struct _Reuse_or_alloc_node {
    _Reuse_or_alloc_node(_Rb_tree& __t)
        : _M_root(__t._M_root()), _M_nodes(__t._M_rightmost()), _M_t(__t) {
      if (_M_root) {
        _M_root->_M_parent = 0;
        if (_M_nodes->_M_left) _M_nodes = _M_nodes->_M_left;
      } else
        _M_nodes = 0;
    }

    ~_Reuse_or_alloc_node() { _M_t._M_erase(static_cast<_Link_type>(_M_root)); }

    template <typename _Arg>
    _Link_type operator()(const _Arg& __arg) {
      _Link_type __node = static_cast<_Link_type>(_M_extract());
      if (__node) {
        _M_t._M_destroy_node(__node);
        _M_t._M_construct_node(__node, __arg);
        return __node;
      }

      return _M_t._M_create_node(__arg);
    }

   private:
    _Base_ptr _M_extract() {
      if (!_M_nodes) return _M_nodes;

      _Base_ptr __node = _M_nodes;
      _M_nodes = _M_nodes->_M_parent;
      if (_M_nodes) {
        if (_M_nodes->_M_right == __node) {
          _M_nodes->_M_right = 0;

          if (_M_nodes->_M_left) {
            _M_nodes = _M_nodes->_M_left;

            while (_M_nodes->_M_right) _M_nodes = _M_nodes->_M_right;

            if (_M_nodes->_M_left) _M_nodes = _M_nodes->_M_left;
          }
        } else  // __node is on the left.
          _M_nodes->_M_left = 0;
      } else
        _M_root = 0;

      return __node;
    }

    /*
    ** _Reuse_or_alloc_node: member variable
    */

    _Base_ptr _M_root;
    _Base_ptr _M_nodes;
    _Rb_tree& _M_t;
  };

  // Functor similar to the previous one but without any pool of nodes to
  // recycle.
  struct _Alloc_node {
    _Alloc_node(_Rb_tree& __t) : _M_t(__t) {}

    template <typename _Arg>
    _Link_type operator()(const _Arg& __arg) const {
      return _M_t._M_create_node(__arg);
    }

   private:
    _Rb_tree& _M_t;
  };

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

  _Node_allocator& _M_get_Node_allocator() { return this->_M_impl; }

  const _Node_allocator& _M_get_Node_allocator() const { return this->_M_impl; }

  allocator_type get_allocator() const {
    return allocator_type(_M_get_Node_allocator());
  }

 protected:
  _Link_type _M_get_node() {
    return _Alloc_traits::allocate(_M_get_Node_allocator(), 1);
  }

  void _M_put_node(_Link_type __p) {
    _Alloc_traits::deallocate(_M_get_Node_allocator(), __p, 1);
  }

  void _M_construct_node(_Link_type __node, const value_type& __x) { // valueだけのallocateを試みている。省略
    __try {
      get_allocator().construct(__node->_M_valptr(), __x);
    }
    __catch(...) {
      _M_put_node(__node);
      __throw_exception_again;
    }
  }

  _Link_type _M_create_node(const value_type& __x) {
    _Link_type __tmp = _M_get_node();
    _M_construct_node(__tmp, __x);
    return __tmp;
  }

  void _M_destroy_node(_Link_type __p) {
    get_allocator().destroy(__p->_M_valptr());
  }

  void _M_drop_node(_Link_type __p) {
    _M_destroy_node(__p);
    _M_put_node(__p);
  }

  template <typename _NodeGen>
  _Link_type _M_clone_node(_Const_Link_type __x, _NodeGen& __node_gen) {
    _Link_type __tmp = __node_gen(*__x->_M_valptr());
    __tmp->_M_color = __x->_M_color;
    __tmp->_M_left = 0;
    __tmp->_M_right = 0;
    return __tmp;
  }

 protected:
  // Unused _Is_pod_comparator is kept as it is part of mangled name.
  template <typename _Key_compare,
            bool /* _Is_pod_comparator */ = __is_pod(_Key_compare)>
  struct _Rb_tree_impl : public _Node_allocator,
                         public _Rb_tree_key_compare<_Key_compare>,
                         public _Rb_tree_header {
    typedef _Rb_tree_key_compare<_Key_compare> _Base_key_compare;

    _Rb_tree_impl() : _Node_allocator() {}

    _Rb_tree_impl(const _Rb_tree_impl& __x)
        : _Node_allocator(_Alloc_traits::_S_select_on_copy(__x)),
          _Base_key_compare(__x._M_key_compare) {}

    _Rb_tree_impl(const _Key_compare& __comp, const _Node_allocator& __a)
        : _Node_allocator(__a), _Base_key_compare(__comp) {}
  };

  _Rb_tree_impl<Compare> _M_impl;

 protected:
  _Base_ptr& _M_root() { return this->_M_impl._M_header._M_parent; }

  _Const_Base_ptr _M_root() const { return this->_M_impl._M_header._M_parent; }

  _Base_ptr& _M_leftmost() { return this->_M_impl._M_header._M_left; }

  _Const_Base_ptr _M_leftmost() const {
    return this->_M_impl._M_header._M_left;
  }

  _Base_ptr& _M_rightmost() { return this->_M_impl._M_header._M_right; }

  _Const_Base_ptr _M_rightmost() const {
    return this->_M_impl._M_header._M_right;
  }

  _Link_type _M_begin() {
    return static_cast<_Link_type>(this->_M_impl._M_header._M_parent);
  }

  _Const_Link_type _M_begin() const {
    return static_cast<_Const_Link_type>(this->_M_impl._M_header._M_parent);
  }

  _Base_ptr _M_end() { return &this->_M_impl._M_header; }

  _Const_Base_ptr _M_end() const { return &this->_M_impl._M_header; }

  static const_reference _S_value(_Const_Link_type __x) {
    return *__x->_M_valptr();
  }

  static const _Key& _S_key(_Const_Link_type __x) {
    return _KeyOfValue()(_S_value(__x));
  }

  static _Link_type _S_left(_Base_ptr __x) {
    return static_cast<_Link_type>(__x->_M_left);
  }

  static _Const_Link_type _S_left(_Const_Base_ptr __x) {
    return static_cast<_Const_Link_type>(__x->_M_left);
  }

  static _Link_type _S_right(_Base_ptr __x) {
    return static_cast<_Link_type>(__x->_M_right);
  }

  static _Const_Link_type _S_right(_Const_Base_ptr __x) {
    return static_cast<_Const_Link_type>(__x->_M_right);
  }

  static const_reference _S_value(_Const_Base_ptr __x) {
    return *static_cast<_Const_Link_type>(__x)->_M_valptr();
  }

  static const _Key& _S_key(_Const_Base_ptr __x) {
    return _KeyOfValue()(_S_value(__x));
  }

  static _Base_ptr _S_minimum(_Base_ptr __x) {
    return _Rb_tree_node_base::_S_minimum(__x);
  }

  static _Const_Base_ptr _S_minimum(_Const_Base_ptr __x) {
    return _Rb_tree_node_base::_S_minimum(__x);
  }

  static _Base_ptr _S_maximum(_Base_ptr __x) {
    return _Rb_tree_node_base::_S_maximum(__x);
  }

  static _Const_Base_ptr _S_maximum(_Const_Base_ptr __x) {
    return _Rb_tree_node_base::_S_maximum(__x);
  }

 public:
  typedef _Rb_tree_iterator<value_type> iterator;
  typedef _Rb_tree_const_iterator<value_type> const_iterator;

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  std::pair<_Base_ptr, _Base_ptr> _M_get_insert_unique_pos(const key_type& __k);

  std::pair<_Base_ptr, _Base_ptr> _M_get_insert_equal_pos(const key_type& __k);

  std::pair<_Base_ptr, _Base_ptr> _M_get_insert_hint_unique_pos(
      const_iterator __pos, const key_type& __k);

  std::pair<_Base_ptr, _Base_ptr> _M_get_insert_hint_equal_pos(
      const_iterator __pos, const key_type& __k);

 private:
  template <typename _NodeGen>
  iterator _M_insert_(_Base_ptr __x, _Base_ptr __y, const value_type& __v,
                      _NodeGen&);

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 233. Insertion hints in associative containers.
  iterator _M_insert_lower(_Base_ptr __y, const value_type& __v);

  iterator _M_insert_equal_lower(const value_type& __x);

  template <typename _NodeGen>
  _Link_type _M_copy(_Const_Link_type __x, _Base_ptr __p, _NodeGen&);

  template <typename _NodeGen>
  _Link_type _M_copy(const _Rb_tree& __x, _NodeGen& __gen) {
    _Link_type __root = _M_copy(__x._M_begin(), _M_end(), __gen);
    _M_leftmost() = _S_minimum(__root);
    _M_rightmost() = _S_maximum(__root);
    _M_impl._M_node_count = __x._M_impl._M_node_count;
    return __root;
  }

  _Link_type _M_copy(const _Rb_tree& __x) {
    _Alloc_node __an(*this);
    return _M_copy(__x, __an);
  }

  void _M_erase(_Link_type __x);

  iterator _M_lower_bound(_Link_type __x, _Base_ptr __y, const _Key& __k);

  const_iterator _M_lower_bound(_Const_Link_type __x, _Const_Base_ptr __y,
                                const _Key& __k) const;

  iterator _M_upper_bound(_Link_type __x, _Base_ptr __y, const _Key& __k);

  const_iterator _M_upper_bound(_Const_Link_type __x, _Const_Base_ptr __y,
                                const _Key& __k) const;

 public:
  // allocation/deallocation

  _Rb_tree() {}

  _Rb_tree(const Compare& __comp, const allocator_type& __a = allocator_type())
      : _M_impl(__comp, _Node_allocator(__a)) {}

  _Rb_tree(const _Rb_tree& __x) : _M_impl(__x._M_impl) {
    if (__x._M_root() != 0) _M_root() = _M_copy(__x);
  }

  ~_Rb_tree() { _M_erase(_M_begin()); }

  _Rb_tree& operator=(const _Rb_tree& __x);

  // Accessors.
  Compare key_comp() const { return _M_impl._M_key_compare; }

  iterator begin() { return iterator(this->_M_impl._M_header._M_left); }

  const_iterator begin() const {
    return const_iterator(this->_M_impl._M_header._M_left);
  }

  iterator end() { return iterator(&this->_M_impl._M_header); }

  const_iterator end() const {
    return const_iterator(&this->_M_impl._M_header);
  }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  bool empty() const { return _M_impl._M_node_count == 0; }

  size_type size() const { return _M_impl._M_node_count; }

  size_type max_size() const {
    return _Alloc_traits::max_size(_M_get_Node_allocator());
  }

  void swap(_Rb_tree& __t);

  // Insert/erase.
  std::pair<iterator, bool> _M_insert_unique(const value_type& __x);

  iterator _M_insert_equal(const value_type& __x);

  template <typename _NodeGen>
  iterator _M_insert_unique_(const_iterator __pos, const value_type& __x,
                             _NodeGen&);

  iterator _M_insert_unique_(const_iterator __pos, const value_type& __x) {
    _Alloc_node __an(*this);
    return _M_insert_unique_(__pos, __x, __an);
  }

  template <typename _NodeGen>
  iterator _M_insert_equal_(const_iterator __pos, const value_type& __x,
                            _NodeGen&);
  iterator _M_insert_equal_(const_iterator __pos, const value_type& __x) {
    _Alloc_node __an(*this);
    return _M_insert_equal_(__pos, __x, __an);
  }

  template <typename _InputIterator>
  void _M_insert_unique(_InputIterator __first, _InputIterator __last);

  template <typename _InputIterator>
  void _M_insert_equal(_InputIterator __first, _InputIterator __last);

 private:
  void _M_erase_aux(const_iterator __position);

  void _M_erase_aux(const_iterator __first, const_iterator __last);

 public:
  void erase(iterator __position) {
    __glibcxx_assert(__position != end());
    _M_erase_aux(__position);
  }

  void erase(const_iterator __position) {
    __glibcxx_assert(__position != end());
    _M_erase_aux(__position);
  }
  size_type erase(const key_type& __x);

  void erase(iterator __first, iterator __last) {
    _M_erase_aux(__first, __last);
  }

  void erase(const_iterator __first, const_iterator __last) {
    _M_erase_aux(__first, __last);
  }

  void erase(const key_type* __first, const key_type* __last);

  void clear() {
    _M_erase(_M_begin());
    _M_impl._M_reset();
  }

  // Set operations.
  iterator find(const key_type& __k);

  const_iterator find(const key_type& __k) const;

  size_type count(const key_type& __k) const;

  iterator lower_bound(const key_type& __k) {
    return _M_lower_bound(_M_begin(), _M_end(), __k);
  }

  const_iterator lower_bound(const key_type& __k) const {
    return _M_lower_bound(_M_begin(), _M_end(), __k);
  }

  iterator upper_bound(const key_type& __k) {
    return _M_upper_bound(_M_begin(), _M_end(), __k);
  }

  const_iterator upper_bound(const key_type& __k) const {
    return _M_upper_bound(_M_begin(), _M_end(), __k);
  }

  std::pair<iterator, iterator> equal_range(const key_type& __k);

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& __k) const;

  // Debugging.
  bool __rb_verify() const;

  /*
  ** add tree.cc
  */

  static void local_Rb_tree_rotate_left(_Rb_tree_node_base* const __x,
                                        _Rb_tree_node_base*& __root) {
    _Rb_tree_node_base* const __y = __x->_M_right;
    __x->_M_right = __y->_M_left;
    if (__y->_M_left != 0) __y->_M_left->_M_parent = __x;
    __y->_M_parent = __x->_M_parent;
    if (__x == __root)
      __root = __y;
    else if (__x == __x->_M_parent->_M_left)
      __x->_M_parent->_M_left = __y;
    else
      __x->_M_parent->_M_right = __y;
    __y->_M_left = __x;
    __x->_M_parent = __y;
  }

  static void local_Rb_tree_rotate_right(_Rb_tree_node_base* const __x,
                                         _Rb_tree_node_base*& __root) {
    _Rb_tree_node_base* const __y = __x->_M_left;
    __x->_M_left = __y->_M_right;
    if (__y->_M_right != 0) __y->_M_right->_M_parent = __x;
    __y->_M_parent = __x->_M_parent;
    if (__x == __root)
      __root = __y;
    else if (__x == __x->_M_parent->_M_right)
      __x->_M_parent->_M_right = __y;
    else
      __x->_M_parent->_M_left = __y;
    __y->_M_right = __x;
    __x->_M_parent = __y;
  }

  void _Rb_tree_insert_and_rebalance(const bool __insert_left,
                                     _Rb_tree_node_base* __x,
                                     _Rb_tree_node_base* __p,
                                     _Rb_tree_node_base& __header) throw() {
    _Rb_tree_node_base*& __root = __header._M_parent;
    // Initialize fields in new node to insert.
    __x->_M_parent = __p;
    __x->_M_left = 0;
    __x->_M_right = 0;
    __x->_M_color = _S_red;
    // Insert.
    // Make new node child of parent and maintain root, leftmost and
    // rightmost nodes.
    // N.B. First node is always inserted left.
    if (__insert_left) {
      __p->_M_left = __x;  // also makes leftmost = __x when __p == &__header
      if (__p == &__header) {
        __header._M_parent = __x;
        __header._M_right = __x;
      } else if (__p == __header._M_left)
        __header._M_left = __x;  // maintain leftmost pointing to min node
    } else {
      __p->_M_right = __x;
      if (__p == __header._M_right)
        __header._M_right = __x;  // maintain rightmost pointing to max node
    }
    // Rebalance.
    while (__x != __root && __x->_M_parent->_M_color == _S_red) {
      _Rb_tree_node_base* const __xpp = __x->_M_parent->_M_parent;
      if (__x->_M_parent == __xpp->_M_left) {
        _Rb_tree_node_base* const __y = __xpp->_M_right;
        if (__y && __y->_M_color == _S_red) {
          __x->_M_parent->_M_color = _S_black;
          __y->_M_color = _S_black;
          __xpp->_M_color = _S_red;
          __x = __xpp;
        } else {
          if (__x == __x->_M_parent->_M_right) {
            __x = __x->_M_parent;
            local_Rb_tree_rotate_left(__x, __root);
          }
          __x->_M_parent->_M_color = _S_black;
          __xpp->_M_color = _S_red;
          local_Rb_tree_rotate_right(__xpp, __root);
        }
      } else {
        _Rb_tree_node_base* const __y = __xpp->_M_left;
        if (__y && __y->_M_color == _S_red) {
          __x->_M_parent->_M_color = _S_black;
          __y->_M_color = _S_black;
          __xpp->_M_color = _S_red;
          __x = __xpp;
        } else {
          if (__x == __x->_M_parent->_M_left) {
            __x = __x->_M_parent;
            local_Rb_tree_rotate_right(__x, __root);
          }
          __x->_M_parent->_M_color = _S_black;
          __xpp->_M_color = _S_red;
          local_Rb_tree_rotate_left(__xpp, __root);
        }
      }
    }
    __root->_M_color = _S_black;
  }
  _Rb_tree_node_base* _Rb_tree_rebalance_for_erase(
      _Rb_tree_node_base* const __z, _Rb_tree_node_base& __header) throw() {
    _Rb_tree_node_base*& __root = __header._M_parent;
    _Rb_tree_node_base*& __leftmost = __header._M_left;
    _Rb_tree_node_base*& __rightmost = __header._M_right;
    _Rb_tree_node_base* __y = __z;
    _Rb_tree_node_base* __x = 0;
    _Rb_tree_node_base* __x_parent = 0;
    if (__y->_M_left == 0)        // __z has at most one non-null child. y == z.
      __x = __y->_M_right;        // __x might be null.
    else if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
      __x = __y->_M_left;         // __x is not null.
    else {
      // __z has two non-null children.  Set __y to
      __y = __y->_M_right;  //   __z's successor.  __x might be null.
      while (__y->_M_left != 0) __y = __y->_M_left;
      __x = __y->_M_right;
    }
    if (__y != __z) {
      // relink y in place of z.  y is z's successor
      __z->_M_left->_M_parent = __y;
      __y->_M_left = __z->_M_left;
      if (__y != __z->_M_right) {
        __x_parent = __y->_M_parent;
        if (__x) __x->_M_parent = __y->_M_parent;
        __y->_M_parent->_M_left = __x;  // __y must be a child of _M_left
        __y->_M_right = __z->_M_right;
        __z->_M_right->_M_parent = __y;
      } else
        __x_parent = __y;
      if (__root == __z)
        __root = __y;
      else if (__z->_M_parent->_M_left == __z)
        __z->_M_parent->_M_left = __y;
      else
        __z->_M_parent->_M_right = __y;
      __y->_M_parent = __z->_M_parent;
      std::swap(__y->_M_color, __z->_M_color);
      __y = __z;
      // __y now points to node to be actually deleted
    } else {  // __y == __z
      __x_parent = __y->_M_parent;
      if (__x) __x->_M_parent = __y->_M_parent;
      if (__root == __z)
        __root = __x;
      else if (__z->_M_parent->_M_left == __z)
        __z->_M_parent->_M_left = __x;
      else
        __z->_M_parent->_M_right = __x;
      if (__leftmost == __z) {
        if (__z->_M_right == 0)  // __z->_M_left must be null also
          __leftmost = __z->_M_parent;
        // makes __leftmost == _M_header if __z == __root
        else
          __leftmost = _Rb_tree_node_base::_S_minimum(__x);
      }
      if (__rightmost == __z) {
        if (__z->_M_left == 0)  // __z->_M_right must be null also
          __rightmost = __z->_M_parent;
        // makes __rightmost == _M_header if __z == __root
        else  // __x == __z->_M_left
          __rightmost = _Rb_tree_node_base::_S_maximum(__x);
      }
    }
    if (__y->_M_color != _S_red) {
      while (__x != __root && (__x == 0 || __x->_M_color == _S_black))
        if (__x == __x_parent->_M_left) {
          _Rb_tree_node_base* __w = __x_parent->_M_right;
          if (__w->_M_color == _S_red) {
            __w->_M_color = _S_black;
            __x_parent->_M_color = _S_red;
            local_Rb_tree_rotate_left(__x_parent, __root);
            __w = __x_parent->_M_right;
          }
          if ((__w->_M_left == 0 || __w->_M_left->_M_color == _S_black) &&
              (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black)) {
            __w->_M_color = _S_red;
            __x = __x_parent;
            __x_parent = __x_parent->_M_parent;
          } else {
            if (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black) {
              __w->_M_left->_M_color = _S_black;
              __w->_M_color = _S_red;
              local_Rb_tree_rotate_right(__w, __root);
              __w = __x_parent->_M_right;
            }
            __w->_M_color = __x_parent->_M_color;
            __x_parent->_M_color = _S_black;
            if (__w->_M_right) __w->_M_right->_M_color = _S_black;
            local_Rb_tree_rotate_left(__x_parent, __root);
            break;
          }
        } else {
          // same as above, with _M_right <-> _M_left.
          _Rb_tree_node_base* __w = __x_parent->_M_left;
          if (__w->_M_color == _S_red) {
            __w->_M_color = _S_black;
            __x_parent->_M_color = _S_red;
            local_Rb_tree_rotate_right(__x_parent, __root);
            __w = __x_parent->_M_left;
          }
          if ((__w->_M_right == 0 || __w->_M_right->_M_color == _S_black) &&
              (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)) {
            __w->_M_color = _S_red;
            __x = __x_parent;
            __x_parent = __x_parent->_M_parent;
          } else {
            if (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black) {
              __w->_M_right->_M_color = _S_black;
              __w->_M_color = _S_red;
              local_Rb_tree_rotate_left(__w, __root);
              __w = __x_parent->_M_left;
            }
            __w->_M_color = __x_parent->_M_color;
            __x_parent->_M_color = _S_black;
            if (__w->_M_left) __w->_M_left->_M_color = _S_black;
            local_Rb_tree_rotate_right(__x_parent, __root);
            break;
          }
        }
      if (__x) __x->_M_color = _S_black;
    }
    return __y;
  }
  unsigned int _Rb_tree_black_count(const _Rb_tree_node_base* __node,
                                    const _Rb_tree_node_base* __root) throw() {
    if (__node == 0) return 0;
    unsigned int __sum = 0;
    do {
      if (__node->_M_color == _S_black) ++__sum;
      if (__node == __root) break;
      __node = __node->_M_parent;
    } while (1);
    return __sum;
  }



 public:
  void debug(){

  }
};

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
inline bool operator==(
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __y) {
  return __x.size() == __y.size() &&
         std::equal(__x.begin(), __x.end(), __y.begin());
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
inline bool operator<(
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __y) {
  return std::lexicographical_compare(__x.begin(), __x.end(), __y.begin(),
                                      __y.end());
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
inline bool operator!=(
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __y) {
  return !(__x == __y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
inline bool operator>(
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __y) {
  return __y < __x;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
inline bool operator<=(
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __y) {
  return !(__y < __x);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
inline bool operator>=(
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __y) {
  return !(__x < __y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
inline void swap(_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __x,
                 _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>& __y) {
  __x.swap(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>&
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::operator=(
    const _Rb_tree& __x) {
  if (this != &__x) {
    // Note that _Key may be a constant type.
    _Reuse_or_alloc_node __roan(*this);
    _M_impl._M_reset();
    _M_impl._M_key_compare = __x._M_impl._M_key_compare;
    if (__x._M_root() != 0) _M_root() = _M_copy(__x, __roan);
  }

  return *this;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
template <typename _NodeGen>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare,
                  _Alloc>::iterator  // iterator が戻り値
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_insert_(
    _Base_ptr __x, _Base_ptr __p, const _Val& __v, _NodeGen& __node_gen) {
  bool __insert_left =
      (__x != 0 || __p == _M_end() ||
       _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__p)));

  _Link_type __z = __node_gen(__v);

  _Rb_tree_insert_and_rebalance(__insert_left, __z, __p,
                                this->_M_impl._M_header);
  ++_M_impl._M_node_count;
  return iterator(__z);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_insert_lower(
    _Base_ptr __p, const _Val& __v) {
  bool __insert_left =
      (__p == _M_end() ||
       !_M_impl._M_key_compare(_S_key(__p), _KeyOfValue()(__v)));

  _Link_type __z = _M_create_node(__v);

  _Rb_tree_insert_and_rebalance(__insert_left, __z, __p,
                                this->_M_impl._M_header);
  ++_M_impl._M_node_count;
  return iterator(__z);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_insert_equal_lower(
    const _Val& __v) {
  _Link_type __x = _M_begin();
  _Base_ptr __y = _M_end();
  while (__x != 0) {
    __y = __x;
    __x = !_M_impl._M_key_compare(_S_key(__x), _KeyOfValue()(__v))
              ? _S_left(__x)
              : _S_right(__x);
  }
  return _M_insert_lower(__y, __v);
}

template <typename _Key, typename _Val, typename _KoV, typename Compare,
          typename _Alloc>
template <typename _NodeGen>
typename _Rb_tree<_Key, _Val, _KoV, Compare, _Alloc>::_Link_type
_Rb_tree<_Key, _Val, _KoV, Compare, _Alloc>::_M_copy(_Const_Link_type __x,
                                                     _Base_ptr __p,
                                                     _NodeGen& __node_gen) {
  // Structural copy. __x and __p must be non-null.
  _Link_type __top = _M_clone_node(__x, __node_gen);
  __top->_M_parent = __p;

  __try {
    if (__x->_M_right)
      __top->_M_right = _M_copy(_S_right(__x), __top, __node_gen);
    __p = __top;
    __x = _S_left(__x);

    while (__x != 0) {
      _Link_type __y = _M_clone_node(__x, __node_gen);
      __p->_M_left = __y;
      __y->_M_parent = __p;
      if (__x->_M_right)
        __y->_M_right = _M_copy(_S_right(__x), __y, __node_gen);
      __p = __y;
      __x = _S_left(__x);
    }
  }
  __catch(...) {
    _M_erase(__top);
    __throw_exception_again;
  }
  return __top;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_erase(
    _Link_type __x) {
  // Erase without rebalancing.
  while (__x != 0) {
    _M_erase(_S_right(__x));
    _Link_type __y = _S_left(__x);
    _M_drop_node(__x);
    __x = __y;
  }
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_lower_bound(
    _Link_type __x, _Base_ptr __y, const _Key& __k) {
  while (__x != 0)
    if (!_M_impl._M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);
  return iterator(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_lower_bound(
    _Const_Link_type __x, _Const_Base_ptr __y, const _Key& __k) const {
  while (__x != 0)
    if (!_M_impl._M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);
  return const_iterator(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_upper_bound(
    _Link_type __x, _Base_ptr __y, const _Key& __k) {
  while (__x != 0)
    if (_M_impl._M_key_compare(__k, _S_key(__x)))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);
  return iterator(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_upper_bound(
    _Const_Link_type __x, _Const_Base_ptr __y, const _Key& __k) const {
  while (__x != 0)
    if (_M_impl._M_key_compare(__k, _S_key(__x)))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);
  return const_iterator(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
std::pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator,
          typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator>
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::equal_range(
    const _Key& __k) {
  _Link_type __x = _M_begin();
  _Base_ptr __y = _M_end();
  while (__x != 0) {
    if (_M_impl._M_key_compare(_S_key(__x), __k))
      __x = _S_right(__x);
    else if (_M_impl._M_key_compare(__k, _S_key(__x)))
      __y = __x, __x = _S_left(__x);
    else {
      _Link_type __xu(__x);
      _Base_ptr __yu(__y);
      __y = __x, __x = _S_left(__x);
      __xu = _S_right(__xu);
      return std::pair<iterator, iterator>(_M_lower_bound(__x, __y, __k),
                                           _M_upper_bound(__xu, __yu, __k));
    }
  }
  return std::pair<iterator, iterator>(iterator(__y), iterator(__y));
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
std::pair<
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::const_iterator,
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::const_iterator>
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::equal_range(
    const _Key& __k) const {
  _Const_Link_type __x = _M_begin();
  _Const_Base_ptr __y = _M_end();
  while (__x != 0) {
    if (_M_impl._M_key_compare(_S_key(__x), __k))
      __x = _S_right(__x);
    else if (_M_impl._M_key_compare(__k, _S_key(__x)))
      __y = __x, __x = _S_left(__x);
    else {
      _Const_Link_type __xu(__x);
      _Const_Base_ptr __yu(__y);
      __y = __x, __x = _S_left(__x);
      __xu = _S_right(__xu);
      return std::pair<const_iterator, const_iterator>(
          _M_lower_bound(__x, __y, __k), _M_upper_bound(__xu, __yu, __k));
    }
  }
  return std::pair<const_iterator, const_iterator>(const_iterator(__y),
                                                   const_iterator(__y));
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::swap(_Rb_tree& __t) {
  if (_M_root() == 0) {
    if (__t._M_root() != 0)  // 親がいる
      _M_impl._M_move_data(__t._M_impl);
  } else if (__t._M_root() == 0)
    __t._M_impl._M_move_data(_M_impl);
  else {
    std::swap(_M_root(), __t._M_root());
    std::swap(_M_leftmost(), __t._M_leftmost());
    std::swap(_M_rightmost(), __t._M_rightmost());

    _M_root()->_M_parent = _M_end();
    __t._M_root()->_M_parent = __t._M_end();
    std::swap(this->_M_impl._M_node_count, __t._M_impl._M_node_count);
  }
  // No need to swap header's color as it does not change.
  std::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);

  _Alloc_traits::_S_on_swap(_M_get_Node_allocator(),
                            __t._M_get_Node_allocator());
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
std::pair<
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_Base_ptr,
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_Base_ptr>
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_get_insert_unique_pos(
    const key_type& __k) {
  typedef std::pair<_Base_ptr, _Base_ptr> _Res;
  _Link_type __x = _M_begin();
  _Base_ptr __y = _M_end();
  bool __comp = true;
  while (__x != 0) {
    __y = __x;
    __comp = _M_impl._M_key_compare(__k, _S_key(__x));
    __x = __comp ? _S_left(__x) : _S_right(__x);
  }
  iterator __j = iterator(__y);
  if (__comp) {
    if (__j == begin())
      return _Res(__x, __y);
    else
      --__j;
  }
  if (_M_impl._M_key_compare(_S_key(__j._M_node), __k)) return _Res(__x, __y);
  return _Res(__j._M_node, 0);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
std::pair<
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_Base_ptr,
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_Base_ptr>
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_get_insert_equal_pos(
    const key_type& __k) {
  typedef std::pair<_Base_ptr, _Base_ptr> _Res;
  _Link_type __x = _M_begin();
  _Base_ptr __y = _M_end();
  while (__x != 0) {
    __y = __x;
    __x =
        _M_impl._M_key_compare(__k, _S_key(__x)) ? _S_left(__x) : _S_right(__x);
  }
  return _Res(__x, __y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
std::pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator,
          bool>
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_insert_unique(
    const _Val& __v) {
  typedef std::pair<iterator, bool> _Res;
  std::pair<_Base_ptr, _Base_ptr> __res =
      _M_get_insert_unique_pos(_KeyOfValue()(__v));

  if (__res.second) {
    _Alloc_node __an(*this);
    return _Res(_M_insert_(__res.first, __res.second, __v, __an), true);
  }

  return _Res(iterator(__res.first), false);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_insert_equal(
    const _Val& __v) {
  std::pair<_Base_ptr, _Base_ptr> __res =
      _M_get_insert_equal_pos(_KeyOfValue()(__v));
  _Alloc_node __an(*this);
  return _M_insert_(__res.first, __res.second, __v, __an);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
std::pair<
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_Base_ptr,
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_Base_ptr>
_Rb_tree<_Key, _Val, _KeyOfValue, Compare,
         _Alloc>::_M_get_insert_hint_unique_pos(const_iterator __position,
                                                const key_type& __k) {
  iterator __pos = __position._M_const_cast();
  typedef std::pair<_Base_ptr, _Base_ptr> _Res;

  // end()
  if (__pos._M_node == _M_end()) {
    if (size() > 0 && _M_impl._M_key_compare(_S_key(_M_rightmost()), __k))
      return _Res(0, _M_rightmost());
    else
      return _M_get_insert_unique_pos(__k);
  } else if (_M_impl._M_key_compare(__k, _S_key(__pos._M_node))) {
    // First, try before...
    iterator __before = __pos;
    if (__pos._M_node == _M_leftmost())  // begin()
      return _Res(_M_leftmost(), _M_leftmost());
    else if (_M_impl._M_key_compare(_S_key((--__before)._M_node), __k)) {
      if (_S_right(__before._M_node) == 0)
        return _Res(0, __before._M_node);
      else
        return _Res(__pos._M_node, __pos._M_node);
    } else
      return _M_get_insert_unique_pos(__k);
  } else if (_M_impl._M_key_compare(_S_key(__pos._M_node), __k)) {
    // ... then try after.
    iterator __after = __pos;
    if (__pos._M_node == _M_rightmost())
      return _Res(0, _M_rightmost());
    else if (_M_impl._M_key_compare(__k, _S_key((++__after)._M_node))) {
      if (_S_right(__pos._M_node) == 0)
        return _Res(0, __pos._M_node);
      else
        return _Res(__after._M_node, __after._M_node);
    } else
      return _M_get_insert_unique_pos(__k);
  } else
    // Equivalent keys.
    return _Res(__pos._M_node, 0);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
template <typename _NodeGen>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_insert_unique_(
    const_iterator __position, const _Val& __v, _NodeGen& __node_gen) {
  std::pair<_Base_ptr, _Base_ptr> __res =
      _M_get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));

  if (__res.second)
    return _M_insert_(__res.first, __res.second, __v, __node_gen);
  return iterator(__res.first);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
std::pair<
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_Base_ptr,
    typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_Base_ptr>
_Rb_tree<_Key, _Val, _KeyOfValue, Compare,
         _Alloc>::_M_get_insert_hint_equal_pos(const_iterator __position,
                                               const key_type& __k) {
  iterator __pos = __position._M_const_cast();
  typedef std::pair<_Base_ptr, _Base_ptr> _Res;

  // end()
  if (__pos._M_node == _M_end()) {
    if (size() > 0 && !_M_impl._M_key_compare(__k, _S_key(_M_rightmost())))
      return _Res(0, _M_rightmost());
    else
      return _M_get_insert_equal_pos(__k);
  } else if (!_M_impl._M_key_compare(_S_key(__pos._M_node), __k)) {
    // First, try before...
    iterator __before = __pos;
    if (__pos._M_node == _M_leftmost())  // begin()
      return _Res(_M_leftmost(), _M_leftmost());
    else if (!_M_impl._M_key_compare(__k, _S_key((--__before)._M_node))) {
      if (_S_right(__before._M_node) == 0)
        return _Res(0, __before._M_node);
      else
        return _Res(__pos._M_node, __pos._M_node);
    } else
      return _M_get_insert_equal_pos(__k);
  } else {
    // ... then try after.
    iterator __after = __pos;
    if (__pos._M_node == _M_rightmost())
      return _Res(0, _M_rightmost());
    else if (!_M_impl._M_key_compare(_S_key((++__after)._M_node), __k)) {
      if (_S_right(__pos._M_node) == 0)
        return _Res(0, __pos._M_node);
      else
        return _Res(__after._M_node, __after._M_node);
    } else
      return _Res(0, 0);
  }
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
template <typename _NodeGen>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_insert_equal_(
    const_iterator __position, const _Val& __v, _NodeGen& __node_gen) {
  std::pair<_Base_ptr, _Base_ptr> __res =
      _M_get_insert_hint_equal_pos(__position, _KeyOfValue()(__v));

  if (__res.second)
    return _M_insert_(__res.first, __res.second, __v, __node_gen);

  return _M_insert_equal_lower(__v);
}

template <typename _Key, typename _Val, typename _KoV, typename _Cmp,
          typename _Alloc>
template <class _II>
void _Rb_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::_M_insert_unique(_II __first,
                                                                _II __last) {
  _Alloc_node __an(*this);
  for (; __first != __last; ++__first) _M_insert_unique_(end(), *__first, __an);
}

template <typename _Key, typename _Val, typename _KoV, typename _Cmp,
          typename _Alloc>
template <class _II>
void _Rb_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::_M_insert_equal(_II __first,
                                                               _II __last) {
  _Alloc_node __an(*this);
  for (; __first != __last; ++__first) _M_insert_equal_(end(), *__first, __an);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_erase_aux(
    const_iterator __position) {
  _Link_type __y = static_cast<_Link_type>(_Rb_tree_rebalance_for_erase(
      const_cast<_Base_ptr>(__position._M_node), this->_M_impl._M_header));
  _M_drop_node(__y);
  --_M_impl._M_node_count;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::_M_erase_aux(
    const_iterator __first, const_iterator __last) {
  if (__first == begin() && __last == end())
    clear();
  else
    while (__first != __last) _M_erase_aux(__first++);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::size_type
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::erase(const _Key& __x) {
  std::pair<iterator, iterator> __p = equal_range(__x);
  const size_type __old_size = size();
  _M_erase_aux(__p.first, __p.second);
  return __old_size - size();
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::erase(
    const _Key* __first, const _Key* __last) {
  while (__first != __last) erase(*__first++);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::find(const _Key& __k) {
  iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
  return (__j == end() || _M_impl._M_key_compare(__k, _S_key(__j._M_node)))
             ? end()
             : __j;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::find(
    const _Key& __k) const {
  const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
  return (__j == end() || _M_impl._M_key_compare(__k, _S_key(__j._M_node)))
             ? end()
             : __j;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::size_type
_Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::count(
    const _Key& __k) const {
  std::pair<const_iterator, const_iterator> __p = equal_range(__k);
  const size_type __n = std::distance(__p.first, __p.second);
  return __n;
}

unsigned int _Rb_tree_black_count(const _Rb_tree_node_base* __node,
                                  const _Rb_tree_node_base* __root) throw();

template <typename _Key, typename _Val, typename _KeyOfValue, typename Compare,
          typename _Alloc>
bool _Rb_tree<_Key, _Val, _KeyOfValue, Compare, _Alloc>::__rb_verify() const {
  if (_M_impl._M_node_count == 0 || begin() == end())
    return _M_impl._M_node_count == 0 && begin() == end() &&
           this->_M_impl._M_header._M_left == _M_end() &&
           this->_M_impl._M_header._M_right == _M_end();

  unsigned int __len = _Rb_tree_black_count(_M_leftmost(), _M_root());
  for (const_iterator __it = begin(); __it != end(); ++__it) {
    _Const_Link_type __x = static_cast<_Const_Link_type>(__it._M_node);
    _Const_Link_type __L = _S_left(__x);
    _Const_Link_type __R = _S_right(__x);

    if (__x->_M_color == _S_red)
      if ((__L && __L->_M_color == _S_red) || (__R && __R->_M_color == _S_red))
        return false;

    if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L))) return false;
    if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__x))) return false;

    if (!__L && !__R && _Rb_tree_black_count(__x, _M_root()) != __len)
      return false;
  }

  if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root())) return false;
  if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root())) return false;
  return true;
}

_GLIBCXX_END_NAMESPACE_VERSION
}  // namespace ft

#endif
