#ifndef TOOLS_HTTP_HTTPCOOKIE_H
#define TOOLS_HTTP_HTTPCOOKIE_H

#include <string>
#include <memory>

/*
 * @brief a container which expects the value of a "Set-Cookie" header
 * @brief it allows access to all the cookie's properties
 */

namespace tools
{
	class HttpCookie
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<HttpCookie> ptr;

	private:
		//member variables
			//
		std::string m_origin;
			//cookie traits
		std::string m_name;
		std::string m_value;
		std::string m_domain;
		std::string m_path;
		std::string m_expires;
		int m_max_age;
		bool m_http_only;
		bool m_secure;

	public:
		//constructors

		//@param set_cookie_val: value of the http header "Set-Cookie"
		HttpCookie(const std::string &set_cookie_val);

	private:
		//member functions
		/*
		 * @brief gets the value of a key value pair only which is in the following format: key=value;
		 * @brief key=value is accepted too but only if the value is the end of the given string
		 * @example csrftoken=tm6NSZWRJk57zpkLfPHygPnrea10wJS5; Domain=.instagram.com; expires=Sat, 12-Dec-2020 07:13:39 GMT; Max-Age=31449600; Path=/; Secure
		 * @param cont: location where to search
		 * @param key: key of the value that we want
		 * @return the found value
		 */
		static std::string get_val(const std::string &cont, const std::string &key) noexcept;

	public:
		/*
		 * @brief getter
		 * @return m_origin
		 */
		std::string to_string() const noexcept;

		/*
		 * @brief getter
		 * @return m_name
		 */
		std::string get_name() const noexcept;

		/*
		 * @brief getter
		 * @return m_value
		 */
		std::string get_value() const noexcept;

		/*
		 * @brief getter
		 * @return m_domain
		 */
		std::string get_domain() const noexcept;

		/*
		 * @brief getter
		 * @return m_path
		 */
		std::string get_path() const noexcept;

		/*
		 * @brief getter
		 * @return m_expires
		 */
		std::string get_expires() const noexcept;

		/*
		 * @brief getter
		 * @return m_max_age
		 */
		int get_max_age() const noexcept;

		/*
		 * @brief getter
		 * @return m_http_only
		 */
		bool get_http_only() const noexcept;

		/*
		 * @brief getter
		 * @return m_secure
		 */
		bool get_secure() const noexcept;
	};
}

#endif
