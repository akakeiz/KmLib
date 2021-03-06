#include "PCH.h"
#include "BufferReader.h"
#include "Serializable.h"
#include "../Common/KmNumeric.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	생성자
////////////////////////////////////////////////////////////////////////////////////////////////////
BufferReader::BufferReader()
:
m_buffer          ( nullptr ),
m_length          ( 0       ),
m_position        ( nullptr ),
m_changeByteOrder ( false   )
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	생성자
///
/// @param	buffer			버퍼
/// @param	length			버퍼의 길이
/// @param	changeByteOrder	바이트 오더 변경 여부
////////////////////////////////////////////////////////////////////////////////////////////////////
BufferReader::BufferReader( const kmUInt8* buffer, kmUInt32 length, kmBool changeByteOrder )
:
m_buffer          ( (kmUInt8*)( buffer ) ),
m_length          ( length               ),
m_position        ( m_buffer             ),
m_changeByteOrder ( changeByteOrder      )
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	소멸자
////////////////////////////////////////////////////////////////////////////////////////////////////
BufferReader::~BufferReader()
{
	Reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	버퍼를 설정한다.
///
/// @param	buffer	버퍼
/// @param	length	버퍼의 크기
///
/// @return	반환 값 없음
////////////////////////////////////////////////////////////////////////////////////////////////////
kmVoid BufferReader::Set( const kmUInt8* buffer, kmUInt32 length )
{
	m_buffer   = (kmUInt8*)( buffer );
	m_length   = length;
	m_position = m_buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	설정된 버퍼를 해제한다.
///
/// @return	반환 값 없음
////////////////////////////////////////////////////////////////////////////////////////////////////
kmVoid BufferReader::Reset()
{
	m_buffer          = nullptr;
	m_length          = 0;
	m_position        = nullptr;
	m_changeByteOrder = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	설정된 버퍼를 반환한다.
///
/// @return	설정된 버퍼
////////////////////////////////////////////////////////////////////////////////////////////////////
const kmUInt8* BufferReader::GetBuffer() const
{
	return m_buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	설정된 버퍼의 길이를 반환한다.
///
/// @return	설정된 버퍼의 길이
////////////////////////////////////////////////////////////////////////////////////////////////////
kmUInt32 BufferReader::GetLength() const
{
	return m_length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	지정한 위치로 포인터를 이동한다.
///
/// @param	seekOrigin	이동 중점
/// @param	offset	  	오프셋
///
/// @return	작업을 성공적으로 수행했으면 true, 그렇지 않으면 false를 반환한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool BufferReader::Seek( Stream::SeekAt seekAt, kmInt32 offset )
{
	kmInt32 newPos = 0;

	switch ( seekAt )
	{
	case Stream::SeekAt::Begin:
		newPos = offset;
		break;
	case Stream::SeekAt::Current:
		newPos = (kmInt32)(m_position - m_buffer) + offset;
		break;
	case Stream::SeekAt::End:
		newPos = m_length + offset;
		break;
	}

	m_position = m_buffer + newPos;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	포인터의 현재 위치를 반환한다.
///
/// @return	포인터의 현재 위치
////////////////////////////////////////////////////////////////////////////////////////////////////
kmInt32 BufferReader::Tell()
{
	return (kmInt32)( m_position - m_buffer );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	데이터를 읽는다.
///
/// @param [in,out]	buffer	읽은 데이터를 저장할 버퍼
/// @param	length		  	읽은 데이터의 길이
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool BufferReader::Read( kmVoid* buffer, kmUInt32 length )
{
	kmUInt32 remainedLen = m_length - (kmUInt32)( m_position - m_buffer );
	kmUInt32 bytesRead =  KmNumeric::Min( remainedLen, length );

	memcpy( buffer, m_position, (size_t)( bytesRead ) );
	m_position += bytesRead;

	SetBytesLastRead( bytesRead );

	return bytesRead == length;
}

kmBool BufferReader::Read( kmBool& v )
{
	kmInt8 tmp = 0;
	if ( !Read( &tmp, sizeof( tmp ) ) )
		return false;

	v = (tmp != 0 ? true : false);
	return true;
}

kmBool BufferReader::Read( kmInt8& v )
{
	return Read( &v, sizeof( v ) );
}

kmBool BufferReader::Read( kmUInt8& v )
{
	return Read( &v, sizeof( v ) );
}

kmBool BufferReader::Read( kmInt16& v )
{
	if ( !Read( &v, sizeof( v ) ) ) return false;
	if ( m_changeByteOrder ) v = KmNumeric::ChangeByteOrder( v );
	return true;
}

kmBool BufferReader::Read( kmUInt16& v )
{
	if ( !Read( &v, sizeof( v ) ) ) return false;
	if ( m_changeByteOrder ) v = KmNumeric::ChangeByteOrder( v );
	return true;
}

kmBool BufferReader::Read( kmInt32& v )
{
	if ( !Read( &v, sizeof( v ) ) ) return false;
	if ( m_changeByteOrder ) v = KmNumeric::ChangeByteOrder( v );
	return true;
}

kmBool BufferReader::Read( kmUInt32& v )
{
	if ( !Read( &v, sizeof( v ) ) ) return false;
	if ( m_changeByteOrder ) v = KmNumeric::ChangeByteOrder( v );
	return true;
}

kmBool BufferReader::Read( kmInt64& v )
{
	if ( !Read( &v, sizeof( v ) ) ) return false;
	if ( m_changeByteOrder ) v = KmNumeric::ChangeByteOrder( v );
	return true;
}

kmBool BufferReader::Read( kmUInt64& v )
{
	if ( !Read( &v, sizeof( v ) ) ) return false;
	if ( m_changeByteOrder ) v = KmNumeric::ChangeByteOrder( v );
	return true;
}

kmBool BufferReader::Read( kmFloat& v )
{
	if ( !Read( &v, sizeof( v ) ) ) return false;
	if ( m_changeByteOrder ) v = KmNumeric::ChangeByteOrder( v );
	return true;
}

kmBool BufferReader::Read( kmDouble& v )
{
	if ( !Read( &v, sizeof( v ) ) ) return false;
	if ( m_changeByteOrder ) v = KmNumeric::ChangeByteOrder( v );
	return true;
}

//! 퍼포먼스가 떨어져 보임. 개량이 필요할 듯
kmBool BufferReader::Read( kmString& v )
{
	v.clear();

	kmUInt16 size;
	if ( !Read( size ) )
		return false;

	kmUInt8 c;
	for ( kmInt32 i = 0; i < size; i++ )
	{
		if ( !Read( c ) )
			return false;

		v += c;
	}

	return true;
}
