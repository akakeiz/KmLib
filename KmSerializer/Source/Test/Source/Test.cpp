#include "PCH.h"

#include "Dummy.h"
#include <Serializer/Source/BufferWriter.h>
#include <Serializer/Source/BufferReader.h>
#include <fstream>

int main()
{
	//! Serialize Request
	PktDummy reqDummy;
	reqDummy.m_uint8 = 1;
	reqDummy.m_uint16 = 2;
	reqDummy.m_int32 = -123456;
	reqDummy.m_int64 = 12345678900;
	reqDummy.m_string = "string test text";
	reqDummy.m_inner.m_bool = true;
	reqDummy.m_inner.m_int32 = 0;
	reqDummy.m_inner.m_map.insert( { 0, "Zero" } );
	reqDummy.m_inner.m_map.insert( { 1, "One" } );
	reqDummy.m_array = { 1, 2, 3, 4, 5 };
	
	for( int i=1; i<=10; i++ )
	{
		reqDummy.m_vector.push_back( i );
		reqDummy.m_list.push_back( i );
	}

	for( int i=1; i<=10; i++ )
	{	
		PktInner inner;
		inner.m_bool = true;
		inner.m_int32 = i;
		inner.m_map.insert( { 1, "One" } );
		inner.m_map.insert( { 3, "Three" } );
		inner.m_map.insert( { 2, "Two" } );

		reqDummy.m_innerList.push_back( inner );
	}

	BufferWriter writer;
	reqDummy.Serialize( writer );

	//! Deseiralize Response
	PktDummy resDummy;
	BufferReader reader;
	reader.Set( writer.GetBuffer(), writer.GetLength() );

	resDummy.Deserialize( reader );
	
	//! Check
	if ( reqDummy == resDummy )
	{
		std::cout << "Success to Serialize and Deserialize!!!!" << std::endl;
	}
	else
	{
		std::cout << "Fail to Serialize and Deserialize!!!!" << std::endl;	
	}

	//! To File
	std::ofstream binFile( "PktDummy.pkt", std::ios::out ); 
	binFile.write( (char*)writer.GetBuffer(), writer.GetLength() );
	binFile.close();

    return 0;
}

