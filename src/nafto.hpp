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

#ifndef NAFTO_HPP
#define NAFTO_HPP


#include "nafto_types.hpp"
#include "flaglist_utils.hpp"
#include "comp_return_type.hpp"
#include "all_set.hpp"
#include "check_or_branches.hpp"
#include "taglist_chars.hpp"
#include "flagsTchar.hpp"
#include "get_missing_type.hpp"
#include "clone_comprehension.hpp"

#include <iostream>
#include <stdexcept>


namespace nafto
{
  namespace detail
  {
    struct empty_ {};
  } // namespace detail


  template<class  baseT,
           class  taglst,
           flagsT flags= 0,
           class  taglst_chars= detail::taglist_chars<taglst> >
  class nafto_proxy
  {
  public:
    using miss_type_t=         detail::get_missing_type<flags,taglst>;
    enum : bool { enable_functor= miss_type_t()() };
    //
    // nafto_proxy( const nafto_proxy& )= default;
    // nafto_proxy( nafto_proxy&& )=      default;
    // nafto_proxy& operator=( const nafto_proxy& )=   default;
    // nafto_proxy& operator=( nafto_proxy&& )=        default;
    //
    decltype(auto)
    operator()()
    {
      static_assert( detail::all_set<flags, taglst>()(),
                     "Insufficient number of function arguments submitted" );
      return (*m_base)();
    }
    //
    template<class T>
    decltype(auto)
    operator()( T && val )
    {
      static_assert( enable_functor, "Cannot be used as a function object" );
      //TODO: Do we need to prevent eval on rvalue reference?
      return set( std::forward<typename miss_type_t::type>(val) )();
    }
    //
    template<class ...T>
    decltype(auto)
    set( T&&... tags  ) &
    {
      // Forward to private function for preventing
      // set getting invoked on an rvalue reference.

      return set_impl( std::forward<T>(tags)... );
    }
    //
    template<class unusedT=detail::empty_>
    decltype(auto)
    clone()
    {
      return
        typename
        detail::select_clone_type<flags,baseT,this_t>::
                                                  type( m_base->clone_impl() );
    }
    //
  protected:
    explicit nafto_proxy( baseT *parent ) : m_base( parent )
    {
      constexpr auto n_ser=  flagsT( taglst_chars::n_params );
      constexpr auto n_bits= flagsT( detail::flagsTchar::n_bits );
      static_assert( n_ser <= n_bits, "Too many tags in taglist" );
    }
    //
    // template<flagsT flgs>
    // using cp_this_type= nafto_proxy<baseT,taglst,flgs,taglst_chars>;
    //
    // template<flagsT flgs>
    // decltype(auto)
    // clone_type( baseT && base, const cp_this_type<flgs> &unused ) &
    // {
    //   return
    //     detail::
    //     clone_comprehension<baseT,
    //                         cp_this_type<flgs> >( std::forward<baseT>(base) );
    // }
    //
    // template<class ParentT>
    // baseT  *get_base_ptr( const ParentT &parent ) const
    // { return parent.m_base; }
    //
  private:
    using ser_taglst=     typename taglst_chars::ser_taglist;
    using this_t=         nafto_proxy<baseT,taglst,flags,taglst_chars>;
    //
    template<class bT, class tlt, flagsT, class sT>
    friend class nafto::nafto_proxy;
    //
    template<class bT,class proxyT>
    friend class nafto::detail::clone_comprehension;
    //
    baseT  *m_base;
    //
    template<class tagT>
    decltype(auto)
    set_impl( tagT &&tag )
    {
      using comp_return_t=
                  detail::comp_return_type<baseT, tagT, taglst,
                                           flags, taglst_chars>;
      using ret_t= typename comp_return_t::type;
      static_assert( comp_return_t::one_h1 == 1, "Tag not found in taglist" );
      static_assert( detail::check_or_branches<ret_t>()(),
                     "Values submitted in two different branches of or_tags" );
      m_base->set_val( std::forward<tagT>( tag ),
                       detail::flaglist_utils<ser_taglst, flags>() );
      return ret_t( m_base );
    }
    //
    template<class tagT1,class tagT2,class ...tail>
    decltype(auto)
    set_impl( tagT1 &&tag1, tagT2 &&tag2, tail&&... tags  )
    {
      return set_impl( std::forward<tagT1>(tag1) ).
             set_impl( std::forward<tagT2>(tag2), std::forward<tail>(tags)... );
    }
  }; // class nafto_proxy



} //  namespace nafto


#define MAKE_FRIEND_OF_NAFTO \
  template<class,class,nafto::flagsT,class>  friend class nafto::nafto_proxy;


#endif // NAFTO_HPP
