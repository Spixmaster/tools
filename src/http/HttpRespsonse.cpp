#include "tools/http/HttpResponse.h"

namespace tools
{
	HttpResponse::HttpResponse(const int &code, const std::vector<HttpHeader> &headers, const std::string &body) :
			m_code(code), m_headers(headers), m_body(body)
	{}
}
