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

#ifndef NAFTO_SERIALIZE_TAGLIST_HPP
#define NAFTO_SERIALIZE_TAGLIST_HPP


#include "nafto_types.hpp"
//#include "concat_taglists.hpp"
#include "append_taglist.hpp"
#include "foldl.hpp"






namespace nafto
{

namespace detail
{
  template<class T>
  struct serialize_taglist
  {
    using type= foldl_t<taglist<>,append_taglist,T>;
  };


  template<class T>
  using serialize_taglist_t= typename serialize_taglist<T>::type;


} //  namespace detail
} //  namespace nafto_types




#endif // NAFTO_SERIALIZE_TAGLIST_HPP
