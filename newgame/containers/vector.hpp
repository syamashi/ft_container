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

  // 容量確認
  size_type size() const { return end() - begin(); }
  bool empty() const { return begin() == end(); }
  size_type capacity() const { return reserved_last - first; }

  // 要素アクセス

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

  reference operator[](size_type i) { return first[i]; }
  const_reference operator[](size_type i) const { return first[i]; }
  reference at(size_type i) {
    if (i >= size()) throw std::out_of_range("index is out of range.");

    return first[i];
  }
  const_reference at(size_type i) const {
    if (i >= size()) throw std::out_of_range("index is out of range.");

    return first[i];
  }

  reference front() { return *first; }
  const_reference front() const { return *first; }
  reference back() { return *(last - 1); }
  const_reference back() const { return *(last - 1); }

  pointer data() { return first; }
  const_pointer data() const { return first; }

  // イテレーターアクセス
  iterator begin() { return first; }
  iterator end() { return last; }
  const_iterator begin() const { return first; }
  const_iterator end() const { return last; }
  reverse_iterator rbegin() { return reverse_iterator(last); }
  reverse_iterator rend() { return reverse_iterator(first); }
  const_reverse_iterator rbegin() const { return reverse_iterator(last); }
  const_reverse_iterator rend() const { return reverse_iterator(first); }

  void clear() { destroy_until(rend()); }

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

  void shrink_to_fit() {
    // 何もする必要がない
    if (size() == capacity()) return;

    // 新しいストレージを確保
    pointer ptr = allocate(size());
    // コピー
    size_type current_size = size();
    for (pointer raw_ptr = ptr, iter = begin(), iter_end = end();
         iter != iter_end; ++iter, ++raw_ptr) {
      construct(raw_ptr, *iter);
    }
    // 破棄
    clear();
    deallocate();
    // 新しいストレージを使う
    first = ptr;
    last = ptr + current_size;
    reserved_last = last;
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

};  // namespace ft

#endif