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
#include <iostream>
#include <cmath>
#include <complex>


std::complex<double>
f3( double x, std::complex<double> z )
{
  return 3.2 * x - 2.1 * x * z.real() + 4.4 * z;
}


std::complex<double>
f3( double x, double re_z, double im_z )
{
  std::complex<double> z{ re_z, im_z };
  return f3( x, z );
}




using                   x_base_t=   nafto::arithmetic_wrap_t<1>;
using                   zre_base_t= nafto::arithmetic_wrap_t<2>;
using                   zim_base_t= nafto::arithmetic_wrap_t<3>;
using                   z_base_t=   nafto::complex_wrap_t<4>;


template<class T> using x_val_t=    x_base_t::type<T>;
template<class T> using zre_val_t=  zre_base_t::type<T>;
template<class T> using zim_val_t=  zim_base_t::type<T>;
template<class T> using z_val_t=    z_base_t::type<T>;

constexpr auto          _x=         x_base_t()();
constexpr auto          _z_re=      zre_base_t()();
constexpr auto          _z_im=      zim_base_t()();
constexpr auto          _z=         z_base_t()();

struct  z_alt_t {};

template<class T>
using z_alter=
      nafto::or_tags<z_alt_t,nafto::taglist<z_val_t<T> >,
                             nafto::taglist<zre_val_t<T>,zim_val_t<T> > >;
template<class T>
using f3_taglst_t= nafto::taglist<x_val_t<T>,z_alter<T> >;

template<class T>
class f3_nafto : public nafto::nafto_proxy<f3_nafto<T>, f3_taglst_t<T> >
{
  MAKE_FRIEND_OF_NAFTO
  //
public:
  f3_nafto() : nafto::nafto_proxy<f3_nafto<T>, f3_taglst_t<T> >( this )
  {}
  //
  std::complex<T>
  operator()( T x, const std::complex<T> &z ) const
  {
    return T(3.2) * x - T(2.1) * x * z.real() + T(4.4) * z;
  }
  //
  std::complex<T>
  operator()( T x, T re_z, T im_z ) const
  {
    std::complex<double> z{ re_z, im_z };
    return (*this)( x, z );
  }
  //
private:
  using cmplxT= std::complex<T>;
  //
  struct
  {
    T                x, re_z, im_z;
    T                x_rez;
    cmplxT           z;
  } p;
  //
  cmplxT
  operator()() const
  { return T(3.2) * p.x - T(2.1) * p.x_rez + T(4.4) * p.z; }
  //
  template<class flagLstT>
  void
  set_val( const typename x_val_t<T>::type &x_val, flagLstT flgs )
  {
    p.x= x_val.val;
    if( flgs.flag( _z_re() ) || flgs.flag( _z() ) )
        p.x_rez = p.x * p.re_z;
  }
  //
  template<class flagLstT>
  void
  set_val( const typename zre_val_t<T>::type &zre_val, flagLstT flgs )
  {
    p.re_z= zre_val.val;
    if( flgs.flag( _x() ) )      // evaluated at compile-time
        p.x_rez = p.x * p.re_z;  // x was submitted before
    if( flgs.flag( _z_im() ) ) p.z= cmplxT{ p.re_z, p.im_z };
  }
  //
  template<class flagLstT>
  void
  set_val( const typename zim_val_t<T>::type &zim_val, flagLstT flgs )
  {
    p.im_z= zim_val.val;
    if( flgs.flag( _z_re() ) ) p.z= cmplxT{ p.re_z, p.im_z };
  }
  //
  template<class flagLstT>
  void
  set_val( const typename z_val_t<T>::type &z_val, flagLstT flgs )
  {
    p.z=    z_val.val;
    p.re_z= p.z.real();
    p.im_z= p.z.imag();
    if( flgs.flag( _x() ) )      // evaluated at compile-time
        p.x_rez = p.x * p.re_z;  // x was submitted before
  }
  //
  template<class ParentT>
  decltype(auto)
  clone_impl()
  {
    f3_nafto<T>  cp_this;
    cp_this.p= p;
    return cp_this;
  }
}; // class f3_nafto



int
main()
{
  double   x= 24.6;
  double   z_re= 11.17;
  double   z_im= 8.54;
  auto     z=  std::complex<long double>{ z_re, z_im };
  auto     z1= std::complex<double>{      z_re, z_im };

  using t3= f3_nafto<float>;
  t3  f3_obj1;
  t3  f3_obj2;

  std::cout << f3( x, z1 ) << "\n"
            << f3( x, z_re, z_im ) << "\n"
            << f3_obj1.set( _x= x, _z= z )() << "\n"
            << f3_obj1.set( _z= z, _x= x )() << "\n"
            << f3_obj2.set( _z_re= z_re, _x= x, _z_im= z_im )() << "\n";

  t3   f3_obj3;
  auto f3_obj3a= f3_obj3.set( _x= x, _z_im= z_im );
  // Must not compile since too few arguments submitted
  //std::cout << f3_obj3a() << "\n";
  auto f3_obj3b= f3_obj3a.set( _z_re= z_re );
  std::cout << f3_obj3b() << "\n";

  //t3   f3_obj4;
  //auto f3_obj4a= f3_obj4.set(  _x= x, _z_im= z_im );
  // Must not compile since z_im was submitted before and z is in another
  // branch of or_tags
  //auto f3_obj4b= f3_obj4a.set( _z= z );
}
