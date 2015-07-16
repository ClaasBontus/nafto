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

#ifndef NAFTO_BITPTR2T_HPP
#define NAFTO_BITPTR2T_HPP




namespace nafto
{
namespace detail
{

  struct empty_t {};


  template<flagsT bitptr, flagsT setflag,class T=empty_t>
  struct bitptr2t
  {
    enum : flagsT { bit_ptr= bitptr, set_flag= setflag };
    //
    using type= T;
  };



} //  namespace detail
} //  namespace nafto_types



#endif // NAFTO_BITPTR2T_HPP
