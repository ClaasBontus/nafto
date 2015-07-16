// NAFTO - the n-ary function tool
//
//  Copyright Claas Bontus
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ClaasBontus/nafto
//

#ifndef NAFTO_VALUE_TYPES_HPP
#define NAFTO_VALUE_TYPES_HPP

#include <type_traits>
#include <utility>
#include <complex>
#include "nafto_types.hpp"



namespace nafto
{


namespace detail
{

  template<size_t n, class T, bool Enable >
  struct val_cont_t;

  template<size_t n, class T>
  struct val_cont_t<n,T,true>
  {
    T   val= T();
    //
    constexpr val_cont_t() {}
    constexpr val_cont_t( const T &v ) : val( v ) {}
    //
    template<class T2>
    constexpr
    val_cont_t( const val_cont_t<n, T2,true> &v2 ) : val( T(v2.val) ) {}
    //
    template<class T2>
    constexpr
    val_cont_t<n,T2,true>
    operator=( T2 v ) const { return val_cont_t<n,T2,true>(v); }
  }; // struct val_cont_t


  template<class T>
  struct is_cmplx : std::false_type {};

  template<class T>
  struct is_cmplx<std::complex<T> > : std::true_type{};


  template<class T>
  struct typeId
  {
    using type= T;
  };

  template<class T>
  struct to_cmplx
  {
    using type= std::complex<T>;
  };



  template<class T>
  struct val_constructor;

  template<class T>
  struct value_constructor;


  template<size_t n,template<size_t,class> class baseT,class defaultT,
           class opt_param,
           template<class> class typeF=typeId>
  struct value_wrap_t
  {
    using this_t= value_wrap_t<n,baseT,defaultT,opt_param,typeF>;
    //
    enum : size_t { val= n };
    //
    template<class T= defaultT>
    using type= tag_entry<baseT<n,typename typeF<T>::type >,opt_param>;
    //
    constexpr
    decltype(auto)
    operator()()
    {
      return val_constructor<this_t>();
    }
  }; // struct value_wrap_t


  template<size_t n,template<size_t,class> class baseT,class defaultT,
           class opt_param>
  struct value_wrap_t2
  {
    using this_t= value_wrap_t2<n,baseT,defaultT,opt_param>;
    //
    enum : size_t { val= n };
    //
    using type= tag_entry<baseT<n,defaultT>,opt_param>;
    //
    constexpr
    decltype(auto)
    operator()()
    {
      return value_constructor<this_t>();
    }
  }; // struct value_wrap_t2




  template<size_t n,template<size_t,class> class bT,class defaultT,
           class opt_param,template<class> class typeF>
  struct val_constructor<value_wrap_t<n,bT,defaultT,opt_param,typeF> >
  {
    template<class T2>
    using baseT= bT<n,T2>;
    //
    template<class T2>
    constexpr
    baseT<T2>
    operator=( const T2 &v ) const { return baseT<T2>( v ); }
    //
    constexpr
    baseT<defaultT>
    operator()() const { return baseT<defaultT>(); }
  }; // struct val_constructor




  template<size_t n,template<size_t,class> class bT,class defaultT,
           class opt_param>
  struct value_constructor<value_wrap_t2<n,bT,defaultT,opt_param> >
  {
    using baseT= bT<n,defaultT>;
    //
    template<class T2>
    constexpr
    baseT
    operator=( const T2 &v ) const { return baseT( v ); }
    //
    constexpr
    baseT
    operator()() const { return baseT(); }
  }; // struct value_constructor



  template<size_t n, class T>
  using val_t= val_cont_t<n,T,true>;


  template<size_t n, class T>
  using floating_point_val_t= val_cont_t<n,T,std::is_floating_point<T>::value>;


  template<size_t n, class T>
  using integral_val_t= val_cont_t<n,T,std::is_integral<T>::value>;


  template<size_t n, class T>
  using arithmetic_val_t= val_cont_t<n,T,std::is_arithmetic<T>::value>;


  template<size_t n, class T>
  using complex_val_t=
        val_cont_t<n,T,(std::is_arithmetic<T>::value || is_cmplx<T>::value)>;

} // namespace detail


template<size_t n,class T,class opt_param=obligatory_tag>
using val_wrap_t= detail::value_wrap_t2<n,detail::val_t,T,opt_param>;

template<size_t n,class opt_param=obligatory_tag>
using floating_point_wrap_t=
      detail::value_wrap_t<n,detail::floating_point_val_t,double,opt_param>;

template<size_t n,class opt_param=obligatory_tag>
using integral_wrap_t=
      detail::value_wrap_t<n,detail::integral_val_t,int,opt_param>;

template<size_t n,class opt_param=obligatory_tag>
using arithmetic_wrap_t=
      detail::value_wrap_t<n,detail::arithmetic_val_t,double,opt_param>;

template<size_t n,class opt_param=obligatory_tag>
using complex_wrap_t=
      detail::value_wrap_t<n,detail::complex_val_t,double,opt_param,
                           detail::to_cmplx >;


} // namespace nafto


#endif // NAFTO_VALUE_TYPES_HPP
