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

#include "bin_func01.hpp"


#include <iostream>
#include <chrono>


int
main()
{
  using  d_two_log_t= bin_func<double,log,log>;
  using  vec_t=  std::vector<double>;
  //
  size_t const    n_result_vals= 1234;
  size_t const    n_outer= 200000;
  size_t const    n_inner= 512;
  vec_t                result_vec1( n_result_vals );
  vec_t                result_vec2( n_result_vals );

  d_two_log_t  t_l( 3.2, 0.76, -4.987 );

  size_t  ct= 0;
  auto start_time = std::chrono::high_resolution_clock::now();
  for( size_t c1= 0; c1 < n_outer; ++c1 )
  {
    double const x= 0.023 + c1 * 1.234;
    for( size_t c2= 0; c2 < n_inner; ++c2 )
    {
      double const y= 2.456 + c2 * 0.789;
      result_vec1[ct%n_result_vals]= t_l( x, y );
      ++ct;
    }
  } // for c1
  auto mid_time = std::chrono::high_resolution_clock::now();

  ct= 0;
  for( size_t c1= 0; c1 < n_outer; ++c1 )
  {
    double const x= 0.023 + c1 * 1.234;
    auto t_l1= t_l.set( _x= x );
    for( size_t c2= 0; c2 < n_inner; ++c2 )
    {
      double const y= 2.456 + c2 * 0.789;
      result_vec2[ct%n_result_vals]= t_l1( y );
      ++ct;
    }
  } // for c1
  auto end_time = std::chrono::high_resolution_clock::now();


  for( size_t c2= 0; c2 < n_result_vals; ++c2 )
  {
    std::cout << result_vec1[c2] << "\t" << result_vec2[c2] << "\n";
  }

  std::chrono::duration<double> diff1 = mid_time - start_time;
  std::chrono::duration<double> diff2 = end_time - mid_time;
  std::cout << "Duration: " << diff1.count() << "s versus "
            << diff2.count() << "s\n";
} // main
