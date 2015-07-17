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

#ifndef NAFTO_GET_EMBEDDED_TYPE_HPP
#define NAFTO_GET_EMBEDDED_TYPE_HPP

#include "nafto_types.hpp"
#include <type_traits>


namespace nafto
{
namespace detail
{

  template<class T> struct get_embedded_type;

  template<class T,class opt_param>
  struct get_embedded_type<tag_entry<T,opt_param> >
  {
    using type= T;
    enum : bool { optional= std::is_same<opt_param,optional_tag>()() };
  };


} // namespace detail
} // namespace nafto

#endif // NAFTO_GET_EMBEDDED_TYPE_HPP
