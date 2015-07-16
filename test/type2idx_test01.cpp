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

#include "type2idx.hpp"
#include "serialize_taglist.hpp"


struct S01{};
struct S02{};
struct S03{};
struct S04{};
struct S05{};
struct S06{};
struct S07{};
struct S08{};
struct S09{};
struct S10{};
struct S11{};
struct S12{};
struct S13{};
struct S14{};
struct S15{};
struct S16{};

struct U01{};
struct U02{};


int
main()
{
  using T01= nafto::tag_entry<S01>;
  using T02= nafto::tag_entry<S02>;
  using T03= nafto::tag_entry<S03>;
  using T04= nafto::tag_entry<S04>;
  using T05= nafto::tag_entry<S05>;
  using T06= nafto::tag_entry<S06>;
  using T07= nafto::tag_entry<S07>;
  using T08= nafto::tag_entry<S08>;
  using T09= nafto::tag_entry<S09>;
  using T10= nafto::tag_entry<S10>;
  using T11= nafto::tag_entry<S11>;
  using T12= nafto::tag_entry<S12>;
  using T13= nafto::tag_entry<S13>;
  using T14= nafto::tag_entry<S14>;
  using T15= nafto::tag_entry<S15>;
  using T16= nafto::tag_entry<S16>;

  using L1=  nafto::taglist<T01,T02>;
  using L1s= nafto::detail::serialize_taglist_t<L1>;

  using or1= nafto::or_tags<U01,nafto::taglist<T03,T04>,
                                nafto::taglist<T05,T06,T07> >;
  using or2= nafto::or_tags<U02,nafto::taglist<T10,or1,T11>,
                                nafto::taglist<T12,T13,T14>,
                                nafto::taglist<T15,T16> >;

  using L2=  nafto::taglist<T01,T02,or1,T08,T09>;
  using L3=  nafto::taglist<T01,T02,or2,T08,T09>;
  using L3s= nafto::detail::serialize_taglist_t<L3>;


  static_assert( nafto::detail::type2idx<L1,S01>().get_idx() == 0 ,"" );
  static_assert( nafto::detail::type2idx<L1,S02>().get_idx() == 1 ,"" );

  static_assert( nafto::detail::type2idx<L1s,S01>().get_idx() == 0 ,"" );
  static_assert( nafto::detail::type2idx<L1s,S02>().get_idx() == 1 ,"" );

  static_assert( nafto::detail::type2idx<L2,S01>().get_idx() == 0 ,"" );
  static_assert( nafto::detail::type2idx<L2,S02>().get_idx() == 1 ,"" );
  static_assert( nafto::detail::type2idx<L2,S03>().get_idx() == 2 ,"" );
  static_assert( nafto::detail::type2idx<L2,S04>().get_idx() == 3 ,"" );
  static_assert( nafto::detail::type2idx<L2,S05>().get_idx() == 4 ,"" );
  static_assert( nafto::detail::type2idx<L2,S06>().get_idx() == 5 ,"" );
  static_assert( nafto::detail::type2idx<L2,S07>().get_idx() == 6 ,"" );
  static_assert( nafto::detail::type2idx<L2,S08>().get_idx() == 7 ,"" );
  static_assert( nafto::detail::type2idx<L2,S09>().get_idx() == 8 ,"" );

  // Must not compile since S10 is not a member of L2
  //constexpr auto i2_09e= nafto::detail::type2idx<L2,S10>().get_idx();

  static_assert( nafto::detail::type2idx<L3,S01>().get_idx() == 0 ,"" );
  static_assert( nafto::detail::type2idx<L3,S02>().get_idx() == 1 ,"" );
  static_assert( nafto::detail::type2idx<L3,S10>().get_idx() == 2 ,"" );
  static_assert( nafto::detail::type2idx<L3,S03>().get_idx() == 3 ,"" );
  static_assert( nafto::detail::type2idx<L3,S04>().get_idx() == 4 ,"" );
  static_assert( nafto::detail::type2idx<L3,S05>().get_idx() == 5 ,"" );
  static_assert( nafto::detail::type2idx<L3,S06>().get_idx() == 6 ,"" );
  static_assert( nafto::detail::type2idx<L3,S07>().get_idx() == 7 ,"" );
  static_assert( nafto::detail::type2idx<L3,S11>().get_idx() == 8 ,"" );
  static_assert( nafto::detail::type2idx<L3,S12>().get_idx() == 9 ,"" );
  static_assert( nafto::detail::type2idx<L3,S13>().get_idx() == 10 ,"" );
  static_assert( nafto::detail::type2idx<L3,S14>().get_idx() == 11 ,"" );
  static_assert( nafto::detail::type2idx<L3,S15>().get_idx() == 12 ,"" );
  static_assert( nafto::detail::type2idx<L3,S16>().get_idx() == 13 ,"" );

  static_assert( nafto::detail::type2idx<L3s,S01>().get_idx() == 0 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S02>().get_idx() == 1 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S10>().get_idx() == 2 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S03>().get_idx() == 3 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S04>().get_idx() == 4 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S05>().get_idx() == 5 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S06>().get_idx() == 6 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S07>().get_idx() == 7 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S11>().get_idx() == 8 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S12>().get_idx() == 9 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S13>().get_idx() == 10 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S14>().get_idx() == 11 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S15>().get_idx() == 12 ,"" );
  static_assert( nafto::detail::type2idx<L3s,S16>().get_idx() == 13 ,"" );


  // Must not compile since T01 is used twice
  // using L1e=  nafto::taglist<T01,T01>;
  // using L1se= nafto::detail::serialize_taglist_t<L1e>;
  // constexpr auto i1e_01=  nafto::detail::type2idx<L1e,S01>().get_idx();
  // constexpr auto i1se_01= nafto::detail::type2idx<L1se,S01>().get_idx();
}
