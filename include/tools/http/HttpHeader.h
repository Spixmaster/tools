#ifndef TOOLS_HTTP_HTTPHEADER_H
#define TOOLS_HTTP_HTTPHEADER_H

#include <string>
#include <memory>

namespace tools
{
	/**
	 * @struct HttpHeader
	 * @brief A container for a key value pair of an HTTP header
	 */
	struct HttpHeader
	{
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself
		 */
		typedef std::shared_ptr<HttpHeader> ptr;

		//Member variables
		/**
		 * @var m_key
		 * @brief The key of the HTTP header
		 */
		std::string m_key;
		/**
		 * @var m_value
		 * @brief The value of the HTTP header
		 */
		std::string m_value;

		//Constructors
		/**
		 * @param[in] key Key of the header
		 * @param[in] value Value of the header
		 */
		HttpHeader(const std::string &key, const std::string &value);
	};
}

#endif
