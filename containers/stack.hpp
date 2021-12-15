#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T>>
class stack {
  /*
  ** Member types
  */

 public:
  typedef T value_type;
  typedef Container container_type;
  typedef size_t size_type;

  explicit stack(const container_type& ctnr = container_type()) : _c(ctnr) {}
  bool empty() const { return _c.empty(); }
  size_type size() const { return _c.size(); }
  value_type& top() { return _c.back(); }
  const value_type& top() const { return _c.back(); }
  void push(const value_type& val) { return _c.push_back(val); }
  void pop() { return _c.pop_back(); }

 protected:
  container_type _c;

  template <class T_, class Container_>
  friend bool operator==(const ft::stack<T_, Container_>& lhs,
                         const ft::stack<T_, Container_>& rhs);
  template <class T_, class Container_>
  friend bool operator!=(const ft::stack<T_, Container_>& lhs,
                         const ft::stack<T_, Container_>& rhs);
  template <class T_, class Container_>
  friend bool operator<(const ft::stack<T_, Container_>& lhs,
                        const ft::stack<T_, Container_>& rhs);
  template <class T_, class Container_>
  friend bool operator<=(const ft::stack<T_, Container_>& lhs,
                         const ft::stack<T_, Container_>& rhs);
  template <class T_, class Container_>
  friend bool operator>(const ft::stack<T_, Container_>& lhs,
                        const ft::stack<T_, Container_>& rhs);
  template <class T_, class Container_>
  friend bool operator>=(const ft::stack<T_, Container_>& lhs,
                         const ft::stack<T_, Container_>& rhs);
};

/*
** Non-member function overloads
*/

template <class T, class Container>
bool operator==(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return (lhs._c == rhs._c);
}
template <class T, class Container>
bool operator!=(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return (lhs._c != rhs._c);
}
template <class T, class Container>
bool operator<(const ft::stack<T, Container>& lhs,
               const ft::stack<T, Container>& rhs) {
  return (lhs._c < rhs._c);
}
template <class T, class Container>
bool operator<=(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return (lhs._c <= rhs._c);
}
template <class T, class Container>
bool operator>(const ft::stack<T, Container>& lhs,
               const ft::stack<T, Container>& rhs) {
  return (lhs._c > rhs._c);
}
template <class T, class Container>
bool operator>=(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return (lhs._c >= rhs._c);
}
}  // namespace ft

#endif