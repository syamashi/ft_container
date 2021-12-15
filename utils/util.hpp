#ifndef UTIL_HPP
#define UTIL_HPP

namespace ft {

/// integral_constant
/*
type と value_type を宣言する必要がある。

・constexpr operator value_type() const noexcept {
  ft::is_integral<int>() // 1
  ft::is_integral<int*>() // 0

・constexpr value_type operator()() const noexcept {
  ft::is_integral<int> F;
  int f = F(); // f==1
*/
template <typename _Tp, _Tp __v>
struct integral_constant {
  static constexpr _Tp value = __v;
  typedef _Tp value_type;
  typedef integral_constant<_Tp, __v> type;
  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

/// The type used as a compile-time boolean with true value.
typedef integral_constant<bool, true> true_type;

/// The type used as a compile-time boolean with false value.
typedef integral_constant<bool, false> false_type;

/// is_same
/*
通常はfalse_typeを継承
型が同じ場合だけtrueになる
*/
template <typename, typename>
struct is_same : public false_type {};

template <typename _Tp>
struct is_same<_Tp, _Tp> : public true_type {};

// Const-volatile modifications.

/// remove_const
template <typename T>
struct remove_const {
  typedef T type;
};

template <typename T>
struct remove_const<T const> {
  typedef T type;
};

/// remove_volatile
template <typename T>
struct remove_volatile {
  typedef T type;
};

template <typename T>
struct remove_volatile<T volatile> {
  typedef T type;
};

/// remove_cv
template <typename T>
struct remove_cv {
  typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

/*
基本的にはfalse_type
trueパターンだけ指定
*/
template <typename>
struct __is_integral_helper : public false_type {};

template <>
struct __is_integral_helper<bool> : public true_type {};

template <>
struct __is_integral_helper<char> : public true_type {};

template <>
struct __is_integral_helper<signed char> : public true_type {};

template <>
struct __is_integral_helper<unsigned char> : public true_type {};

template <>
struct __is_integral_helper<wchar_t> : public true_type {};

template <>
struct __is_integral_helper<char16_t> : public true_type {};

template <>
struct __is_integral_helper<char32_t> : public true_type {};

template <>
struct __is_integral_helper<short> : public true_type {};

template <>
struct __is_integral_helper<unsigned short> : public true_type {};

template <>
struct __is_integral_helper<int> : public true_type {};

/*
template <>
struct __is_integral_helper<int>{
  static constexpr bool value = true;
  typedef int value_type;
  typedef __is_integral_helper<int> type;
  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};
*/

template <>
struct __is_integral_helper<unsigned int> : public true_type {};

template <>
struct __is_integral_helper<long> : public true_type {};

template <>
struct __is_integral_helper<unsigned long> : public true_type {};

template <>
struct __is_integral_helper<long long> : public true_type {};

template <>
struct __is_integral_helper<unsigned long long> : public true_type {};

//// is_integral
template <typename T>
struct is_integral
    : public __is_integral_helper<typename remove_cv<T>::type>::type {};

//// enable_if
/*
type の存在有無で型判断に進む。

bool B がtrueの時だけ、enable_if::type が定義される。

  set(InputIt first, InputIt last, const _Compare& comp = _Compare(),
      const allocator_type& a = allocator_type(),
      typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* =
          nullptr)
ft::is_integral< T >::valueがtrueのときは
ft::enable_if< false , > になるので、::typeが存在せず、
5個目の引数 typename ft::enable_if---::type がないものとして扱われるので、このオーバーロードに入らなくなる。

*/
template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
  typedef T type;
};

//// _KeyOfValue

template <typename _Pair>
struct _Select1st {
  typename _Pair::first_type& operator()(_Pair& __x) const { return __x.first; }

  const typename _Pair::first_type& operator()(const _Pair& __x) const {
    return __x.first;
  }
};

template <typename _Tp>
struct _Identity {
  _Tp& operator()(_Tp& __x) const { return __x; }

  const _Tp& operator()(const _Tp& __x) const { return __x; }
};

// Partial specialization, avoids confusing errors in e.g. std::set<const T>.
template <typename _Tp>
struct _Identity<const _Tp> : _Identity<_Tp> {};

};  // namespace ft
#endif