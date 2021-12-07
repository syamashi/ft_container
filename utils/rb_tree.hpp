#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>

#include "../containers/stack.hpp"
#include "alloc_traits.hpp"
#include "iterator.hpp"

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
  if (_S_right(__x) == __x) return __x;
  if (_S_right(__x) != 0) {
    __x = _S_right(__x);
    while (_S_left(__x) != 0) __x = _S_left(__x);
  } else {
    _Rb_tree_node<_Val>* __y = __x->_M_parent;
    while (__x == __y->_M_right) {
      __x = __y;
      __y = __y->_M_parent;
    }
    if (_S_right(__x) != __y) {
      /*
      _S_right(__x) == __y
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
  if (_S_right(__x) == __x) return __x;
  // __x == dummy == M.end()
  if (__x->_M_color == _S_red && __x->_M_parent->_M_parent == __x)
    __x = _S_right(__x);
  else if (_S_left(__x) != 0) {
    _Rb_tree_node<_Val>* __y = _S_left(__x);
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

 protected:
  _Node_allocator& _M_get_Node_allocator() { return _Node_allocator(); }
  const _Node_allocator& _M_get_Node_allocator() const {
    return _Node_allocator();
  }

  // member value ////
 private:
  _Link_type _M_header;
  size_type _M_node_count;
  key_compare _M_key_compare;
  _Node_allocator _M_node_alloc;

 public:
  key_type _S_key(_Link_type __x) { return __x->_M_value_type.first; }
  key_type _S_key(value_type __x) { return __x.first; }
  _Link_type _S_right(_Link_type __x) { return __x->_M_right; }
  _Link_type _S_left(_Link_type __x) { return __x->_M_left; }
  _Link_type _S_parent(_Link_type __x) { return __x->_M_parent; }
  _Link_type _S_root() { return _S_parent(_M_header); }
  _Link_type& _M_root() { return _M_header->_M_parent; }

 public:
  typedef _Rb_tree_iterator<value_type> iterator;
  typedef _Rb_tree_const_iterator<value_type> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin() {
    return iterator(_S_left(_M_header));
  }  // _M_begin()は_M_parentなの。
  const_iterator begin() const { return const_iterator(_S_left(_M_header)); }
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

  // insertのhelper4関数

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


  4.5を入れるとしたら？
  root=2
  4.5>2

  root=4
  4.5>4

  root=6
  4.5<6

  root=5
  4.5<5

  root=NULL

  (root=5) // かわるのはここだけ。
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
    if (_S_key(pt) < _S_key(root)) {
      root->_M_left = BSTInsert(root->_M_left, pt);
      root->_M_left->_M_parent = root;
    } else if (_S_key(pt) > _S_key(root)) {
      root->_M_right = BSTInsert(root->_M_right, pt);
      root->_M_right->_M_parent = root;
    }

    /* return the (unchanged) node pointer */
    return root;
  }

  /*
  before                                        after
  　　　　　　root                                    root
              |                                       |
             50(B) pt: grand_parent                  70(B) pt_right
            /   \                                   /   \
    uncle 20(B)  70(R) parent                  pt 50(R)  88(R)
                /  \                             /   \
            60(B)  88(R)                     20(B)  60(B)

  祖父母の右を親の左に、
  親を祖父母に、
  祖父母を兄弟に回転し、
  色を塗りなおす。
  親が黒になるので、上は気にしないでよくなる。
  */
  void rotateLeft(_Link_type root, _Link_type pt) {
    // 70
    _Link_type pt_right = pt->_M_right;

    // 50の右が、70の左(60)に
    pt->_M_right = pt_right->_M_left;

    // もし60があるなら、60の親が50
    if (pt->_M_right != NULL) pt->_M_right->_M_parent = pt;

    // 70の親をroot(仮)に
    pt_right->_M_parent = pt->_M_parent;

    // 70の親がいないならroot
    if (pt->_M_parent == NULL)
      root = pt_right;
    // 70が左の子ならrootの左に
    else if (pt == pt->_M_parent->_M_left)
      pt->_M_parent->_M_left = pt_right;
    // 70が右の子ならrootの右に
    else
      pt->_M_parent->_M_right = pt_right;

    // 70の左を50に
    pt_right->_M_left = pt;
    // 50の親を70に
    pt->_M_parent = pt_right;
  }

  /*
  before                                        after
  　　　　　　root                                    root
              |                                       |
             50(B) pt: grand_parent                  20(B) pt_left
            /   \                                   /  \
  Parent 20(R)   70(B) uncle                     16(R)  50(R) pt
          /  \                                         /   \
       16(R)  24(B)                                  24(B)  70(B)

  祖父母の左を親の右に、
  親を祖父母に、
  祖父母を兄弟に回転し、
  色を塗りなおす。
  親が黒になるので、上は気にしないでよくなる。
  */
  void rotateRight(_Link_type root, _Link_type pt) {
    _Link_type pt_left = pt->_M_left; // parent

    // 祖父母の左を、親の右に
    pt->_M_left = pt_left->_M_right;
    if (pt->_M_left != NULL) pt->_M_left->_M_parent = pt;

    // 親を祖父母に
    pt_left->_M_parent = pt->_M_parent;

    // 親の親からみて、子供を結ぶ。親の親がいないなら、自分がroot
    if (pt->_M_parent == NULL)
      root = pt_left;
    else if (pt == pt->_M_parent->_M_left)
      pt->_M_parent->_M_left = pt_left;
    else
      pt->_M_parent->_M_right = pt_left;

    // 親の右が祖父母に
    pt_left->_M_right = pt;
    // 祖父母の親が親に。
    pt->_M_parent = pt_left;
  }

  void fixViolation(_Link_type root, _Link_type pt) {
    _Link_type parent_pt = NULL;
    _Link_type grand_parent_pt = NULL;

    while ((pt != root) && (pt->_M_color != _S_black) &&
           (pt->_M_parent->_M_color == _S_red))  // 根っこじゃない、かつ赤赤が続いてる
    {
      parent_pt = pt->_M_parent;
      grand_parent_pt = pt->_M_parent->_M_parent;

      /*
         Case : A
              Parent of pt is left child of Grand-parent of pt.
              ptの親はptの祖父母の左の子になります
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

        叔父も赤なら、色を変えるだけ
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
          いったんptを左につけかえる
                   B grand_parent
                  / \
          Parent R   B uncle
                  \
                   R
          */
          if (pt == parent_pt->_M_right) {
            rotateLeft(root, parent_pt);
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

          ---------- before -------------------------------- after ---------------
          　　　　　　root                                    root
                      |                                       |
                     50(B) pt: grand_parent                  20(B) pt_left
                    /   \                                   /  \
          Parent 20(R)   70(B) uncle                     16(R)  50(R) pt
                  /                                               \
               16(R)                                               70(B)
          親を祖父母に、
          祖父母を兄弟に回転し、
          色を塗りなおす。 swap(20(B) 50(R))
          親が黒になるので、上は気にしないでよくなる。
          */
          rotateRight(root, grand_parent_pt);
          // swap
          _Rb_tree_color tmpc = parent_pt->_M_color;
          parent_pt->_M_color = grand_parent_pt->_M_color;
          grand_parent_pt->_M_color = tmpc;
          pt = parent_pt;
        }
      }

      /* Case : B
      Parent of pt is right child
      of Grand-parent of pt */
      else {
        _Link_type uncle_pt = grand_parent_pt->_M_left;

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
          Right-rotation required */
          if (pt == parent_pt->_M_left) {
            rotateRight(root, parent_pt);
            pt = parent_pt;
            parent_pt = pt->_M_parent;
          }

          /* Case : 3
          pt is right child of its parent
          Left-rotation required */
          rotateLeft(root, grand_parent_pt);
          // swap
          _Rb_tree_color tmpc = parent_pt->_M_color;
          parent_pt->_M_color = grand_parent_pt->_M_color;
          grand_parent_pt->_M_color = tmpc;
          pt = parent_pt;
        }
      }
    }

    root->_M_color = _S_black;
  }

 public:
  std::pair<iterator, bool> insert(const value_type& __x) {
    // keyが重複してないこと
    iterator it = lower_bound(_S_key(__x));
    if (it != end() && !_M_key_compare(_S_key(__x), _S_key(it._M_node)))
      return {it, false};
    // node作る
    _Link_type pt = _M_create_node(__x);
    // insertする
    _M_root() = BSTInsert(_S_root(), pt);
    // rebalanceする
    fixViolation(_S_root(), pt);

    return {iterator(pt), true};
  }

  // helper ////
 protected:
  _Link_type _M_begin() { return _M_header->_M_parent; }
  _Link_type _M_end() { return _M_header; }

  _Link_type _M_get_node() { return _M_node_alloc.allocate(1); }
  void _M_put_node(_Link_type __p) { _M_node_alloc.deallocate(__p, 1); }
  void _M_construct_node(_Link_type __node, const value_type& __x) {
    try {
      _M_node_alloc.construct(&__node->_M_value_type, __x);
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

  __xが探索。__yが1手前の状態。
  __xの探索がnillに至ったら、return(__y)
  */

  iterator _M_lower_bound(_Link_type __x, _Link_type __y, const _Key& __k) {
    while (__x != 0)
      if (!_M_key_compare(_S_key(__x), __k))
        __y = __x, __x = _S_left(__x);
      else
        __x = _S_right(__x);
    return iterator(__y);
  }

  const_iterator _M_lower_bound(_Const_Link_type __x, _Const_Link_type __y,
                                  const _Key& __k) const{
    while (__x != 0)
      if (!_M_key_compare(_S_key(__x), __k))
        __y = __x, __x = _S_left(__x);
      else
        __x = _S_right(__x);
    return const_iterator(__y);
  }

  iterator _M_upper_bound(_Link_type __x, _Link_type __y, const _Key& __k) {
    while (__x != 0)
      if (_M_key_compare(__k, _S_key(__x)))
        __y = __x, __x = _S_left(__x);
      else
        __x = _S_right(__x);
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