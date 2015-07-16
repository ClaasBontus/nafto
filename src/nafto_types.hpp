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

#ifndef NAFTO_TYPES_HPP
#define NAFTO_TYPES_HPP


#include <cstddef>
#include <cstdint>
#include <type_traits>


namespace nafto
{

  using flagsT = uintmax_t;



  template<class ... T>
  struct taglist
  {};

  struct  obligatory_tag {};
  struct  optional_tag {};

  template<class T,class opt_param=obligatory_tag>
  struct tag_entry
  {
    using type= T;
    constexpr static bool optional= std::is_same<opt_param,optional_tag>()();
  };


  template<class nameT, class ... tagT>
  struct or_tags
  {};



} //  namespace nafto



#endif // NAFTO_TYPES_HPP
