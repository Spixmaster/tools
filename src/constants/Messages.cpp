#include "tools/constants/Messages.h"
#include <string>
#include <iostream>

namespace tools
{
	const std::string Messages::given_str_empty = "Error: The given string is empty.";
	const std::string Messages::not_gzip_compressed = "Error: That is not gzip compressed data.";
	const std::string Messages::http_response_code_not_200 = "Error: Response's http code is not 200!";

	void Messages::file_non_existent(const std::string &file) noexcept
	{
		std::cerr << "Error: The file \"" + file + "\" does not exist." << std::endl;
	}

	std::string Messages::enter_pos_num_to_read_in_file(const std::string &file) noexcept
	{
		return std::string("Error: You need to enter a positive value and greater than 0 to read in") + " \"" + file + "\".";
	}

	std::string Messages::no_num_str_end(const std::string &str) noexcept
	{
		return "Error: There are no numerals at the end of the string: \"" + str + "\"";
	}
}
