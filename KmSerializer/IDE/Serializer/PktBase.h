////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	패킷의 최상위 클래스
///
/// @Note	프로토콜 정의에 따라서(프로젝트에 따라서) 클래스를 적당히 수정하자.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "Serializable.h"


class PktBase
:
public Serializable
{
private:
	kmInt16 m_length; ///< 길이
	
public:
	virtual ~PktBase() {}

	/// 패킷 길이를 설정한다.
	kmVoid SetLength( kmInt16 length ) { m_length = length; }

	/// 패킷 길이를 반환한다.
	kmInt16 GetLength() { return m_length; }

	/// 패킷의 식별자를 반환한다.
	virtual kmInt32 GetPacketID() const { return 0; }
};
