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

#ifndef NAFTO_CHECK_OR_BRANCHES
#define NAFTO_CHECK_OR_BRANCHES

#include "nafto_types.hpp"
#include "nafto_proxy_fwd.hpp"
#include "foldl.hpp"
#include "bitptr2t.hpp"
#include "eval_set.hpp"




namespace nafto
{



namespace detail
{


  template<class V1, class V2,class tagT>
  struct check_or_branches_f2;



  template<flagsT bitptr1,flagsT setflag1,class T1,
           flagsT bitptr2,flagsT setflag2,class T2>
  struct check_or_branches_f2<bitptr2t<bitptr1,setflag1,T1>,
                              bitptr2t<bitptr2,setflag2,T2>,
                              taglist_tag >
  {
    using type= bitptr2t<bitptr2,(setflag1 | setflag2),T2>;
  };


  template<flagsT bitptr1,flagsT setflag1,class T1,
           flagsT bitptr2,flagsT setflag2,class T2>
  struct check_or_branches_f2<bitptr2t<bitptr1,setflag1,T1>,
                              bitptr2t<bitptr2,setflag2,T2>,
                              ortags_tag >
  {
    enum : flagsT
    { h1= ( (setflag1&1) | (setflag2&1) ), // at least one in each branch
      h2= ( (setflag1&1) & (setflag2&1) ), // one in both branches
      h3= ( (setflag1&2) | (setflag2&2) ), // forward errors
      errbit= flagsT( h2 || h3 ) * 2 };
    using type= bitptr2t<bitptr2,(h1 + errbit),T2>;
  };


  /// For the second template-int of the bitptr2t:
  /// bit0 is set if at least one parameter was submitted for the taglst
  /// currently under investigation.
  /// bit1 is set if parameters in two different or_tags branches were
  /// submitted, i.e. bit1 indicates an error.
  template<flagsT flags, class taglst>
  struct check_or_branches_h
  {
    template<class V,class T1>
    using F1= eval_set<flags,V,T1,false>;
    //
    using result= foldl2_t<bitptr2t<1,0>,F1,check_or_branches_f2,taglst>;
  };


  /// \brief Checks if values in different branches of or_tags
  /// were submitted.
  template<class T>
  struct check_or_branches;

  template<class baseT, class taglst, flagsT flags, class taglst_chars>
  struct check_or_branches<nafto_proxy<baseT,taglst,flags,taglst_chars> >
  {
    using result= typename check_or_branches_h<flags,taglst>::result;
    //
    constexpr
    bool
    operator()()   { return ( ( result::set_flag & 2 ) == 0 ); }
  };



} //  namespace detail
} //  namespace nafto_types



#endif // NAFTO_CHECK_OR_BRANCHES
