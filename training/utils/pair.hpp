#ifndef PAIR_H
#define PAIR_H
#include <bits/move.h>  // for std::move / std::forward, and std::swap
#define __cplusplus 200001L

namespace ft {
template <typename _T1, typename _T2>
struct pair {
  typedef _T1 first_type;   /// @c first_type is the first bound type
  typedef _T2 second_type;  /// @c second_type is the second bound type

  _T1 first;   /// @c first is a copy of the first object
  _T2 second;  /// @c second is a copy of the second object

  constexpr pair() : first(), second() {}

  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}

  template <typename _U1, typename _U2>
  pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}
};

/// Two pairs of the same type are equal iff their members are equal.
template <typename _T1, typename _T2>
inline constexpr bool operator==(const pair<_T1, _T2>& __x,
                                          const pair<_T1, _T2>& __y) {
  return __x.first == __y.first && __x.second == __y.second;
}

/// <http://gcc.gnu.org/onlinedocs/libstdc++/manual/utilities.html>
template <typename _T1, typename _T2>
inline constexpr bool operator<(const pair<_T1, _T2>& __x,
                                         const pair<_T1, _T2>& __y) {
  return __x.first < __y.first ||
         (!(__y.first < __x.first) && __x.second < __y.second);
}

/// Uses @c operator== to find the result.
template <typename _T1, typename _T2>
inline constexpr bool operator!=(const pair<_T1, _T2>& __x,
                                          const pair<_T1, _T2>& __y) {
  return !(__x == __y);
}

/// Uses @c operator< to find the result.
template <typename _T1, typename _T2>
inline constexpr bool operator>(const pair<_T1, _T2>& __x,
                                         const pair<_T1, _T2>& __y) {
  return __y < __x;
}

/// Uses @c operator< to find the result.
template <typename _T1, typename _T2>
inline constexpr bool operator<=(const pair<_T1, _T2>& __x,
                                          const pair<_T1, _T2>& __y) {
  return !(__y < __x);
}

/// Uses @c operator< to find the result.
template <typename _T1, typename _T2>
inline constexpr bool operator>=(const pair<_T1, _T2>& __x,
                                          const pair<_T1, _T2>& __y) {
  return !(__x < __y);
}
template <typename _T1, typename _T2>
inline pair<_T1, _T2> make_pair(_T1 __x, _T2 __y) {
  return pair<_T1, _T2>(__x, __y);
}
}  // namespace std

#endif /* _STL_PAIR_H */
