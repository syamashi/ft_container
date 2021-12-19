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
  /*
  ** Member types
  */

  typedef T value_type;
  typedef Allocator allocator_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename ft::random_access_iterator<value_type> iterator;
  typedef typename ft::random_access_iterator<const value_type> const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  /*
  ** Member functions
  */

  vector()
      : _first(NULL),
        _last(NULL),
        _reserved_last(NULL),
        _alloc(allocator_type()) {}
  explicit vector(const Allocator& alloc)
      : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {}
  explicit vector(size_type count, const T& value = T(),
                  const Allocator& alloc = Allocator())
      : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {
    resize(count, value);
  }

  template <class InputIt>
  vector(InputIt head, InputIt tail, const Allocator& alloc = Allocator(),
         typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                InputIt>::type* = NULL)
      : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {
    difference_type sz = ft::distance(head, tail);
    resize(sz);
    pointer ptr = _first;
    for (InputIt src = head; src != tail; ++src, ++ptr) {
      construct(ptr, *src);
    }
  }

  vector(const vector& other)
      : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(other._alloc) {
    reserve(other.size());

    pointer dest = _first;
    for (const_iterator src = other.begin(), last = other.end(); src != last;
         ++dest, ++src) {
      construct(dest, *src);
    }
    _last = _first + other.size();
  }

  ~vector() {
    clear();
    deallocate();
  };
  vector& operator=(const vector& r) {
    if (this == &r) return *this;
    if (size() == r.size()) {
      std::copy(r.begin(), r.end(), begin());
    } else {
      if (capacity() >= r.size()) {
        std::copy(r.begin(), r.begin() + r.size(), begin());
        for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end();
             src_iter != src_end; ++src_iter, ++_last) {
          construct(_last, *src_iter);
        }
      } else {
        destroy_until(rbegin());
        reserve(r.size());
        for (const_iterator src_iter = r.begin(), src_end = r.end();
             src_iter != src_end; ++src_iter, ++_last) {
          construct(_last, *src_iter);
        }
      }
    }
    return *this;
  };

  void assign(size_type count, const T& value) {
    if (count > capacity()) {
      clear();
      _alloc.deallocate(_first, capacity());
      pointer ptr = allocate(count);
      _first = ptr;
      _last = _first;
      _reserved_last = _first + count;
      for (size_type i = 0; i < count; ++i) construct(_last++, value);
    } else if (count > size()) {
      pointer ptr = _first;
      for (size_type i = 0; i < count; ++i) {
        if (i < size())
          *(ptr++) = value;
        else
          construct(_last++, value);
      }
    } else {
      clear();
      for (size_type i = 0; i < count; ++i) construct(_last++, value);
    }
  }

  template <class InputIt>
  void assign(InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
    size_type count = last - first;
    if (count > capacity()) {
      clear();
      _alloc.deallocate(_first, capacity());
      pointer ptr = allocate(count);
      _first = ptr;
      _last = _first;
      _reserved_last = _first + count;
      for (InputIt head = first; head != last; ++head)
        construct(_last++, *head);
    } else if (count > size()) {
      pointer ptr = _first;
      for (size_type i = 0; i < count; ++i) {
        if (i < size())
          *(ptr++) = *first++;
        else
          construct(_last++, *first++);
      }
    } else {
      clear();
      for (InputIt head = first; head != last; ++head)
        construct(_last++, *head);
    }
  }

  allocator_type get_allocator() const { return allocator_type(_alloc); }

  /*
  ** Member functions: Element access
  */

  reference at(size_type i) {
    if (i >= size()) throw std::out_of_range("index is out of range.");
    return _first[i];
  }
  const_reference at(size_type i) const {
    if (i >= size()) throw std::out_of_range("index is out of range.");
    return _first[i];
  }
  reference operator[](size_type i) { return _first[i]; }
  const_reference operator[](size_type i) const { return _first[i]; }
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }
  pointer data() { return _first; }
  const_pointer data() const { return _first; }

  /*
  ** Member functions: iterators
  */

  iterator begin() { return _first; }
  const_iterator begin() const { return _first; }
  iterator end() { return _last; }
  const_iterator end() const { return _last; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return reverse_iterator(begin()); }

  /*
  ** Member functions: Capacity
  */

  bool empty() const { return begin() == end(); }
  size_type size() const { return end() - begin(); }
  size_type max_size() const {
    size_t div = sizeof(value_type);
    if (div == 1) ++div;
    return std::numeric_limits<size_type>::max() / div;
//    return _alloc.max_size();
  }

  void reserve(size_type sz) {
    if (sz <= capacity()) return;

    if (sz > this->max_size()) throw std::length_error("vector::reserve");

    pointer ptr = allocate(sz);
    pointer old_first = _first;
    pointer old_last = _last;
    size_type old_capacity = capacity();

    _first = ptr;
    _last = _first;
    _reserved_last = _first + sz;

    for (pointer old_iter = old_first; old_iter != old_last;
         ++old_iter, ++_last) {
      construct(_last, *old_iter);
    }

    for (reverse_iterator riter = reverse_iterator(old_last),
                          rend = reverse_iterator(old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
    _alloc.deallocate(old_first, old_capacity);
  }

  size_type capacity() const { return _reserved_last - _first; }

  /*
  ** Member functions: Modifiers
  */

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
    for (; _last != _first + new_size; ++_last) construct(_last);

    iterator tail = _last - 1;
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
    for (; _last != _first + new_size; ++_last) construct(_last);

    iterator tail = _last - 1;
    iterator range_end = begin() + offset + count - 1;
    // pos + count - 1 までmemmove
    for (; tail > range_end; --tail) *tail = *(tail - count);
    iterator range_begin = begin() + offset - 1;
    for (; tail > range_begin; --tail) *tail = value;
  }

  template <class InputIt>
  void insert(iterator pos, InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
    difference_type count = last - first;
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
    for (; _last != _first + new_size; ++_last) construct(_last);

    iterator tail = _last - 1;
    iterator range_end = begin() + offset + count - 1;
    // pos + count - 1 までmemmove
    for (; tail > range_end; --tail) *tail = *(tail - count);
    iterator range_begin = begin() + offset - 1;
    --last;
    for (; last > first - 1; --last) *tail-- = *last;
  }

  iterator erase(iterator pos) {
    // The iterator first does not need to be dereferenceable if first==last:
    // erasing an empty range is a no-op.
    if (_first == _last) return NULL;

    difference_type offset = pos - begin();

    for (iterator src = pos + 1; src < end(); ++src) {
      *(src - 1) = *src;
    }
    destroy(--_last);
    return (begin() + offset);
  }

  iterator erase(iterator first, iterator last) {
    if (_first == _last) return NULL;

    difference_type head_offset = first - begin();
    difference_type tail_offset = last - first;

    for (iterator head = first, tail = last; tail < end(); ++head, ++tail)
      *head = *tail;
    destroy_until(rbegin() + tail_offset);

    return (begin() + head_offset);
  }

  void push_back(const_reference value) {
    if (size() + 1 > capacity()) {
      size_type c = size();
      if (c == 0)
        c = 1;
      else
        c *= 2;
      reserve(c);
    }
    construct(_last, value);
    ++_last;
  }

  void pop_back() { destroy(--_last); }

  void resize(size_type sz) {
    if (sz < size()) {
      size_type diff = size() - sz;
      destroy_until(rbegin() + diff);
      _last = _first + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; _last != _reserved_last; ++_last) {
        construct(_last);
      }
    }
  }

  void resize(size_type sz, const_reference value) {
    if (sz < size()) {
      size_type diff = size() - sz;
      destroy_until(rbegin() + diff);
      _last = _first + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; _last != _reserved_last; ++_last) {
        construct(_last, value);
      }
    }
  }

  void swap(vector& other) {
    if (other == *this) return;

    pointer save_first = other._first;
    pointer save_last = other._last;
    pointer save_reserved_last = other._reserved_last;
    allocator_type save_alloc = other._alloc;

    other._first = this->_first;
    other._last = this->_last;
    other._reserved_last = this->_reserved_last;
    other._alloc = this->_alloc;

    this->_first = save_first;
    this->_last = save_last;
    this->_reserved_last = save_reserved_last;
    this->_alloc = save_alloc;
  }

 protected:
  pointer _first;
  pointer _last;
  pointer _reserved_last;
  allocator_type _alloc;

  pointer allocate(size_type n) { return _alloc.allocate(n); }
  void deallocate() { _alloc.deallocate(_first, capacity()); }
  void construct(pointer ptr) { _alloc.construct(ptr, 0); }
  void construct(pointer ptr, const_reference value) {
    _alloc.construct(ptr, value);
  }
  void destroy(pointer ptr) { _alloc.destroy(ptr); }
  void destroy_until(reverse_iterator rend) {
    for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --_last) {
      destroy(&*riter);
    }
  }
};

/*
** Non-member functions
*/

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

}  // namespace ft

namespace std {
template <class T, class Alloc>
void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) {
  lhs.swap(rhs);
}
}  // namespace std

#endif