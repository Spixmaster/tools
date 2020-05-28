#include "tools/constants/Constants.h"
#include <string>
#include <iostream>
#include "tools/Tools.h"
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

namespace tools
{
	const std::string Constants::version = "1.1.36";
	const std::string Constants::release = "28.May.2020";
	const std::size_t Constants::max_tmp_err_logs = 10;

	const std::string Constants::ansii_reset = "\x1B[0m";
	const std::string Constants::ansii_black = "\x1B[30m";
	const std::string Constants::ansii_red = "\x1B[31m";
	const std::string Constants::ansii_green = "\x1B[32m";
	const std::string Constants::ansii_yellow = "\x1B[33m";
	const std::string Constants::ansii_blue = "\x1B[34m";
	const std::string Constants::ansii_magenta = "\x1B[35m";
	const std::string Constants::ansii_cyan = "\x1B[36m";
	const std::string Constants::ansii_white = "\x1B[37m";
	const std::string Constants::ansii_bright_black = "\x1B[90m";
	const std::string Constants::ansii_bright_red = "\x1B[91m";
	const std::string Constants::ansii_bright_green = "\x1B[92m";
	const std::string Constants::ansii_bright_yellow = "\x1B[93m";
	const std::string Constants::ansii_bright_blue = "\x1B[94m";
	const std::string Constants::ansii_bright_magenta = "\x1B[95m";
	const std::string Constants::ansii_bright_cyan = "\x1B[96m";
	const std::string Constants::ansii_bright_white = "\x1B[97m";
	const std::string Constants::ansii_bold_black = "\x1B[1;30m";
	const std::string Constants::ansii_bold_red = "\x1B[1;31m";
	const std::string Constants::ansii_bold_green = "\x1B[1;32m";
	const std::string Constants::ansii_bold_yellow = "\x1B[1;33m";
	const std::string Constants::ansii_bold_blue = "\x1B[1;34m";
	const std::string Constants::ansii_bold_magenta = "\x1B[1;35m";
	const std::string Constants::ansii_bold_cyan = "\x1B[1;36m";
	const std::string Constants::ansii_bold_white = "\x1B[1;37m";
	const std::string Constants::ansii_bold_bright_black = "\x1B[1;90m";
	const std::string Constants::ansii_bold_bright_red = "\x1B[1;91m";
	const std::string Constants::ansii_bold_bright_green = "\x1B[1;92m";
	const std::string Constants::ansii_bold_bright_yellow = "\x1B[1;93m";
	const std::string Constants::ansii_bold_bright_blue = "\x1B[1;94m";
	const std::string Constants::ansii_bold_bright_magenta = "\x1B[1;95m";
	const std::string Constants::ansii_bold_bright_cyan = "\x1B[1;96m";
	const std::string Constants::ansii_bold_bright_white = "\x1B[1;97m";

	const std::string Constants::folder = "./files/";
	const std::string Constants::folder_error_logs = Constants::folder + "error-logs/";
	const std::string Constants::folder_error_logs_tmp = Constants::folder + "error-logs-tmp/";

	std::string Constants::file_err_log() noexcept
	{
		return Constants::folder_error_logs + std::to_string(Tools::get_time()) + ".txt";
	}

	std::string Constants::file_err_log_tmp() noexcept
	{
		return Constants::folder_error_logs_tmp + std::to_string(Tools::get_time()) + ".txt";
	}
}
