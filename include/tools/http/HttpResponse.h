#ifndef TOOLS_HTTP_HTTPRESPONSE_H
#define TOOLS_HTTP_HTTPRESPONSE_H

#include <string>
#include <memory>
#include <vector>
#include "tools/http/HttpHeader.h"

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
	};
}

#endif
