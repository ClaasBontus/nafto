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

#ifndef NAFTO_COMP_RETURN_TYPE_HPP
#define NAFTO_COMP_RETURN_TYPE_HPP



#include "nafto_types.hpp"
#include "nafto_proxy_fwd.hpp"
#include "type2idx.hpp"


namespace nafto
{

  namespace detail
  {

    template<class  baseT,
             class  tagT,
             class  taglst,
             flagsT flags,
             class  taglst_chars>
    struct comp_return_type
    {
      using ser_taglst=          typename taglst_chars::ser_taglist;
      //
      static constexpr maybe_n idx_h=
          detail::type2idx<ser_taglst, tagT>().get_idx_unchecked();
      //
      enum : flagsT { idx=     (idx_h.valid()) ? idx_h.value() : 0,
                      one_h1= ((idx_h.valid()) ? 1 : 0) };
      //
      typedef nafto_proxy<baseT, taglst,
                          (flags | (one_h1 << idx)),
                          taglst_chars> type;
    };

    template<class  baseT, class  tagT, class  taglst,
             flagsT flags, class  taglst_chars>
    constexpr maybe_n
    comp_return_type<baseT,tagT,taglst,flags,taglst_chars>::idx_h;

  } // namespace detail

} //  namespace nafto



#endif // NAFTO_COMP_RETURN_TYPE_HPP
