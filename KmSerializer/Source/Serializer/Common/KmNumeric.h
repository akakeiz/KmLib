#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	수식과 관련한 각종 함수들의 모음
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace KmNumeric
{
	const kmFloat  Pi        = 3.141592653f;                       ///< PI
	const kmFloat Epsilon    = 0.001f;                             ///< 수식 비교에 사용되는 엡실론
	const kmUInt32 MaxUInt8  = ((kmUInt8)( ~((kmUInt8)( 0 )) ));   ///< kmUInt8 타입의 최대 값
	const kmInt32  MaxInt8   = ((kmInt8)( MaxUInt8 >> 1 ));        ///< kmInt8 타입의 최대 값
	const kmUInt32 MaxUInt16 = ((kmUInt16)( ~((kmUInt16)( 0 )) )); ///< kmUInt16 타입의 최대 값
	const kmInt32  MaxInt16  = ((kmInt16)( MaxUInt16 >> 1 ));      ///< kmInt16 타입의 최대 값
	const kmUInt32 MaxUInt24 = 0xFFFFFF;                           ///< UInt24 타입의 최대 값
	const kmUInt32 MaxUInt32 = ((kmUInt32)( ~((kmUInt32)( 0 )) )); ///< kmUInt32 타입의 최대 값
	const kmInt32  MaxInt32  = ((kmInt32)( MaxUInt32 >> 1 ));      ///< kmInt32 타입의 최대 값
	const kmUInt64 MaxUInt64 = ((kmUInt64)( ~((kmUInt64)( 0 )) )); ///< kmUInt64 타입의 최대 값
	const kmInt64  MaxInt64  = ((kmInt64)( MaxUInt64 >> 1 ));      ///< kmInt64 타입의 최대 값
	const kmFloat  MaxSingle = 3.402823466e+38F;                   ///< kmSingle 타입의 최대 값
	const kmDouble MaxDouble = 1.7976931348623158e+308;            ///< kmDouble 타입의 최대 값
	
	/// 절대 값을 반환한다.
	template< typename Type >
	Type Abs( Type n );

	/// 평균 값을 반환한다.
	template< typename Type >
	Type Average( Type min, Type max );

	/// 주어진 값들 중 가장 작은 값을 반환한다.
	template< typename Type >
	Type Min( Type a, Type b );

	/// 주어진 값들 중 가장 작은 값을 반환한다.
	template< typename Type >
	Type Min( Type a, Type b, Type c );

	/// 주어진 값들 중 가장 작은 값을 반환한다.
	template< typename Type >
	Type Min( Type a, Type b, Type c, Type d );

	/// 주어진 값들 중 가장 작은 값을 반환한다.
	template< typename Type >
	Type Min( Type a, Type b, Type c, Type d, Type e );

	/// 주어진 값들 중 가장 큰 값을 반환한다.
	template< typename Type >
	Type Max( Type a, Type b );

	/// 주어진 값들 중 가장 큰 값을 반환한다.
	template< typename Type >
	Type Max( Type a, Type b, Type c );

	/// 주어진 값들 중 가장 큰 값을 반환한다.
	template< typename Type >
	Type Max( Type a, Type b, Type c, Type d );

	/// 주어진 값들 중 가장 큰 값을 반환한다.
	template< typename Type >
	Type Max( Type a, Type b, Type c, Type d, Type e );

	/// @a n 이 주어진 범위 안에 포함되는지 확인한다.
	template< typename Type >
	kmBool IsIn( Type n, Type min, Type max );

	/// 주어진 값이 2의 지수승인지 확인한다.
	template< typename Type >
	kmBool IsPowerOf2( Type n );

	/// @a n 을 주어진 범위 내로 자른다.
	template< typename Type >
	Type Clamp( Type n, Type min, Type max );

	/// n에 더해질 v에 대해 결과가 min ~ max에 오도록 v를 자른다.
	template< typename Type >
	Type Clamp( Type n, Type min, Type max, Type v );

	/// @a m 으로 나누어지는 값 중 @a v 에 가장 가까운 큰 값을 반환한다.
	template< typename Value, typename Modulator >
	Value RoundUp( Value v, Modulator m );

	/// @a m 으로 나누어지는 값 중 @a v 에 가장 가까운 작은 값을 반환한다.
	template< typename Value, typename Modulator >
	Value RoundDown( Value v, Modulator m );

	/// 주어진 두 값을 합쳐 2 바이트로 만든다.
	template< typename Type >
	kmUInt16 MakeWord( Type lo, Type hi );

	/// 주어진 두 값을 합쳐 4 바이트로 만든다.
	template< typename Type >
	kmUInt32 MakeLong( Type lo, Type hi );

	/// 주어진 값의 하위 바이트를 반환한다.
	template< typename Type >
	kmUInt8 LoByte( Type n );

	/// 주어진 값의 상위 바이트를 반환한다.
	template< typename Type >
	kmUInt8 HiByte( Type n );

	/// 주어진 값의 하위 워드를 반환한다.
	template< typename Type >
	kmUInt16 LoWord( Type n );

	/// 주어진 값의 상위 워드를 반환한다.
	template< typename Type >
	kmUInt16 HiWord( Type n );

	/// 문자 네 개를 합쳐 4 바이트로 만든다.
	template< typename Type >
	kmUInt32 MakeFourCC( Type c1, Type c2, Type c3, Type c4 );

	/// 일반 각도를 라디안 각도로 변환한다.
	template< typename Type >
	Type ToRadian( Type degree );

	/// 라디안 각도를 일반 각도로 변환한다.
	template< typename Type >
	Type ToDegree( Type radian );

	/// 제곱근을 반환한다.
	template< typename Type >
	Type Sqrt( Type n );

	/// 제곱한 값을 반환한다.
	template< typename Base, typename Power >
	Base Pow( Base b, Power p );

	/// 사인 값을 반환한다.
	template< typename Type >
	Type Sin( Type n );

	/// 코사인 값을 반환한다.
	template< typename Type >
	Type Cos( Type n );

	/// 탄젠트 값을 반환한다.
	template< typename Type >
	Type Tan( Type n );

	/// 아크사인 값을 반환한다.
	template< typename Type >
	Type Asin( Type n );

	/// 아크코사인 값을 반환한다.
	template< typename Type >
	Type Acos( Type n );

	/// 아크탄젠트 값을 반환한다.
	template< typename Type >
	Type Atan( Type n );

	/// X 축에서 점(x, y)까지의 각도를 라디안 값으로 반환한다.
	template< typename Type >
	Type Atan2( Type y, Type x );

	/// 주어진 범위 안에 속하는 난수를 생성한다.
	kmInt32 Random( kmInt32 min, kmInt32 max );

	/// 주어진 범위 안에 속하는 난수를 생성한다.
	kmFloat Random( kmFloat min, kmFloat max );

	/// 주어진 범위 안에 속하는 난수를 생성한다.
	kmDouble Random( kmDouble min, kmDouble max );

	/// 10000 이 100% 를 의미하는 확률값에 대해 난수가 해당 확률을 만족하는지 여부를 반환한다.
	kmBool CheckRandom( kmInt32 rate );

	/// 1.0 이 100% 를 의미하는 확률값에 대해 난수가 해당 확률을 만족하는지 여부를 반환한다.
	kmBool CheckRandomDouble( kmDouble rate );

	/// 곱셈 연산에서 오버 플로우를 확인한다.
	kmBool CheckOverflowMultifly( kmInt32 l, kmInt32 r );

	/// 주어진 범위 안에 속하는 난수를 생성한다.
	kmUInt32 RandomSeededMt( kmUInt32 min, kmUInt32 max );

	/// 바이트 오더를 변경한다.
	kmInt16 ChangeByteOrder( kmInt16 v );

	/// 바이트 오더를 변경한다.
	kmUInt16 ChangeByteOrder( kmUInt16 v );

	/// 바이트 오더를 변경한다.
	kmInt32 ChangeByteOrder( kmInt32 v );

	/// 바이트 오더를 변경한다.
	kmUInt32 ChangeByteOrder( kmUInt32 v );

	/// 바이트 오더를 변경한다.
	kmInt64 ChangeByteOrder( kmInt64 v );

	/// 바이트 오더를 변경한다.
	kmUInt64 ChangeByteOrder( kmUInt64 v );

	/// 바이트 오더를 변경한다.
	kmFloat ChangeByteOrder( kmFloat v );

	/// 바이트 오더를 변경한다.
	kmDouble ChangeByteOrder( kmDouble v );
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	절대 값을 반환한다.
///
/// @param	n	절대 값으로 바꿀 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Abs( Type n )
{
	return (n < 0) ? -n : n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	평균 값을 반환한다.
///
/// @param	min	평균을 낼 첫 번째 값
/// @param	max	평균을 낼 두 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Average( Type min, Type max )
{
	return min + ((max - min) / 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값들 중 가장 작은 값을 반환한다.
///
/// @param	a	첫 번째 값
/// @param	b	두 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Min( Type a, Type b )
{
	return (a < b) ? a : b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값들 중 가장 작은 값을 반환한다.
///
/// @param	a	첫 번째 값
/// @param	b	두 번째 값
/// @param	c	세 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Min( Type a, Type b, Type c )
{
	return Min( Min( a, b ), c );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값들 중 가장 작은 값을 반환한다.
///
/// @param	a	첫 번째 값
/// @param	b	두 번째 값
/// @param	c	세 번째 값
/// @param	d	네 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Min( Type a, Type b, Type c, Type d )
{
	return Min( Min( a, b, c ), d );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값들 중 가장 작은 값을 반환한다.
///
/// @param	a	첫 번째 값
/// @param	b	두 번째 값
/// @param	c	세 번째 값
/// @param	d	네 번째 값
/// @param	e	다섯 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Min( Type a, Type b, Type c, Type d, Type e )
{
	return Min( Min( a, b, c, d ), e );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값들 중 가장 큰 값을 반환한다.
///
/// @param	a	첫 번째 값
/// @param	b	두 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Max( Type a, Type b )
{
	return (a > b) ? a : b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값들 중 가장 큰 값을 반환한다.
///
/// @param	a	첫 번째 값
/// @param	b	두 번째 값
/// @param	c	세 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Max( Type a, Type b, Type c )
{
	return Max( Max( a, b ), c );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값들 중 가장 큰 값을 반환한다.
///
/// @param	a	첫 번째 값
/// @param	b	두 번째 값
/// @param	c	세 번째 값
/// @param	d	네 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Max( Type a, Type b, Type c, Type d )
{
	return Max( Max( a, b, c ), d );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값들 중 가장 큰 값을 반환한다.
///
/// @param	a	첫 번째 값
/// @param	b	두 번째 값
/// @param	c	세 번째 값
/// @param	d	네 번째 값
/// @param	e	다섯 번째 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Max( Type a, Type b, Type c, Type d, Type e )
{
	return Max( Max( a, b, c, d ), e );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	@a n 이 주어진 범위 안에 포함되는지 확인한다.
///
/// @param	n  	검사할 값
/// @param	min	대상 범위의 최소 값
/// @param	max	대상 범위의 최대 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmBool KmNumeric::IsIn( Type n, Type min, Type max )
{
	return (n >= min) && (n <= max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값이 2의 지수승인지 확인한다.
///
/// @param	n	검사할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmBool KmNumeric::IsPowerOf2( Type n )
{
	return (n > 1) && !(n & (n - 1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	@a n 을 주어진 범위 내로 자른다.
///
/// @param	n  	잘려질 값
/// @param	min	대상 범위의 최소 값
/// @param	max	대상 범위의 최대 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Clamp( Type n, Type min, Type max )
{
	if ( n < min ) return min;
	if ( n > max ) return max;

	return n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief n에 더해질 v에 대해 결과가 min ~ max에 오도록 v를 자른다.
///
/// @param	n  	잘려질 값
/// @param	min	대상 범위의 최소 값
/// @param	max	대상 범위의 최대 값
/// @param	v	n에 더해질 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Clamp( Type n, Type min, Type max, Type v )
{
	if ( n + v < min ) return min - n;
	if ( n + v > max ) return max - n;

	return v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	@a m 으로 나누어지는 값 중 @a v 에 가장 가까운 큰 값을 반환한다.
///
/// @param	v	변환될 값
/// @param	m	나누어질 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Value, typename Modulator >
Value KmNumeric::RoundUp( Value v, Modulator m )
{
	return RoundDown( v, m ) + (((v % (Value)( m )) > 0) ? m : 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	@a m 으로 나누어지는 값 중 @a v 에 가장 가까운 작은 값을 반환한다.
///
/// @param	v	변환될 값
/// @param	m	나누어질 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Value, typename Modulator >
Value KmNumeric::RoundDown( Value v, Modulator m )
{
	kmInt32 floor = (kmInt32)( v / m + Epsilon );

	return (Value)( floor * m );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 두 값을 합쳐 2 바이트로 만든다.
///
/// @param	lo	하위 바이트의 값
/// @param	hi	상위 바이트의 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmUInt16 KmNumeric::MakeWord( Type lo, Type hi )
{
	return (kmUInt16)( (kmUInt32)( lo ) & 0xff ) | (kmUInt16)( ((kmUInt32)( hi ) & 0xff) << 8 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 두 값을 합쳐 4 바이트로 만든다.
///
/// @param	lo	하위 워드의 값
/// @param	hi	상위워드의 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmUInt32 KmNumeric::MakeLong( Type lo, Type hi )
{
	return (kmUInt32)( (kmUInt32)( lo ) & 0xffff ) | (kmUInt16)( ((kmUInt32)( hi ) & 0xffff) << 16 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값의 하위 바이트를 반환한다.
///
/// @param	n	2 바이트 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmUInt8 KmNumeric::LoByte( Type n )
{
	return (kmUInt8)( (kmUInt32)( n ) & 0xff );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값의 상위 바이트를 반환한다.
///
/// @param	n	2 바이트 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmUInt8 KmNumeric::HiByte( Type n )
{
	return (kmUInt8)( ((kmUInt32)( n ) >> 8) & 0xff );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값의 하위 워드를 반환한다.
///
/// @param	n	4 바이트 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmUInt16 KmNumeric::LoWord( Type n )
{
	return (kmUInt16)( (kmUInt32)( n ) & 0xffff );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	주어진 값의 상위 워드를 반환한다.
///
/// @param	n	4 바이트 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmUInt16 KmNumeric::HiWord( Type n )
{
	return (kmUInt16)( ((kmUInt32)( n ) >> 16) & 0xffff );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	문자 네 개를 합쳐 4 바이트로 만든다.
///
/// @param	c1	첫 번째 문자
/// @param	c2	두 번째 문자
/// @param	c3	세 번째 문자
/// @param	c4	네 번째 문자
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
kmUInt32 KmNumeric::MakeFourCC( Type c1, Type c2, Type c3, Type c4 )
{
	return
		((kmUInt32)( kmUInt8 )( c1 ))       |
		((kmUInt32)( kmUInt8 )( c2 ) <<  8) |
		((kmUInt32)( kmUInt8 )( c3 ) << 16) |
		((kmUInt32)( kmUInt8 )( c4 ) << 24);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	일반 각도를 라디안 각도로 변환한다.
///
/// @param	degree	일반 각도
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::ToRadian( Type degree )
{
	return degree * KmNumeric::Pi / 180.f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	라디안 각도를 일반 각도로 변환한다.
///
/// @param	radian	라디안 각도
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::ToDegree( Type radian )
{
	return radian * 180.f / KmNumeric::Pi;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	제곱근을 반환한다.
///
/// @param	n	계산할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Sqrt( Type n )
{
	return (Type)( sqrt( (kmDouble)( n ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	제곱한 값을 반환한다.
///
/// @param	b	계산할 값
/// @param	p	제곱할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Base, typename Power >
Base KmNumeric::Pow( Base b, Power p )
{
	return (Base)( pow( (kmDouble)( b ), (kmDouble)( p ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	사인 값을 반환한다.
///
/// @param	n	계산할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Sin( Type n )
{
	return (Type)( sin( (kmDouble)( n ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	코사인 값을 반환한다.
///
/// @param	n	계산할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Cos( Type n )
{
	return (Type)( cos( (kmDouble)( n ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	탄젠트 값을 반환한다.
///
/// @param	n	계산할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Tan( Type n )
{
	return (Type)( tan( (kmDouble)( n ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	아크사인 값을 반환한다.
///
/// @param	n	계산할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Asin( Type n )
{
	return (Type)( asin( (kmDouble)( n ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	아크코사인 값을 반환한다.
///
/// @param	n	계산할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Acos( Type n )
{
	return (Type)( acos( (kmDouble)( n ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	아크탄젠트 값을 반환한다.
///
/// @param	n	계산할 값
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Atan( Type n )
{
	return (Type)( atan( (kmDouble)( n ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	X 축에서 점(x, y)까지의 각도를 라디안 값으로 반환한다.
///
/// @param	y	Y 축 좌표
/// @param	x	X 축 좌표
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename Type >
Type KmNumeric::Atan2( Type y, Type x )
{
	return (Type)( atan2( (kmDouble)( y ), (kmDouble)( x ) ) );
}
