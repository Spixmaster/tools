#ifndef TOOLS_HTTP_HTTPARG_H
#define TOOLS_HTTP_HTTPARG_H

#include <string>
#include <memory>
#include <variant>
#include "tools/http/InputFile.h"

//@brief simply a container for a key value pair of http arguments

namespace tools
{
	struct HttpArg
	{
		//pointer of itself
		typedef std::shared_ptr<HttpArg> ptr;

		//member variables
		std::string m_key;
		std::variant<long long, std::string, InputFile::ptr> m_value;

		//constructors
		/*
		 * @param key: key of the post data
		 * @param value: value of the post data
		 */
		HttpArg(const std::string &key, const std::variant<long long, std::string, InputFile::ptr> &value);
	};
}

#endif
