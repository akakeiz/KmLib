#include "PCH.h"
#include "Dummy.h"


bool PktDummy::Serialize( StreamWriter& writer ) const
{
	if ( !(writer << m_uint8) ) return false;
	if ( !(writer << m_uint16) ) return false;
	if ( !(writer << m_int32) ) return false;
	if ( !(writer << m_int64) ) return false;
	if ( !(writer << m_string) ) return false;
	if ( !(writer << m_vector) ) return false;
	if ( !(writer << m_list) ) return false;
	if ( !(writer << m_inner) ) return false;
	if ( !(writer << m_innerList ) ) return false;
	if ( !(writer << m_array ) ) return false;

	return true;
}

bool PktDummy::Deserialize( StreamReader& reader )
{
	if ( !(reader >> m_uint8) ) return false;
	if ( !(reader >> m_uint16) ) return false;
	if ( !(reader >> m_int32) ) return false;
	if ( !(reader >> m_int64) ) return false;
	if ( !(reader >> m_string) ) return false;
	if ( !(reader >> m_vector) ) return false;
	if ( !(reader >> m_list) ) return false;
	if ( !(reader >> m_inner) ) return false;
	if ( !(reader >> m_innerList) ) return false;
	if ( !(reader >> m_array) ) return false;

	return true;
}

bool PktDummy::operator== ( const PktDummy& rhs )
{
	if ( m_uint8 != rhs.m_uint8 ) return false;
	if ( m_uint16 != rhs.m_uint16 ) return false;
	if ( m_int32 != rhs.m_int32 ) return false;
	if ( m_int64 != rhs.m_int64 ) return false;
	if ( m_string != rhs.m_string ) return false;
	if ( m_vector != rhs.m_vector ) return false;
	if ( m_list != rhs.m_list ) return false;
	if ( m_inner != rhs.m_inner ) return false;
	if ( m_innerList != rhs.m_innerList ) return false;
	if ( m_array != rhs.m_array ) return false;

	return true;
}
