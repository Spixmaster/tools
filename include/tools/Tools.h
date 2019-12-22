#ifndef TOOLS_TOOLS_H
#define TOOLS_TOOLS_H

#include <string>
#include <vector>
#include <memory>
#include <Poco/Crypto/DigestEngine.h>
#include <rapidjson/document.h>

/*
 * @brief content: all functions for general C++ use or generally necessary for this project
 * @brief it is a monostate
 */

namespace tools
{
	class Tools
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<Tools> ptr;

		//member functions
		/*
		 * @brief lists down all words in a vector
		 * @brief one vector location --> one word
		 * @brief args.at(0) is /'command'
		 * @brief can handle new lines and several spaces
		 * @brief gets only words
		 * @brief be aware when writing the arguments down --> you need to put spaces in between
		 * @param str: string from which we want to get the args
		 * @return vector where each element represent one argument
		 */
		static std::vector<std::string> get_args(const std::string &str);

		/*
		 * @brief lists down all words in a vector
		 * @brief one vector location --> one word
		 * @brief args.at(0) is /'command'
		 * @brief can handle new lines and several spaces
		 * @brief additionally gets new lines
		 * @brief example:
		 * 			at(0) --> hello\nhow
		 * 			are
		 * 			you?
		 * @brief be aware when writing the arguments down --> you need to put spaces in between
		 * @param str: string from which we want to get the args
		 * @return vector where each element represent one argument
		 */
		static std::vector<std::string> get_args_w_lns(const std::string &str);

		/*
		 * @brief considers empty lines
		 * @param file: path to file whose content we want
		 * @return everything from file in string
		 * @return new line included at end which is important as when appending stuff I assume that it goes into a new line
		 */
		static std::string get_file_cont(const std::string &file);

		/*
		 * @brief considers empty lines
		 * @param file: path to file whose content we want
		 * @param srch: string whose line shall not be included
		 * @return everything but the line which contains the search string
		 * @return new line at end included
		 */
		static std::string get_file_cont_wo_srch_ln(const std::string &file, const std::string &srch);

		/*
		 * @brief gets beginning line of first fitting string it mets
		 * @brief with that postion one can overwrite the beginning of the line
		 * @param file: path to file whose content we want
		 * @param srch: string whose line shall not be included
		 * @return position of beginning of line which contains "srch" for file pointer
		 * @return by default, returns 0
		 */
		static size_t get_beg_pos_ln(const std::string &file, const std::string &srch);

		/*
		 * @brief ',' and '.' in string return false too
		 * @param str: string which shall represent a positive integer
		 * @return true when string only consists of number --> therefore, postive integer
		 * @return in case of negative number returns false
		 */
		static bool is_pos_int(const std::string &str);

		/*
		 * @brief ',' and '.' return false too
		 * @param ch: char which shall represent a positive integer
		 * @return true when char is number --> 0 - 9
		 * @return in case of negative number returns false
		 */
		static bool is_pos_int(const char &ch);

		/*
		 * @brief gets line of first fitting string it mets
		 * @brief when only part of string appears it does not count
		 * @param file: path to file whose content we want
		 * @param srch: string whose line shall not be included
		 * @return line which contains the string srch
		 * @return by default, returns nothing
		 */
		static std::string get_file_ln_w_srch(const std::string &file, const std::string &srch);

		/*
		 * @brief searches for position 0 in a string
		 * @param str: relevant string
		 * @return first char of string
		 * @return by default, return nothing
		 */
		static char get_first_char(const std::string &str);

		/*
		 * @brief checks beginning of a string
		 * @param str: string whose beginning shall be checked
		 * @param beg: string of which we want to know whether it is the beginning of str
		 * @return states whether str begins with beg
		 * @return by default, returns nothing
		 */
		static bool starts_w(const std::string &str, const std::string &beg);

		/*
		 * @brief checks end of a string
		 * @param str: string whose end shall be checked
		 * @param beg: string of which we want to know whether it is the end of str
		 * @return states whether str ends with beg
		 * @return by default, returns nothing
		 */
		static bool ends_w(const std::string &str, const std::string &end);

		/*
		 * @brief states whether string is in file
		 * @brief if only part of string appears it does not count
		 * @param file: path to file its content we want to inspect
		 * @param srch: string whose whose existence we want to know in the file
		 * @return true when str appears in file
		 */
		static bool file_cont_str(const std::string &file, const std::string &str);

		/*
		 * @brief gets rid of first char
		 * @param str: string to shorten
		 * @return str without .at(0)
		 */
		static std::string cut_off_first_char(const std::string &str);

		/*
		 * @brief checks whether the file exists
		 * @param file: path to file we want to know whether it exists
		 * @return true when file exists
		 */
		static bool file_exists(const std::string &file);

		/*
		 * @brief gets first "ln_nums" lines of the file "file"
		 * @brief it does not matter whether "file" does not have "ln_nums" lines --> then, all are got
		 * @brief e.g. get first 5 lines of file
		 * @brief neglects empty lines
		 * @brief new line included at end
		 * @param file: path to file whose content we want
		 * @param ln_nums: number of lines we want from the beginning
		 * @return first lines of content as a string
		 */
		static std::string get_first_lns_file(const std::string &file, const int &ln_nums);

		/*
		 * @brief skips first "ln_nums" lines of the file "file"
		 * @brief it does not matter whether "file" does not have "ln_nums" lines --> then, all are got
		 * @brief e.g. first 2 lines are skipped
		 * @brief neglects empty lines
		 * @brief new line included at end
		 * @param file: path to file whose content we want
		 * @param ln_nums: number of lines we want from the end
		 * @return last lines of content as a string
		 */
		static std::string get_last_lns_file(const std::string &file, const int &ln_nums);

		/*
		 * @brief does not work properly when number contains: '.', ','
		 * @param entry: string whose ending number we want
		 * @return the positive/negative integer at the end of a file
		 * @return when no numerals at end or empty entry --> returns 0
		 */
		static long long get_int_ln_end (const std::string &entry);

		/*
		 * @brief first line is line 1 (not 0)
		 * @brief gets line "ln_num" of the file "file"
		 * @brief e.g. gets line 5 of file
		 * @param file: path to file whose content we want
		 * @param ln_num: needs to be greater than 0; states the line we want
		 * @return it does not matter whether "file" does not have "ln_num" line --> then, nothing is got
		 * @return NO new line ("\n") included at end
		 */
		static std::string get_file_ln(const std::string &file, const int &ln_num);

		/*
		 * @brief empty lines do not count
		 * @param file: path to file
		 * @return the amount of written lines in a file
		 * @return by default, returns 0
		 */
		static int get_amnt_file_lns(const std::string &file);

		/*
		 * @brief Linux only: returns the path in which the program is in with appended executable name
		 * @return path to exe
		 */
		static std::string get_exe_path();

		/*
		 * @brief returns a md5 hash for the proper seed
		 * @param seed: seed which shall be encrypted
		 * @return the md5 hash
		 */
		static std::string md5_hash(const std::string &seed);

		/*
		 * @brief returns a hmac sha256 hash for the proper string
		 * @param secret_key: key for the hmac encryption
		 * @param str: actual string which shall be encoded
		 * @return the hmac sha256 hash
		 */
		static std::string hmac_sha256_hash(const std::string &secret_key, const std::string &str);

		/*
		 * @brief substitutes non-ascii characters with escaped chars %...
		 * @param url: url which shall be encoded
		 * @return the parsed url
		 */
		static std::string parse_url(const std::string &url, const std::string &escaped_chars);

		/*
		 * @brief with the help of https://gist.github.com/MightyPork/52eda3e5677b4b03524e40c9f0ab1da5
		 * @brief substitutes non-ascii characters with the hex value of the char
		 * @param str: string which shall be encoded
		 * @return the parsed string
		 */
		static std::string encode_utf8(const std::wstring &wstr);

		/*
		 * @brief expects an int and turns it into its octal equivalent
		 * @param val: the int which shall be converted
		 * @return the octal value as a string
		 */
		static std::string to_oct(const int &val);

		/*
		 * @brief expects an int and turns it into its hexadecimal equivalent
		 * @param val: the int which shall be converted
		 * @return the hexadecimal value as a string
		 */
		static std::string to_hex(const int &val);

		/*
		 * @brief copied from here: https://gist.github.com/yfnick/6ba33efa7ba12e93b148
		 * @brief gzip compresses data
		 * @param data: the data to gzip compress
		 * @return the compressed data
		 */
		static std::string gzip_compress(const std::string &data);

		/*
		 * @brief copied from here: https://gist.github.com/yfnick/6ba33efa7ba12e93b148
		 * @brief decompresses gzip compressed data
		 * @param data: the gzip compressed data
		 * @return the decompressed data
		 */
		static std::string gzip_decompress(const std::string &data);

		/*
		 * @brief checks whether data is gzipped
		 * @param data: the possible gzip compressed data
		 * @return whether gzip compressed
		 */
		static bool is_gzipped(const std::string &data);

		/*
		 * @brief expects a rapidjson::Value and turns it back into a string
		 * @param the rapidjson::Value which shall be converted
		 * @return the string of the json
		 */
		static std::string get_json_as_string(const rapidjson::Value &val);
	};
}

#endif
