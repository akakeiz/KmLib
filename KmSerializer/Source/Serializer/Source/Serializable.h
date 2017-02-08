#pragma once


class StreamReader;
class StreamWriter;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	객체를 직렬화 시킬수 있도록 하기 위한 인터페이스
////////////////////////////////////////////////////////////////////////////////////////////////////
class Serializable
{
public:
	virtual ~Serializable() { }

	/// StreamWriter에 클래스의 내용을 기록한다.
	virtual bool Serialize( StreamWriter& writer ) const = 0;

	/// 스트림 리더에서 클래스의 내용을 읽어온다.
	virtual bool Deserialize( StreamReader& reader ) = 0;
};
