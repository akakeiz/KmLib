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
/// @brief	패킷을 직렬화 한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool Protocol::{{param['classname'][0]}}::Serialize( StreamWriter& writer ) const
{
    {%- for member in param['request_member'] %}
    if( !(writer << {{member}}) ) return false;
    {%- endfor %}

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	패킷을 역직렬화 한다.
////////////////////////////////////////////////////////////////////////////////////////////////////
kmBool Protocol::{{param['classname'][0]}}::Deserialize( StreamReader& reader )
{
    {%- for member in param['request_member'] %}
    if( !(reader >> {{member}}) ) return false;
    {%- endfor %}

    return true;
}
