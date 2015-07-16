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

#ifndef NAFTO_ALL_SET_HPP
#define NAFTO_ALL_SET_HPP

#include "nafto_types.hpp"
#include "foldl.hpp"
#include "bitptr2t.hpp"
#include "eval_set.hpp"






namespace nafto
{
namespace detail
{


  template<class V1, class V2,class tagT>
  struct all_set_fold_f2;



  template<flagsT bitptr1,flagsT setflag1,class T1,
           flagsT bitptr2,flagsT setflag2,class T2>
  struct all_set_fold_f2<bitptr2t<bitptr1,setflag1,T1>,
                         bitptr2t<bitptr2,setflag2,T2>,
                         ortags_tag >
  {
    using type= bitptr2t<bitptr2,flagsT(setflag1 || setflag2),T2>;
  };


  template<flagsT bitptr1,flagsT setflag1,class T1,
           flagsT bitptr2,flagsT setflag2,class T2>
  struct all_set_fold_f2<bitptr2t<bitptr1,setflag1,T1>,
                         bitptr2t<bitptr2,setflag2,T2>,
                         taglist_tag >
  {
    using type= bitptr2t<bitptr2,flagsT(setflag1 && setflag2),T2>;
  };



  template<flagsT flags, class taglst>
  struct all_set
  {
    template<class V,class T1>
    using F1= eval_set<flags,V,T1,true>;
    //
    using result= foldl2_t<bitptr2t<1,flagsT(true)>,
                           F1,all_set_fold_f2,taglst>;
    //
    constexpr
    bool
    operator()()   { return result::set_flag; }
  };


} //  namespace detail
} //  namespace nafto_types


#endif // NAFTO_ALL_SET_HPP
