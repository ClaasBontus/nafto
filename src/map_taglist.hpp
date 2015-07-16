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

#ifndef NAFTO_MAP_TAGLIST_HPP
#define NAFTO_MAP_TAGLIST_HPP


#include "nafto_types.hpp"






namespace nafto
{

namespace detail
{


  template<class F,class T>
  struct map
  {
    using type= typename F<T>::type;
  };



  template<class F>
  struct map<F,taglist<> >
  {
    using type= taglist<>;
  };


  template<class F,class nameT, class ... orT>
  struct map<F,or_tags<nameT,orT...> >
  {
    using type=
      or_tags<nameT,
              typename map<F,orT>::type... >;
  };


  template<class F,class ... T>
  struct map<F,taglist<T...> >
  {
    using type= taglist<typename map<F,T>::type... >;
  };


} //  namespace detail
} //  namespace nafto_types




#endif // NAFTO_MAP_TAGLIST_HPP
