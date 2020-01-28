#include "tools/Constants.h"
#include <string>
#include <iostream>

namespace tools
{
	const std::string Constants::version = "1.1.1";
	const std::string Constants::release = "28.Jan.2020";

	void Constants::file_non_existent(const std::string &file)
	{
		std::cerr << "Error: The file \"" + file + "\" does not exist." << std::endl;
	}
}
