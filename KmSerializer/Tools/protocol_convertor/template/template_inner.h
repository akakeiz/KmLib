{#- ファイル出力テンプレート（テスト） -#}
{#- 以下テンプレート本体 -#}
// 컨버터에서 자동 생성되는 파일. 직접 수정 금지!!! - ( {{param['filename'][0]}} )
#ifndef {{param['ifdef'][0]}}
{% for define in param['define'] %}
#define {{define}}
{%-endfor-%}
{% for o_include in param['originalinclude']%}
#include "{{o_include}}"
{%-endfor%}
#include "base_protocol.h"
#include <list>
#include <string>
{% for i in param['include'] %}
#include "{{i}}"
{%-endfor-%}
{% for i_sub in param['include_sub'] %}
#include "{{i_sub}}"
{%-endfor%}

namespace Protocol {
	{% if param['comment_class'][0] %}
	// {{param['comment_class'][0]}}
	{%endif-%}	
	class {{param['classname'][0]}} : public Base {
	{%if param['type']%}	
	public:
	{%for type in param['type']%}
		{{type}} {{param['member'][loop.index-1]}};{%-if param['comment_member'][loop.index-1]%} // {{param['comment_member'][loop.index-1]}}{%-endif%}
	{%-endfor%}
	{%endif%}
	
	public:
	protected:
		void init_members(void);
		void pack_custom_class(msgpkw::MPObject* obj_p, boost::any member_p);
		void unpack_custom_class(boost::any member_p, boost::any value);
		template <typename T> msgpkw::MPObject pack_class(T* p) {
			return p->pack();
		}
		template <typename T> msgpkw::MPArray pack_array_class(std::list<T>* p) {
			msgpkw::MPArray array;
			for(typename std::list<T>::iterator i = p->begin(), end_ = p->end(); i != end_; ++i) {
				array.push((*i).pack());
			}
			return array;
		}
		
		template <typename T> void unpack_class(T* p, msgpkw::MPMap map) {
			p->unpack(map);
		}
		
		template <typename T> void unpack_array_class(std::list<T>* p, msgpkw::MPArray array) {
			p->clear();
			
			for(typename std::list<msgpkw::MPObject>::iterator i = array.begin(), end_ = array.end(); i != end_; ++i) {
				T c;
				msgpkw::MPMap map = boost::any_cast<msgpkw::MPMap>((*i).get_value());
				c.unpack(map);
				p->push_back(c);
			}
		}
	};
}

#endif // {{param['ifdef'][0]}}