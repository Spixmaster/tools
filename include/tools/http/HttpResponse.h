#ifndef TOOLS_HTTP_HTTPRESPONSE_H
#define TOOLS_HTTP_HTTPRESPONSE_H

#include <string>
#include <memory>

//@brief struct that contains some information about the http request

namespace tools
{
	struct HttpResponse
	{
		//pointer of itself
		typedef std::shared_ptr<HttpResponse> ptr;

		//member variables
		int code;
		std::string txt;
	};
}

#endif
