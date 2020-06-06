#ifndef TOOLS_TOOLS_H
#define TOOLS_TOOLS_H

#include <string>
#include <vector>
#include <memory>
#include <Poco/Crypto/DigestEngine.h>
#include <rapidjson/document.h>
#include <ctime>

/**
 * @mainpage tools-cpp
 * @author Matheus Gabriel Werny de Lima
 * @copyright GNU General Public License v2.0
 * @version
 * 1.1.40 (06.06.2020)
 * - Added a .pot file.
 * - Modified the messages.
 * @version
 * 1.1.39 (04.06.2020)
 * - Source code revision.
 * @version
 * 1.1.38 (31.05.2020)
 * - Bug fix.
 * @version
 * 1.1.37 (29.05.2020)
 * - Changed the name of error log files from the current Unix timestamp in second to milliseconds to prevent files from being overwritten.
 * @version
 * 1.1.36 (28.05.2020)
 * - Comment updated.
 * @version
 * 1.1.35 (24.05.2020)
 * - Added a function.
 * @version
 * 1.1.34 (23.05.2020)
 * - Contributing.md update.
 * @version
 * 1.1.33 (17.05.2020)
 * - Added the function "tools::Tools::exec".
 * @version
 * 1.1.32 (15.05.2020)
 * - Bug fix.
 * @version
 * 1.1.31 (15.05.2020)
 * - Readme update.
 * @version
 * 1.1.30 (15.05.2020)
 * - Contributing.md update.
 * @version
 * 1.1.29 (11.05.2020)
 * - Updated the readme.
 * @version
 * 1.1.28 (01.05.2020)
 * - Regenerated the documentation.
 * @version
 * 1.1.27 (29.04.2020)
 * - Updated the contributing file.
 * @version
 * 1.1.26 (29.04.2020)
 * - Regenerated the documentation.
 * @version
 * 1.1.25 (28.04.2020)
 * - Fixed some typos in comments.
 * @version
 * 1.1.24 (27.04.2020)
 * - Minor source code fixes.
 * @version
 * 1.1.23 (27.04.2020)
 * - Added the function "tools::Tools::mkdir()".
 * @version
 * 1.1.22 (27.04.2020)
 * - Revision of all comments.
 * @version
 * 1.1.21 (27.04.2020)
 * - All the source code was improved.
 * - All suitable comments are revised to fit the Doxygen syntax.
 * - Two functions were included for logging error messages instead of the stderr.
 * - String formatting was applied to the Messages object to ease translations.
 */

namespace tools
{
	/**
	 * @class Tools
	 * @brief A class for all functions I use regularly.
	 * @details It is a monostate.
	 */
	class Tools
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<Tools> ptr;

		//Member functions
		/**
		 * @brief All words in the passed string are listed down in a vector while one element represent a word.
		 * @details It can handle new lines and several spaces as it neglects them and only gets the pure words.
		 * @param[in] str The string from which we want to get the arguments.
		 * @return The vector where each element represents one argument.
		 */
		static std::vector<std::string> get_args(const std::string &str) noexcept;

		/**
		 * @brief All words in the passed string are listed down in a vector while one element represent a word.
		 * @details It can handle new lines and several spaces but this time it only neglects several spaces.
		 * @details Example:
		 * at(0): Hello,\\nhow
		 * at(1): are
		 * at(2): you?
		 * @param[in] str The string from which we want to get the arguments.
		 * @return The vector where each element represents one argument.
		 */
		static std::vector<std::string> get_args_w_lns(const std::string &str) noexcept;

		/**
		 * @brief The functions gets the content of the stated file.
		 * @details Empty lines are considered.
		 * @param[in] file Path to file whose content we want.
		 * @return Everything from the file is returned as a string. Additionally, a new line is included at the end which is important as when appending text I assume that it goes into a new line.
		 * @retval "" An empty line is returned if the file does not exist.
		 */
		static std::string get_file_cont(const std::string &file) noexcept;

		/**
		 * @brief The functions gets the content of the stated file except one line which is skipped.
		 * @param[in] file Path to file whose content we want.
		 * @param[in] srch String whose line shall not be included.
		 * @return Everything from the file except that one line is returned as a string. Additionally, a new line is included at the end which is important as when appending text I assume that it goes into a new line.
		 * @retval "" An empty line is returned if the file does not exist.
		 */
		static std::string get_file_cont_wo_srch_ln(const std::string &file, const std::string &srch) noexcept;

		/**
		 * @brief States whether the passed string is a positive integer. The number 0 counts too.
		 * @param[in] str The string of which we want to know whether it is a positive integer.
		 * @return It is returned true when the string only consists of number.
		 */
		static bool is_pos_int(const std::string &str) noexcept;

		/**
		 * @brief States whether the passed char is a positive integer.
		 * @param[in] ch The char of which we want to know whether it is a positive integer.
		 * @return If the char is a number, true is returned.
		 */
		static bool is_pos_int(const char &ch) noexcept;

		/**
		 * @brief It gets the first line which contains the passed string.
		 * @details The whole string needs to be contained in the file line and not just a fraction.
		 * @param[in] file Path to file whose content we want.
		 * @param[in] srch The string which shall be included in the file line that we search.
		 * @return The file line which contains the whole string.
		 * @retval "" The string does not appear in the file.
		 */
		static std::string get_file_ln_w_srch(const std::string &file, const std::string &srch) noexcept;

		/**
		 * @brief Retrieves the first char of a string.
		 * @param[in] str The string whose first char we want.
		 * @return The first char of a string.
		 * @retval '' An empty string was passed to the function.
		 */
		static char get_first_char(const std::string &str) noexcept;

		/**
		 * @brief It is compared whether one string starts with a sequence of chars.
		 * @param[in] str The string whose beginning shall be checked.
		 * @param[in] beg The string of which we want to know whether it occurs at the beginning of the other string.
		 * @return It is returned true if the one string starts with the other.
		 */
		static bool starts_w(const std::string &str, const std::string &beg) noexcept;

		/**
		 * @brief It is compared whether one string ends with a sequence of chars.
		 * @param[in] str The string whose end shall be checked.
		 * @param[in] end The string of which we want to know whether it occurs at the end of the other string.
		 * @return It is returned true if the one string ends with the other.
		 */
		static bool ends_w(const std::string &str, const std::string &end) noexcept;

		/**
		 * @brief It is checked whether the whole string appears in the file.
		 * @param[in] file The path to the file its content we want to inspect.
		 * @param[in] str The string whose whose existence we want to know in the file.
		 * @return It is returned true if the string appears in the file.
		 */
		static bool file_cont_str(const std::string &file, const std::string &str) noexcept;

		/**
		 * @brief Cuts off the first char of the passed string.
		 * @param[in] str The string to shorten.
		 * @return The shortened string.
		 * @retval "" The passed string is empty.
		 */
		static std::string cut_off_first_char(const std::string &str) noexcept;

		/**
		 * @brief Checks whether the file exists.
		 * @param[in] file The path to file we want to know whether it exists.
		 * @return It is returned true if the file exists.
		 */
		static bool file_exists(const std::string &file) noexcept;

		/**
		 * @brief This function gets the first lines of a file.
		 * @details It does not matter whether the file does have sufficient lines. In that case, all are got.
		 * @details Empty lines are neglected.
		 * @param[in] file The path to file whose content we want.
		 * @param[in] ln_nums The number of lines we want from the beginning.
		 * @return The first lines of the file content are returned. A new line char is appended at the end.
		 * @retval "" The file does not exist, there is no file content or the file number does not exist.
		 */
		static std::string get_first_lns_file(const std::string &file, const int &ln_nums) noexcept;

		/**
		 * @brief The function skips the first file lines of the file and then gathers the remaining lines.
		 * @details It does not matter whether the file does have sufficient lines. In that case, all are got.
		 * @details Empty lines are neglected.
		 * @param[in] file The path to file whose content we want.
		 * @param[in] ln_nums The number of lines we want from the end.
		 * @return The last lines of content as a string are returned. A new line char is appended at the end.
		 * @retval "" The file does not exist, there is no file content or the file number does not exist.
		 */
		static std::string get_last_lns_file(const std::string &file, const int &ln_nums) noexcept;

		/**
		 * @brief This function gets the integer at the end of a string.
		 * @param[in] entry The string whose ending number we want.
		 * @return The positive or negative integer at the end of a file line.
		 * @retval -1 There no numerals at the end of the file line or it is empty.
		 */
		static long long get_num_ln_end(const std::string &entry) noexcept;

		/**
		 * @brief The function gets the line of a given file.
		 * @details The first line is line 1.
		 * @details Example: The function may get line 5 of a file.
		 * @param[in] file The file path to the file whose content we want.
		 * @param[in] ln_num The number needs to be greater than 0. It states the line we want.
		 * @return The file line with new line char included at the end is returned.
		 * @retval "" The file or the file line does not exist.
		 */
		static std::string get_file_ln(const std::string &file, const int &ln_num) noexcept;

		/**
		 * @brief It is counted the number of lines a file has.
		 * @details Empty lines do not count.
		 * @param[in] file The path to file.
		 * @return The amount of written lines in a file.
		 * @retval -1 The file does not exist.
		 */
		static int get_amnt_file_lns(const std::string &file) noexcept;

		/**
		 * @brief Creates a md5 hash for the proper seed.
		 * @param[in] seed The seed which shall be encrypted.
		 * @return The md5 hash.
		 */
		static std::string md5_hash(const std::string &seed) noexcept;

		/**
		 * @brief Computes an hmac sha256 hash for the proper seed.
		 * @param[in] secret_key The key for the hmac encryption.
		 * @param[in] seed The actual string which shall be encoded.
		 * @return The hmac sha256 hash.
		 */
		static std::string hmac_sha256_hash(const std::string &secret_key, const std::string &seed) noexcept;

		/**
		 * @brief It URL parses the given string.
		 * @param[in] url URL or string which shall be encoded.
		 * @param[in] escaped_chars Non-ASCII chars are escaped either way but with this string there can be stated additional chars to escape.
		 * @return The URL parsed string.
		 */
		static std::string parse_url(const std::string &url, const std::string &escaped_chars = "") noexcept;

		/**
		 * @brief It substitutes non-ASCII characters with the hex value of the char.
		 * @details With the help of https://gist.github.com/MightyPork/52eda3e5677b4b03524e40c9f0ab1da5.
		 * @param[in] wstr The string which shall be encoded.
		 * @return The parsed string.
		 */
		static std::string encode_utf8(const std::wstring &wstr) noexcept;

		/**
		 * @brief Expects an integer and turns it into its octal equivalent.
		 * @param[in] val The integer which shall be converted.
		 * @return The octal value as a string.
		 */
		static std::string to_oct(const int &val) noexcept;

		/**
		 * @brief Expects an integer and turns it into its hexadecimal equivalent.
		 * @param[in] val The integer which shall be converted.
		 * @return The hexadecimal value as a string.
		 */
		static std::string to_hex(const int &val) noexcept;

		/**
		 * @brief The function GZIP compresses the passed data.
		 * @details Copied from here: https://gist.github.com/yfnick/6ba33efa7ba12e93b148.
		 * @param[in] data The data to GZIP compress.
		 * @return The GZIP compressed data.
		 */
		static std::string gzip_compress(const std::string &data) noexcept;

		/**
		 * @brief The function GZIP decompresses the passed data.
		 * @details Copied from here: https://gist.github.com/yfnick/6ba33efa7ba12e93b148.
		 * @param[in] data The data to GZIP decompress.
		 * @return The GZIP decompressed data.
		 */
		static std::string gzip_decompress(const std::string &data) noexcept;

		/**
		 * @brief Checks whether the passed data is GZIP compressed.
		 * @param[in] data The data to check.
		 * @return Whether the passes data is GZIP compressed.
		 */
		static bool is_gzipped(const std::string &data) noexcept;

		/**
		 * @brief A JSON object or array is turned into a string.
		 * @details The library rapidjson is used.
		 * @param[in] val The JSON object or array to convert.
		 * @return The string of the JSON.
		 */
		static std::string get_json_as_string(const rapidjson::Value &val) noexcept;

		/**
		 * @brief Returns the current time in milliseconds.
		 * @details Example: 1583068819924.
		 * @return The Unix time in milliseconds.
		 */
		static long long get_time_in_millisec() noexcept;

		/**
		 * @brief Returns the current time in seconds.
		 * @details Example: 1583068819.
		 * @return The Unix time in seconds.
		 */
		static long long get_time() noexcept;

		/**
		 * @brief Returns the current time in seconds with milliseconds.
		 * @details Example: 1583068819.924.
		 * @return The Unix time in seconds with milliseconds.
		 */
		static double get_time_w_millisec() noexcept;

		/**
		 * @brief Returns the current time and makes the date.
		 * @return Output of asctime() with no new line appended.
		 */
		static std::string get_date(const std::time_t &time = 0) noexcept;

		/**
		 * @brief Returns the ISO 8601 offset from UTC in time zone (1 minute=1, 1 hour=100).
		 * @details Example: -18000.
		 * @return The time zone offset.
		 */
		static std::string get_timezone_offset() noexcept;

		/**
		 * @brief Returns a seed which changes every millisecond to ensure that not the same seed is used in a programme.
		 * @details The function calls the current time in milliseconds and shortens it to fit into an in so that is can be used as a a seed.
		 * @return A random number.
		 */
		static int get_seed() noexcept;

		/**
		 * @brief Gets the tm struct for us.
		 * @details By default, the struct std::tm gets the current time but optionally, the wanted time can be stated.
		 * @param[in] time Input for the struct std::tm.
		 * @return The struct std::tm.
		 */
		static std::tm* get_tm(const std::time_t &time = 0) noexcept;

		/**
		 * @brief This function gets values out of settings files.
		 * @details Values in lines are saved like: "key0 (key1 key2): value0 (value1 value2)".
		 * @param[in] ln The file line whose value we want.
		 * @return The value for the setting.
		 */
		static std::string get_file_ln_val(const std::string &ln) noexcept;

		/**
		 * @brief This function is thought to be used to log error messages which need treatment.
		 * @details It should be used instead of the stderr output.
		 * @param[in] err_msg The error message which shall be logged.
		 */
		static void write_err_log(const std::string &err_msg) noexcept;

		/**
		 * @brief This function is thought to be used to log error messages temporarily.
		 * @details It should be used instead of the stderr output.
		 * @param[in] err_msg The error message which shall be logged.
		 */
		static void write_err_log_tmp(const std::string &err_msg) noexcept;

		/**
		 * @brief Deletes the passed file.
		 * @param[in] file The file to delete.
		 */
		static void del_file(const std::string &file) noexcept;

		/**
		 * @brief Makes a directory.
		 * @param[in] path The path to the directory which shall be made.
		 */
		static void mkdir(const std::string &path) noexcept;

		/**
		 * @brief Deletes a directory.
		 * @param[in] path The path to the directory which shall be deleted.
		 */
		static void rmdir(const std::string &path) noexcept;

		/**
		 * @brief Calls a command and return the stdout.
		 * @param[in] cmd The called command.
		 * @return The output made to stdout.
		 */
		static std::string exec(const char *cmd) noexcept;
	};
}

#endif
