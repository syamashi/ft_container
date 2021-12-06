
#ifndef ALLOC_TRAITS_H
#define ALLOC_TRAITS_H

//#include <bits/allocator.h>  // for __alloc_swap

namespace ft
{
template<typename _Alloc, typename = typename _Alloc::value_type>
  struct __alloc_traits
  {
    typedef _Alloc allocator_type;
    typedef typename _Alloc::pointer                pointer;
    typedef typename _Alloc::const_pointer          const_pointer;
    typedef typename _Alloc::value_type             value_type;
    typedef typename _Alloc::reference              reference;
    typedef typename _Alloc::const_reference        const_reference;
    typedef typename _Alloc::size_type              size_type;
    typedef typename _Alloc::difference_type        difference_type;

    static pointer
    allocate(_Alloc& __a, size_type __n)
    { return __a.allocate(__n); }

    static void deallocate(_Alloc& __a, pointer __p, size_type __n)
    { __a.deallocate(__p, __n); }

    template<typename _Tp>
      static void construct(_Alloc& __a, pointer __p, const _Tp& __arg)
      { __a.construct(__p, __arg); }

    static void destroy(_Alloc& __a, pointer __p)
    { __a.destroy(__p); }

    static size_type max_size(const _Alloc& __a)
    { return __a.max_size(); }

    static const _Alloc& _S_select_on_copy(const _Alloc& __a) { return __a; }

    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
    {
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 431. Swapping containers with unequal allocators.
      std::__alloc_swap<_Alloc>::_S_do_it(__a, __b);
    }

    template<typename _Tp>
      struct rebind
      { typedef typename _Alloc::template rebind<_Tp>::other other; };
  };

} // namespace ft

#endif
