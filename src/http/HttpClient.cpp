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

namespace tools
{
	HttpClient::HttpClient(const std::string &url) : m_url(url)
	{}

	HttpClient::HttpClient(const std::string &url, const std::vector<HttpArg> &http_args) : m_url(url), m_http_args(http_args)
	{}

	HttpClient::HttpClient(const std::string &url, const std::vector<HttpArg> &http_args, const std::map<std::string, std::string> &headers) :
			m_url(url), m_http_args(http_args), m_headers(headers)
	{}

	HttpResponse HttpClient::send_get_req(const bool &debug)
	{
		Poco::Net::HTTPResponse::HTTPStatus http_response_code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;
		std::string http_response_txt;

		try
		{
			//uri
			Poco::URI uri(m_url);
			std::string path_query = uri.getPathAndQuery();
			if(path_query.empty())
				path_query = "/";

			//request
		    const Poco::Net::Context::Ptr context = new Poco::Net::Context(
		        Poco::Net::Context::CLIENT_USE, "", "", "",
		        Poco::Net::Context::VERIFY_NONE, 9, false,
		        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
			Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path_query, Poco::Net::HTTPMessage::HTTP_1_1);

	        	//options and headers
	        for(std::map<std::string, std::string>::iterator it = m_headers.begin(); it != m_headers.end(); ++it)
	            req.set(it->first, it->second);
	        session.setTimeout(Poco::Timespan(150L, 0L));

	        //send the request
	        session.sendRequest(req);
	        //print request to stdout
	        if(debug == true)
	        	req.write(std::cout);

			//response
			Poco::Net::HTTPResponse response;
			std::ostringstream oss;
			std::istream  &in = session.receiveResponse(response);
			http_response_code = response.getStatus();
			Poco::StreamCopier::copyStream(in, oss);
			http_response_txt = oss.str();

			if(http_response_code != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK)
			{
				std::cerr << "Error: Request's http code is not 200!" << std::endl;
				std::cerr << "http status code: " << http_response_code << std::endl;
				std::cerr << "http response text: " << http_response_txt << std::endl;

				HttpResponse http_response;
				http_response.code = http_response_code;
				http_response.txt = http_response_txt;
				return http_response;
			}

			HttpResponse http_response;
			http_response.code = http_response_code;
			http_response.txt = http_response_txt;
			return http_response;
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;

			HttpResponse http_response;
			http_response.code = http_response_code;
			http_response.txt = http_response_txt;
			return http_response;
		}
	}

	HttpResponse HttpClient::send_post_req_urlencoded(const bool &debug)
	{
		Poco::Net::HTTPResponse::HTTPStatus http_response_code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;;
		std::string http_response_txt;

		try
		{
			//uri
			Poco::URI uri(m_url);
			std::string path_query = uri.getPathAndQuery();
			if(path_query.empty())
				path_query = "/";

			//request
		    const Poco::Net::Context::Ptr context = new Poco::Net::Context(
		        Poco::Net::Context::CLIENT_USE, "", "", "",
		        Poco::Net::Context::VERIFY_NONE, 9, false,
		        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
			Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path_query, Poco::Net::HTTPMessage::HTTP_1_1);

				//options and headers
			for(std::map<std::string, std::string>::iterator it = m_headers.begin(); it != m_headers.end(); ++it)
				req.set(it->first, it->second);
			session.setTimeout(Poco::Timespan(150L, 0L));

				//http body
			std::string http_body;
			for (std::size_t j = 0; j < m_http_args.size(); ++j)
			{
				if(std::holds_alternative<long long>(m_http_args.at(j).m_value))
					http_body.append(m_http_args.at(j).m_key + "=" + std::to_string(std::get<long long>(m_http_args.at(j).m_value)));
				else if(std::holds_alternative<std::string>(m_http_args.at(j).m_value))
					http_body.append(m_http_args.at(j).m_key + "=" + std::get<std::string>(m_http_args.at(j).m_value));
				//value is type of InputFile::ptr and thus ignored

				//add & for next key value pair
				if(j < (m_http_args.size() - 1))
					http_body.append("&");
			}
			req.setContentLength(http_body.length());

			//send the request
	        std::ostream& os = session.sendRequest(req);
	        //send the body
	        os << http_body;
	        //print request to stdout
	        if(debug == true)
	        	req.write(std::cout);

			//response
			Poco::Net::HTTPResponse response;
			std::ostringstream oss;
			std::istream  &in = session.receiveResponse(response);
			http_response_code = response.getStatus();
			Poco::StreamCopier::copyStream(in, oss);
			http_response_txt = oss.str();

			if(http_response_code != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK)
			{
				std::cerr << "Error: Request's http code is not 200!" << std::endl;
				std::cerr << "http status code: " << http_response_code << std::endl;
				std::cerr << "http response text: " << http_response_txt << std::endl;

				HttpResponse http_response;
				http_response.code = http_response_code;
				http_response.txt = http_response_txt;
				return http_response;
			}

			HttpResponse http_response;
			http_response.code = http_response_code;
			http_response.txt = http_response_txt;
			return http_response;
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;

			HttpResponse http_response;
			http_response.code = http_response_code;
			http_response.txt = http_response_txt;
			return http_response;
		}
	}

	HttpResponse HttpClient::send_post_req_multipart(const bool &debug)
	{
		Poco::Net::HTTPResponse::HTTPStatus http_response_code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;;
		std::string http_response_txt;

		try
		{
			//uri
			Poco::URI uri(m_url);
			std::string path_query = uri.getPathAndQuery();
			if(path_query.empty())
				path_query = "/";

			//request
		    const Poco::Net::Context::Ptr context = new Poco::Net::Context(
		        Poco::Net::Context::CLIENT_USE, "", "", "",
		        Poco::Net::Context::VERIFY_NONE, 9, false,
		        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
			Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path_query, Poco::Net::HTTPMessage::HTTP_1_1);

				//options and headers
			for(std::map<std::string, std::string>::iterator it = m_headers.begin(); it != m_headers.end(); ++it)
				req.set(it->first, it->second);
			session.setTimeout(Poco::Timespan(150L, 0L));

				//html form
			Poco::Net::HTMLForm form(Poco::Net::HTMLForm::ENCODING_MULTIPART);
					//add each field
			for (std::size_t j = 0; j < m_http_args.size(); ++j)
			{
				if(std::holds_alternative<long long>(m_http_args.at(j).m_value))
					form.set(m_http_args.at(j).m_key, std::to_string(std::get<long long>(m_http_args.at(j).m_value)));
				else if(std::holds_alternative<std::string>(m_http_args.at(j).m_value))
					form.set(m_http_args.at(j).m_key, std::get<std::string>(m_http_args.at(j).m_value));
				//value is type of InputFile::ptr
				else
					form.addPart(m_http_args.at(j).m_key, new Poco::Net::FilePartSource(std::get<InputFile::ptr>(m_http_args.at(j).m_value)->m_path));
			}

			//send the request
			form.prepareSubmit(req);
			form.write(session.sendRequest(req));
	        //print request to stdout
			if(debug == true)
	        	req.write(std::cout);

			//response
			Poco::Net::HTTPResponse response;
			std::ostringstream oss;
			std::istream  &in = session.receiveResponse(response);
			http_response_code = response.getStatus();
			Poco::StreamCopier::copyStream(in, oss);
			http_response_txt = oss.str();

			if(http_response_code != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK)
			{
				std::cerr << "Error: Request's http code is not 200!" << std::endl;
				std::cerr << "http status code: " << http_response_code << std::endl;
				std::cerr << "http response text: " << http_response_txt << std::endl;

				HttpResponse http_response;
				http_response.code = http_response_code;
				http_response.txt = http_response_txt;
				return http_response;
			}

			HttpResponse http_response;
			http_response.code = http_response_code;
			http_response.txt = http_response_txt;
			return http_response;
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;

			HttpResponse http_response;
			http_response.code = http_response_code;
			http_response.txt = http_response_txt;
			return http_response;
		}
	}
}
