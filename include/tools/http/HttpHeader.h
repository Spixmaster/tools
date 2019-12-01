#ifndef TOOLS_HTTP_HTTPHEADER_H
#define TOOLS_HTTP_HTTPHEADER_H

#include <string>
#include <memory>

//@brief simply a container for a key value pair of an http header

namespace tools
{
	struct HttpHeader
	{
		//pointer of itself
		typedef std::shared_ptr<HttpHeader> ptr;

		//member variables
		std::string m_key;
		std::string m_value;

		//constructors
		/*
		 * @param key: key of the header
		 * @param value: value of the header
		 */
		HttpHeader(const std::string &key, const std::string &value);
	};
}

#endif
