#include "tools/Constants.h"
#include <string>
#include <iostream>

namespace tools
{
	const std::string Constants::version = "1.1.0";
	const std::string Constants::release = "23.Jan.2020";

	void Constants::file_non_existent(const std::string &file)
	{
		std::cerr << "Error: The file \"" + file + "\" does not exist." << std::endl;
	}
}
