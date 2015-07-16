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

#ifndef NAFTO_CONCAT_TAGLISTS_HPP
#define NAFTO_CONCAT_TAGLISTS_HPP


# include "nafto_types.hpp"


namespace nafto
{

namespace detail
{

  template<class ... T>
  struct concat_taglists;



  template<>
  struct concat_taglists<>
  {
    using type= taglist<>;
  };

  template<>
  struct concat_taglists<taglist<> >
  {
    using type= taglist<>;
  };


  template<class ... T1>
  struct concat_taglists<taglist<T1...> >
  {
    using type= taglist<T1...>;
  };



  template<class ... T1, class ... tail>
  struct concat_taglists<taglist<T1...>, taglist<>, tail... >
  {
    using type=
      typename concat_taglists<
        taglist<T1...>,
        tail...
      >::type;
  };



  template<class ... T1, class head, class ... T2, class ... tail>
  struct concat_taglists<taglist<T1...>, taglist<head, T2...>, tail ... >
  {
    using type=
      typename concat_taglists<
        typename concat_taglists<taglist<T1...,head>, taglist<T2...> >::type,
        tail...
      >::type;
  };




} //  namespace detail
} //  namespace nafto


#endif // NAFTO_CONCAT_TAGLISTS_HPP
