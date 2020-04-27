#ifndef TOOLS_HTTP_HTTPRESPONSE_H
#define TOOLS_HTTP_HTTPRESPONSE_H

#include <string>
#include <memory>
#include <vector>
#include "tools/http/HttpHeader.h"
#include "tools/http/HttpCookie.h"

namespace tools
{
	/**
	 * @struct HttpResponse
	 * @brief This object represents an HTTP response.
	 */
	struct HttpResponse
	{
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<HttpResponse> ptr;

		//Member variables
		/**
		 * @var m_code
		 * @brief The HTTP status code.
		 */
		int m_code;
		/**
		 * @var m_headers
		 * @brief The HTTP headers.
		 */
		std::vector<HttpHeader> m_headers;
		/**
		 * @var m_body
		 * @brief The HTTP body.
		 */
		std::string m_body;
		/**
		 * @var m_cookies
		 * @brief The HTTP cookies.
		 */
		std::vector<HttpCookie> m_cookies;

		//Constructors
		/**
		 * @param[in] code The request's status code.
		 * @param[in] headers A vector where each element represents a header.
		 * @param[in] body The request's body.
		 * @param[in] cookies The request's cookies.
		 */
		HttpResponse(const int &code, const std::vector<HttpHeader> &headers, const std::string &body, const std::vector<HttpCookie> &cookies);
	};
}

#endif
