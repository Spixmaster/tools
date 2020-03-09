#ifndef TOOLS_HTTP_HTTPCLIENT_H
#define TOOLS_HTTP_HTTPCLIENT_H

#include <string>
#include <memory>
#include "tools/http/HttpArg.h"
#include "tools/http/HttpResponse.h"
#include <vector>
#include "tools/http/HttpHeader.h"
#include <variant>

/*
 * @brief class does all http requests
 * @brief for post methods the content length is set automatically
 * @brief if necessary the post methods url parse the http body by themselves
 */

namespace tools
{
	class HttpClient
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<HttpClient> ptr;

	private:
		//member variables
		std::string m_url;
		std::vector<HttpHeader> m_http_headers;
		std::vector<HttpArg> m_http_args;
		bool m_print_error = true;

	public:
		//constructors
		/*
		 * @param url: to which server the request shall be sent
		 * @param print_error: whether the error message shall be output to stderr if the server responds with an error
		 */
		HttpClient(const std::string &url, const bool &print_error = true);

		/*
		 * @param url: to which server the request shall be sent
		 * @param http_headers: contains the http headers
		 * @param print_error: whether the error message shall be output to stderr if the server responds with an error
		 */
		HttpClient(const std::string &url, const std::vector<HttpHeader> &http_headers, const bool &print_error = true);

		/*
		 * @param url: to which server the request shall be sent
		 * @param http_args: contains the http args
		 * @param print_error: whether the error message shall be output to stderr if the server responds with an error
		 */
		HttpClient(const std::string &url, const std::vector<HttpArg> &http_args, const bool &print_error = true);

		/*
		 * @param url: to which server the request shall be sent
		 * @param http_headers: http headers which are sent with the request (key: value)
		 * @param http_args: http args which are sent with the request
		 * @param print_error: whether the error message shall be output to stderr if the server responds with an error
		 */
		HttpClient(const std::string &url, const std::vector<HttpHeader> &http_headers, const std::vector<HttpArg> &http_args, const bool &print_error = true);

		//member functions
		/*
		 * @brief makes a simple get request
		 * @param debug: prints to stdout headers and args of the request and the response
		 * @return the server response
		 */
		HttpResponse send_get_req(const bool &debug = false) const noexcept;

		/*
		 * @brief makes a post request via application/x-www-form-urlencoded
		 * @param body_json: converts the http args to json before they are sent
		 * @param debug: prints to stdout headers and args of the request and the response
		 * @return the server response
		 */
		HttpResponse send_post_req_urlencoded(const bool body_json = false, const bool &debug = false) const noexcept;

		/*
		 * @brief the function which is overloaded is almost the same
		 * @brief makes a post request via application/x-www-form-urlencoded
		 * @brief necessary as Instagram for example demands very specific http bodies: hmac sha256 hashed and prefix
		 * @param http_body: the special http body which is going to be sent
		 * @param debug: prints to stdout headers and args of the request and the response
		 * @return the server response
		 */
		HttpResponse send_post_req_urlencoded(std::string http_body, const bool &debug = false) const noexcept;

		/*
		 * @brief makes a post request via multipart/form-data
		 * @param debug: prints to stdout headers and args of the request and the response
		 * @return the server response
		 */
		HttpResponse send_post_req_multipart(const bool &debug = false) const noexcept;

		/*
		 * @brief getter
		 * @return m_url
		 */
		std::string get_url() const noexcept;

		/*
		 * @brief getter
		 * @return m_http_header
		 */
		std::vector<HttpHeader> get_http_headers() const noexcept;

		/*
		 * @brief getter
		 * @return m_http_args
		 */
		std::vector<HttpArg> get_http_args() const noexcept;

		/*
		 * @brief getter
		 * @return m_print_error
		 */
		bool get_print_error() const noexcept;
	};
}

#endif
