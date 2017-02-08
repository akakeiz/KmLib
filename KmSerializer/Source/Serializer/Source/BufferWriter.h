#pragma once


#include "StreamWriter.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	메모리로부터 스트림을 쓰기 위한 클래스
////////////////////////////////////////////////////////////////////////////////////////////////////
class BufferWriter
:
public StreamWriter
{
private:
	/// 바이트 목록 타입 정의
	using ByteList = std::vector< kmUInt8 >;

private:
	ByteList m_buffer;     ///< 버퍼
	kmUInt32 m_bufferSize; ///< 버퍼 크기
	kmUInt32 m_pos;        ///< 커서 위치
	kmUInt32 m_length;     ///< Write한 길이

public:
	/// 생성자
	BufferWriter();

	/// 소멸자
	virtual ~BufferWriter();

	/// 버퍼크기를 재조정한다.
	kmVoid Resize( kmUInt32 size );

	/// 버퍼를 비운다.
	kmVoid Truncate();

	/// 버퍼를 반환한다.
	const kmUInt8* GetBuffer() const;

	/// Write한 길이를 반환한다.
	kmUInt32 GetLength() const { return m_length; }

	/// 지정한 위치로 포인터를 이동한다.
	virtual kmBool Seek( Stream::SeekAt seelAt, kmInt32 offset ) override;

	/// 포인터의 현재 위치를 반환한다.
	virtual kmInt32 Tell() override;

	/// 데이터를 쓴다.
	virtual kmBool Write( const kmVoid* buffer, kmUInt32 length ) override;
	virtual kmBool Write( kmBool v ) override;
	virtual kmBool Write( kmInt8 v ) override;
	virtual kmBool Write( kmUInt8 v ) override;
	virtual kmBool Write( kmInt16 v ) override;
	virtual kmBool Write( kmUInt16 v ) override;
	virtual kmBool Write( kmInt32 v ) override;
	virtual kmBool Write( kmUInt32 v ) override;
	virtual kmBool Write( kmInt64 v ) override;
	virtual kmBool Write( kmUInt64 v ) override;
	virtual kmBool Write( kmFloat v ) override;
	virtual kmBool Write( kmDouble v ) override;
	virtual kmBool Write( const kmString& v ) override;
};
