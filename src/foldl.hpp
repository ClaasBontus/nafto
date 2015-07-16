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

#ifndef NAFTO_FOLDL_HPP
#define NAFTO_FOLDL_HPP


#include "nafto_types.hpp"


namespace nafto
{
namespace detail
{


struct taglist_tag {};
struct ortags_tag  {};


template<class T1,class T2,class>
struct id2
{
  using type= T2;
};





template<class V,template<class ...> class F1,template<class ...> class F2,
         class T>
struct foldl2
{
  using type= typename F1<V,T>::type;
};



template<class V,template<class ...> class F1,template<class ...> class F2>
struct foldl2<V,F1,F2,taglist<> >
{
  using type= V;
};


template<class V,template<class ...> class F1,template<class ...> class F2,
         class nameT, class orT>
struct foldl2<V,F1,F2,or_tags<nameT, orT> >
{
  using type= typename foldl2<V,F1,F2,orT>::type;
};


template<class V, template<class ...> class F1,template<class ...> class F2,
         class nameT, class orT1, class ... orT>
struct foldl2<V,F1,F2,or_tags<nameT, orT1, orT...> >
{
  using f1=   typename foldl2<V, F1,F2,orT1>::type;
  using f2=   typename foldl2<f1,F1,F2,or_tags<nameT,orT...> >::type;
  using type= typename F2<f1,f2,ortags_tag>::type;
};


template<class V,template<class ...> class F1,template<class ...> class F2,
         class T>
struct foldl2<V,F1,F2,taglist<T> >
{
  using type= typename foldl2<V,F1,F2,T>::type;
};


template<class V,template<class ...> class F1,template<class ...> class F2,
         class T1, class ... T>
struct foldl2<V,F1,F2,taglist<T1,T...> >
{
  using f1=   typename foldl2<V, F1,F2,T1>::type;
  using f2=   typename foldl2<f1,F1,F2,taglist<T...> >::type;
  using type= typename F2<f1,f2,taglist_tag>::type;
};




template<class V,template<class ...> class F,class T>
struct foldl
{
  using type= typename foldl2<V,F,id2,T>::type;
};



template<class V,template<class ...> class F1,template<class ...> class F2,
         class T>
using foldl2_t= typename foldl2<V,F1,F2,T>::type;


template<class V,template<class ...> class F,class T>
using foldl_t= typename foldl<V,F,T>::type;




} //  namespace detail
} //  namespace nafto_types




#endif // NAFTO_FOLDL_HPP
