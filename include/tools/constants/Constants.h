#ifndef TOOLS_CONSTANTS_CONSTANTS_H
#define TOOLS_CONSTANTS_CONSTANTS_H

#include <string>
#include <memory>

namespace tools
{
	/**
	 * @struct Constants
	 * @brief A container of all constants in the programme
	 * @details It is a monostate.
	 */
	struct Constants
	{
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself
		 */
		typedef std::shared_ptr<Constants> ptr;

		//Member variables
		/**
		 * @var version
		 * @brief The version of the software
		 */
		static const std::string version;
		/**
		 * @var release
		 * @brief The release date of the current version
		 */
		static const std::string release;
		/**
		 * @var max_tmp_err_logs
		 * @brief This variable defines the maximum amount of temporary error logs.
		 * @details The oldest one is deleted if a new one is created and there are too many of them.
		 */
		static const std::size_t max_tmp_err_logs;
		//ANSII colour codes
		/**
		 * @var ansii_reset
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_reset;
		/**
		 * @var ansii_black
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_black;
		/**
		 * @var ansii_red
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_red;
		/**
		 * @var ansii_green
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_green;
		/**
		 * @var ansii_yellow
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_yellow;
		/**
		 * @var ansii_blue
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_blue;
		/**
		 * @var ansii_magenta
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_magenta;
		/**
		 * @var ansii_cyan
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_cyan;
		/**
		 * @var ansii_white
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_white;
		/**
		 * @var ansii_bright_black
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bright_black;
		/**
		 * @var ansii_bright_red
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bright_red;
		/**
		 * @var ansii_bright_green
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bright_green;
		/**
		 * @var ansii_bright_yellow
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bright_yellow;
		/**
		 * @var ansii_bright_blue
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bright_blue;
		/**
		 * @var ansii_bright_magenta
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bright_magenta;
		/**
		 * @var ansii_bright_cyan
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bright_cyan;
		/**
		 * @var ansii_bright_white
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bright_white;
		/**
		 * @var ansii_bold_black
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_black;
		/**
		 * @var ansii_bold_red
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_red;
		/**
		 * @var ansii_bold_green
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_green;
		/**
		 * @var ansii_bold_yellow
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_yellow;
		/**
		 * @var ansii_bold_blue
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_blue;
		/**
		 * @var ansii_bold_magenta
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_magenta;
		/**
		 * @var ansii_bold_cyan
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_cyan;
		/**
		 * @var ansii_bold_white
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_white;
		/**
		 * @var ansii_bold_bright_black
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_bright_black;
		/**
		 * @var ansii_bold_bright_red
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_bright_red;
		/**
		 * @var ansii_bold_bright_green
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_bright_green;
		/**
		 * @var ansii_bold_bright_yellow
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_bright_yellow;
		/**
		 * @var ansii_bold_bright_blue
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_bright_blue;
		/**
		 * @var ansii_bold_bright_magenta
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_bright_magenta;
		/**
		 * @var ansii_bold_bright_cyan
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_bright_cyan;
		/**
		 * @var ansii_bold_bright_white
		 * @brief An ANSII colour code which is used to colour the stdout and stderr
		 */
		static const std::string ansii_bold_bright_white;
		//Folders
		/**
		 * @var folder
		 * @brief The base folder for all files which are created by this software
		 */
		static const std::string folder;
		/**
		 * @var folder_error_logs
		 * @brief The folder for all error log files which need treatment
		 */
		static const std::string folder_error_logs;
		/**
		 * @var folder_error_logs_tmp
		 * @brief The folder for all temporary error logs
		 * @details The old logs are deleted if the folder contains a certain amount of files.
		 */
		static const std::string folder_error_logs_tmp;

		//Member functions
		//Files
		/**
		 * @brief Creates the file name for an error log.
		 * @return The file name
		 */
		static std::string file_err_log() noexcept;

		/**
		 * @brief Creates the file name for a temporary error log.
		 * @details This error log is not kept long.
		 * @details Temporary error logs exists as some errors do not need treatment. For example, the error that occurs when an HTTP response's status code is not 2xx, is not crucial and we cannot affect it.
		 * @return The file name
		 */
		static std::string file_err_log_tmp() noexcept;
	};
}

#endif
