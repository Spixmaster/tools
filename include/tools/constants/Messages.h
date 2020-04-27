#ifndef TOOLS_CONSTANTS_MESSAGES_H
#define TOOLS_CONSTANTS_MESSAGES_H

#include <string>
#include <memory>

namespace tools
{
	/**
	 * @class Messages
	 * @brief The class contains messages which are used throughout the programme.
	 * @details It is a monostate.
	 */
	class Messages
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<Messages> ptr;

		//Member variables
		/**
		 * @var given_str_empty
		 * @brief Message that the given string is empty.
		 */
		static const std::string given_str_empty;
		/**
		 * @var not_gzip_compressed
		 * @brief Message that the data is not compressed with GZIP.
		 */
		static const std::string not_gzip_compressed;
		/**
		 * @var http_response_code_not_200
		 * @brief Message that the HTTP status code is not 200.
		 */
		static const std::string http_response_code_not_200;
		/**
		 * @var not_pos_int
		 * @brief Message that the string or number is not a positive integer.
		 */
		static const std::string not_pos_int;
		/**
		 * @var req
		 * @brief This string is used before outputting the HTTP request in the debug mode.
		 */
		static const std::string req;

		//Member functions
		/**
		 * @brief Logs an error message that the file does not exist.
		 * @param[in] file The file name which is included in the error message.
		 */
		static void file_non_existent(const std::string &file) noexcept;

		/**
		 * @brief Returns a message that asks for a positive line number as there are no negative ones.
		 * @param[in] file The file name which is included in the error message.
		 * @return The message
		 */
		static std::string enter_pos_num_to_read_in_file(const std::string &file) noexcept;

		/**
		 * @brief Returns a message that states that there are no numerals at the end of the string.
		 * @param[in] str The string where the numbers at the end are missing.
		 * @return The message
		 */
		static std::string no_num_str_end(const std::string &str) noexcept;

		/**
		 * @brief Returns a message that states that the given file cannot be deleted.
		 * @param[in] file The file name which is included in the error message.
		 * @return The message
		 */
		static std::string file_del_err(const std::string &file) noexcept;

		/**
		 * @brief The introduction for the following HTTP response.
		 * @param[in] status_code The status code of the HTTP response.
		 * @return The message.
		 */
		static std::string resp(const int &status_code) noexcept;
	};
}

#endif
