#include "tools/Constants.h"
#include <string>
#include <iostream>

namespace tools
{
	const std::string Constants::version = "1.1.35";
	const std::string Constants::release = "21.Feb.2020";
	const std::string Constants::ansi_reset = "\x1B[0m";
	const std::string Constants::ansi_black = "\x1B[30m";
	const std::string Constants::ansi_red = "\x1B[31m";
	const std::string Constants::ansi_green = "\x1B[32m";
	const std::string Constants::ansi_yellow = "\x1B[33m";
	const std::string Constants::ansi_blue = "\x1B[34m";
	const std::string Constants::ansi_magenta = "\x1B[35m";
	const std::string Constants::ansi_cyan = "\x1B[36m";
	const std::string Constants::ansi_white = "\x1B[37m";
	const std::string Constants::ansi_bright_black = "\x1B[90m";
	const std::string Constants::ansi_bright_red = "\x1B[91m";
	const std::string Constants::ansi_bright_green = "\x1B[92m";
	const std::string Constants::ansi_bright_yellow = "\x1B[93m";
	const std::string Constants::ansi_bright_blue = "\x1B[94m";
	const std::string Constants::ansi_bright_magenta = "\x1B[95m";
	const std::string Constants::ansi_bright_cyan = "\x1B[96m";
	const std::string Constants::ansi_bright_white = "\x1B[97m";
	const std::string Constants::ansi_bold_black = "\x1B[1;30m";
	const std::string Constants::ansi_bold_red = "\x1B[1;31m";
	const std::string Constants::ansi_bold_green = "\x1B[1;32m";
	const std::string Constants::ansi_bold_yellow = "\x1B[1;33m";
	const std::string Constants::ansi_bold_blue = "\x1B[1;34m";
	const std::string Constants::ansi_bold_magenta = "\x1B[1;35m";
	const std::string Constants::ansi_bold_cyan = "\x1B[1;36m";
	const std::string Constants::ansi_bold_white = "\x1B[1;37m";
	const std::string Constants::ansi_bold_bright_black = "\x1B[1;90m";
	const std::string Constants::ansi_bold_bright_red = "\x1B[1;91m";
	const std::string Constants::ansi_bold_bright_green = "\x1B[1;92m";
	const std::string Constants::ansi_bold_bright_yellow = "\x1B[1;93m";
	const std::string Constants::ansi_bold_bright_blue = "\x1B[1;94m";
	const std::string Constants::ansi_bold_bright_magenta = "\x1B[1;95m";
	const std::string Constants::ansi_bold_bright_cyan = "\x1B[1;96m";
	const std::string Constants::ansi_bold_bright_white = "\x1B[1;97m";

	void Constants::file_non_existent(const std::string &file) noexcept
	{
		std::cerr << "Error: The file \"" + file + "\" does not exist." << std::endl;
	}
}
