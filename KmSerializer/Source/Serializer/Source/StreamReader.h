#pragma once


#include "Stream.h"


class Serializable;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	스트림을 읽기 위한 인터페이스
////////////////////////////////////////////////////////////////////////////////////////////////////
class StreamReader
:
public Stream
{
private:
	kmUInt32 m_bytesLastRead; ///< 마지막으로 읽은 바이트 수
	kmUInt32 m_version;       ///< 버전 정보
	kmBool   m_versionSwitch; ///< 버전에 따른 처리가 필요한지 여부

public:
	/// 생성자
	StreamReader();

	/// 소멸자
	~StreamReader();

	/// 버전 정보를 설정한다.
 	kmVoid SetVersion( kmUInt32 version ) { m_version = version; }

	/// 버전에 따른 처리가 필요한지 여부를 설정한다.
 	kmVoid SetVersionSwitch( kmBool versionSwitch ) { m_versionSwitch = versionSwitch; }

	/// 마지막으로 읽은 바이트의 수를 반환한다.
	kmUInt32 GetBytesLastRead() const;

	/// 버전 정보를 반환한다.
 	kmUInt32 GetVersion() const { return m_version; }

	/// 버전에 따른 처리가 필요한지 여부를 반환한다.
 	kmBool GetVersionSwitch() const { return m_versionSwitch; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief	데이터를 읽는다.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual kmBool Read( kmVoid* buffer, kmUInt32 length ) = 0;
	virtual kmBool Read( kmBool& v ) = 0;
	virtual kmBool Read( kmInt8& v ) = 0;
	virtual kmBool Read( kmUInt8& v ) = 0;
	virtual kmBool Read( kmInt16& v ) = 0;
	virtual kmBool Read( kmUInt16& v ) = 0;
	virtual kmBool Read( kmInt32& v ) = 0;
	virtual kmBool Read( kmUInt32& v ) = 0;
	virtual kmBool Read( kmInt64& v ) = 0;
	virtual kmBool Read( kmUInt64& v ) = 0;
	virtual kmBool Read( kmFloat& v ) = 0;
	virtual kmBool Read( kmDouble& v ) = 0;
	virtual kmBool Read( kmString& v ) = 0;

	kmBool Read( Serializable& v );

	template< typename Type >
	kmBool Read( std::list< Type >& v );

	template< typename Type >
	kmBool Read( std::vector< Type >& v );

	template< typename Type >
	kmBool Read( std::set< Type >& v );

	template< typename KeyType, typename ValueType >
	kmBool Read( std::map< KeyType, ValueType >& v );

	template< typename Type, std::size_t N >
	kmBool Read( std::array< Type, N >& v );
	
	template< typename Type >
	kmBool operator >> ( Type& v );

	/// 포인터의 위치를 변경하지 않고 데이터를 읽는다.
	kmBool Peek( kmVoid* buffer, kmUInt32 length );

protected:
	/// 마지막으로 읽은 바이트 수를 설정한다.
	kmVoid SetBytesLastRead( kmUInt32 bytesLastRead );
};


/// 템플릿 함수 구현
template <typename Type >
kmBool StreamReader::Read( std::list< Type >& v )
{
	v.clear();

	// Header 2Byte : List Size
	kmUInt16 count;
	if ( !Read( count ) )
		return false;

	while ( count-- > 0 )
	{
		Type item;
		if ( !Read( item ) )
			return false;
		
		v.push_back( std::move( item ) );
	}

	return true;
}

template <typename Type >
kmBool StreamReader::Read( std::vector< Type >& v )
{
	v.clear();

	kmUInt16 count;
	if ( !Read( count ) )
		return false;

	v.reserve( count );

	while ( count-- > 0 )
	{
		Type item;
		if ( !Read( item ) )
			return false;
		
		v.push_back( std::move( item ) );
	}

	return true;
}

template< typename Type >
kmBool StreamReader::Read( std::set< Type >& v )
{
	v.clear();

	kmUInt16 count;
	if ( !Read( count ) )	
		return false;

	while ( count-- > 0 )
	{
		Type item;
		if ( !Read( item ) )
			return false;

		v.insert( std::move( item ) );
	}
}

template <typename KeyType, typename ValueType >
kmBool StreamReader::Read( std::map< KeyType, ValueType >& v )
{
	v.clear();

	kmUInt16 count;
	if ( !Read( count ) )	
		return false;

	while ( count-- > 0 )
	{
		KeyType key;
		if ( !Read( key ) )      return false;
		if ( !Read( v[ key ] ) ) return false;
	}

	return true;
}

template< typename Type, std::size_t N >
kmBool StreamReader::Read( std::array< Type, N >& v )
{
	if ( N >= KmNumeric::MaxUInt16 )
		return false;

	for ( kmUInt16 index = 0; index < N; index++ )
	{
		if ( !Read( v[ index ] ) )
			return false;
	}

	return true;
}

template < typename Type >
kmBool StreamReader::operator >> ( Type& v )
{
	return Read( v );
}
