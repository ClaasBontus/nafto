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
#include "get_missing_type.hpp"
#include <iostream>
#include <type_traits>


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


template<class T>
void flags_out()
{
  std::cout << "allset= " << T::allset
            << ",  nonset= " << T::nonset
            << ",  onemsng= " << T::onemsng << "\n";
}


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
  using L2=  nafto::taglist<T01,T02,T03>;

  using or1= nafto::or_tags<U01,nafto::taglist<T03,T04>,
                                nafto::taglist<T05,T06,T07> >;
  using or2= nafto::or_tags<U02,nafto::taglist<T10,or1,T11>,
                                nafto::taglist<T12,T13,T14>,
                                nafto::taglist<T15,T16> >;
  using or3= nafto::or_tags<U03,nafto::taglist<T03>,
                                nafto::taglist<T04> >;

  using L3=  nafto::taglist<T01,T02,or1,T08,T09>;
  using L4=  nafto::taglist<T01,T02,or2,T08,T09>;
  using L5=  nafto::taglist<or3>;
  using L6=  nafto::taglist<T01,T02,or3>;
  using L7=  nafto::taglist<or3,T05,T06>;

  using m1a= nafto::detail::get_missing_type<0b01,L1>;
  using m1b= nafto::detail::get_missing_type<0b10,L1>;
  using m2a= nafto::detail::get_missing_type<0b011,L2>;
  using m2b= nafto::detail::get_missing_type<0b101,L2>;
  using m2c= nafto::detail::get_missing_type<0b110,L2>;
  using m3a= nafto::detail::get_missing_type<0b011,L3>;
  using m3b= nafto::detail::get_missing_type<0b110001110,L3>;
  using m3c= nafto::detail::get_missing_type<0b110000111,L3>;
  using m3d= nafto::detail::get_missing_type<0b111010011,L3>;
  using m4= nafto::detail::get_missing_type<0b011,L4>;
  using m5a= nafto::detail::get_missing_type<0b00,L5>;
  using m5b= nafto::detail::get_missing_type<0b01,L5>;
  using m5c= nafto::detail::get_missing_type<0b11,L5>;
  using m5d= nafto::detail::get_missing_type<0b10,L5>;
  using m6a= nafto::detail::get_missing_type<0b0000,L6>;
  using m6b= nafto::detail::get_missing_type<0b0001,L6>;
  using m6c= nafto::detail::get_missing_type<0b0011,L6>;
  using m6d= nafto::detail::get_missing_type<0b0111,L6>;
  using m6e= nafto::detail::get_missing_type<0b1001,L6>;
  using m6f= nafto::detail::get_missing_type<0b0110,L6>;
  using m7a= nafto::detail::get_missing_type<0b1100,L7>;
  using m7b= nafto::detail::get_missing_type<0b1101,L7>;
  using m7c= nafto::detail::get_missing_type<0b1001,L7>;
  using m7d= nafto::detail::get_missing_type<0b0110,L7>;

  flags_out<m5b>();
  flags_out<m5d>();
  flags_out<m6e>();

  static_assert( m1a()(), "" );
  static_assert( std::is_same<m1a::type,S02>::value, "" );
  static_assert( m1b()(), "" );
  static_assert( std::is_same<m1b::type,S01>::value, "" );

  static_assert( m2a()(), "" );
  static_assert( std::is_same<m2a::type,S03>::value, "" );
  static_assert( m2b()(), "" );
  static_assert( std::is_same<m2b::type,S02>::value, "" );
  static_assert( m2c()(), "" );
  static_assert( std::is_same<m2c::type,S01>::value, "" );

  static_assert( !m3a()(), "" );
  static_assert( m3b()(), "" );
  static_assert( std::is_same<m3b::type,S01>::value, "" );
  static_assert( m3c()(), "" );
  static_assert( std::is_same<m3c::type,S04>::value, "" );
  static_assert( m3d()(), "" );
  static_assert( std::is_same<m3d::type,S06>::value, "" );
  static_assert( !m4()(), "" );
  static_assert( !m5a()(), "" );
  static_assert( !m5b()(), "" );
  static_assert( !m5c()(), "" );
  static_assert( !m5d()(), "" );
  static_assert( !m4()(), "" );
  static_assert( !m6a()(), "" );
  static_assert( !m6b()(), "" );
  static_assert( !m6c()(), "" );
  static_assert( !m6d()(), "" );
  static_assert( m6e()(), "" );
  static_assert( std::is_same<m6e::type,S02>::value, "" );
  static_assert( m6f()(), "" );
  static_assert( std::is_same<m6f::type,S01>::value, "" );
  static_assert( !m7a()(), "" );
  static_assert( !m7b()(), "" );
  static_assert( m7c()(), "" );
  static_assert( std::is_same<m7c::type,S05>::value, "" );
  static_assert( m7d()(), "" );
  static_assert( std::is_same<m7d::type,S06>::value, "" );
}
