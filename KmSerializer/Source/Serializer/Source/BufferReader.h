#pragma once


#include "StreamReader.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	메모리로부터 스트림을 읽기 위한 클래스
////////////////////////////////////////////////////////////////////////////////////////////////////
class BufferReader
:
public StreamReader
{
private:
	kmUInt8* m_buffer;          // 버퍼
	kmUInt32 m_length;          // 버퍼의 길이
	kmUInt8* m_position;        ///< 커서 위치
	kmBool   m_changeByteOrder; ///< 바이트 오더 변경 여부

public:
	/// 생성자
	BufferReader();

	/// 생성자
	BufferReader( const kmUInt8* buffer, kmUInt32 length, kmBool changeByOrder = false );

	/// 소멸자
	~BufferReader();

	/// 버퍼를 설정한다.
	kmVoid Set( const kmUInt8* buffer, kmUInt32 length );

	/// 설정된 버퍼를 해제한다.
	kmVoid Reset();

	/// 설정된 버퍼를 반환한다.
	const kmUInt8* GetBuffer() const;

	/// 설정된 버퍼의 길이를 반환한다.
	kmUInt32 GetLength() const;

	/// 지정한 위치로 포인터를 이동한다.
	virtual kmBool Seek( Stream::SeekAt seekAt, kmInt32 offset ) override;
	
	/// 포인터의 현재 위치를 반환한다.
	virtual kmInt32 Tell() override;

	/// 데이터를 읽는다.
	virtual kmBool Read( kmVoid* buffer, kmUInt32 length ) override;
	virtual kmBool Read( kmBool& v ) override;
	virtual kmBool Read( kmInt8& v ) override;
	virtual kmBool Read( kmUInt8& v ) override;
	virtual kmBool Read( kmInt16& v ) override;
	virtual kmBool Read( kmUInt16& v ) override;
	virtual kmBool Read( kmInt32& v ) override;
	virtual kmBool Read( kmUInt32& v ) override;
	virtual kmBool Read( kmInt64& v ) override;
	virtual kmBool Read( kmUInt64& v ) override;
	virtual kmBool Read( kmFloat& v ) override;
	virtual kmBool Read( kmDouble& v ) override;
	virtual kmBool Read( kmString& v ) override;
};

