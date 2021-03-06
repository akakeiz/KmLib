#include "PCH.h"
#include "BufferWriter.h"
#include "Serializable.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	생성자
////////////////////////////////////////////////////////////////////////////////////////////////////
BufferWriter::BufferWriter()
:
m_bufferSize ( 0 ),
m_pos        ( 0 ),
m_length     ( 0 )
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	소멸자
////////////////////////////////////////////////////////////////////////////////////////////////////
BufferWriter::~BufferWriter()
{
	Truncate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	버퍼크기를 재조정한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmVoid BufferWriter::Resize( kmUInt32 size )
{
	m_buffer.resize( size );
	m_bufferSize = size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	버퍼를 비운다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmVoid BufferWriter::Truncate()
{
	m_buffer.clear();
	m_bufferSize = 0;
	m_pos        = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	Write한 버퍼를 반환한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
const kmUInt8* BufferWriter::GetBuffer() const
{
	if ( !m_bufferSize ) return nullptr;

	return &m_buffer[ 0 ];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	지정한 위치로 포인터를 이동한다.
///
/// @param	seekAt	이동 시작점
/// @param	offset 	오프셋
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool BufferWriter::Seek( Stream::SeekAt seekAt, kmInt32 offset )
{
	switch ( seekAt )
	{
	case Stream::SeekAt::Begin:   m_pos = offset;                break;
	case Stream::SeekAt::Current: m_pos += offset;               break;
	case Stream::SeekAt::End:     m_pos = m_bufferSize + offset; break;
	}

	// Check border
	if ( m_pos < 0 ||  m_pos > m_bufferSize - 1 )
	{
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	포인터의 현재 위치를 반환한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmInt32 BufferWriter::Tell()
{
	return m_pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	데이터를 쓴다.
///
/// @param	buffer	쓸 데이터를 담고 있는 버퍼
/// @param	length	쓸 데이터의 길이
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool BufferWriter::Write( const kmVoid* buffer, kmUInt32 length )
{
	// 0 바이트를 쓰는 경우 memcpy에서 assert가 나는 것을 방지한다.
	if ( length <= 0 ) return true;

	// 버퍼가 부족할 경우, Resize  //! 굳이 이렇게 해야하나?
	if ( m_bufferSize - m_pos < length )
	{
		if ( !m_bufferSize )
			m_bufferSize = 512;

		do 
		{
			m_bufferSize *= 2;
		} while ( m_bufferSize - m_pos < length );

		m_buffer.resize( m_bufferSize );
	}

	memcpy( &m_buffer[ m_pos ], buffer, (size_t)( length ) );
	m_pos    += length;
	m_length += length;

	SetBytesLastWritten( length );

	return true;
}

kmBool BufferWriter::Write( kmBool v )
{
	kmInt8 tmp = (kmInt8)( v ? 1 : 0 );
	return Write( &tmp, sizeof( tmp ) );
}

kmBool BufferWriter::Write( kmInt8 v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmUInt8 v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmInt16 v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmUInt16 v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmInt32 v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmUInt32 v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmInt64 v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmUInt64 v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmFloat v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( kmDouble v )
{
	return Write( &v, sizeof( v ) );
}

kmBool BufferWriter::Write( const kmString& v )
{
	Write( (kmUInt16)( v.size() ) );
	Write( v.c_str(), (kmUInt32)( v.size() ) );
	return true;
}