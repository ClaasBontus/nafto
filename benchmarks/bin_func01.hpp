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

#include "nafto.hpp"
#include "value_types.hpp"
#include <cmath>


using                   x_base_t= nafto::arithmetic_wrap_t<1>;
using                   y_base_t= nafto::arithmetic_wrap_t<2>;
template<class T> using x_val_t=  x_base_t::type<T>;
template<class T> using y_val_t=  y_base_t::type<T>;
constexpr auto          _x=       x_base_t()();
constexpr auto          _y=       y_base_t()();


template<class T>
using bin_func_taglst_t= nafto::taglist<x_val_t<T>,y_val_t<T> >;



template<class T,T(*F1)(T),T(*F2)(T)>
class bin_func
: public nafto::nafto_proxy<bin_func<T,F1,F2>, bin_func_taglst_t<T> >
{
  MAKE_FRIEND_OF_NAFTO
  //
public:
  bin_func( T fac1, T fac12, T fac2 )
  : nafto::nafto_proxy<bin_func<T,F1,F2>, bin_func_taglst_t<T> >( this )
  , p( fac1, fac12, fac2 )
  {}
  //
  T
  operator()( T x, T y ) const
  {
    T const lx= F1( x );
    T const ly= F2( y );
    return p.fac1 * lx + p.fac12 * lx * ly + p.fac2 * ly;
  }
  //
private:
  struct P
  {
    P( T f1, T f12, T f2 )
    : fac1(f1)
    , fac12(f12)
    , fac2(f2)
    {}
    //
    T const  fac1, fac12, fac2;
    T        lx, ly;
    T        f_lx, f_ly, f_lxly;
  } p;
  //
  T
  operator()() const
  { return p.f_lx + p.f_lxly + p.f_ly; }
  //
  template<class flagLstT>
  void
  set_val( const typename x_val_t<T>::type &x_val, flagLstT flgs )
  {
    p.lx = F1( x_val.val );
    p.f_lx= p.fac1 * p.lx;
    if( flgs.flag( _y() ) )                // evaluated at compile-time
        p.f_lxly = p.fac12 * p.lx * p.ly;  // y was submitted before
  }
  //
  template<class flagLstT>
  void
  set_val( const typename y_val_t<T>::type &y_val, flagLstT flgs )
  {
    p.ly= F2( y_val.val );
    p.f_ly= p.fac2 * p.ly;
    if( flgs.flag( _x() ) )                // evaluated at compile-time
        p.f_lxly = p.fac12 * p.lx * p.ly;  // x was submitted before
  }
  //
  decltype(auto)
  clone_impl()
  {
    bin_func<T,F1,F2>  cp_this;
    cp_this.p= p;
    return cp_this;
  }
  //
}; // class bin_func
