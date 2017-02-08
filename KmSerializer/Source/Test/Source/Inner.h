#pragma once


#include <Serializer/Source/Serializable.h>
#include <Serializer/Source/StreamWriter.h>
#include <Serializer/Source/StreamReader.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	
////////////////////////////////////////////////////////////////////////////////////////////////////
class PktInner
:
public Serializable
{
public:
	kmBool                           m_bool; 
	kmInt32                          m_int32;
	std::map< kmInt32, std::string > m_map;  

public:
	bool Serialize( StreamWriter& writer ) const override;

	bool Deserialize( StreamReader& reader ) override;

	bool operator== ( const PktInner& rhs ) const;

	bool operator!= ( const PktInner& rhs ) const;
};
