#ifndef PAIR_H
#define PAIR_H

namespace ft {
template <class _T1, class _T2>
struct pair {
  typedef _T1 first_type;
  typedef _T2 second_type;

  _T1 first;
  _T2 second;

  //// constructer
  pair() : first(), second() {}

  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}

  template <class _U1, class _U2>
  pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}

  //// operator=
  pair& operator=(const pair& other) {
    if (this == &other) return *this;
    first = other.first;
    second = other.second;
    return *this;
  }
};

//// Non-member functions

template <class _T1, class _T2>
ft::pair<_T1, _T2> make_pair(_T1 __x, _T2 __y) {
  return pair<_T1, _T2>(__x, __y);
}

template <class _T1, class _T2>
bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first == __y.first && __x.second == __y.second;
}

template <class _T1, class _T2>
bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first < __y.first ||
         (!(__y.first < __x.first) && __x.second < __y.second);
}

template <class _T1, class _T2>
bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x == __y);
}

template <class _T1, class _T2>
bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __y < __x;
}

template <class _T1, class _T2>
bool operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__y < __x);
}

template <class _T1, class _T2>
bool operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x < __y);
}
}  // namespace ft

#endif
