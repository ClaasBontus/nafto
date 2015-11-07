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
using two_log_taglst_t= nafto::taglist<x_val_t<T>,y_val_t<T> >;


template<class T>
class two_log : public nafto::nafto_proxy<two_log<T>, two_log_taglst_t<T> >
{
  MAKE_FRIEND_OF_NAFTO
  //
public:
  two_log() : nafto::nafto_proxy<two_log<T>, two_log_taglst_t<T> >( this )
  {}
  //
  T
  operator()( T x, T y ) const
  {
    T const lx= log( x );
    T const ly= log( y );
    return 3.1 * lx - 0.4 * lx * ly + 2.7 * ly;
  }
  //
private:
  struct
  {
    T   lx, ly;
    T   f_lx, f_ly, f_lxly;
  } p;
  //
  T
  operator()() const
  { return p.f_lx - p.f_lxly + p.f_ly; }
  //
  template<class flagLstT>
  void
  set_val( const typename x_val_t<T>::type &x_val, flagLstT flgs )
  {
    p.lx = log( x_val.val );
    p.f_lx= 3.1 * p.lx;
    if( flgs.flag( _y() ) )            // evaluated at compile-time
        p.f_lxly = 0.4 * p.lx * p.ly;  // y was submitted before
  }
  //
  template<class flagLstT>
  void
  set_val( const typename y_val_t<T>::type &y_val, flagLstT flgs )
  {
    p.ly= log( y_val.val );
    p.f_ly= 2.7 * p.ly;
    if( flgs.flag( _x() ) )            // evaluated at compile-time
        p.f_lxly = 0.4 * p.lx * p.ly;  // x was submitted before
  }
  //
  decltype(auto)
  clone_impl()
  {
    two_log<T>  cp_this;
    cp_this.p= p;
    return cp_this;
  }
  //
}; // class two_log
