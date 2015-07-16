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



double f2( double x, double y, double z= 4.15 )
{
  return 3.0 * x * x - 2.0 * x * y + 4.0 * y * y - y * z + 5.0 * z * z;
}


using                   x_base_t= nafto::arithmetic_wrap_t<1>;
using                   y_base_t= nafto::arithmetic_wrap_t<2>;
using                   z_base_t= nafto::arithmetic_wrap_t<3,
                                                           nafto::optional_tag>;
template<class T> using x_val_t=  x_base_t::type<T>;
template<class T> using y_val_t=  y_base_t::type<T>;
template<class T> using z_val_t=  z_base_t::type<T>;
constexpr auto          _x=       x_base_t()();
constexpr auto          _y=       y_base_t()();
constexpr auto          _z=       z_base_t()();



template<class T>
using f2_taglst_t = nafto::taglist<x_val_t<T>,y_val_t<T>,z_val_t<T> >;
//using f2_taglst_t = nafto::taglist<x_val_t<T>,z_val_t<T>,y_val_t<T> >;

template<class T>
class f2_nafto : public nafto::nafto_proxy<f2_nafto<T>, f2_taglst_t<T> >
{
  MAKE_FRIEND_OF_NAFTO
  //
public:
  f2_nafto() : nafto::nafto_proxy<f2_nafto<T>, f2_taglst_t<T> >( this )
  {}
  //
  T
  operator()( T X, T Y, T Z= 4.15 ) const
  {
    f2_nafto<T>  f;
    return f.set( _x= X, _y= Y, _z= Z )();
  }
  //
private:
  struct
  {
    T   x,  y,   z= 4.15;
    T   xx, yy, zz= 4.15 * 4.15;
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
    p.yz= p.y * p.z; // z defaults to 4.15 ==> we must noch test if it was
                     // submitted before
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
    f2_nafto<T>  cp_this;
    cp_this.p= p;
    return cp_this;
  }
  //
}; // class f2_nafto



int
main()
{
  double   x= 12.7;
  float    y= -18.4, z=  22.9;
  float    y2= 8.4;

  using t2= f2_nafto<long double>;
  t2  f2_obj1;
  t2  f2_obj2;
  t2  f2_obj3;
  t2  f2_obj4;
  t2  f2_obj5;
  t2  f2_obj6;

  std::cout << f2( x, y, z ) << "\n"
            << f2_obj1.set( _x= x, _y= y, _z= z )() << "\n"
            << f2_obj2.set( _y= y, _z= z, _x= x )() << "\n"
            << f2_obj3.set( _z= z, _x= x, _y= y )() << "\n";

  std::cout << "\n" << f2( x, y ) << "\n"
            << f2_obj4.set( _x= x, _y= y )() << "\n"
            << f2_obj5.set( _y= y, _x= x )() << "\n"
            << f2_obj6( x, y ) << "\n";

  t2  f2_obj7;
  auto pr1= f2_obj7.set( _x= x, _y= y );
  std::cout << "\n" << pr1() << "\n";

  // Cloning
  t2   f2_obj8a;
  auto pr8a_1= f2_obj8a.set( _x= x );
  auto pr8b_1= pr8a_1.clone();

  // Must not compile
  // pr8b_1();

  auto pr8a_2= pr8a_1.set( _y= y );
  auto pr8b_2= pr8b_1.set( _y= y2 );

  std::cout << "\n" << pr8a_2() << "\n"
            << pr8b_2() << "\n"
            << pr8a_2() << "\n"
            << f2_obj8a( x, y2 ) << "\n";
} // main












// end
