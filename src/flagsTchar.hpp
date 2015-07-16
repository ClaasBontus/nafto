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

#ifndef NAFTO_FLAGSTCHAR_HPP
#define NAFTO_FLAGSTCHAR_HPP

#include "nafto_types.hpp"
#include <limits>


namespace nafto
{

namespace detail
{


  inline
  constexpr
  flagsT
  ct_bits( flagsT val )
  {
    return ( val == 0 ) ?  0 :
           ( (val >= 255) ? (8+ct_bits(val>>8)) : (1+ct_bits(val>>1) ) );
  }

  struct flagsTchar
  {
    enum : flagsT { max=           std::numeric_limits<flagsT>::max(),
                    n_bits=        ct_bits(max) };
  };




} //  namespace detail

} //  namespace nafto



#endif // NAFTO_FLAGSTCHAR_HPP
