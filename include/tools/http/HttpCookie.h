#ifndef TOOLS_HTTP_HTTPCOOKIE_H
#define TOOLS_HTTP_HTTPCOOKIE_H

#include <string>
#include <memory>

namespace tools
{
	/**
	 * @class HttpCookie
	 * @brief A container which expects the value of a "Set-Cookie" header and makes each attribute accessible via a member variable
	 * @details It allows access to all the cookie's properties.
	 */
	class HttpCookie
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<HttpCookie> ptr;

	private:
		//Member variables
		/**
		 * @var m_origin
		 * @brief The raw cookie which this container class received.
		 */
		std::string m_origin;
		//Cookie traits
		/**
		 * @m_name
		 * @brief A cookie value for the proper key.
		 */
		std::string m_name;
		/**
		 * @m_value
		 * @brief A cookie value for the proper key.
		 */
		std::string m_value;
		/**
		 * @m_domain
		 * @brief A cookie value for the proper key.
		 */
		std::string m_domain;
		/**
		 * @m_path
		 * @brief A cookie value for the proper key.
		 */
		std::string m_path;
		/**
		 * @m_expires
		 * @brief A cookie value for the proper key.
		 */
		std::string m_expires;
		/**
		 * @m_max_age
		 * @brief A cookie value for the proper key.
		 */
		int m_max_age;
		/**
		 * @m_http_only
		 * @brief A cookie value for the proper key.
		 */
		bool m_http_only;
		/**
		 * @m_secure
		 * @brief A cookie value for the proper key.
		 */
		bool m_secure;

	public:
		//Constructors
		/**
		 * @param[in] set_cookie_val The value of the HTTP header "Set-Cookie".
		 */
		HttpCookie(const std::string &set_cookie_val);

	private:
		//Member functions
		/**
		 * @brief It gets the value of a key value pair only when is in the following format: "key=value;".
		 * @details "key=value" is accepted too but only if the value is the end of the given string.
		 * @details Example: csrftoken=tm6NSZWRJk57zpkLfPHygPnrea10wJS5; Domain=.instagram.com; expires=Sat, 12-Dec-2020 07:13:39 GMT; Max-Age=31449600; Path=/; Secure
		 * @param[in] cont The location where to search or better said the HTTP header value of "Set-Cookie".
		 * @param[in] key The key of the value that we want.
		 * @return The found value.
		 */
		static std::string get_val(const std::string &cont, const std::string &key) noexcept;

	public:
		/**
		 * @brief Getter.
		 * @return m_origin
		 */
		std::string to_string() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_name
		 */
		std::string get_name() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_value
		 */
		std::string get_value() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_domain
		 */
		std::string get_domain() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_path
		 */
		std::string get_path() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_expires
		 */
		std::string get_expires() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_max_age
		 */
		int get_max_age() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_http_only
		 */
		bool get_http_only() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_secure
		 */
		bool get_secure() const noexcept;
	};
}

#endif
