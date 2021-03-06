#pragma once


#include "Stream.h"
#include "../Common/KmNumeric.h"

class Serializable;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	스트림을 쓰기 위한 인터페이스
////////////////////////////////////////////////////////////////////////////////////////////////////
class StreamWriter
:
public Stream
{
private:
	kmUInt32 m_bytesLastWritten; ///< 마지막으로 쓴 바이트 수
	kmUInt32 m_version;          ///< 버전 정보
	kmBool   m_versionSwitch;    ///< 버전에 따른 처리가 필요한지 여부

public:
	/// 생성자
	StreamWriter();

	/// 소멸자
	virtual ~StreamWriter();

	/// 버전 정보를 설정한다.
 	kmVoid SetVersion( kmUInt32 version ) { m_version = version; }

	/// 버전에 따른 처리가 필요한지 여부를 설정한다.
 	kmVoid SetVersionSwitch( kmBool versionSwitch ) { m_versionSwitch = versionSwitch; }

	/// 마지막으로 쓴 바이트의 수를 반환한다.
	kmUInt32 GetBytesLastWritten() const { return m_bytesLastWritten; }

	/// 버전 정보를 반환한다.
 	kmUInt32 GetVersion() const { return m_version; }

	/// 버전에 따른 처리가 필요한지 여부를 반환한다.
 	kmBool GetVersionSwitch() const { return m_versionSwitch; }
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief	데이터를 쓴다.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual kmBool Write( const kmVoid* buffer, kmUInt32 length ) = 0;
	virtual kmBool Write( kmBool v ) = 0;
	virtual kmBool Write( kmInt8 v ) = 0;
	virtual kmBool Write( kmUInt8 v ) = 0;
	virtual kmBool Write( kmInt16 v ) = 0;
	virtual kmBool Write( kmUInt16 v ) = 0;
	virtual kmBool Write( kmInt32 v ) = 0;
	virtual kmBool Write( kmUInt32 v ) = 0;
	virtual kmBool Write( kmInt64 v ) = 0;
	virtual kmBool Write( kmUInt64 v ) = 0;
	virtual kmBool Write( kmFloat v ) = 0;
	virtual kmBool Write( kmDouble v ) = 0;
	virtual kmBool Write( const kmString& v ) = 0;

	kmBool Write( const Serializable& v );

	template< typename Type >
	kmBool Write( const std::list< Type >& v );

	template< typename Type >
	kmBool Write( const std::vector< Type >& v );

	template< typename Type >
	kmBool Write( const std::set< Type >& v );

	template< typename Type, std::size_t N >
	kmBool Write( const std::array< Type, N >& v );

	template< typename KeyType, typename ValueType >
	kmBool Write( const std::map< KeyType, ValueType >& v );

	/// 연산자 중첩 ( << )  //! 템플릿 함수로 바꾸면 되지 않나?
	virtual kmBool operator << ( kmBool v              ) { return Write( v ); }
	virtual kmBool operator << ( kmInt8 v              ) { return Write( v ); }
	virtual kmBool operator << ( kmUInt8 v             ) { return Write( v ); }
	virtual kmBool operator << ( kmInt16 v             ) { return Write( v ); }
	virtual kmBool operator << ( kmUInt16 v            ) { return Write( v ); }
	virtual kmBool operator << ( kmInt32 v             ) { return Write( v ); }
	virtual kmBool operator << ( kmUInt32 v            ) { return Write( v ); }
	virtual kmBool operator << ( kmInt64 v             ) { return Write( v ); }
	virtual kmBool operator << ( kmUInt64  v           ) { return Write( v ); }
	virtual kmBool operator << ( kmFloat v             ) { return Write( v ); }
	virtual kmBool operator << ( kmDouble v            ) { return Write( v ); }
	virtual kmBool operator << ( const kmString& v     ) { return Write( v ); }
	virtual kmBool operator << ( const Serializable& v ) { return Write( v ); }

	template< typename Type >
	kmBool operator << ( Type& v );

	template< typename Type >
	kmBool operator << ( const std::list< Type >& v ) { return Write( v ); }

	template< typename Type >
	kmBool operator << ( const std::vector< Type >& v ) { return Write( v ); }

	template< typename Type >
	kmBool operator << ( const std::set< Type >& v ) { return Write( v ); }

	template< typename Type, std::size_t N >
	kmBool operator << ( const std::array< Type, N >& v ) { return Write( v ); }

	template< typename KeyType, typename ValueType >
	kmBool operator << ( const std::map< KeyType, ValueType >& v ) { return Write( v ); }

protected:
	/// 마지막으로 쓴 바이트의 수를 설정한다.
	kmVoid SetBytesLastWritten( kmUInt32 bytesLastWritten );
};


/// 템플릿 함수 구현
template< typename Type >
kmBool StreamWriter::Write( const std::list< Type >& v )
{
	// Header 2Byte : List Size
	kmUInt16 count = (kmUInt16)( v.size() );
	if ( !Write( count ) )
		return false;

	for ( typename std::list< Type >::const_iterator iter = v.begin(); iter != v.end(); ++iter )
	{
		if ( !Write( *iter ) )
			return false;
	}

	return true;
}

template< typename Type >
kmBool StreamWriter::Write( const std::vector< Type >& v )
{
	kmUInt16 count = (kmUInt16)( v.size() );
	if ( !(*this << count) )
		return false;

	for ( kmUInt16 index = 0; index < count; ++index )
		if ( !(*this << v[ index ]) )
			return false;

	return true;
}

template< typename Type >
kmBool StreamWriter::Write( const std::set< Type >& v )
{
	kmUInt16 count = (kmUInt16)( v.size() );
	if ( !(*this << count) )
		return false;

	for ( typename std::set< Type >::const_iterator iter = v.begin(); iter != v.end(); ++iter )
		if ( !(*this << *iter) )
			return false;

	return true;
}

template< typename Type, std::size_t N >
kmBool StreamWriter::Write( const std::array< Type, N >& v )
{
	if ( N >= KmNumeric::MaxUInt16 )
		return false;

	for ( kmUInt16 index = 0; index < N; ++index )
	{
		if ( !Write( v[ index ] ) )
			return false;
	}

	return true;
}

template< typename KeyType, typename ValueType >
kmBool StreamWriter::Write( const std::map< KeyType, ValueType >& v )
{
	kmUInt16 count = (kmUInt16)( v.size() );
	if ( !Write( count ) )
		return false;

	for ( typename std::map< KeyType, ValueType >::const_iterator iter = v.begin(); iter != v.end(); ++iter )
	{
		if ( !Write( iter->first ) ) return false;
		if ( !Write( iter->second ) ) return false;
	}

	return true;
}

template < typename Type >
kmBool StreamWriter::operator << ( Type& v )
{
	return Write( v );
}
