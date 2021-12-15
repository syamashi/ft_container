#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
template <typename T>
class random_access_iterator
    : public ft::iterator<ft::random_access_iterator_tag, T> {
 protected:
  T* _current;

 public:
  typedef typename ft::iterator<ft::random_access_iterator_tag,
                                T>::iterator_category iterator_category;
  typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type
      value_type;
  typedef
      typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type
          difference_type;
  typedef T* pointer;
  typedef T& reference;

  random_access_iterator() : _current(nullptr) {}
  random_access_iterator(pointer x) : _current(x) {}
  random_access_iterator(const random_access_iterator& other)
      : _current(other._current) {}
  random_access_iterator& operator=(const random_access_iterator& other) {
    if (this == &other) return (*this);
    _current = other._current;
    return (*this);
  }
  ~random_access_iterator() {}
  pointer base() const { return _current; }
  reference operator*() const { return *_current; }
  pointer operator->() const { return &(operator*()); }
  reference operator[](difference_type n) const { return *(*this + n); }
  random_access_iterator& operator++() {
    ++_current;
    return *this;
  }
  random_access_iterator& operator--() {
    --_current;
    return *this;
  }
  random_access_iterator operator++(int) {
    random_access_iterator __tmp = *this;
    ++_current;
    return __tmp;
  }
  random_access_iterator operator--(int) {
    random_access_iterator __tmp = *this;
    --_current;
    return __tmp;
  }
  random_access_iterator operator+(difference_type n) const {
    return random_access_iterator(_current + n);
  }
  random_access_iterator operator-(difference_type n) const {
    return random_access_iterator(_current - n);
  }
  random_access_iterator& operator+=(difference_type n) {
    _current += n;
    return *this;
  }
  random_access_iterator& operator-=(difference_type n) {
    _current -= n;
    return *this;
  }

  /*
  ** ex. ft::reverse_iterator<ft::vector<int>::const_iterator> it1 =
  *a1.rbegin();
  */
  operator random_access_iterator<const T>() const {
    return (random_access_iterator<const T>(_current));
  }
};

//// Non-member functions

template <class Iterator1, class Iterator2>
bool operator==(const ft::random_access_iterator<Iterator1>& lhs,
                const ft::random_access_iterator<Iterator2>& rhs) {
  return lhs.base() == rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator!=(const ft::random_access_iterator<Iterator1>& lhs,
                const ft::random_access_iterator<Iterator2>& rhs) {
  return !(lhs == rhs);
}
template <class Iterator1, class Iterator2>
bool operator<(const ft::random_access_iterator<Iterator1>& lhs,
               const ft::random_access_iterator<Iterator2>& rhs) {
  return lhs.base() < rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator<=(const ft::random_access_iterator<Iterator1>& lhs,
                const ft::random_access_iterator<Iterator2>& rhs) {
  return rhs < lhs;
}
template <class Iterator1, class Iterator2>
bool operator>(const ft::random_access_iterator<Iterator1>& lhs,
               const ft::random_access_iterator<Iterator2>& rhs) {
  return rhs < lhs;
}
template <class Iterator1, class Iterator2>
bool operator>=(const ft::random_access_iterator<Iterator1>& lhs,
                const ft::random_access_iterator<Iterator2>& rhs) {
  return lhs < rhs;
}

template <class Iter>
ft::random_access_iterator<Iter> operator+(
    typename ft::random_access_iterator<Iter>::difference_type n,
    const ft::random_access_iterator<Iter>& it) {
  return ft::random_access_iterator<Iter>(it.base() + n);
}

template <class Iterator>
typename ft::random_access_iterator<Iterator>::difference_type operator-(
    const ft::random_access_iterator<Iterator>& lhs,
    const ft::random_access_iterator<Iterator>& rhs) {
  return lhs.base() - rhs.base();
}
};  // namespace ft
#endif
