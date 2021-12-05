#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>

#include "../containers/stack.hpp"
#include "alloc_traits.hpp"
#include "iterator.hpp"

/*
constructで作るのは、
色、右、左、自分、val
をもったstruct。

map<int, int> M
で、最初に作るのはなに？
M[1] = 2
insertとかで追加するのはなに？
追加するときにどんなデータをどんなふうに管理するの？

vector<int> V
の場合
iteratorに渡してたのは、valueのポインタだけだった。
けど、mapではいろいろ渡さなきゃいけない。
だからstruct?。

begin()で返すようで、
leftと
rightを常にメンバでもっておく

iteratorは、value_typeのポインタを返すことになる。
*/

namespace ft {

enum _Rb_tree_color { _S_red = false, _S_black = true };

template <typename _Val>
struct _Rb_tree_node {
  typedef _Rb_tree_node<_Val>* _Link_type;

  _Rb_tree_color _M_color;
  _Link_type _M_parent;
  _Link_type _M_left;
  _Link_type _M_right;
  _Val _M_value_type;
};

template <typename _Val>
static _Rb_tree_node<_Val>* local_Rb_tree_increment(
    _Rb_tree_node<_Val>* __x) throw() {
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
  1. 右がある(4->5)
    右に進んだ後、突き当りまで左
  2. 右がない(5->6)
    親から見て、自分が右なら戻り続ける。
  3. 最大だった場合(7->dummy)
    Dummyまで戻る。dummyの右、4の上で終了
  */

  // size==0
  if (__x->_M_right == __x) return __x;
  if (__x->_M_right != 0) {
    __x = __x->_M_right;
    while (__x->_M_left != 0) __x = __x->_M_left;
  } else {
    _Rb_tree_node<_Val>* __y = __x->_M_parent;
    while (__x == __y->_M_right) {
      __x = __y;
      __y = __y->_M_parent;
    }
    if (__x->_M_right != __y) {
      /*
      __x->_M_right == __y
       <=> M.size()==1 && __x==dummy, return(dummy)

        dummy(R): 0x7ffde6b05688
       | + right: ROOT
       + | left: ROOT
        ROOT(B): 0x9414d0
          right: 0
          left: 0
      */
      __x = __y;
    }
  }
  return __x;
}

template <typename _Val>
_Rb_tree_node<_Val>* _Rb_tree_increment(_Rb_tree_node<_Val>* __x) throw() {
  return local_Rb_tree_increment(__x);
}

template <typename _Val>
const _Rb_tree_node<_Val>* _Rb_tree_increment(
    const _Rb_tree_node<_Val>* __x) throw() {
  return local_Rb_tree_increment(const_cast<_Rb_tree_node<_Val>*>(__x));
}

template <typename _Val>
static _Rb_tree_node<_Val>* local_Rb_tree_decrement(
    _Rb_tree_node<_Val>* __x) throw() {
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
  1. 左がある(4->3)
    左に進んだ後、突き当りまで右
  2. 左がない(5->4)
    親から見て、自分が左なら戻り続ける。
  3. 最後だった場合(dummy->7)
    Dummy->right
  */

  // size==0
  if (__x->_M_right == __x) return __x;
  // __x == dummy == M.end()
  if (__x->_M_color == _S_red && __x->_M_parent->_M_parent == __x)
    __x = __x->_M_right;
  else if (__x->_M_left != 0) {
    _Rb_tree_node<_Val>* __y = __x->_M_left;
    while (__y->_M_right != 0) {
      __y = __y->_M_right;
    }
    __x = __y;
  } else {
    _Rb_tree_node<_Val>* __y = __x->_M_parent;
    while (__x == __y->_M_left) {
      __x = __y;
      __y = __y->_M_parent;
    }
    __x = __y;
  }
  return __x;
}

template <typename _Val>
_Rb_tree_node<_Val>* _Rb_tree_decrement(_Rb_tree_node<_Val>* __x) throw() {
  return local_Rb_tree_decrement(__x);
}

template <typename _Val>
const _Rb_tree_node<_Val>* _Rb_tree_decrement(
    const _Rb_tree_node<_Val>* __x) throw() {
  return local_Rb_tree_decrement(const_cast<_Rb_tree_node<_Val>*>(__x));
}

template <typename _Tp>
struct _Rb_tree_iterator {
  typedef typename _Rb_tree_node<_Tp>::_Link_type _Link_type;
  typedef _Tp& reference;
  typedef _Tp* pointer;
  typedef _Rb_tree_iterator<_Tp> _Self;

  _Rb_tree_iterator() : _M_node() {}
  explicit _Rb_tree_iterator(_Link_type __x) : _M_node(__x) {}

  reference operator*() const { return _M_node->_M_value_type; }
  pointer operator->() const { return &_M_node->_M_value_type; }

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
  explicit _Rb_tree_const_iterator(_Link_type __x) : _M_node(__x) {}
  _Rb_tree_const_iterator(const iterator& __it) : _M_node(__it._M_node) {}
  iterator _M_const_cast() const {
    return iterator(const_cast<typename iterator::_Link_type>(_M_node));
  }
  reference operator*() const { return _M_node->_M_value_type; }
  pointer operator->() const { return &_M_node->_M_value_type; }

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

  // member value ////
  _Link_type _M_node;
};

template <typename _Key, typename _Val, typename Compare,
          typename _Alloc = std::allocator<_Val>>
class _Rb_tree {
  // _Allocの引数<_Val> を <Node<_Val>> に 置き換える
  typedef typename _Alloc::template rebind<_Rb_tree_node<_Val>>::other
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

  _Node_allocator& _M_get_Node_allocator() { return _Node_allocator(); }
  const _Node_allocator& _M_get_Node_allocator() const {
    return _Node_allocator();
  }

  key_type _S_key(_Link_type __x) { return __x->_M_value_type.first; }
  _Link_type _S_right(_Link_type __x) { return __x->_M_right; }
  _Link_type _S_left(_Link_type __x) { return __x->_M_left; }

 public:
  typedef _Rb_tree_iterator<value_type> iterator;
  typedef _Rb_tree_const_iterator<value_type> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin() { return iterator(_M_header->_M_parent); }
  const_iterator begin() const { return const_iterator(_M_header->_M_parent); }
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
  bool empty() const { return _M_node_count == 0; }
  size_type size() const { return _M_node_count; }
  /*
    size_type max_size() const {
      return _Alloc::max_size(_M_get_Node_allocator());
    }
  */

 public:
  _Rb_tree() : _Rb_tree(key_compare(), _Node_allocator()) {}
  _Rb_tree(const key_compare& key_comp, const _Node_allocator& node_alloc)
      : _M_node_count(0), _M_key_compare(key_comp), _M_node_alloc(node_alloc) {
    _M_header = _M_create_node(value_type());
    _M_header->_M_color = _S_red;
    _M_header->_M_parent = 0;
    _M_header->_M_left = _M_header;
    _M_header->_M_right = _M_header;
  }
  _Rb_tree(_Rb_tree const& src) {
    _M_header = src->_M_header;
    _M_key_compare = src->_M_key_compare;
    _M_node_alloc = src->_M_node_alloc;
    _M_node_count = src->_M_node_count;
  }
  ~_Rb_tree() {}
  _Rb_tree& operator=(const _Rb_tree& src) {
    _M_header = src->_M_header;
    _M_key_compare = src->_M_key_compare;
    _M_node_alloc = src->_M_node_alloc;
    _M_node_count = src->_M_node_count;
  }

 public:
  iterator _M_insert_(_Link_type __x, _Link_type __y, const value_type& __v) {
    bool __insert_left =
        (__x != 0 || __y == _M_end() || _M_key_compare(__v.first, _S_key(__y)));

    _Link_type __z = _M_create_node(__v);

    //    _Rb_tree_insert_and_rebalance(__insert_left, __z, __y,
    //    this->_M_impl._M_header);
    ++_M_node_count;
    return iterator(__z);
  }

  //  std::pair<iterator, bool> _M_insert_unique(const value_type& __x);
  std::pair<_Link_type, _Link_type> _M_get_insert_unique_pos(
      const key_type& __k) {
    typedef std::pair<_Link_type, _Link_type> _Res;
    _Link_type __x = _M_begin();
    _Link_type __y = _M_end();
    bool __comp = true;
    while (__x != 0) {
      __y = __x;
      __comp = _M_key_compare(__k, _S_key(__x));
      __x = __comp ? __x->_M_left : __x->_M_right;
    }
    iterator __j = iterator(__y);
    if (__comp) {
      if (__j == begin())
        return _Res(__x, __y);
      else
        --__j;
    }
    if (_M_key_compare(_S_key(__j._M_node), __k))
      return _Res(__x, __y);
    return _Res(__j._M_node, 0);
  }
  std::pair<_Link_type, _Link_type> _M_get_insert_hint_unique_pos(
      const_iterator __position, const key_type& __k) {
    iterator __pos = __position._M_const_cast();
    typedef std::pair<_Link_type, _Link_type> _Res;

    // _M_end()
    if (__pos._M_node == _M_end()) {
      if (size() > 0 &&
          _M_key_compare(_S_key(_M_header->_M_right), __k))
        return _Res(0, _M_header->_M_right);
      else
        return _M_get_insert_unique_pos(__k);
    } else if (_M_key_compare(__k, _S_key(__pos._M_node))) {
      // First, try before...
      iterator __before = __pos;
      if (__pos._M_node == _M_header->_M_left)  // begin()
        return _Res(_M_header->_M_left, _M_header->_M_left);
      else if (_M_key_compare(_S_key((--__before)._M_node), __k)) {
        if (_S_right(__before._M_node) == 0)
          return _Res(0, __before._M_node);
        else
          return _Res(__pos._M_node, __pos._M_node);
      } else
        return _M_get_insert_unique_pos(__k);
    } else if (_M_key_compare(_S_key(__pos._M_node), __k)) {
      // ... then try after.
      iterator __after = __pos;
      if (__pos._M_node == _M_header->_M_right)
        return _Res(0, _M_header->_M_right);
      else if (_M_key_compare(__k,
                              (_S_key((++__after)._M_node)))) {
        if (__pos._M_node->_M_right == 0)
          return _Res(0, __pos._M_node);
        else
          return _Res(__after._M_node, __after._M_node);
      } else
        return _M_get_insert_unique_pos(__k);
    } else
      // Equivalent keys.
      return _Res(__pos._M_node, 0);
  }

  std::pair<_Link_type, _Link_type> _M_get_insert_hint_equal_pos(
      const_iterator __pos, const key_type& __k);

  iterator _M_insert_unique_(iterator __position, const value_type& __x) {
    std::pair<_Link_type, _Link_type> __res =
        _M_get_insert_hint_unique_pos(__position, __x.first);
    if (__res.second) return _M_insert_(__res.first, __res.second, __x);
    return iterator(__res.first);
  }

  /*
    template <typename _InputIterator>
    void insert(_InputIterator __first, _InputIterator __last) {
      _M_insert_unique(__first, __last);
    }
  */
  // member value ////

  _Link_type _M_header;
  size_type _M_node_count;
  key_compare _M_key_compare;
  _Node_allocator _M_node_alloc;

  // helper ////
 protected:
  _Link_type _M_begin() { return _M_header->_M_parent; }
  _Link_type _M_end() { return _M_header; }

  _Link_type _M_get_node() { return _M_node_alloc.allocate(1); }
  void _M_put_node(_Link_type __p) { _M_node_alloc.deallocate(__p, 1); }
  void _M_construct_node(_Link_type __node, const value_type& __x) {
    try {
      _M_node_alloc.construct(&__node->_M_value_type, __x);

      std::cout << "[_N_get_node] val:{" << __x.first << " " << __x.second
                << "}" << std::endl;
      std::cout << __node->_M_value_type.first << " " << __node->_M_value_type.second << std::endl;
    } catch (...) {
      _M_put_node(__node);
      //      throw; // __throw_exception_again;
    }
  }


  _Link_type _M_create_node(const value_type& __x) {
    _Link_type __tmp = _M_get_node();
    _M_construct_node(__tmp, __x);
    return __tmp;
  }

  void _M_destroy_node(_Link_type __p) { _M_node_alloc.destroy(__p); }

  void _M_drop_node(_Link_type __p) {
    _M_destroy_node(__p);
    _M_put_node(__p);
  }

  /*
  ** Lookup
  */

  iterator _M_lower_bound(_Link_type __x, _Link_type __y, const _Key& __k) {
    while (__x != 0)
      if (!_M_key_compare(__x->_M_value_type.first, __k))  // less()(key1,
                                                           // key2)?
        __y = __x, __x = __x->_M_left;
      else
        __x = __x->_M_right;
    return iterator(__y);
  }

  //  const_iterator _M_lower_bound(_Const_Link_type __x, _Const_Link_type __y,
  //                                const _Key& __k) const;

  iterator _M_upper_bound(_Link_type __x, _Link_type __y, const _Key& __k) {
    while (__x != 0)
      if (_M_key_compare(__k, _S_key(__x)))
        __y = __x, __x = __x->_M_left;
      else
        __x = __x->_M_right;
    return iterator(__y);
  }

  //  const_iterator _M_upper_bound(_Const_Link_type __x, _Const_Link_type __y,
  //                                const _Key& __k) const;

 public:
  iterator lower_bound(const key_type& __k) {
    return _M_lower_bound(_M_begin(), _M_end(), __k);
  }

  //  const_iterator lower_bound(const key_type& __k) const {
  //    return _M_lower_bound(_M_begin(), _M_end(), __k);
  //  }

  iterator upper_bound(const key_type& __k) {
    return _M_upper_bound(_M_begin(), _M_end(), __k);
  }

  //  const_iterator upper_bound(const key_type& __k) const {
  //    return _M_upper_bound(_M_begin(), _M_end(), __k);
  //  }
};
}  // namespace ft
#endif