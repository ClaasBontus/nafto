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

#ifndef NAFTO_EVAL_SET_HPP
#define NAFTO_EVAL_SET_HPP

#include "bitptr2t.hpp"
#include "get_embedded_type.hpp"



namespace nafto
{
namespace detail
{


  template<flagsT flags,class V,class T,bool chk_optional>
  struct eval_set;

  template<flagsT flags,class T,flagsT bitptr,flagsT setflag,class T1,
           bool chk_optional>
  struct eval_set<flags,bitptr2t<bitptr,setflag,T1>,T,chk_optional>
  {
    using embedded_t= get_embedded_type<T>;
    enum : bool { eval_opt= chk_optional && embedded_t::optional,
                  this_set= ((flags & bitptr) == bitptr),
                  this_ok=  this_set || eval_opt };
    using type= bitptr2t<(bitptr<<1),flagsT(this_ok),embedded_t>;
  };



} //  namespace detail
} //  namespace nafto_types



#endif // NAFTO_EVAL_SET_HPP
