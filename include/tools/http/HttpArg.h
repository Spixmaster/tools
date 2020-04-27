#ifndef TOOLS_HTTP_HTTPARG_H
#define TOOLS_HTTP_HTTPARG_H

#include <string>
#include <memory>
#include <variant>
#include "tools/http/InputFile.h"

namespace tools
{
	/**
	 * @struct HttpArg
	 * @brief It is simply a container for a key value pair of an HTTP argument.
	 */
	struct HttpArg
	{
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself
		 */
		typedef std::shared_ptr<HttpArg> ptr;

		//Member variables
		/**
		 * @var m_key
		 * @brief The key of the HTTP argument
		 */
		std::string m_key;
		/**
		 * @var m_value
		 * @brief The value of the HTTP argument
		 */
		std::variant<long long, std::string, InputFile::ptr> m_value;

		//Constructors
		/**
		 * @param[in] key The key of the post data
		 * @param[in] value The value of the post data
		 */
		HttpArg(const std::string &key, const std::variant<long long, std::string, InputFile::ptr> &value);
	};
}

#endif
