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

#include "nafto_types.hpp"
#include "check_or_branches.hpp"


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
struct U03{};


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

  using or1= nafto::or_tags<U01,nafto::taglist<T03,T04>,
                                nafto::taglist<T05,T06,T07> >;
  using or2= nafto::or_tags<U02,nafto::taglist<T10,or1,T11>,
                                nafto::taglist<T12,T13,T14>,
                                nafto::taglist<T15,T16> >;
  using or3= nafto::or_tags<U03,nafto::taglist<T03>,
                                nafto::taglist<T04> >;

  using L2=  nafto::taglist<T01,T02,or1,T08,T09>;
  using L3=  nafto::taglist<T01,T02,or2,T08,T09>;
  using L4=  nafto::taglist<or3>;

  using r1_0= typename nafto::detail::check_or_branches_h<0,L1>::result;
  using r1_1= typename nafto::detail::check_or_branches_h<1,L1>::result;
  using r1_2= typename nafto::detail::check_or_branches_h<2,L1>::result;
  using r1_3= typename nafto::detail::check_or_branches_h<3,L1>::result;
  static_assert( (r1_0::set_flag & 2) == 0, "" );
  static_assert( (r1_1::set_flag & 2) == 0, "" );
  static_assert( (r1_2::set_flag & 2) == 0, "" );
  static_assert( (r1_3::set_flag & 2) == 0, "" );

  using r2_000= typename nafto::detail::check_or_branches_h<0,L2>::result;
  using r2_001= typename nafto::detail::check_or_branches_h<1,L2>::result;
  using r2_002= typename nafto::detail::check_or_branches_h<2,L2>::result;
  using r2_004= typename nafto::detail::check_or_branches_h<4,L2>::result;
  using r2_008= typename nafto::detail::check_or_branches_h<8,L2>::result;
  using r2_016= typename nafto::detail::check_or_branches_h<16,L2>::result;
  using r2_032= typename nafto::detail::check_or_branches_h<32,L2>::result;
  using r2_064= typename nafto::detail::check_or_branches_h<64,L2>::result;
  using r2_128= typename nafto::detail::check_or_branches_h<128,L2>::result;
  using r2_256= typename nafto::detail::check_or_branches_h<256,L2>::result;

  using r2_020=
    typename nafto::detail::check_or_branches_h<0b10100,L2>::result;
  using r2_040=
    typename nafto::detail::check_or_branches_h<0b101000,L2>::result;
  using r2_399=
    typename nafto::detail::check_or_branches_h<0b110001111,L2>::result;
  using r2_499=
    typename nafto::detail::check_or_branches_h<0b111110011,L2>::result;
  using r2_507=
    typename nafto::detail::check_or_branches_h<0b111111011,L2>::result;

  static_assert( (r2_000::set_flag & 2) == 0, "" );
  static_assert( (r2_001::set_flag & 2) == 0, "" );
  static_assert( (r2_002::set_flag & 2) == 0, "" );
  static_assert( (r2_004::set_flag & 2) == 0, "" );
  static_assert( (r2_008::set_flag & 2) == 0, "" );
  static_assert( (r2_016::set_flag & 2) == 0, "" );
  static_assert( (r2_032::set_flag & 2) == 0, "" );
  static_assert( (r2_064::set_flag & 2) == 0, "" );
  static_assert( (r2_128::set_flag & 2) == 0, "" );
  static_assert( (r2_256::set_flag & 2) == 0, "" );

  static_assert( (r2_020::set_flag & 2) == 2, "" );
  static_assert( (r2_040::set_flag & 2) == 2, "" );
  static_assert( (r2_399::set_flag & 2) == 0, "" );
  static_assert( (r2_499::set_flag & 2) == 0, "" );
  static_assert( (r2_507::set_flag & 2) == 2, "" );

  using r3_00000= typename nafto::detail::check_or_branches_h<0,L3>::result;
  using r3_00001= typename nafto::detail::check_or_branches_h<1,L3>::result;
  using r3_00002= typename nafto::detail::check_or_branches_h<2,L3>::result;
  using r3_00004= typename nafto::detail::check_or_branches_h<4,L3>::result;
  using r3_00008= typename nafto::detail::check_or_branches_h<8,L3>::result;
  using r3_00016= typename nafto::detail::check_or_branches_h<16,L3>::result;
  using r3_00032= typename nafto::detail::check_or_branches_h<32,L3>::result;
  using r3_00064= typename nafto::detail::check_or_branches_h<64,L3>::result;
  using r3_00128= typename nafto::detail::check_or_branches_h<128,L3>::result;
  using r3_00256= typename nafto::detail::check_or_branches_h<256,L3>::result;
  using r3_00512= typename nafto::detail::check_or_branches_h<512,L3>::result;
  using r3_01024=
    typename nafto::detail::check_or_branches_h<0b10000000000,L3>::result;
  using r3_02048=
    typename nafto::detail::check_or_branches_h<0b100000000000,L3>::result;
  using r3_04096=
    typename nafto::detail::check_or_branches_h<0b1000000000000,L3>::result;
  using r3_08192=
    typename nafto::detail::check_or_branches_h<0b10000000000000,L3>::result;
  using r3_16384=
    typename nafto::detail::check_or_branches_h<0b100000000000000,L3>::result;
  using r3_32768=
    typename nafto::detail::check_or_branches_h<0b1000000000000000,L3>::result;

  using r3_00040=
    typename nafto::detail::check_or_branches_h<0b101000,L3>::result;
  using r3_00080=
    typename nafto::detail::check_or_branches_h<0b1010000,L3>::result;
  using r3_00287=
    typename nafto::detail::check_or_branches_h<0b100011111,L3>::result;
  using r3_00516=
    typename nafto::detail::check_or_branches_h<0b1000000100,L3>::result;
  using r3_03619=
    typename nafto::detail::check_or_branches_h<0b111000100011,L3>::result;
  using r3_04104=
    typename nafto::detail::check_or_branches_h<0b1000000001000,L3>::result;
  using r3_03587=
    typename nafto::detail::check_or_branches_h<0b111000000011,L3>::result;
  using r3_07683=
    typename nafto::detail::check_or_branches_h<0b1111000000011,L3>::result;
  using r3_49439=
    typename nafto::detail::check_or_branches_h<0b1100000100011111,L3>::result;

  static_assert( (r3_00000::set_flag & 2) == 0, "" );
  static_assert( (r3_00001::set_flag & 2) == 0, "" );
  static_assert( (r3_00002::set_flag & 2) == 0, "" );
  static_assert( (r3_00004::set_flag & 2) == 0, "" );
  static_assert( (r3_00008::set_flag & 2) == 0, "" );
  static_assert( (r3_00016::set_flag & 2) == 0, "" );
  static_assert( (r3_00032::set_flag & 2) == 0, "" );
  static_assert( (r3_00064::set_flag & 2) == 0, "" );
  static_assert( (r3_00128::set_flag & 2) == 0, "" );
  static_assert( (r3_00256::set_flag & 2) == 0, "" );
  static_assert( (r3_00512::set_flag & 2) == 0, "" );
  static_assert( (r3_01024::set_flag & 2) == 0, "" );
  static_assert( (r3_02048::set_flag & 2) == 0, "" );
  static_assert( (r3_04096::set_flag & 2) == 0, "" );
  static_assert( (r3_08192::set_flag & 2) == 0, "" );
  static_assert( (r3_16384::set_flag & 2) == 0, "" );
  static_assert( (r3_32768::set_flag & 2) == 0, "" );

  static_assert( (r3_00040::set_flag & 2) == 2, "" );
  static_assert( (r3_00080::set_flag & 2) == 2, "" );
  static_assert( (r3_00287::set_flag & 2) == 0, "" );
  static_assert( (r3_00516::set_flag & 2) == 2, "" );
  static_assert( (r3_03619::set_flag & 2) == 2, "" );
  static_assert( (r3_03587::set_flag & 2) == 0, "" );
  static_assert( (r3_04104::set_flag & 2) == 2, "" );
  static_assert( (r3_07683::set_flag & 2) == 2, "" );
  static_assert( (r3_49439::set_flag & 2) == 0, "" );

  using r4_00000= typename nafto::detail::check_or_branches_h<0,L4>::result;
  using r4_00001= typename nafto::detail::check_or_branches_h<1,L4>::result;
  using r4_00002= typename nafto::detail::check_or_branches_h<2,L4>::result;
  using r4_00003= typename nafto::detail::check_or_branches_h<3,L4>::result;

  static_assert( (r4_00000::set_flag & 2) == 0, "" );
  static_assert( (r4_00001::set_flag & 2) == 0, "" );
  static_assert( (r4_00002::set_flag & 2) == 0, "" );
  static_assert( (r4_00003::set_flag & 2) == 2, "" );
}
