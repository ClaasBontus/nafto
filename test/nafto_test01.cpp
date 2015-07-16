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



double f1( double x, double y, double z )
{
  return 3.0 * x * x - 2.0 * x * y + 4.0 * y * y - y * z + 5.0 * z * z;
}


using                   x_base_t= nafto::arithmetic_wrap_t<1>;
using                   y_base_t= nafto::arithmetic_wrap_t<2>;
using                   z_base_t= nafto::arithmetic_wrap_t<3>;
template<class T> using x_val_t=  x_base_t::type<T>;
template<class T> using y_val_t=  y_base_t::type<T>;
template<class T> using z_val_t=  z_base_t::type<T>;
constexpr auto          _x=       x_base_t()();
constexpr auto          _y=       y_base_t()();
constexpr auto          _z=       z_base_t()();



using f1_taglst_t =
      nafto::taglist<x_val_t<double>,y_val_t<double>,z_val_t<double> >;

class f1_nafto : public nafto::nafto_proxy<f1_nafto, f1_taglst_t>
{
  MAKE_FRIEND_OF_NAFTO
  //
public:
  f1_nafto() : nafto::nafto_proxy<f1_nafto, f1_taglst_t>( this )
  {}
  //
private:
  double   x,  y,   z;
  double   xx, yy, zz;
  double   xy, yz;
  //
  double
  operator()() const
  { return 3.0 * xx - 2.0 * xy + 4.0 * yy - yz + 5.0 * zz; }
  //
  template<class flagLstT>
  void
  set_val( const x_val_t<double>::type &x_val, flagLstT flgs )
  {
    x = x_val.val;
    xx = x * x;
    if( flgs.flag( _y() ) ) // evaluated at compile-time
        xy = x * y;         // y was submitted before
  }
  //
  template<class flagLstT>
  void
  set_val( const y_val_t<double>::type &y_val, flagLstT flgs )
  {
    y = y_val.val;
    yy = y * y;
    if( flgs.flag( _x() ) ) // evaluated at compile-time
        xy = x * y;         // x was submitted before
    if( flgs.flag( _z() ) ) yz= y * z;
  }
  //
  template<class flagLstT>
  void
  set_val( const z_val_t<double>::type &z_val, flagLstT flgs )
  {
    z = z_val.val;
    zz = z * z;
    if( flgs.flag( _y() ) ) // evaluated at compile-time
        yz = y * z;         // y was submitted before
  }
}; // class f1_nafto




template<class T>
using f1a_taglst_t = nafto::taglist<x_val_t<T>,y_val_t<T>,z_val_t<T> >;

template<class T>
class f1a_nafto : public nafto::nafto_proxy<f1a_nafto<T>, f1a_taglst_t<T> >
{
  MAKE_FRIEND_OF_NAFTO
  //
public:
  f1a_nafto() : nafto::nafto_proxy<f1a_nafto<T>, f1a_taglst_t<T> >( this )
  {}
  //
  T
  operator()( T X, T Y, T Z )
  {
    f1a_nafto<T>  f;
    return f.set( _x= X, _y= Y, _z= Z )();
    //return 3.0 * X * X - 2.0 * X * Y + 4.0 * Y * Y - Y * Z + 5.0 * Z * Z;
  }
  //
private:
  struct
  {
    T   x,  y,   z;
    T   xx, yy, zz;
    T   xy, yz;
  } p;
  //
  T
  operator()() const
  { return 3.0 * p.xx - 2.0 * p.xy + 4.0 * p.yy - p.yz + 5.0 * p.zz; }
  //
  template<class flagLstT>
  void
  set_val( const typename x_val_t<T>::type &x_val, flagLstT flgs )
  {
    p.x = x_val.val;
    p.xx = p.x * p.x;
    if( flgs.flag( _y() ) ) // evaluated at compile-time
        p.xy = p.x * p.y;   // y was submitted before
  }
  //
  template<class flagLstT>
  void
  set_val( const typename y_val_t<T>::type &y_val, flagLstT flgs )
  {
    p.y = y_val.val;
    p.yy = p.y * p.y;
    if( flgs.flag( _x() ) ) // evaluated at compile-time
        p.xy = p.x * p.y;   // x was submitted before
    if( flgs.flag( _z() ) ) p.yz= p.y * p.z;
  }
  //
  template<class flagLstT>
  void
  set_val( const typename z_val_t<T>::type &z_val, flagLstT flgs )
  {
    p.z = z_val.val;
    p.zz = p.z * p.z;
    if( flgs.flag( _y() ) ) // evaluated at compile-time
        p.yz = p.y * p.z;   // y was submitted before
  }
  //
  decltype(auto)
  clone_impl()
  {
    f1a_nafto<T>  cp_this;
    cp_this.p= p;
    return cp_this;
  }
  //
}; // class f1a_nafto



int
main()
{
  double   x= 12.7;
  float    y= -18.4, z=  22.9;
  float    y2= 8.4, z2= -12.9;

  f1_nafto  f1_obj1;
  f1_nafto  f1_obj2;
  f1_nafto  f1_obj3;

  std::cout << f1( x, y, z ) << "\n"
            << f1_obj1.set( _x= x, _y= y, _z= z )() << "\n"
            << f1_obj2.set( _y= y, _z= z, _x= x )() << "\n"
            << f1_obj3.set( _z= z, _x= x, _y= y )() << "\n\n";

  using t1= f1a_nafto<long double>;
  t1   f1a_obj1;

  auto f1a_clone= f1a_obj1.clone();

  auto pr1= f1a_obj1.set( _x= x, _y= y );
  auto pr2x= pr1.clone();
  auto pr2= pr2x.set( _z= z );
  std::cout << pr2() << "\n"
            << f1a_obj1( x, y, z ) << " == " << f1a_clone( x, y, z ) << "\n"
            << pr1( z2 ) << " == " << f1a_obj1( x, y, z2 ) << "\n\n";

  // Must no compile since there is no argument missing.
  //pr2( z );

  // Must not compile since set must not be called on an rvalue ref.
  // auto pr2_1= f1a_nafto<double>().set( _y= y );

  // Cloning
  t1   f1a_obj2a;
  auto pr2a_1= f1a_obj2a.set( _x= x );
  auto pr2b_1= pr2a_1.clone();

  // Must not compile since there is more than one argument missing.
  //pr2a_1( y );

  // Must not compile
  //pr2b_1();

  auto pr2a_2= pr2a_1.set( _y= y );
  auto pr2b_2= pr2b_1.set( _y= y2 );

  // Must not compile
  //pr2b_2();

  auto pr2b_3= pr2b_2.set( _z= z2 );
  auto pr2a_3= pr2a_2.set( _z= z );

  std::cout << "\n" << pr2a_3() << "\n"
            << pr2b_3() << "\n"
            << f1a_obj2a( x, y2, z2 ) << "\n";

} // main












// end
