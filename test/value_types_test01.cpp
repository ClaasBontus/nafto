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

#include "value_types.hpp"
#include <iostream>
#include <string>
#include <vector>


using                 base_t_1= nafto::integral_wrap_t<1>;
using                 base_t_2= nafto::floating_point_wrap_t<2>;
using                 base_t_3= nafto::arithmetic_wrap_t<3>;
using                 base_t_4= nafto::complex_wrap_t<4>;
using                 base_t_5= nafto::val_wrap_t<5,std::string>;
using                 base_t_6= nafto::val_wrap_t<6,std::vector<double> >;

template<class T> using x_val_1=  base_t_1::type<T>;
template<class T> using x_val_2=  base_t_2::type<T>;
template<class T> using x_val_3=  base_t_3::type<T>;
template<class T> using x_val_4=  base_t_4::type<T>;
using                   x_val_5=  base_t_5::type;
using                   x_val_6=  base_t_6::type;

constexpr auto          _x1=      base_t_1()();
constexpr auto          _x2=      base_t_2()();
constexpr auto          _x3=      base_t_3()();
constexpr auto          _x4=      base_t_4()();
constexpr auto          _x5=      base_t_5()();
constexpr auto          _x6=      base_t_6()();


void
str_f( const x_val_5::type &str_val )
{
  std::cout << str_val.val << "\n";
}

void
cmplx_f( const x_val_4<double>::type &cmplx_val )
{
  std::cout << cmplx_val.val << "\n";
}

void
d_vec_f( const x_val_6::type &d_vec )
{
  for( auto const d : d_vec.val ) std::cout << d << "  ";
  std::cout << "\n";
}


int main()
{

  auto v1= (_x1= 3);
  std::cout << v1.val << "\n";

  // Must not compile since 4.15 is not an integral type
  //auto v2a= (_x1= 4.15);

  auto v2= (_x1= int(4.15));
  std::cout << v2.val << "\n";



  auto v3= (_x2= 4.15);
  std::cout << v3.val << "\n";

  // Must not compile since 5 is not a floating point type
  //auto v4a= (_x2= 5);

  auto v4= (_x2= double(5));
  std::cout << v4.val << "\n";



  // Must not compile since "hello world" is not an arithmetic type
  //auto v5a= (_x3= "hello world");

  auto v5= (_x3= 5.16);
  auto v6= (_x3= 6);
  std::cout << v5.val << "  " << v6.val << "\n";




  auto v7a= (_x4= -11.8);
  std::cout << "v7a= " << v7a.val << "\n";
  cmplx_f( v7a );

  auto v7= (_x4=std::complex<float>( 2.17, -5.89 ));
  std::cout << "v7= " << v7.val << "\n";
  cmplx_f( v7 ); // std::complex<float> converts to std::complex<double>



  // Must not compile since 3 is not convertible to std::string
  //auto v8a= (_x5= 3);

  auto v8= (_x5= std::string( "hello" ));
  std::cout << v8.val << "\n";
  str_f( v8 );

  auto v9= (_x5= "world");
  std::cout << v9.val << "\n";
  str_f( v9 );

  std::vector<double>  d_vec1{ 1.0, 2.1, 3.2 };
  auto v10= (_x6= d_vec1);
  for( auto const d : v10.val ) std::cout << d << "  ";
  std::cout << "\n";
  d_vec_f( v10 );
}
