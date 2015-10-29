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
#include <vector>
#include <numeric>
#include <chrono>

using base_nom_t=   nafto::ptr_pair_wrap_t<1>;
using base_denom_t= nafto::ptr_pair_wrap_t<2>;
template<class T> using nom_t=   typename base_nom_t::type<T>;
template<class T> using denom_t= typename base_denom_t::type<T>;
constexpr auto          _nom=    base_nom_t()();
constexpr auto          _denom=  base_denom_t()();


template<class T>
using vector_quotient_taglst_t= nafto::taglist<nom_t<T>,denom_t<T> >;



template<class T>
class vector_quotient : public nafto::nafto_proxy<vector_quotient<T>,
                                                  vector_quotient_taglst_t<T> >
{
  MAKE_FRIEND_OF_NAFTO
  //
public:
  using vec_t= std::vector<T>;
  using nom_type=   typename nom_t<T>::type;
  using denom_type= typename denom_t<T>::type;
  //
  vector_quotient() : nafto::nafto_proxy<vector_quotient<T>,
                                         vector_quotient_taglst_t<T> >( this )
  {}
  //
  T
  operator()( const vec_t & nom_vals, const vec_t & denom_vals )
  {
    auto const nom=
         std::accumulate( nom_vals.begin(), nom_vals.end(), T(0.0) );
    auto const de_nom=
         std::accumulate( denom_vals.begin(), denom_vals.end(), T(0.0) );
    return nom / de_nom;
  }
  //
private:
  struct
  {
    //T  nom_sum, inv_denom_sum;
    T  nom_sum, denom_sum;
  } p;
  //
  T
  operator()() const
  //{ return p.nom_sum * p.inv_denom_sum; }
  { return p.nom_sum / p.denom_sum; }
  //
  template<class flagLstT>
  void
  set_val( const nom_type &nom_vals, flagLstT  )
  {
    p.nom_sum=
         std::accumulate( nom_vals.val.first, nom_vals.val.second, T(0.0) );
  }
  //
  template<class flagLstT>
  void
  set_val( const typename denom_t<T>::type &denom_vals, flagLstT  )
  {
    p.denom_sum=
        std::accumulate( denom_vals.val.first, denom_vals.val.second, T(0.0));
    // p.inv_denom_sum=
    //      1.0 /
    //      std::accumulate( denom_vals.val.first, denom_vals.val.second, T(0.0));
  }
  //
  decltype(auto)
  clone_impl()
  {
    vector_quotient<T>  cp_this;
    cp_this.p= p;
    return cp_this;
  }
}; // class vector_quotient




int
main()
{
  using d_vq_t= vector_quotient<double>;
  using vec_t=  std::vector<double>;
  vec_t         v1, v2;
  constexpr size_t     n_nom_vecs= 7;
  constexpr size_t     n_denom_vecs= 5;
  std::vector<vec_t>   nom_vecs( n_nom_vecs );
  std::vector<vec_t>   denom_vecs( n_denom_vecs );
  vec_t                result_vec1( n_denom_vecs );
  vec_t                result_vec2( n_denom_vecs );
  d_vq_t               vq1;

  for( int c= 0; c < 1000; ++c )
  {
    v1.push_back( (c+1) * 1.01 );
    for( size_t c1= 0; c1 < n_nom_vecs; ++c1 )
    {
      nom_vecs[c1].push_back( (c+1) * 1.01 * pow( ( c1 + 1 ), 0.567 ) );
    }
  }

  double fac= 1.0;
  for( int c= 0; c < 2000; ++c )
  {
    v2.push_back( (c+1) * 0.998 * fac );
    for( size_t c2= 0; c2 < n_denom_vecs; ++c2 )
    {
      denom_vecs[c2].push_back( (c+1) * 0.998 * fac * pow( ( c2 + 1 ), 0.765 ));
    }
    fac= -fac;
  }

  auto  vq1_1= vq1.set( _nom= v1, _denom= v2 );
  std::cout << vq1( v1, v2 ) << " == " << vq1_1() << "\n";

  constexpr size_t n_loops= 80000;

  auto start_time = std::chrono::high_resolution_clock::now();
  for( size_t ct= 0; ct < n_loops; ++ct )
  {
    for( size_t c2= 0; c2 < n_denom_vecs; ++c2 )
    {
      result_vec1[c2]= vq1( nom_vecs[ct%n_nom_vecs], denom_vecs[c2] );
    }
  }
  auto mid_time = std::chrono::high_resolution_clock::now();

  for( size_t ct= 0; ct < n_loops; ++ct )
  {
    auto  vq1_2= vq1.set( _nom= nom_vecs[ct%n_nom_vecs] );
    for( size_t c2= 0; c2 < n_denom_vecs; ++c2 )
    {
      result_vec2[c2]= vq1_2.set( _denom= denom_vecs[c2] )();
    }
  }
  auto end_time = std::chrono::high_resolution_clock::now();


  for( size_t c2= 0; c2 < n_denom_vecs; ++c2 )
  {
    std::cout << result_vec1[c2] << "\t" << result_vec2[c2] << "\n";
  }

  std::chrono::duration<double> diff1 = mid_time - start_time;
  std::chrono::duration<double> diff2 = end_time - mid_time;
  std::cout << "Duration: " << diff1.count() << "s versus "
            << diff2.count() << "s\n";
} // main
