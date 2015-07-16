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

#ifndef NAFTO_APPEND_TAGLIST_HPP
#define NAFTO_APPEND_TAGLIST_HPP


# include "nafto_types.hpp"


namespace nafto
{

namespace detail
{

  template<class ... T>
  struct append_taglist;


  template<class ... T1>
  struct append_taglist<taglist<T1...> >
  {
    using type= taglist<T1...>;
  };


  template<class ... T1,class T>
  struct append_taglist<taglist<T1...>,T >
  {
    using type= taglist<T1...,T>;
  };




} //  namespace detail
} //  namespace nafto



#endif // NAFTO_APPEND_TAGLIST_HPP
