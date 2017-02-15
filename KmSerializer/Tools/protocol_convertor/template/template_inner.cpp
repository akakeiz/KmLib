{#- ファイル出力テンプレート（テスト） -#}
{#- 以下テンプレート本体 -#}
// 컨버터에서 자동 생성되는 파일. 직접 수정 금지!!! - ( {{param['filename'][0]}} )
{% for i in param['include'] %}
#include "{{i}}"
{%-endfor%}

{% if param['comment_class'][0] %}
// {{param['comment_class'][0]}}
{%endif-%}
void Protocol::{{param['classname'][0]}}::init_members(void){
	// MessagePack화 하고 싶은 멤버 변수의 이름과 포인터를 등록한다
	{% for _add_member in param['member'] %}
		{#-addmenberのループ-#}
		add_member("{{_add_member}}",&(this->{{_add_member}}));{%-if param['comment_member'][loop.index-1]%} // {{param['comment_member'][loop.index-1]}}{%-endif%}
	{% endfor %}
}



void Protocol::{{param['classname'][0]}}::pack_custom_class(msgpkw::MPObject* obj_p, boost::any member_p) {
    // 클래스 등을 시리얼라이즈 하고 싶은 경우 여기에 처리를 추가한다
	{% for member in param['originalclass']%}
	if(member_p.type() == typeid({{member}}*)) {
		*obj_p = pack_class(boost::any_cast<{{member}}*>(member_p));
	} else if(member_p.type() == typeid(std::list<{{member}}>*)) {
		*obj_p = pack_array_class(boost::any_cast<std::list<{{member}}>*>(member_p));
	}
	
	{%-endfor%}
}

void Protocol::{{param['classname'][0]}}::unpack_custom_class(boost::any member_p, boost::any value) {
	// 클래스 등을 디시리얼라이즈 하고 싶은 경우 여기에 처리를 추가한다
	{%for member in param['originalclass']%}
	if(member_p.type() == typeid({{member}}*)) {
		unpack_class(boost::any_cast<{{member}}*>(member_p), boost::any_cast<msgpkw::MPMap>(value));
	} else if(member_p.type() == typeid(std::list<{{member}}>*)) {
		unpack_array_class(boost::any_cast<std::list<{{member}}>*>(member_p), boost::any_cast<msgpkw::MPArray>(value));
	}
	{%-endfor%}
	
}

