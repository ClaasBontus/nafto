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

#ifndef NAFTO_TAGLIST_CHARS_HPP
#define NAFTO_TAGLIST_CHARS_HPP

#include "nafto_types.hpp"
#include "serialize_taglist.hpp"
#include "count_member.hpp"





namespace nafto
{
namespace detail
{

template<class taglst,
         class ser_taglst= detail::serialize_taglist_t<taglst> >
struct taglist_chars
{
    using  ser_taglist=           ser_taglst;
    //
    constexpr static flagsT  n_params= count_member<ser_taglist>()();
}; // struct taglist_chars


} // namespace detail
} //  namespace nafto




#endif // NAFTO_TAGLIST_CHARS_HPP
