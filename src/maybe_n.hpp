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

#ifndef NAFTO_MAYBE_N_HPP
#define NAFTO_MAYBE_N_HPP

#include "nafto_types.hpp"

namespace nafto
{

namespace detail
{


  struct maybe_n
  {
    constexpr
    maybe_n( bool valid, flagsT n= 0 ) : vlid(valid), vlue( n ) {}
    //
    constexpr
    bool
    valid() { return vlid; }
    //
    constexpr
    flagsT
    value() { return vlue; }
    //
    const bool    vlid;
    const flagsT  vlue;
  };


} // namespace detail

} // namespace nafto



#endif // NAFTO_MAYBE_N_HPP
