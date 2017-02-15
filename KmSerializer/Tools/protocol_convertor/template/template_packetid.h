{#- 패킷ID 출력 템플릿 -#}

// 자동 생성되는 파일. 직접 수정 금지!
#pragma once

// 패킷의 해시코드
struct PACKET
{
    static kmInt64 HashCode;
};

enum class PacketID : kmInt32
{
    {%- for packet in param %}
    {{ packet[0] }} = {{ packet[1] }},
    {%- endfor %}
    Max
};

