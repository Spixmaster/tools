#include "tools/http/HttpCookie.h"
#include "tools/Tools.h"
#include <iostream>

namespace tools
{
	HttpCookie::HttpCookie(const std::string &set_cookie_val)
	{
		for(size_t j = 0; j < set_cookie_val.size(); ++j)
		{
			if(set_cookie_val.at(j) != '=')
				m_name += set_cookie_val.at(j);
			else
				break;
		}
		m_value = get_val(set_cookie_val, m_name);
		m_domain = get_val(set_cookie_val, "Domain");
		m_path = get_val(set_cookie_val, "Path");
		m_expires = get_val(set_cookie_val, "expires");
		try
		{
			if(!get_val(set_cookie_val, "Max-Age").empty())
				m_max_age = std::stoi(get_val(set_cookie_val, "Max-Age"));
			else
				m_max_age = -1;
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		m_http_only = set_cookie_val.find("HttpOnly") != std::string::npos ? true : false;
		m_secure = set_cookie_val.find("Secure") != std::string::npos ? true : false;
	}

	std::string HttpCookie::get_val(const std::string &cont, const std::string &key)
	{
		bool key_found = false;

		//iterate through the content
		for(size_t j = 0; j < cont.size(); ++j)
		{
			//we iterate through the content as long as we have found the key's first char
			if(cont.at(j) == key.at(0))
			{
				/*
				 * save the value of j so that we do not manipulate it itself
				 * now, we iterate through the key and check whether is corresponds to the following content chars
				 */
				size_t temp = j;
				//iterate through the key
				for(size_t k = 0; k < key.size(); ++k)
				{
					/*
					 * check whether we are still in the range of cont to access cont.at(temp)
					 * -1 as we check whether the next char is '='
					 */
					if(temp < (cont.size() - 1))
					{
						if(!(cont.at(temp) == key.at(k)))
							break;

						/*
						 * the key is found when we were able to iterate through the whole key without breaking out of the loop
						 * additional conditions: next char in cont would be '='
						 */
						if(k == key.size() - 1 && cont.at(temp + 1) == '=')
							key_found = true;

						++temp;
					}
					else
						break;
				}

				//get the value
				std::string val;
				if(key_found == true)
				{
					//right now, temp is at the '=' in cont
					for(size_t l = temp + 1; l < cont.size(); ++l)
					{
						if(cont.at(l) == ';')
							break;

						val += cont.at(l);
					}
					return val;
				}
			}
		}
		return "";
	}

	std::string HttpCookie::get_name() const
	{
		return m_name;
	}

	std::string HttpCookie::get_value() const
	{
		return m_value;
	}

	std::string HttpCookie::get_domain() const
	{
		return m_domain;
	}

	std::string HttpCookie::get_path() const
	{
		return m_path;
	}

	std::string HttpCookie::get_expires() const
	{
		return m_expires;
	}

	int HttpCookie::get_max_age() const
	{
		return m_max_age;
	}

	bool HttpCookie::get_http_only() const
	{
		return m_http_only;
	}

	bool HttpCookie::get_secure() const
	{
		return m_secure;
	}
}
