#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft {

/*
** TAGS
*/

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/*
** iterator_traits
*/

template <class Iterator>
class iterator_traits {
 public:
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

template <class T>
class iterator_traits<T*> {
 public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
 public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

/*
** other iterators
*/

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
    : public iterator<typename iterator_traits<Iter>::iterator_category,
                      typename iterator_traits<Iter>::value_type,
                      typename iterator_traits<Iter>::difference_type,
                      typename iterator_traits<Iter>::pointer,
                      typename iterator_traits<Iter>::reference> {
 protected:
  Iter current;
  typedef ft::iterator_traits<Iter> traits_type;

 public:
  typedef Iter iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::pointer pointer;
  typedef typename traits_type::reference reference;

  /*
  ** Member functions
  */

  reverse_iterator() : current() {}
  explicit reverse_iterator(iterator_type x) : current(x) {}
  template <class U>
  reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}

  template <class U>
  reverse_iterator& operator=(const reverse_iterator<U>& other) {
	if (this == &other)
		return *this ;
    current = other.base();
	return *this ;
  }
  // test
  ~reverse_iterator() {}

  iterator_type base() const { return current; }
  reference operator*() const {
    Iter tmp = current;
    return *--tmp;
  }
  pointer operator->() const { return &(operator*()); }

  reference operator[](difference_type n) const {
    return *(*this + n);
  }

  reverse_iterator& operator++() {
    --current;
    return *this;
  }
  reverse_iterator& operator--() {
    ++current;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator __tmp = *this;
    --current;
    return __tmp;
  }
  reverse_iterator operator--(int) {
    reverse_iterator __tmp = *this;
    ++current;
    return __tmp;
  }
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current - n);
  }
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current + n);
  }
  reverse_iterator& operator+=(difference_type n) {
    current -= n;
    return *this;
  }
  reverse_iterator& operator-=(difference_type n) {
    current += n;
    return *this;
  }
};

/*
** reverse_it nonmember func
*/

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
bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs < rhs;
}
template <class Iterator1, class Iterator2>
bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs < rhs;
}
template <class Iterator1, class Iterator2>
bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return rhs < lhs;
}

template <class Iter>
reverse_iterator<Iter> operator+(
    typename reverse_iterator<Iter>::difference_type n,
    const reverse_iterator<Iter>& it) {
  return reverse_iterator<Iter>(it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
  return rhs.base() - lhs.base();
}

/*
** FUNCTIONS
*/

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
    InputIterator first, InputIterator last)
{
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
struct insert_iterator : public iterator<output_iterator_tag, void, void, void, void> {
  protected:
  Container* c;
  typename Container::iterator iter;

  public:
  typedef Container container_type;
  insert_iterator( Container& c) : c(&c) {}
  /*
        insert_iterator(_Container& __x, typename _Container::iterator __i)
      : container(std::__addressof(__x)), iter(__i) {}
  */
  insert_iterator( Container& c, typename Container::iterator i ) : c(&c), iter(i) {}
  insert_iterator& operator*() { return *this; }
  insert_iterator& operator++() { return *this; }
  insert_iterator operator++(int) { return *this; }
  insert_iterator& operator=(const typename Container::value_type&
                                 value) {  // ここをかえないといけない
    iter = c->insert(iter, value);
    ++iter;
    return *this;
  }
};




template <class Container, class Iterator>
insert_iterator<Container> inserter(Container& x, Iterator it) {
  return insert_iterator<Container>(x, typename Container::iterator( it ));
}


/*
  template<typename _Container, typename _Iterator>
    inline insert_iterator<_Container>
    inserter(_Container& __x, _Iterator __i)
    {
      return insert_iterator<_Container>(__x,
					 typename _Container::iterator(__i));
    }

*/
};  // namespace ft

#endif