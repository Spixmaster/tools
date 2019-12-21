#include "tools/http/HttpResponse.h"

namespace tools
{
	HttpResponse::HttpResponse(const int &code, const std::vector<HttpHeader> &headers, const std::string &body, const std::vector<HttpCookie> &cookies) :
			m_code(code), m_headers(headers), m_body(body), m_cookies(cookies)
	{}
}
