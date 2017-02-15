{#- 파일 출력 템플릿 (테스트) -#}
{#- 이하 템플릿 본문 -#}
/**
/// @file {{param['classname'][0] | camel_to_pascal}}.cs
/// @brief 이 파일은 자동생성 되었습니다
*/

using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Yto3.ProtocolService.Param;


namespace Yto3.ProtocolService 
{
	{% if param['comment_class'][0] %}
	/// <summary>
	/// {{param['comment_class'][0]}}
	/// </summary>
	{%endif-%}
	public class {{param['classname'][0] | camel_to_pascal}} : ProtocolServiceBase 
	{

		/// <summary>
		/// 송신 데이터
		/// </summary>
		[System.Serializable]
		public class Request : ProtocolRequest 
		{
			{% for type in param['request_type']%}
			
			{%-if param['comment_member_request'][loop.index-1]%}
			/// <summary>
			/// {{param['comment_member_request'][loop.index-1]}}
			/// </summary>
			{%-endif%}
			public {{type}} {{param['request_member'][loop.index-1]}};
			{%-endfor%}
		}
		
		/// <summary>
		/// 응답 데이터
		/// </summary>
		[System.Serializable]
		public class Response : ProtocolResponse 
		{
			{% for type in param['response_type']%}
			
			{%-if param['comment_member_response'][loop.index-1]%}
			/// <summary>
			/// {{param['comment_member_response'][loop.index-1]}}
			/// </summary>
			{%-endif%}
			public {{type}} {{param['response_member'][loop.index-1]}};
			{%-endfor%}
		}
		
		public Request request = new Request();
		public Response response = new Response();
		
		override public string url { get { return "api/{{param['classname'][0]}}/"; } }
		override public ProtocolRequest requestObject { get { return request; } }
		override public ProtocolResponse responseObject { get { return response; } set { response = value as Response; } }
	}
}

