#ifndef TOOLS_HTTP_HTTPCLIENT_H
#define TOOLS_HTTP_HTTPCLIENT_H

#include <string>
#include <memory>
#include "tools/http/HttpArg.h"
#include "tools/http/HttpResponse.h"
#include <vector>
#include "tools/http/HttpHeader.h"
#include <variant>

namespace tools
{
	/**
	 * @class HttpClient
	 * @brief The class represents an HTTP client which sends out HTTP requests.
	 * @details For post methods, the content length is set automatically.
	 * @details If necessary, the post methods URL parse the HTTP body by themselves.
	 */
	class HttpClient
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself
		 */
		typedef std::shared_ptr<HttpClient> ptr;

	private:
		//Member variables
		/**
		 * @var m_url
		 * @brief The destination of the request
		 */
		std::string m_url;
		/**
		 * @var m_http_headers
		 * @brief The HTTP headers
		 */
		std::vector<HttpHeader> m_http_headers;
		/**
		 * @var m_http_args
		 * @brief The HTTP arguments
		 */
		std::vector<HttpArg> m_http_args;
		/**
		 * @var m_http_args
		 * @brief The boolean decides whether error messages shall be printed.
		 * @details Sometimes, it is not wanted to create error logs.
		 */
		bool m_print_error = true;

	public:
		//Constructors
		/**
		 * @param[in] url Defines to which server the request shall be sent.
		 * @param[in] print_error Decides whether the error message shall be output to stderr if the server responds with an error.
		 */
		HttpClient(const std::string &url, const bool &print_error = true);

		/**
		 * @param[in] url Defines to which server the request shall be sent.
		 * @param[in] http_headers The HTTP headers to send with the request
		 * @param[in] print_error Decides whether the error message shall be output to stderr if the server responds with an error.
		 */
		HttpClient(const std::string &url, const std::vector<HttpHeader> &http_headers, const bool &print_error = true);

		/**
		 * @param[in] url Defines to which server the request shall be sent.
		 * @param[in] http_args: The HTTP arguments to send with the request
		 * @param[in] print_error Decides whether the error message shall be output to stderr if the server responds with an error.
		 */
		HttpClient(const std::string &url, const std::vector<HttpArg> &http_args, const bool &print_error = true);

		/**
		 * @param[in] url Defines to which server the request shall be sent.
		 * @param[in] http_headers The HTTP headers to send with the request
		 * @param[in] http_args: The HTTP arguments to send with the request
		 * @param[in] print_error Decides whether the error message shall be output to stderr if the server responds with an error.
		 */
		HttpClient(const std::string &url, const std::vector<HttpHeader> &http_headers, const std::vector<HttpArg> &http_args, const bool &print_error = true);

		//Member functions
		/**
		 * @brief Makes a simple get request.
		 * @param[in] debug Prints to stdout headers and args of the request and the response.
		 * @return The server response
		 */
		HttpResponse send_get_req(const bool &debug = false) const noexcept;

		/**
		 * @brief Makes a post request via "application/x-www-form-urlencoded".
		 * @param[in] body_json If value is true, it converts the HTTP args to json before they are sent.
		 * @param[in] debug Prints to stdout headers and args of the request and the response.
		 * @return The server response
		 */
		HttpResponse send_post_req_urlencoded(const bool body_json = false, const bool &debug = false) const noexcept;

		/**
		 * @brief Makes a post request via "application/x-www-form-urlencoded".
		 * @details This overload is necessary as Instagram for example demands very specific http bodies (hmac sha256 hashed and prefix).
		 * @param[in] http_body The special HTTP body which is going to be sent
		 * @param[in] debug Prints to stdout headers and args of the request and the response.
		 * @return The server response
		 */
		HttpResponse send_post_req_urlencoded(std::string http_body, const bool &debug = false) const noexcept;

		/**
		 * @brief Makes a post request via "multipart/form-data".
		 * @param[in] debug Prints to stdout headers and args of the request and the response.
		 * @return The server response
		 */
		HttpResponse send_post_req_multipart(const bool &debug = false) const noexcept;

		/**
		 * @brief Getter
		 * @return m_url
		 */
		std::string get_url() const noexcept;

		/**
		 * @brief Getter
		 * @return m_http_header
		 */
		std::vector<HttpHeader> get_http_headers() const noexcept;

		/**
		 * @brief Getter
		 * @return m_http_args
		 */
		std::vector<HttpArg> get_http_args() const noexcept;

		/**
		 * @brief Getter
		 * @return m_print_error
		 */
		bool get_print_error() const noexcept;
	};
}

#endif
