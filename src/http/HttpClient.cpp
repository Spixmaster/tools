#include <iostream>
#include <rapidjson/document.h>
#include "tools/http/HttpClient.h"
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/Context.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <string>
#include <Poco/Net/NameValueCollection.h>
#include "tools/Tools.h"
#include <boost/algorithm/string.hpp>
#include "tools/constants/Constants.h"
#include "tools/constants/Messages.h"
#include <boost/format.hpp>

namespace tools
{
	HttpClient::HttpClient(const std::string &url, const bool &print_error) : m_url(Tools::parse_url(url)), m_print_error(print_error)
	{}

	HttpClient::HttpClient(const std::string &url, const std::vector<HttpHeader> &http_headers, const bool &print_error) : m_url(Tools::parse_url(url)),
			m_http_headers(http_headers), m_print_error(print_error)
	{}

	HttpClient::HttpClient(const std::string &url, const std::vector<HttpArg> &http_args, const bool &print_error) : m_url(Tools::parse_url(url)), m_http_args(http_args),
			m_print_error(print_error)
	{}

	HttpClient::HttpClient(const std::string &url, const std::vector<HttpHeader> &http_headers, const std::vector<HttpArg> &http_args, const bool &print_error) :
			m_url(Tools::parse_url(url)), m_http_headers(http_headers), m_http_args(http_args), m_print_error(print_error)
	{}

	HttpResponse HttpClient::send_get_req(const bool &debug) const noexcept
	{
		Poco::Net::HTTPResponse::HTTPStatus http_response_code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;
		std::string http_response_body;

		try
		{
			//URI
			Poco::URI uri(m_url);
			std::string path_query = uri.getPathAndQuery();
			if(path_query.empty())
				path_query = "/";

			//Request
		    const Poco::Net::Context::Ptr context = new Poco::Net::Context(
		        Poco::Net::Context::CLIENT_USE, "", "", "",
		        Poco::Net::Context::VERIFY_NONE, 9, false,
		        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
			Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path_query, Poco::Net::HTTPMessage::HTTP_1_1);

	        //Options and headers
	        for(std::size_t j = 0; j < m_http_headers.size(); ++j)
	            req.set(m_http_headers.at(j).m_key, m_http_headers.at(j).m_value);

	        session.setTimeout(Poco::Timespan(150L, 0L));

	        //Send the request.
	        session.sendRequest(req);

	        //Print the request to stdout if the debugging mode is on.
	        if(debug == true)
	        {
	        	std::cout << Constants::ansii_bold_cyan << Messages::req << Constants::ansii_reset << std::endl;
	        	std::cout << Constants::ansii_cyan;
	        	req.write(std::cout);
				std::cout << Constants::ansii_reset;
	        }

			//Response
			Poco::Net::HTTPResponse response;
			std::ostringstream oss;
			std::istream &in = session.receiveResponse(response);
			http_response_code = response.getStatus();
			Poco::StreamCopier::copyStream(in, oss);

			//Check whether the response HTTP body is gzipped. If so, decompress it.
			if(tools::Tools::is_gzipped(oss.str()))
				http_response_body = tools::Tools::gzip_decompress(oss.str());
			else
				http_response_body = oss.str();

			//Print the response if the debugging mode is on.
			if(debug == true)
			{
				Poco::Net::NameValueCollection::ConstIterator j = response.begin();
				std::string http_repsonse_headers;

				while(j != response.end())
				{
					http_repsonse_headers.append(j->first + ": " + j->second + "\n");
					++j;
				}

				//Remove the last new line.
				if(!http_repsonse_headers.empty())
					http_repsonse_headers.pop_back();

				std::cout << Constants::ansii_bold_bright_cyan << Messages::resp(http_response_code) << Constants::ansii_reset << std::endl;
	        	std::cout << Constants::ansii_bright_cyan << http_repsonse_headers << std::endl;
				std::cout << http_response_body << Constants::ansii_reset << std::endl;
			}

			if(http_response_code != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK && m_print_error)
			{
				//Gather the request but do not log it now.
				std::string tmp = Messages::http_response_code_not_200 + "\n";
				tmp.append(Messages::req + "\n");
				std::stringstream ss;
				req.write(ss);
				tmp.append(ss.str() + "\n");

				//Get the response and log request and response.
				Poco::Net::NameValueCollection::ConstIterator j = response.begin();
				std::string http_repsonse_headers;

				while(j != response.end())
				{
					http_repsonse_headers.append(j->first + ": " + j->second + "\n");
					++j;
				}

				//Remove the last new line.
				if(!http_repsonse_headers.empty())
					http_repsonse_headers.pop_back();

				tmp.append(Messages::resp(http_response_code) + "\n");
				tmp.append(http_repsonse_headers + "\n");
				tmp.append(http_response_body);
				Tools::write_err_log_tmp(tmp);

				//HTTP response
				std::vector<HttpHeader> temp_http_headers;
				Poco::Net::NameValueCollection::ConstIterator k = response.begin();

				while(k != response.end())
				{
					HttpHeader http_header(k->first, k->second);
					temp_http_headers.push_back(http_header);
					++k;
				}

				std::vector<HttpCookie> http_cookies;

				for(std::size_t j = 0; j < temp_http_headers.size(); ++j)
				{
					if(boost::iequals(temp_http_headers.at(j).m_key, "Set-Cookie"))
						http_cookies.push_back(HttpCookie(temp_http_headers.at(j).m_value));
				}

				HttpResponse http_response(http_response_code, temp_http_headers, http_response_body, http_cookies);
				return http_response;
			}

			//HTTP response
			std::vector<HttpHeader> temp_http_headers;
			Poco::Net::NameValueCollection::ConstIterator j = response.begin();

			while(j != response.end())
			{
				HttpHeader http_header(j->first, j->second);
				temp_http_headers.push_back(http_header);
				++j;
			}

			std::vector<HttpCookie> http_cookies;

			for(std::size_t j = 0; j < temp_http_headers.size(); ++j)
			{
				if(boost::iequals(temp_http_headers.at(j).m_key, "Set-Cookie"))
					http_cookies.push_back(HttpCookie(temp_http_headers.at(j).m_value));
			}

			HttpResponse http_response(http_response_code, temp_http_headers, http_response_body, http_cookies);
			return http_response;
		}
		catch(const std::exception &e)
		{
			Tools::write_err_log_tmp(e.what());

			//The HTTP response is without the HTTP headers as they are not accessible here.
			HttpResponse http_response(http_response_code, std::vector<HttpHeader>(), http_response_body, std::vector<HttpCookie>());
			return http_response;
		}
	}

	HttpResponse HttpClient::send_post_req_urlencoded(const bool body_json, const bool &debug) const noexcept
	{
		Poco::Net::HTTPResponse::HTTPStatus http_response_code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;;
		std::string http_response_body;

		try
		{
			//URI
			Poco::URI uri(m_url);
			std::string path_query = uri.getPathAndQuery();
			if(path_query.empty())
				path_query = "/";

			//Request
		    const Poco::Net::Context::Ptr context = new Poco::Net::Context(
		        Poco::Net::Context::CLIENT_USE, "", "", "",
		        Poco::Net::Context::VERIFY_NONE, 9, false,
		        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
			Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path_query, Poco::Net::HTTPMessage::HTTP_1_1);

			//Options and headers
	        for(std::size_t j = 0; j < m_http_headers.size(); ++j)
	            req.set(m_http_headers.at(j).m_key, m_http_headers.at(j).m_value);

			session.setTimeout(Poco::Timespan(150L, 0L));

			//HTTP body
			std::string http_body;

			if(!body_json)
			{
				for(std::size_t j = 0; j < m_http_args.size(); ++j)
				{
					if(std::holds_alternative<long long>(m_http_args.at(j).m_value))
					{
						http_body.append(m_http_args.at(j).m_key + "=" + std::to_string(std::get<long long>(m_http_args.at(j).m_value)));

						//Add "&" for the next key value pair.
						if(j != m_http_args.size() - 1)
							http_body.append("&");
					}
					else if(std::holds_alternative<std::string>(m_http_args.at(j).m_value))
					{
						http_body.append(m_http_args.at(j).m_key + "=" + std::get<std::string>(m_http_args.at(j).m_value));

						//Add "&" for the next key value pair.
						if(j != m_http_args.size() - 1)
							http_body.append("&");
					}
					//The value of type InputFile::ptr is ignored.
				}
			}
			else
			{
				http_body.append("{");

				for(std::size_t j = 0; j < m_http_args.size(); ++j)
				{
					if(std::holds_alternative<long long>(m_http_args.at(j).m_value))
					{
						http_body.append("\"" + m_http_args.at(j).m_key + "\": " + std::to_string(std::get<long long>(m_http_args.at(j).m_value)));

						//Add "," for the next key value pair.
						if(j != m_http_args.size() - 1)
							http_body.append(", ");
					}
					else if(std::holds_alternative<std::string>(m_http_args.at(j).m_value))
					{
						http_body.append("\"" + m_http_args.at(j).m_key + "\": \"" + std::get<std::string>(m_http_args.at(j).m_value) + "\"");

						//Add "," for the next key value pair.
						if(j != m_http_args.size() - 1)
							http_body.append(", ");
					}
					//The value of type InputFile::ptr is ignored.
				}

				http_body.append("}");
			}

			//Check whether it is necessary to URL parse the HTTP body.
			for(std::size_t j = 0; j < m_http_headers.size(); ++j)
			{
				if(m_http_headers.at(j).m_key == "Content-Type" &&  m_http_headers.at(j).m_value.find("application/x-www-form-urlencoded") != std::string::npos)
				{
					http_body = tools::Tools::parse_url(http_body);
					break;
				}
			}

			if(!http_body.empty())
				req.setContentLength(http_body.length());

			//Send the request.
	        std::ostream& os = session.sendRequest(req);
	        //Send the body.
	        os << http_body;

	        //Print the request to stdout if the debugging mode is on.
	        if(debug == true)
	        {
	        	std::cout << Constants::ansii_bold_cyan << Messages::req << Constants::ansii_reset << std::endl;
	        	std::cout << Constants::ansii_cyan;
	        	req.write(std::cout);
				std::cout << http_body << Constants::ansii_reset << std::endl;
	        }

	        //Response
			Poco::Net::HTTPResponse response;
			std::ostringstream oss;
			std::istream &in = session.receiveResponse(response);
			http_response_code = response.getStatus();
			Poco::StreamCopier::copyStream(in, oss);

			//Check whether the response HTTP body is gzipped. If so, decompress it.
			if(tools::Tools::is_gzipped(oss.str()))
				http_response_body = tools::Tools::gzip_decompress(oss.str());
			else
				http_response_body = oss.str();

			//Print the response if the debugging mode is on.
			if(debug == true)
			{
				Poco::Net::NameValueCollection::ConstIterator j = response.begin();
				std::string http_repsonse_headers;

				while(j != response.end())
				{
					http_repsonse_headers.append(j->first + ": " + j->second + "\n");
					++j;
				}

				//Remove the last new line.
				if(!http_repsonse_headers.empty())
					http_repsonse_headers.pop_back();

				std::cout << Constants::ansii_bold_bright_cyan << Messages::resp(http_response_code) << Constants::ansii_reset << std::endl;
	        	std::cout << Constants::ansii_bright_cyan << http_repsonse_headers << std::endl;
				std::cout << http_response_body << Constants::ansii_reset << std::endl;
			}

			if(http_response_code != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK && m_print_error)
			{
				//Gather the request but do not log it now.
				std::string tmp = Messages::http_response_code_not_200 + "\n";
				tmp.append(Messages::req + "\n");
				std::stringstream ss;
				req.write(ss);
				tmp.append(ss.str() + "\n");
				tmp.append(http_body + "\n");

				//Get the response and log request and response.
				Poco::Net::NameValueCollection::ConstIterator j = response.begin();
				std::string http_repsonse_headers;

				while(j != response.end())
				{
					http_repsonse_headers.append(j->first + ": " + j->second + "\n");
					++j;
				}

				//Remove the last new line.
				if(!http_repsonse_headers.empty())
					http_repsonse_headers.pop_back();

				tmp.append(Messages::resp(http_response_code) + "\n");
				tmp.append(http_repsonse_headers + "\n");
				tmp.append(http_response_body);
				Tools::write_err_log_tmp(tmp);

				//HTTP response
				std::vector<HttpHeader> temp_http_headers;
				Poco::Net::NameValueCollection::ConstIterator k = response.begin();

				while(k != response.end())
				{
					HttpHeader http_header(k->first, k->second);
					temp_http_headers.push_back(http_header);
					++k;
				}

				std::vector<HttpCookie> http_cookies;

				for(std::size_t j = 0; j < temp_http_headers.size(); ++j)
				{
					if(boost::iequals(temp_http_headers.at(j).m_key, "Set-Cookie"))
						http_cookies.push_back(HttpCookie(temp_http_headers.at(j).m_value));
				}

				HttpResponse http_response(http_response_code, temp_http_headers, http_response_body, http_cookies);
				return http_response;
			}

			//HTTP response
			std::vector<HttpHeader> temp_http_headers;
			Poco::Net::NameValueCollection::ConstIterator j = response.begin();

			while(j != response.end())
			{
				HttpHeader http_header(j->first, j->second);
				temp_http_headers.push_back(http_header);
				++j;
			}

			std::vector<HttpCookie> http_cookies;

			for(std::size_t j = 0; j < temp_http_headers.size(); ++j)
			{
				if(boost::iequals(temp_http_headers.at(j).m_key, "Set-Cookie"))
					http_cookies.push_back(HttpCookie(temp_http_headers.at(j).m_value));
			}

			HttpResponse http_response(http_response_code, temp_http_headers, http_response_body, http_cookies);
			return http_response;
		}
		catch(const std::exception &e)
		{
			Tools::write_err_log_tmp(e.what());

			//The HTTP response is without the HTTP headers as they are not accessible here.
			HttpResponse http_response(http_response_code, std::vector<HttpHeader>(), http_response_body, std::vector<HttpCookie>());
			return http_response;
		}
	}

	HttpResponse HttpClient::send_post_req_urlencoded(std::string http_body, const bool &debug) const noexcept
	{
		Poco::Net::HTTPResponse::HTTPStatus http_response_code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;;
		std::string http_response_body;

		try
		{
			//URI
			Poco::URI uri(m_url);
			std::string path_query = uri.getPathAndQuery();
			if(path_query.empty())
				path_query = "/";

			//Request
		    const Poco::Net::Context::Ptr context = new Poco::Net::Context(
		        Poco::Net::Context::CLIENT_USE, "", "", "",
		        Poco::Net::Context::VERIFY_NONE, 9, false,
		        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
			Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path_query, Poco::Net::HTTPMessage::HTTP_1_1);

			//Options and headers
	        for(std::size_t j = 0; j < m_http_headers.size(); ++j)
	            req.set(m_http_headers.at(j).m_key, m_http_headers.at(j).m_value);

			session.setTimeout(Poco::Timespan(150L, 0L));

			//Check whether it is necessary to URL parse the HTTP body.
			for(std::size_t j = 0; j < m_http_headers.size(); ++j)
			{
				if(m_http_headers.at(j).m_key == "Content-Type" &&  m_http_headers.at(j).m_value.find("application/x-www-form-urlencoded") != std::string::npos)
				{
					http_body = tools::Tools::parse_url(http_body);
					break;
				}
			}

			//HTTP body
			if(!http_body.empty())
				req.setContentLength(http_body.length());

			//Send the request.
	        std::ostream& os = session.sendRequest(req);
	        //Send the body.
	        os << http_body;

	        //Print the request to stdout if the debugging mode is on.
	        if(debug == true)
	        {
	        	std::cout << Constants::ansii_bold_cyan << Messages::req << Constants::ansii_reset << std::endl;
	        	std::cout << Constants::ansii_cyan;
	        	req.write(std::cout);
				std::cout << http_body << Constants::ansii_reset << std::endl;
	        }

	        //Response
			Poco::Net::HTTPResponse response;
			std::ostringstream oss;
			std::istream &in = session.receiveResponse(response);
			http_response_code = response.getStatus();
			Poco::StreamCopier::copyStream(in, oss);

			//Check whether the response HTTP body is gzipped. If so, decompress it.
			if(tools::Tools::is_gzipped(oss.str()))
				http_response_body = tools::Tools::gzip_decompress(oss.str());
			else
				http_response_body = oss.str();

			//Print the response if the debugging mode is on.
			if(debug == true)
			{
				Poco::Net::NameValueCollection::ConstIterator j = response.begin();
				std::string http_repsonse_headers;

				while(j != response.end())
				{
					http_repsonse_headers.append(j->first + ": " + j->second + "\n");
					++j;
				}

				//Remove the last new line.
				if(!http_repsonse_headers.empty())
					http_repsonse_headers.pop_back();

				std::cout << Constants::ansii_bold_bright_cyan << Messages::resp(http_response_code) << Constants::ansii_reset << std::endl;
	        	std::cout << Constants::ansii_bright_cyan << http_repsonse_headers << std::endl;
				std::cout << http_response_body << Constants::ansii_reset << std::endl;
			}

			if(http_response_code != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK && m_print_error)
			{
				//Gather the request but do not log it now.
				std::string tmp = Messages::http_response_code_not_200 + "\n";
				tmp.append(Messages::req + "\n");
				std::stringstream ss;
				req.write(ss);
				tmp.append(ss.str() + "\n");
				tmp.append(http_body + "\n");

				//Get the response and log request and response.
				Poco::Net::NameValueCollection::ConstIterator j = response.begin();
				std::string http_repsonse_headers;

				while(j != response.end())
				{
					http_repsonse_headers.append(j->first + ": " + j->second + "\n");
					++j;
				}

				//Remove the last new line.
				if(!http_repsonse_headers.empty())
					http_repsonse_headers.pop_back();

				tmp.append(Messages::resp(http_response_code) + "\n");
				tmp.append(http_repsonse_headers + "\n");
				tmp.append(http_response_body);
				Tools::write_err_log_tmp(tmp);

				//HTTP response
				std::vector<HttpHeader> temp_http_headers;
				Poco::Net::NameValueCollection::ConstIterator k = response.begin();

				while(k != response.end())
				{
					HttpHeader http_header(k->first, k->second);
					temp_http_headers.push_back(http_header);
					++k;
				}

				std::vector<HttpCookie> http_cookies;

				for(std::size_t j = 0; j < temp_http_headers.size(); ++j)
				{
					if(boost::iequals(temp_http_headers.at(j).m_key, "Set-Cookie"))
						http_cookies.push_back(HttpCookie(temp_http_headers.at(j).m_value));
				}

				HttpResponse http_response(http_response_code, temp_http_headers, http_response_body, http_cookies);
				return http_response;
			}

			//HTTP response
			std::vector<HttpHeader> temp_http_headers;
			Poco::Net::NameValueCollection::ConstIterator j = response.begin();

			while(j != response.end())
			{
				HttpHeader http_header(j->first, j->second);
				temp_http_headers.push_back(http_header);
				++j;
			}

			std::vector<HttpCookie> http_cookies;

			for(std::size_t j = 0; j < temp_http_headers.size(); ++j)
			{
				if(boost::iequals(temp_http_headers.at(j).m_key, "Set-Cookie"))
					http_cookies.push_back(HttpCookie(temp_http_headers.at(j).m_value));
			}

			HttpResponse http_response(http_response_code, temp_http_headers, http_response_body, http_cookies);
			return http_response;
		}
		catch(const std::exception &e)
		{
			Tools::write_err_log_tmp(e.what());

			//The HTTP response is without the HTTP headers as they are not accessible here.
			HttpResponse http_response(http_response_code, std::vector<HttpHeader>(), http_response_body, std::vector<HttpCookie>());
			return http_response;
		}
	}

	HttpResponse HttpClient::send_post_req_multipart(const bool &debug) const noexcept
	{
		Poco::Net::HTTPResponse::HTTPStatus http_response_code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;;
		std::string http_response_body;

		try
		{
			//URI
			Poco::URI uri(m_url);
			std::string path_query = uri.getPathAndQuery();
			if(path_query.empty())
				path_query = "/";

			//Request
		    const Poco::Net::Context::Ptr context = new Poco::Net::Context(
		        Poco::Net::Context::CLIENT_USE, "", "", "",
		        Poco::Net::Context::VERIFY_NONE, 9, false,
		        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
			Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path_query, Poco::Net::HTTPMessage::HTTP_1_1);

			//Options and headers
	        for(std::size_t j = 0; j < m_http_headers.size(); ++j)
	            req.set(m_http_headers.at(j).m_key, m_http_headers.at(j).m_value);

			session.setTimeout(Poco::Timespan(150L, 0L));

			//HTML form
			Poco::Net::HTMLForm form(Poco::Net::HTMLForm::ENCODING_MULTIPART);

			//Add each field.
			for(std::size_t j = 0; j < m_http_args.size(); ++j)
			{
				if(std::holds_alternative<long long>(m_http_args.at(j).m_value))
					form.set(m_http_args.at(j).m_key, std::to_string(std::get<long long>(m_http_args.at(j).m_value)));
				else if(std::holds_alternative<std::string>(m_http_args.at(j).m_value))
					form.set(m_http_args.at(j).m_key, std::get<std::string>(m_http_args.at(j).m_value));
				else if(std::holds_alternative<InputFile::ptr>(m_http_args.at(j).m_value))
					form.addPart(m_http_args.at(j).m_key, new Poco::Net::FilePartSource(std::get<InputFile::ptr>(m_http_args.at(j).m_value)->m_path));
			}

			//Send the request.
			form.prepareSubmit(req);
			form.write(session.sendRequest(req));

			//Print the request to stdout if the debugging mode is on.
	        if(debug == true)
	        {
				std::string temp_http_args;

				//The type InputFile is neglected.
				for(std::size_t j = 0; j < m_http_args.size(); ++j)
				{
					if(std::holds_alternative<long long>(m_http_args.at(j).m_value))
						temp_http_args.append(m_http_args.at(j).m_key + "=" + std::to_string(std::get<long long>(m_http_args.at(j).m_value)));
					else if(std::holds_alternative<std::string>(m_http_args.at(j).m_value))
						temp_http_args.append(m_http_args.at(j).m_key + "=" + std::get<std::string>(m_http_args.at(j).m_value));

					if(j != m_http_args.size() - 1)
						temp_http_args.append("\n");
				}

	        	std::cout << Constants::ansii_bold_cyan << Messages::req << Constants::ansii_reset << std::endl;
	        	std::cout << Constants::ansii_cyan;
	        	req.write(std::cout);
				std::cout << temp_http_args << Constants::ansii_reset << std::endl;
	        }

	        //Response
			Poco::Net::HTTPResponse response;
			std::ostringstream oss;
			std::istream &in = session.receiveResponse(response);
			http_response_code = response.getStatus();
			Poco::StreamCopier::copyStream(in, oss);

			//Check whether the response HTTP body is gzipped. If so, decompress it.
			if(tools::Tools::is_gzipped(oss.str()))
				http_response_body = tools::Tools::gzip_decompress(oss.str());
			else
				http_response_body = oss.str();

			//Print the response if the debugging mode is on.
			if(debug == true)
			{
				Poco::Net::NameValueCollection::ConstIterator j = response.begin();
				std::string http_repsonse_headers;

				while(j != response.end())
				{
					http_repsonse_headers.append(j->first + ": " + j->second + "\n");
					++j;
				}

				//Remove the last new line.
				if(!http_repsonse_headers.empty())
					http_repsonse_headers.pop_back();

				std::cout << Constants::ansii_bold_bright_cyan << Messages::resp(http_response_code) << Constants::ansii_reset << std::endl;
	        	std::cout << Constants::ansii_bright_cyan << http_repsonse_headers << std::endl;
				std::cout << http_response_body << Constants::ansii_reset << std::endl;
			}

			if(http_response_code != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK && m_print_error)
			{
				//Gather the request but do not log it now.
				std::string temp_http_args;

				//The type InputFile is neglected.
				for(std::size_t j = 0; j < m_http_args.size(); ++j)
				{
					if(std::holds_alternative<long long>(m_http_args.at(j).m_value))
						temp_http_args.append(m_http_args.at(j).m_key + "=" + std::to_string(std::get<long long>(m_http_args.at(j).m_value)));
					else if(std::holds_alternative<std::string>(m_http_args.at(j).m_value))
						temp_http_args.append(m_http_args.at(j).m_key + "=" + std::get<std::string>(m_http_args.at(j).m_value));

					if(j != m_http_args.size() - 1)
						temp_http_args.append("\n");
				}

				std::string tmp = Messages::http_response_code_not_200 + "\n";
				tmp.append(Messages::req + "\n");
				std::stringstream ss;
				req.write(ss);
				tmp.append(ss.str() + "\n");
				tmp.append(temp_http_args + "\n");

				//Get the response and log request and response.
				Poco::Net::NameValueCollection::ConstIterator j = response.begin();
				std::string http_repsonse_headers;

				while(j != response.end())
				{
					http_repsonse_headers.append(j->first + ": " + j->second + "\n");
					++j;
				}

				//Remove the last new line.
				if(!http_repsonse_headers.empty())
					http_repsonse_headers.pop_back();

				tmp.append(Messages::resp(http_response_code) + "\n");
				tmp.append(http_repsonse_headers + "\n");
				tmp.append(http_response_body);
				Tools::write_err_log_tmp(tmp);

				//HTTP response
				std::vector<HttpHeader> temp_http_headers;
				Poco::Net::NameValueCollection::ConstIterator k = response.begin();

				while(k != response.end())
				{
					HttpHeader http_header(k->first, k->second);
					temp_http_headers.push_back(http_header);
					++k;
				}

				std::vector<HttpCookie> http_cookies;

				for(std::size_t j = 0; j < temp_http_headers.size(); ++j)
				{
					if(boost::iequals(temp_http_headers.at(j).m_key, "Set-Cookie"))
						http_cookies.push_back(HttpCookie(temp_http_headers.at(j).m_value));
				}

				HttpResponse http_response(http_response_code, temp_http_headers, http_response_body, http_cookies);
				return http_response;
			}

			//HTTP response
			std::vector<HttpHeader> temp_http_headers;
			Poco::Net::NameValueCollection::ConstIterator j = response.begin();

			while(j != response.end())
			{
				HttpHeader http_header(j->first, j->second);
				temp_http_headers.push_back(http_header);
				++j;
			}

			std::vector<HttpCookie> http_cookies;

			for(std::size_t j = 0; j < temp_http_headers.size(); ++j)
			{
				if(boost::iequals(temp_http_headers.at(j).m_key, "Set-Cookie"))
					http_cookies.push_back(HttpCookie(temp_http_headers.at(j).m_value));
			}

			HttpResponse http_response(http_response_code, temp_http_headers, http_response_body, http_cookies);
			return http_response;
		}
		catch(const std::exception &e)
		{
			Tools::write_err_log_tmp(e.what());

			//The HTTP response is without the HTTP headers as they are not accessible here.
			HttpResponse http_response(http_response_code, std::vector<HttpHeader>(), http_response_body, std::vector<HttpCookie>());
			return http_response;
		}
	}

	std::string HttpClient::get_url() const noexcept
	{
		return m_url;
	}

	std::vector<HttpHeader> HttpClient::get_http_headers() const noexcept
	{
		return m_http_headers;
	}

	std::vector<HttpArg> HttpClient::get_http_args() const noexcept
	{
		return m_http_args;
	}

	bool HttpClient::get_print_error() const noexcept
	{
		return m_print_error;
	}
}
