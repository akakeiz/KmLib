{#- 파일 출력 템플릿 -#}

// 자동 생성되는 파일. 직접 수정 금지!
#pragma once


#include "PktBase.h"
#include <list>
#include <string>
{% for i in param['include'] %}
#include "{{i}}"
{%-endfor-%}
{% for i_sub in param['include_sub'] %}
#include "{{i_sub}}"
{%-endfor%}

{#- 레이아웃을 위한 매크로 정의 -#}
{%- macro Render_layout( maxvar, curvar ) -%}
    {% set space_cnt = maxvar|int - curvar|length %}
    {%- for n in range(0, space_cnt) -%}
        {{ ' ' }}
    {%- endfor %}
{%- endmacro %}

{% if param['comment_class'][0] %}
// {{param['comment_class'][0]}}
{%endif-%}
namespace Protocol {
namespace {{param['classname'][0]}} {

    //***** 요청 패킷
    class Notify
    :
    public PktBase
    {
    {%- if param['request_member'] %}
    public:
    {%- for type in param['request_type_cpp'] %}
        {{type}}{{ Render_layout(param['layout_maxreq_typelen'], type) }} {{param['request_member'][loop.index-1]}};{%-if param['comment_member_request'][loop.index-1]%}{{ Render_layout( param['layout_maxreq_varname'], param['request_member'][loop.index-1]) }} // {{param['comment_member_request'][loop.index-1]}}{%-endif%}
    {%-endfor%}
    {%-endif %}

    public:
        /// 패킷의 ID를 반환한다.
        virtual kmInt32 GetPacketID() const override;

        /// 패킷을 직렬화 한다.
        virtual kmBool Serialize( StreamWriter& writer ) const override;

        /// 패킷을 역직렬화 한다.
        virtual kmBool Deserialize( StreamReader& reader ) override;
    };

} /* {{param['classname'][0]}} */
} /* Protocol */
