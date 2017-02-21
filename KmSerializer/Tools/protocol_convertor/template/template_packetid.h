{#- 패킷ID 출력 템플릿 -#}
{#- PktID.h -#}

// 자동 생성되는 파일. 직접 수정 금지!
#pragma once

{#- 레이아웃을 위한 매크로 정의 -#}
{%- macro Render_layout( maxvar, curvar ) -%}
    {% set space_cnt = maxvar|int - curvar|length %}
    {%- for n in range(0, space_cnt) -%}
        {{ ' ' }}
    {%- endfor %}
{%- endmacro %}

// 패킷의 해시코드
struct PACKET
{
    static kmInt64 HashCode;
};

enum class PacketID : kmInt32
{
    {%- for packet in param[ 'packet' ] %}
    {{ packet[0] }}{{ Render_layout(param['layout_max_name'], packet[0]) }} = {{ packet[1] }},
    {%- endfor %}
    Max
};

