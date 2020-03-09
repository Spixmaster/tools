#ifndef TOOLS_CONSTANTS_MESSAGES_H
#define TOOLS_CONSTANTS_MESSAGES_H

#include <string>
#include <memory>

/*
 * @brief class contains messages which are used throughout the programme
 * @brief it is a monostate
 */

namespace tools
{
	class Messages
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<Messages> ptr;

		//member variables
		static const std::string given_str_empty;
		static const std::string not_gzip_compressed;
		static const std::string http_response_code_not_200;
		static const std::string not_pos_int;

		//member functions
		/*
		 * @brief puts an error message out to stderr
		 * @param file: the filename which is included in the error message
		 */
		static void file_non_existent(const std::string &file) noexcept;

		/*
		 * @brief message that asks for a positive line number as there are no negative ones
		 * @param file: the filename which is included in the error message
		 * @return the message
		 */
		static std::string enter_pos_num_to_read_in_file(const std::string &file) noexcept;

		/*
		 * @brief message that states that there are no numerals at the end of the string
		 * @param str: the string where the numbers at the end are missing
		 * @return the message
		 */
		static std::string no_num_str_end(const std::string &str) noexcept;
	};
}

#endif
