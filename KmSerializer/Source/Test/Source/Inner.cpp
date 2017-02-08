#include "PCH.h"
#include "Inner.h"


bool PktInner::Serialize( StreamWriter& writer ) const
{
	if ( !(writer << m_bool) ) return false;
	if ( !(writer << m_int32) ) return false;
	if ( !(writer << m_map) ) return false;

	return true;
}

bool PktInner::Deserialize( StreamReader& reader )
{
	if ( !(reader >> m_bool) ) return false;
	if ( !(reader >> m_int32) ) return false;
	if ( !(reader >> m_map) ) return false;

	return true;
}

bool PktInner::operator== ( const PktInner& rhs ) const 
{
	if ( m_bool != rhs.m_bool ) return false;
	if ( m_int32 != rhs.m_int32 ) return false;
	if ( m_map != rhs.m_map ) return false;

	return true;
}

bool PktInner::operator!= ( const PktInner& rhs ) const
{
	return !( (*this) == rhs );
}
