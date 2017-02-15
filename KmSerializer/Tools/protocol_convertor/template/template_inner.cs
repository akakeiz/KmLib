{#- 파일 출력 템플릿 (테스트) -#}
{#- 이하 템플릿 본문 -#}
/**
/// @file {{param['classname'][0] | camel_to_pascal}}.cs
/// @brief 이 파일은 자동생성 되었습니다
*/

using System.Collections;
using System.Collections.Generic;


namespace Yto3.ProtocolService.Param
{

	{%- if param['comment_class'][0] %}
	
	/// <summary>
	/// {{param['comment_class'][0]}}
	/// </summary>
	{%endif-%}
	[System.Serializable]
	public class {{param['classname'][0] | camel_to_pascal}} 
	{
		
		{%- for type in param['type']%}

		{%- if param['comment_member'][loop.index-1] %}
		/// <summary>
		/// {{param['comment_member'][loop.index-1]}}
		/// </summary>
		{%-endif%}
		public {{type}} {{param['member'][loop.index-1]}};
		{%-endfor%}
	}
}