#include "rb_tree.hpp"

namespace ft
{
  template <typename _Val>
  static _Rb_tree_node<_Val>*
  local_Rb_tree_increment(_Rb_tree_node<_Val>* __x) throw ()
  {
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
    if (__x->_M_right != 0)
      {
        __x = __x->_M_right;
        while (__x->_M_left != 0)
          __x = __x->_M_left;
      }
    else
      {
        _Rb_tree_node<_Val>* __y = __x->_M_parent;
        while (__x == __y->_M_right)
          {
            __x = __y;
            __y = __y->_M_parent;
          }
        if (__x->_M_right != __y){
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
  _Rb_tree_node<_Val>*
  _Rb_tree_increment(_Rb_tree_node<_Val>* __x) throw ()
  {
    return local_Rb_tree_increment(__x);
  }

  template <typename _Val>
  const _Rb_tree_node<_Val>*
  _Rb_tree_increment(const _Rb_tree_node<_Val>* __x) throw ()
  {
    return local_Rb_tree_increment(const_cast<_Rb_tree_node<_Val>*>(__x));
  }

  template <typename _Val>
  static _Rb_tree_node<_Val>*
  local_Rb_tree_decrement(_Rb_tree_node<_Val>* __x) throw ()
  {
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
      }
    else
      {
        _Rb_tree_node<_Val>* __y = __x->_M_parent;
        while (__x == __y->_M_left)
          {
            __x = __y;
            __y = __y->_M_parent;
          }
        __x = __y;
      }
    return __x;
  }

  template <typename _Val>
  _Rb_tree_node<_Val>*
  _Rb_tree_decrement(_Rb_tree_node<_Val>* __x) throw ()
  {
    return local_Rb_tree_decrement(__x);
  }

  template <typename _Val>
  const _Rb_tree_node<_Val>*
  _Rb_tree_decrement(const _Rb_tree_node<_Val>* __x) throw ()
  {
    return local_Rb_tree_decrement(const_cast<_Rb_tree_node<_Val>*>(__x));
  }
} // namespace
