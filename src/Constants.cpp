#include "tools/Constants.h"
#include <string>
#include <iostream>

namespace tools
{
	std::string Constants::version = "0.0.0";
	std::string Constants::release = "30.Nov.2019";

	void Constants::file_non_existent(const std::string &file)
	{
		std::cerr << "Error. The file \"" + file + "\" does not exist." << std::endl;
	}
}
