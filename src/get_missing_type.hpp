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

#ifndef NAFTO_GET_MISSING_TYPE_HPP
#define NAFTO_GET_MISSING_TYPE_HPP

#include "nafto_types.hpp"
#include "foldl.hpp"
#include "bitptr2t.hpp"
#include "eval_set.hpp"
#include "flagsTchar.hpp"
#include <type_traits>





namespace nafto
{
namespace detail
{


  template<class V1, class V2,class tagT>
  struct get_missing_type_fold_f2;


  template<flagsT bitptr1,flagsT setflag1,class T1,
           flagsT bitptr2,flagsT setflag2,class T2>
  struct get_missing_type_fold_f2<bitptr2t<bitptr1,setflag1,T1>,
                                  bitptr2t<bitptr2,setflag2,T2>,
                                  taglist_tag >
  {
    enum : flagsT { as1= ( setflag1 & 1 ),
                    as2= ( setflag2 & 1 ),
                    am1= ( setflag1 & 2 ),
                    am2= ( setflag2 & 2 ),
                    om1= ( setflag1 & 4 ) & (as2 << 2),
                    om2= ( setflag2 & 4 ) & (as1 << 2),
                    as=  as1 & as2,
                    am=  am1 & am2,
                    om=  om1 ^ om2 };
    using fwd_t= std::conditional_t<bool(om1),T1,T2>;
    using type= bitptr2t<bitptr2,(as+am+om),fwd_t>;
  };





  template<flagsT bitptr1,flagsT setflag1,class T1,
           flagsT bitptr2,flagsT setflag2,class T2>
  struct get_missing_type_fold_f2<bitptr2t<bitptr1,setflag1,T1>,
                                  bitptr2t<bitptr2,setflag2,T2>,
                                  ortags_tag >
  {
    enum : flagsT { as1= ( setflag1 & 1 ),
                    as2= ( setflag2 & 1 ),
                    am1= ( setflag1 & 2 ),
                    am2= ( setflag2 & 2 ),
                    om1= ( setflag1 & 4 ),
                    om2= ( setflag2 & 4 ),
                    as=  as1 | as2,
                    am=  am1 & am2,
                    om=  ( om1 | om2 ) & ((am^2)<<1) };
    enum : bool { tf = ( bool(om1) && !bool(am1) ) || !bool(om2) };
    using fwd_t= std::conditional_t<tf,T1,T2>;
    using type= bitptr2t<bitptr2,(as+am+om),fwd_t>;
  };


  template<class T>
  struct promote_bits;

  template<flagsT bitptr,flagsT setflag,class T1>
  struct promote_bits<bitptr2t<bitptr,setflag,T1> >
  {
    enum : flagsT { allset=     setflag & 1,
                    allmissing= (allset^1) << 1,
                    onemissing= allmissing << 1 };
    using type= bitptr2t<bitptr,(allset+allmissing+onemissing),T1>;
  };


  /// bit0 is set if all parameters were submitted.
  /// bit1 is set if no parameter at all was submitted.
  /// bit2 is set if exactly one parameter is missing.
  template<flagsT flags, class taglst>
  struct get_missing_type
  {
    template<class V,class T1>
    using F1=
      promote_bits<typename eval_set<flags,V,T1,true>::type>;
    //
    using result= foldl2_t<bitptr2t<1,0>,
                           F1,get_missing_type_fold_f2,taglst>;
    //
    enum : bool
      { allset=  ( result::set_flag & 1 ) == 1,
        nonset=  ( result::set_flag & 2 ) == 2,
        onemsng= ( result::set_flag & 4 ) == 4 };
    //
    using type= typename result::type::type;
    //
    constexpr
    bool
    operator()()   { return onemsng && (!allset); }
  };






} //  namespace detail
} //  namespace nafto_types




#endif // NAFTO_GET_MISSING_TYPE_HPP
