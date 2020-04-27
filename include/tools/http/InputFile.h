#ifndef TOOLS_HTTP_INPUTFILE_H
#define TOOLS_HTTP_INPUTFILE_H

#include <memory>

namespace tools
{
	/**
	 * @struct InputFile
	 * @brief A representation of a file which shall be uploaded by an HTTP request via "multipart/form"
	 */
	struct InputFile
	{
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself
		 */
		typedef std::shared_ptr<InputFile> ptr;

		//Member variables
		/**
		 * @var m_path
		 * @brief The path to the file
		 */
		std::string m_path;

		//Constructors
		/**
		 * @param[in] path The path where the file is located
		 */
		InputFile(const std::string &path);
	};
}

#endif
