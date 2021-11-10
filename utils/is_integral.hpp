#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include "integral_constant.hpp"

namespace ft {

  // Const-volatile modifications.

  /// remove_const
  template<typename T>
    struct remove_const
    { typedef T     type; };

  template<typename T>
    struct remove_const<T const>
    { typedef T     type; };

  /// remove_volatile
  template<typename T>
    struct remove_volatile
    { typedef T     type; };

  template<typename T>
    struct remove_volatile<T volatile>
    { typedef T     type; };

  /// remove_cv
  template<typename T>
    struct remove_cv
    {
      typedef typename
      remove_const<typename remove_volatile<T>::type>::type     type;
    };

  template<typename>
    struct __is_integral_helper
    : public false_type { };

  template<>
    struct __is_integral_helper<bool>
    : public true_type { };

  template<>
    struct __is_integral_helper<char>
    : public true_type { };

  template<>
    struct __is_integral_helper<signed char>
    : public true_type { };

  template<>
    struct __is_integral_helper<unsigned char>
    : public true_type { };

//#ifdef _GLIBCXX_USE_WCHAR_T
  template<>
    struct __is_integral_helper<wchar_t>
    : public true_type { };
//#endif

  template<>
    struct __is_integral_helper<char16_t>
    : public true_type { };

  template<>
    struct __is_integral_helper<char32_t>
    : public true_type { };

  template<>
    struct __is_integral_helper<short>
    : public true_type { };

  template<>
    struct __is_integral_helper<unsigned short>
    : public true_type { };

  template<>
    struct __is_integral_helper<int>
    : public true_type { };

  template<>
    struct __is_integral_helper<unsigned int>
    : public true_type { };

  template<>
    struct __is_integral_helper<long>
    : public true_type { };

  template<>
    struct __is_integral_helper<unsigned long>
    : public true_type { };

  template<>
    struct __is_integral_helper<long long>
    : public true_type { };

  template<>
    struct __is_integral_helper<unsigned long long>
    : public true_type { };


  // is_integral
  template<typename T>
    struct is_integral
    : public __is_integral_helper<typename remove_cv<T>::type>::type
    { };


};  // namespace ft

#endif