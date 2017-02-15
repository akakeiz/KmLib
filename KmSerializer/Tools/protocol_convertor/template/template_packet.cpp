{#- 파일 출력 템플릿 -#}

// 자동 생성되는 파일. 직접 수정 금지!
#include "PCH.h"
{%- for i in param['include'] %}
#include "{{i}}"
{%-endfor%}
#include "PktID"
#include "StreamReader.h"
#include "StreamWriter.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	패킷의 ID를 반환한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmInt32 Protocol::{{param['classname'][0]}}::Request::GetPacketID() const
{
    return PacketID::{{param['classname'][0]}};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	패킷을 직렬화 한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool Protocol::{{param['classname'][0]}}::Request::Serialize( StreamWriter& writer ) const
{
    {%- for member in param['request_member'] %}
    if( !(writer << {{member}}) ) return false;
    {%- endfor %}

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	패킷을 역직렬화 한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool Protocol::{{param['classname'][0]}}::Request::Deserialize( StreamReader& reader )
{
    {%- for member in param['request_member'] %}
    if( !(reader >> {{member}}) ) return false;
    {%- endfor %}

    return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	패킷의 ID를 반환한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmInt32 Protocol::{{param['classname'][0]}}::Response::GetPacketID() const
{
    return PacketID::{{param['classname'][0]}};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	패킷을 직렬화 한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool Protocol::{{param['classname'][0]}}::Response::Serialize( StreamWriter& writer ) const
{
    if( !(writer << m_result) ) return false;
    {%- for member in param['response_member'] %}
    if( !(writer << {{member}}) ) return false;
    {%- endfor %}

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	패킷을 역직렬화 한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool Protocol::{{param['classname'][0]}}::Response::Deserialize( StreamReader& reader )
{
    if( !(reader >> m_result) ) return false;
    {%- for member in param['response_member'] %}
    if( !(reader >> {{member}}) ) return false;
    {%- endfor %}

    return true;
}
