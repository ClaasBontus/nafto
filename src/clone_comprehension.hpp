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

#ifndef NAFTO_CLONE_COMPREHENSION_HPP
#define NAFTO_CLONE_COMPREHENSION_HPP


#include <utility>
#include <type_traits>
#include "nafto_types.hpp"


namespace nafto
{
  namespace detail
  {

    template<class baseT,class proxyT>
    class clone_comprehension
    {
    public:
      clone_comprehension( baseT && base )
      : m_base( base )
      , m_proxy( &m_base )
      {}
      //
      clone_comprehension( const clone_comprehension & )=            delete;
      clone_comprehension& operator=( const clone_comprehension & )= delete;
      clone_comprehension( clone_comprehension && )=                 default;
      clone_comprehension& operator=( clone_comprehension && )=      default;
      //
      decltype(auto)
      operator()()
      { return m_proxy(); }
      //
      template<class T>
      decltype(auto)
      operator()( T && val )
      { return m_proxy( std::forward<T>(val) ); }
      //
      template<class ...T>
      decltype(auto)
      set( T&&... tags  ) &
      { return m_proxy.set( std::forward<T>(tags)... ); }
    private:
      baseT   m_base;
      proxyT  m_proxy;
    }; // class clone_comprehension


    template<flagsT flags,class baseT,class proxyT>
    struct select_clone_type
    {
      using type= std::conditional_t<(flags==0),
                                     baseT,
                                     clone_comprehension<baseT,proxyT> >;
    };


  } // namespace detail
} // namespace nafto



#endif // NAFTO_CLONE_COMPREHENSION_HPP
