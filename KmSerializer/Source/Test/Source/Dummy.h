#pragma once


#include <Serializer/Source/Serializable.h>
#include <Serializer/Source/StreamWriter.h>
#include <Serializer/Source/StreamReader.h>
#include "Inner.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	
////////////////////////////////////////////////////////////////////////////////////////////////////
class PktDummy
:
public Serializable
{
public:
	kmUInt8                  m_uint8;     
	kmUInt16                 m_uint16;    
	kmInt32                  m_int32;     
	kmInt64                  m_int64;     
	kmString                 m_string;    
	std::vector< kmInt32 >   m_vector;    
	std::list< kmInt32 >     m_list;      
	PktInner                 m_inner;     
	std::list< PktInner >    m_innerList; 
	std::array< kmInt32, 5 > m_array;     

public:
	bool Serialize( StreamWriter& writer ) const override;

	bool Deserialize( StreamReader& reader ) override;

	bool operator== ( const PktDummy& rhs );
};
