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

#ifndef NAFTO_TYPE2IDX_HPP
#define NAFTO_TYPE2IDX_HPP


#include <cstddef>
#include <type_traits>
#include "nafto_types.hpp"
#include "maybe_n.hpp"
#include "get_embedded_type.hpp"
#include "foldl.hpp"


namespace nafto
{
namespace detail
{

  template<flagsT cnt=0,bool fnd=false,flagsT idx=0>
  struct idx2t
  {
    enum : bool   { found= fnd };
    enum : flagsT { count= cnt, fnd_idx= idx };
  };



  template<class T,class V,class T1>
  struct cmp_types;


  template<class T,class T1,flagsT cnt,bool fnd,flagsT idx>
  struct cmp_types<T,idx2t<cnt,fnd,idx>,T1>
  {
    using embedded_headT= typename get_embedded_type<T1>::type;
    //
    enum : bool { flag= std::is_same<       T,embedded_headT>::value
                     || std::is_convertible<T,embedded_headT>::value };
    //
    using type= idx2t<cnt+1, flag || fnd, (flag ? cnt : idx)>;
    //
    static_assert( !flag || !fnd, "Type occurs twice in taglist" );
  };



  template<class typelst, class T>
  struct type2idx
  {
    template<class V,class T1>
    using cmpF=   cmp_types<T,V,T1>;
    //
    using idx_h=  foldl_t<idx2t<0,false,0>,cmpF,typelst>;

    static constexpr maybe_n  idx{ idx_h::found, idx_h::fnd_idx };
    //
    constexpr
    flagsT
    get_idx()
    {
      static_assert( idx.valid(), "Type is not a member of taglist" );
      return idx.value();
    }
    //
    constexpr
    maybe_n
    get_idx_unchecked()
    {
      return idx;
    }
  }; // struct type2idx



} //  namespace detail
} //  namespace nafto



#endif // NAFTO_TYPE2IDX_HPP
