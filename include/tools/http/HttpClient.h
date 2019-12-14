#ifndef TOOLS_HTTP_HTTPCLIENT_H
#define TOOLS_HTTP_HTTPCLIENT_H

#include <string>
#include <memory>
#include "tools/http/HttpArg.h"
#include "tools/http/HttpResponse.h"
#include <vector>
#include "tools/http/HttpHeader.h"
#include <variant>

//@brief class does all http requests

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

	public:
		//constructors

		//@param url: to which server the request shall be sent
		HttpClient(const std::string &url);

		/*
		 * @param url: to which server the request shall be sent
		 * @param http_comp: either contains the http headers or the http args
		 */
		HttpClient(const std::string &url, const std::variant<std::vector<HttpHeader>, std::vector<HttpArg>> &http_comp);

		/*
		 * @param url: to which server the request shall be sent
		 * @param http_headers: http headers which are sent with the request (key: value)
		 * @param http_args: http args which are sent with the request
		 */
		HttpClient(const std::string &url, const std::vector<HttpHeader> &http_headers, const std::vector<HttpArg> &http_args);

		//member functions

		/*
		 * @brief makes a simple get request
		 * @param debug: prints to stdout headers and args of the request and the response
		 * @return the server response
		 */
		HttpResponse send_get_req(const bool &debug = false);

		/*
		 * @brief makes a post request via application/x-www-form-urlencoded
		 * @param body_json: converts the http args to json before they are sent
		 * @param debug: prints to stdout headers and args of the request and the response
		 * @return the server response
		 */
		HttpResponse send_post_req_urlencoded(const bool body_json = false, const bool &debug = false);

		/*
		 * @brief the function which is overloaded is almost the same
		 * @brief makes a post request via application/x-www-form-urlencoded
		 * @brief necessary as Instagram for example demands very specific http bodies: hmac sha256 hashed and prefix
		 * @param http_body: the special http body which is going to be sent
		 * @param debug: prints to stdout headers and args of the request and the response
		 * @return the server response
		 */
		HttpResponse send_post_req_urlencoded(const std::string &http_body, const bool &debug = false);

		/*
		 * @brief makes a post request via multipart/form-data
		 * @param debug: prints to stdout headers and args of the request and the response
		 * @return the server response
		 */
		HttpResponse send_post_req_multipart(const bool &debug = false);
	};
}

#endif
