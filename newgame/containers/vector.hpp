#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <limits>

#include "../utils/algorithm.hpp"
#include "../utils/iterator.hpp"
#include "../utils/random_access_iterator.hpp"
#include "../utils/util.hpp"

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector {
 public:
  // value_typeなどネストされた型名
  typedef T value_type;
  typedef T* pointer;
  typedef const pointer const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  typedef typename ft::random_access_iterator<value_type> iterator;
  typedef typename ft::random_access_iterator<const value_type> const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // コンストラクター
  vector()
      : first(NULL), last(NULL), reserved_last(NULL), alloc(allocator_type()) {}

  vector(const allocator_type& alloc)
      : first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {}

  explicit vector(size_type count, const T& value = T(),
                  const Allocator& alloc = Allocator())
      : first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {
    resize(count, value);
  }

  template <typename InputIterator>
  vector(InputIterator first, InputIterator last,
         const Allocator& alloc = Allocator(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type* = NULL)
      : first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {
    reserve(ft::distance(first, last));
    for (InputIterator i = first; i != last; ++i) {
      push_back(*i);
    }
  }

  // コピー
  vector(const vector& r)
      : first(NULL), last(NULL), reserved_last(NULL), alloc(r.alloc) {
    // コピー元の要素数を保持できるだけのストレージを確保
    reserve(r.size());
    // コピー元の要素をコピー構築
    // destはコピー先
    // [src, last)はコピー元
    pointer dest = first;
    for (const_iterator src = r.begin(), last = r.end(); src != last;
         ++dest, ++src) {
      construct(dest, *src);
    }
    last = first + r.size();
  }

  vector& operator=(const vector& r) {
    // 1. 自分自身への代入なら何もしない
    if (this == &r) return *this;

    // 2. 要素数が同じならば
    if (size() == r.size()) {  // 要素ごとにコピー代入
      std::copy(r.begin(), r.end(), begin());
    }
    // 3. それ以外の場合で
    else
        // 予約数が十分ならば、
        if (capacity() >= r.size()) {
      // 有効な要素はコピー
      std::copy(r.begin(), r.begin() + r.size(), begin());
      // 残りはコピー構築
      last = first + r.size();
      for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end();
           src_iter != src_end; ++src_iter, ++last) {
        construct(last, *src_iter);
      }
    }
    // 4. 予約数が不十分ならば
    else {
      // 要素をすべて破棄
      destroy_until(rbegin());
      // 予約
      reserve(r.size());
      // コピー構築
      for (const_iterator src_iter = r.begin(), src_end = r.end();
           src_iter != src_end; ++src_iter, ++last) {
        construct(last, *src_iter);
      }
    }
    return *this;
  }

  // デストラクター
  ~vector() {
    // 1. 要素を末尾から先頭に向かう順番で破棄
    clear();
    // 2. 生のメモリーを解放する
    deallocate();
  }

  void assign(size_type count, const T& value) {
    if (count > capacity()) {
      clear();
      deallocate();

      first = allocate(count);
      last = first;
      reserved_last = first + count;
      for (size_type i = 0; i < count; ++i) construct(last++, value);
    } else if (count > size()) {
      pointer ptr = first;
      for (size_type i = 0; i < count; ++i) {
        if (i < size())
          *(ptr++) = value;
        else
          construct(last++, value);
      }
    } else {
      clear();
      for (size_type i = 0; i < count; ++i) construct(last++, value);
    }
  }

  template <class InputIt>
  void assign(InputIt src_first, InputIt src_last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
    size_type count = src_last - src_first;
    if (count > capacity()) {
      clear();
      deallocate();

      first = allocate(count);
      last = first;
      reserved_last = first + count;
      for (InputIt head = src_first; head != src_last; ++head)
        construct(last++, *head);
    } else if (count > size()) {
      pointer ptr = first;
      for (size_type i = 0; i < count; ++i) {
        if (i < size())
          *(ptr++) = *src_first++;
        else
          construct(last++, *src_first++);
      }
    } else {
      clear();
      for (InputIt head = src_first; head != src_last; ++head)
        construct(last++, *head);
    }
  }

  allocator_type get_allocator() const { return allocator_type(alloc); }

  //// Element access

  reference at(size_type i) {
    if (i >= size()) throw std::out_of_range("index is out of range.");
    return first[i];
  }
  const_reference at(size_type i) const {
    if (i >= size()) throw std::out_of_range("index is out of range.");
    return first[i];
  }
  reference operator[](size_type i) { return first[i]; }
  const_reference operator[](size_type i) const { return first[i]; }
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }
  pointer data() { return first; }
  const_pointer data() const { return first; }

  //// Iterators
  iterator begin() { return first; }
  iterator end() { return last; }
  const_iterator begin() const { return first; }
  const_iterator end() const { return last; }
  reverse_iterator rbegin() { return reverse_iterator(last); }
  reverse_iterator rend() { return reverse_iterator(first); }
  const_reverse_iterator rbegin() const { return reverse_iterator(last); }
  const_reverse_iterator rend() const { return reverse_iterator(first); }

  // 容量確認
  size_type size() const { return end() - begin(); }
  bool empty() const { return begin() == end(); }

  size_type max_size() const {
    size_t div = sizeof(value_type);
    if (div == 1) ++div;
    return std::numeric_limits<size_type>::max() / div;
    //    return alloc.max_size();
  }

  /*
  1. すでに指定された要素数以上に予約されているなら何もしない
  2. まだ動的メモリー確保が行われていなければ動的メモリー確保をする
  3. 有効な要素がある場合は新しいストレージにコピーする
  */
  void reserve(size_type sz) {
    // すでに指定された要素数以上に予約されているなら何もしない
    if (sz <= capacity()) return;

    // 動的メモリー確保をする
    pointer ptr = allocate(sz);

    // 古いストレージの情報を保存
    pointer old_first = first;
    pointer old_last = last;
    size_type old_capacity = capacity();

    // 新しいストレージに差し替え
    first = ptr;
    last = first;
    reserved_last = first + sz;

    // 例外安全のため
    // 関数を抜けるときに古いストレージを破棄する
    //    std::scope_exit e(
    //        [&] { traits::deallocate(alloc, old_first, old_capacity); });

    // 古いストレージから新しいストレージに要素をコピー構築
    // 実際にはムーブ構築
    for (pointer old_iter = old_first; old_iter != old_last;
         ++old_iter, ++last) {
      // このコピーの理解にはムーブセマンティクスの理解が必要
      construct(last, *old_iter);
    }

    // 新しいストレージにコピーし終えたので
    // 古いストレージの値は破棄
    for (reverse_iterator riter = reverse_iterator(old_last),
                          rend = reverse_iterator(old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
    // scope_exitによって自動的にストレージが破棄される
    alloc.deallocate(old_first, old_capacity);
  }

  size_type capacity() const { return reserved_last - first; }

  void clear() { destroy_until(rend()); }

  /*
   V = {1, 2, 3, 4}

   ・insert(V.begin()+1, 0)
   resize: {1, 2, 3, 4, 0}
                              -> (count)
   insert: {1, 0, 2, 3, 4}
                           | begin() + offset + count - 1
   */

  iterator insert(iterator pos, const T& value) {
    size_type count = 1;
    difference_type offset = pos - begin();

    size_type c = capacity();
    size_type pre_c = c;
    size_type new_size = size() + count;
    while (new_size > c) {
      if (c == 0)
        c = 1;
      else
        c = c << 1;
      if ((c >> 1) != pre_c) throw std::overflow_error("vector::insert");
      pre_c = c;
    }
    reserve(c);
    for (; last != first + new_size; ++last) construct(last);

    iterator tail = last - 1;
    iterator range_end = begin() + offset + count - 1;
    // pos + count - 1 までmemmove
    for (; tail > range_end; --tail) *tail = *(tail - count);
    iterator range_begin = begin() + offset - 1;
    for (; tail > range_begin; --tail) *tail = value;

    return begin() + offset;
  }

  void insert(iterator pos, size_type count, const T& value) {
    if (count < 0) throw std::length_error("negative length.");
    if (count == 0) return;

    difference_type offset = pos - begin();
    size_type c = capacity();
    size_type pre_c = c;
    size_type new_size = size() + count;
    while (c < new_size) {
      if (c == 0)
        c = 1;
      else
        c = c << 1;
      if ((c >> 1) != pre_c) throw std::overflow_error("vector::insert");
      pre_c = c;
    }
    reserve(c);
    for (; last != first + new_size; ++last) construct(last);

    iterator tail = last - 1;
    iterator range_end = begin() + offset + count - 1;
    // pos + count - 1 までmemmove
    for (; tail > range_end; --tail) *tail = *(tail - count);
    iterator range_begin = begin() + offset - 1;
    for (; tail > range_begin; --tail) *tail = value;
  }

  template <class InputIt>
  void insert(iterator pos, InputIt src_first, InputIt src_last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
    difference_type count = src_last - src_first;
    if (count < 0) throw std::length_error("negative length.");
    if (count == 0) return;

    difference_type offset = pos - begin();
    size_type c = capacity();
    size_type pre_c = c;
    size_type new_size = size() + count;
    while (c < new_size) {
      if (c == 0)
        c = 1;
      else
        c = c << 1;
      if ((c >> 1) != pre_c) throw std::overflow_error("vector::insert");
      pre_c = c;
    }
    reserve(c);
    for (; last != first + new_size; ++last) construct(last);

    iterator tail = last - 1;
    iterator range_end = begin() + offset + count - 1;
    // pos + count - 1 までmemmove
    for (; tail > range_end; --tail) *tail = *(tail - count);
    iterator range_begin = begin() + offset - 1;
    --src_last;
    for (; src_last > src_first - 1; --src_last) *tail-- = *src_last;
  }

  iterator erase(iterator pos) {
    // The iterator first does not need to be dereferenceable if first==last:
    // erasing an empty range is a no-op.
    if (first == last) return NULL;

    difference_type offset = pos - begin();

    for (iterator src = pos + 1; src < end(); ++src) {
      *(src - 1) = *src;
    }
    destroy(--last);
    return (begin() + offset);
  }

  iterator erase(iterator src_first, iterator src_last) {
    if (first == last) return NULL;

    difference_type head_offset = src_first - begin();
    difference_type tail_offset = src_last - src_first;

    for (iterator head = src_first, tail = src_last; tail < end(); ++head, ++tail)
      *head = *tail;
    destroy_until(rbegin() + tail_offset);

    return (begin() + head_offset);
  }

  void push_back(const_reference value) {
    // 予約メモリーが足りなければ拡張
    if (size() + 1 > capacity()) {
      // 現在のストレージサイズ
      size_type c = size();
      // 0の場合は1に
      if (c == 0)
        c = 1;
      else
        // それ以外の場合は2倍する
        c *= 2;

      reserve(c);
    }
    construct(last, value);
    ++last;
  }

  void pop_back() { destroy(--last); }

  /*
  1. 現在の要素数より少なくリサイズする場合、末尾から要素を破棄する
  2. 現在の要素数より大きくリサイズする場合、末尾に要素を追加する
  3. 現在の要素数と等しくリサイズする場合、何もしない
  */
  void resize(size_type sz) {
    // 現在の要素数より少ない
    if (sz < size()) {
      difference_type diff = size() - sz;
      destroy_until(rbegin() + diff);
      last = first + sz;
    }
    // 現在の要素数より大きい
    else if (sz > size()) {
      reserve(sz);
      for (; last != reserved_last; ++last) {
        construct(last);
      }
    }
  }

  void resize(size_type sz, const_reference value) {
    // 現在の要素数より少ない
    if (sz < size()) {
      difference_type diff = size() - sz;
      destroy_until(rbegin() + diff);
      last = first + sz;
    }
    // 現在の要素数より大きい
    else if (sz > size()) {
      reserve(sz);
      for (; last != reserved_last; ++last) {
        construct(last, value);
      }
    }
  }

  void swap(vector& other) {
    pointer save_first = other.first;
    pointer save_last = other.last;
    pointer save_reserved_last = other.reserved_last;
    allocator_type save_alloc = other.alloc;

    other.first = this->first;
    other.last = this->last;
    other.reserved_last = this->reserved_last;
    other.alloc = this->alloc;

    this->first = save_first;
    this->last = save_last;
    this->reserved_last = save_reserved_last;
    this->alloc = save_alloc;
  }

 private:
  // 先頭の要素へのポインター
  pointer first;
  // 最後の要素の1つ前方のポインター
  pointer last;
  // 確保したストレージの終端
  pointer reserved_last;
  // アロケーターの値
  allocator_type alloc;

  // ヘルパー関数
 private:
  pointer allocate(size_type n) { return alloc.allocate(n); }
  void deallocate() { alloc.deallocate(first, capacity()); }
  void construct(pointer ptr) { alloc.construct(ptr, 0); }
  void construct(pointer ptr, const_reference value) {
    alloc.construct(ptr, value);
  }
  void destroy(pointer ptr) { alloc.destroy(ptr); }
  void destroy_until(reverse_iterator rend) {
    for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last) {
      destroy(&*riter);
    }
  }
};

//// Non-member functions

template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return (lhs.size() == rhs.size() &&
          ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}
template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
}
template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end()));
}
template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return !(rhs < lhs);
}
template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs) {
  return (rhs < lhs);
}
template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
}

};  // namespace ft

namespace std {
template <class T, class Alloc>
void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) {
  lhs.swap(rhs);
}
}  // namespace std

#endif