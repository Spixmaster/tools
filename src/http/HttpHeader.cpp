#include "tools/http/HttpHeader.h"

namespace tools
{
	HttpHeader::HttpHeader(const std::string &key, const std::string &value) : m_key(key), m_value(value)
	{}
}
