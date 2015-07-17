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

#ifndef NAFTO_FLAGLIST_UTILS_HPP
#define NAFTO_FLAGLIST_UTILS_HPP


#include "nafto_types.hpp"
#include "type2idx.hpp"



namespace nafto
{
namespace detail
{


  template<class tagT, class ser_taglst>
  struct flaglist_utils_helper
  {
    static constexpr maybe_n idx1=
        detail::type2idx<ser_taglst, tagT>().get_idx_unchecked();
  };

  template<class tagT, class ser_taglst>
  constexpr maybe_n flaglist_utils_helper<tagT,ser_taglst>::idx1;


  template<class ser_taglst, flagsT flags>
  struct flaglist_utils
  {
    template<class tagT>
    using helper= flaglist_utils_helper<tagT, ser_taglst>;
    //
    template <class T>
    constexpr bool
    flag( T ) const
    {
      using helper_t= helper<T>;
      static_assert( helper_t::idx1.valid(),
                     "Tag is not a member of taglists" );

      return ( ( flags & (1 << (helper_t::idx1.value())  ) ) != 0 );
    }
  }; // struct flaglist_utils





} // namespace detail
} // namespace nafto




#endif // NAFTO_FLAGLIST_UTILS_HPP
