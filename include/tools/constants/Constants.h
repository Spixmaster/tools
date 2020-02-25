#ifndef TOOLS_CONSTANTS_CONSTANTS_H
#define TOOLS_CONSTANTS_CONSTANTS_H

#include <string>
#include <memory>

/*
 * @brief container of all constants in the programme
 * @brief it is a monostate
 */

namespace tools
{
	struct Constants
	{
		//pointer of itself
		typedef std::shared_ptr<Constants> ptr;

		//member variables
		static const std::string version;
		static const std::string release;
			//ANSI colour codes
		static const std::string ansi_reset;
		static const std::string ansi_black;
		static const std::string ansi_red;
		static const std::string ansi_green;
		static const std::string ansi_yellow;
		static const std::string ansi_blue;
		static const std::string ansi_magenta;
		static const std::string ansi_cyan;
		static const std::string ansi_white;
		static const std::string ansi_bright_black;
		static const std::string ansi_bright_red;
		static const std::string ansi_bright_green;
		static const std::string ansi_bright_yellow;
		static const std::string ansi_bright_blue;
		static const std::string ansi_bright_magenta;
		static const std::string ansi_bright_cyan;
		static const std::string ansi_bright_white;
		static const std::string ansi_bold_black;
		static const std::string ansi_bold_red;
		static const std::string ansi_bold_green;
		static const std::string ansi_bold_yellow;
		static const std::string ansi_bold_blue;
		static const std::string ansi_bold_magenta;
		static const std::string ansi_bold_cyan;
		static const std::string ansi_bold_white;
		static const std::string ansi_bold_bright_black;
		static const std::string ansi_bold_bright_red;
		static const std::string ansi_bold_bright_green;
		static const std::string ansi_bold_bright_yellow;
		static const std::string ansi_bold_bright_blue;
		static const std::string ansi_bold_bright_magenta;
		static const std::string ansi_bold_bright_cyan;
		static const std::string ansi_bold_bright_white;
	};
}

#endif
