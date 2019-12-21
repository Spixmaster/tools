#ifndef TOOLS_HTTP_HTTPRESPONSE_H
#define TOOLS_HTTP_HTTPRESPONSE_H

#include <string>
#include <memory>
#include <vector>
#include "tools/http/HttpHeader.h"
#include "tools/http/HttpCookie.h"

//@brief struct that contains some information about the http request

namespace tools
{
	struct HttpResponse
	{
		//pointer of itself
		typedef std::shared_ptr<HttpResponse> ptr;

		//member variables
		int m_code;
		std::vector<HttpHeader> m_headers;
		std::string m_body;
		std::vector<HttpCookie> m_cookies;

		//constructors
		/*
		 * @param code: request's status code
		 * @param headers: vector where each element represents a header
		 * @param body: the request's body
		 */
		HttpResponse(const int &code, const std::vector<HttpHeader> &headers, const std::string &body, const std::vector<HttpCookie> &cookies);
	};
}

#endif
