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
#include <string>
#include <chrono>


using                 int_t_1= nafto::integral_wrap_t<1>;
using                 int_t_2= nafto::integral_wrap_t<2>;

template<class T> using int_val_1=  int_t_1::type<T>;
template<class T> using int_val_2=  int_t_2::type<T>;

constexpr auto          _x1=      int_t_1()();
constexpr auto          _x2=      int_t_2()();


template<class T>
using two_ints_t= nafto::taglist<int_val_1<T>,int_val_2<T> >;

template<class T>
class s_a : public nafto::nafto_proxy<s_a<T>,two_ints_t<T> >
{
  MAKE_FRIEND_OF_NAFTO
  //
public:
  s_a() : nafto::nafto_proxy<s_a<T>,two_ints_t<T> >( this )
  {}
  //
  std::string
  operator()( T i1, T i2 )
  {
    return l1
         + std::to_string(i1)
         + c1
         + std::to_string(i2)
         + r1;
  }
  //
private:
  using  one_t= typename int_val_1<T>::type;
  using  two_t= typename int_val_2<T>::type;
  //
  std::string  l1= "first int: ";
  std::string  c1= ", second int: ";
  std::string  r1= " Yippee!";
  //
  struct
  {
    std::string  lft;
    std::string  rht;
  } p;
  //
  std::string
  operator()() const
  {
    return p.lft + p.rht;
  }
  //
  template<class flagLstT>
  void
  set_val( const one_t &i1, flagLstT  )
  {
    p.lft= l1 + std::to_string(i1.val) + c1;
  }
  //
  template<class flagLstT>
  void
  set_val( const two_t &i2, flagLstT  )
  {
    p.rht= std::to_string(i2.val) + r1;
  }
  //
  decltype(auto)
  clone_impl()
  {
    s_a<T>  cp_this;
    cp_this.p= p;
    return cp_this;
  }
  //
}; // class s_a





int
main()
{
  using i_s_a= s_a<int>;
  using vec_t= std::vector<std::string>;

  size_t  store_n_vec= 55;

  i_s_a   isa;
  vec_t   result_vec1( store_n_vec );
  vec_t   result_vec2( store_n_vec );

  constexpr int n_loops= 2000;
  constexpr int n_inner= 1234;

  size_t  cnt= 0;
  auto start_time = std::chrono::high_resolution_clock::now();
  for( int ct= 0; ct < n_loops; ++ct )
  {
    for( int c2= 0; c2 < n_inner; ++c2 )
    {
      result_vec1[cnt%store_n_vec]= isa( ct, c2 );
      ++cnt;
    }
  }
  auto mid_time = std::chrono::high_resolution_clock::now();

  cnt= 0;
  for( int ct= 0; ct < n_loops; ++ct )
  {
    auto isa2= isa.set( _x1= ct );
    for( int c2= 0; c2 < n_inner; ++c2 )
    {
      result_vec2[cnt%store_n_vec]= isa2.set( _x2= c2 )();
      ++cnt;
    }
  }
  auto end_time = std::chrono::high_resolution_clock::now();

  for( size_t c= 0; c < store_n_vec; ++ c )
  {
    std::cout << result_vec1[c] << "\t"
              << result_vec2[c]
              << "\n";
  }
  std::chrono::duration<double> diff1 = mid_time - start_time;
  std::chrono::duration<double> diff2 = end_time - mid_time;
  std::cout << "Duration: " << diff1.count() << "s versus "
            << diff2.count()
            << "s\n";

  return 0;
}
