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

#ifndef NAFTO_COUNT_MEMBER_HPP
#define NAFTO_COUNT_MEMBER_HPP

#include "nafto_types.hpp"


namespace nafto
{
namespace detail
{



  template<class T>
  struct count_member;

  template<class ... T>
  struct count_member<taglist<T...> >
  {
    constexpr
    flagsT
    operator()() { return (sizeof...(T)); }
  };


} //  namespace detail
} //  namespace nafto_types



#endif // NAFTO_COUNT_MEMBER_HPP
