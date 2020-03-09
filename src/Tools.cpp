#include "tools/Tools.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <limits.h>
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/HMACEngine.h"
#include <Poco/URI.h>
#include "tools/SHA256Engine.h"
#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "tools/constants/Constants.h"
#include "tools/constants/Messages.h"
#include <chrono>

namespace tools
{
	std::vector<std::string> Tools::get_args(const std::string &str) noexcept
	{
		std::vector<std::string> args;
		std::string word;

		for(std::size_t j = 0; j < str.length(); ++j)
		{
			//deal with last char/word
			//add last char to word
			//at end no ' ' --> otherwise, last word would not be added to vector
			if(j == (str.length() - 1) && str.at(j) != ' ')
			{
				word += str.at(j);
				args.push_back(word);
				word = "";
				break;	//otherwise, next condition would be true
			}

			//add characters
			if(str.at(j) != ' ' && str.at(j) != '\n')
				word += str.at(j);

			//detect words
			//&& !word.empty() --> so that e. g. several spaces would not add an empty slot in args
			if((str.at(j) == ' ' || str.at(j) == '\n') && !word.empty())
			{
				args.push_back(word);
				word = "";
			}
		}
		return args;
	}

	std::vector<std::string> Tools::get_args_w_lns(const std::string &str) noexcept
	{
		std::vector<std::string> args;
		std::string word;

		for(std::size_t j = 0; j < str.length(); ++j)
		{
			//deal with last char/word
			//add last char to word
			//at end no ' ' --> otherwise, last word would not be added to vector
			if(j == (str.length() - 1) && str.at(j) != ' ')
			{
				word += str.at(j);
				args.push_back(word);
				word = "";
				break;	//otherwise, next condition would be true
			}

			//add characters
			if(str.at(j) != ' ')
				word += str.at(j);
			//detect words
			else
			{
				args.push_back(word);
				word = "";
			}
		}
		return args;
	}

	std::string Tools::get_file_cont(const std::string &file) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);
			std::string cont;

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::string cur_ln;
					std::getline(inf, cur_ln);
					cont.append(cur_ln + "\n");
				}

				/*
				 * we need to do this as there is always a trailing \n at the end of the file
				 * if we would not do this the file would be filled with one more empty line each time
				 * condition: pop_back of empty string crashes the programme
				 */
				if(cont.size() > 0)
					cont.pop_back();
			}
			return cont;
		}
		else
		{
			Messages::file_non_existent(file);

			return "";
		}
	}

	std::string Tools::get_file_cont_wo_srch_ln(const std::string &file, const std::string &srch) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);
			std::string cont;
			std::size_t found;

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::string cur_ln;
					std::getline(inf, cur_ln);

					//srch in line
					if((found = cur_ln.find(srch)) != std::string::npos)
						continue;
					else
						cont.append(cur_ln + "\n");
				}

				/*
				 * we need to do this as there is always a trailing \n at the end of the file
				 * if we would not do this the file would be filled with one more empty line each time
				 * condition: pop_back of empty string crashes the programme
				 */
				if(cont.size() > 0)
					cont.pop_back();
			}

			return cont;
		}
		else
		{
			Messages::file_non_existent(file);

			return "";
		}
	}

	std::size_t Tools::get_beg_pos_ln(const std::string &file, const std::string &srch) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);
			std::string cur_ln;
			std::size_t found;
			std::size_t chars_to_srch = 0;

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::getline(inf, cur_ln);

					//srch found
					if((found = cur_ln.find(srch)) != std::string::npos)
						break;

					//due to "\n"
					chars_to_srch += cur_ln.length();
					chars_to_srch += 2;
				}
			}
			return chars_to_srch;
		}
		else
		{
			Messages::file_non_existent(file);

			return 0;
		}
	}

	bool Tools::is_pos_int(const std::string &str) noexcept
	{
		for(std::size_t j = 0; j < str.length(); ++j)
			if(!isdigit(str[j]))
				return false;

		return true;
	}

	bool Tools::is_pos_int(const char &ch) noexcept
	{
		if(!isdigit(ch))
			return false;

		return true;
	}

	std::string Tools::get_file_ln_w_srch(const std::string &file, const std::string &srch) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);
			std::string cur_ln;
			std::size_t found;

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::getline(inf, cur_ln);

					//srch found
					if((found = cur_ln.find(srch)) != std::string::npos)
						return cur_ln;
				}
				//otherwise, if nothing found he would send the last line
				cur_ln = "";
			}
			return cur_ln;
		}
		else
		{
			Messages::file_non_existent(file);

			return "";
		}
	}

	char Tools::get_first_char(const std::string &str) noexcept
	{
		if(str.size() >= 1)
			return str.at(0);

		const char *c = "";

		return *c;
	}

	bool Tools::starts_w(const std::string &str, const std::string &beg) noexcept
	{
		//otherwise beginning could not even be beginning
		if(str.length() > beg.length())
		{
			for(std::size_t j = 0; j < beg.length(); ++j)
				if(!(beg.at(j) == str.at(j)))
					return false;

			return true;
		}
		return false;
	}

	bool Tools::ends_w(const std::string &str, const std::string &end) noexcept
	{
		//otherwise end could not even be end
		if(str.length() > end.length())
		{
			for(std::size_t j = 0; j < end.length(); ++j)
				if(!(end.at(end.length() - 1 - j) == str.at(str.length() - 1 - j)))
					return false;

			return true;
		}
		return false;
	}

	bool Tools::file_cont_str(const std::string &file, const std::string &str) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);
			std::string cur_ln;
			std::size_t found;

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::getline(inf, cur_ln);

					if((found = cur_ln.find(str)) != std::string::npos)
						return true;
				}
			}
			return false;
		}
		else
		{
			Messages::file_non_existent(file);

			return false;
		}
	}

	std::string Tools::cut_off_first_char(const std::string &str) noexcept
	{
		std::string res;
		//j = 1 --> omit .at(0)
		for(std::size_t j = 1; j < str.length(); ++j)
			res.push_back(str.at(j));

		//as with .length() = 1 for loop is not executed
		if(str.length() == 1)
			res = "";

		return res;
	}

	bool Tools::file_exists(const std::string &file) noexcept
	{
		std::ifstream inf(file);

		return inf.good();
	}

	std::string Tools::get_first_lns_file(const std::string &file, const int &ln_nums) noexcept
	{
		if(Tools::file_exists(file))
		{
			if(ln_nums >= 0)
			{
				std::ifstream inf(file);
				std::string str;
				int count = 0;

				if(inf.is_open())
				{
					while(!inf.eof())
					{
						if(count == ln_nums)
							break;
						std::string cache;
						std::getline(inf, cache);
						if(!cache.empty())
							str.append(cache + "\n");
						++count;
					}
				}
				return str;
			}
			else
			{
				std::cerr << Messages::enter_pos_num_to_read_in_file(file) << std::endl;

				return "";
			}
		}
		else
		{
			Messages::file_non_existent(file);

			return "";
		}
	}

	std::string Tools::get_last_lns_file(const std::string &file, const int &ln_nums) noexcept
	{
		if(Tools::file_exists(file))
		{
			if(ln_nums >= 0)
			{
				std::ifstream inf(file);
				std::string str;
				int count = 0;

				if(inf.is_open())
				{
					while(!inf.eof())
					{
						if(count < ln_nums)
						{
							std::string cache;
							std::getline(inf, cache);
							++count;
						}
						else
						{
							std::string cache;
							std::getline(inf, cache);
							if(!cache.empty())
								str.append(cache + "\n");

							++count;
						}
					}
				}
				return str;
			}
			else
			{
				std::cerr << Messages::enter_pos_num_to_read_in_file(file) << std::endl;

				return "";
			}
		}
		else
		{
			Messages::file_non_existent(file);

			return "";
		}
	}

	long long Tools::get_num_ln_end(const std::string &entry) noexcept
	{
		if(!entry.empty())
		{
			long long number = 0;
			bool is_neg = false;

			//get amount of numerals at the end
			int pos = 1; //begin with last char else end sequence
			int digits = 0;

			//no numerals at end --> digits = 0
			while(true)
			{
				if(Tools::is_pos_int(entry.at(entry.length() - pos)) || entry.at(entry.length() - pos) == '-')
				{
					if(entry.at(entry.length() - pos) != '-')
						++digits;
					else
					{
						//so that '-' cannot occur in the middle of a number
						is_neg = true;
						break;
					}
					++pos;
				}
				else
					break;
			}

			//if digits = 0 --> 0 is returned
			if(digits == 0)
			{
				std::cerr << Messages::no_num_str_end(entry) << std::endl;
				return 0;
			}

			//get number according to digits
			for(int j = 0; j < digits; ++j)
			{
				//+ 1 --> else first iteration would end sequence
				char numeral = entry.at(entry.length() - (j + 1));
				//first iteration: j = 0 --> pow(10, 0) = 1
				number += static_cast<long long>(pow(10, j) * static_cast<long long>(numeral - 48));
			}

			//consider sign
			if(is_neg)
				return -number;
			else
				return number;
		}
		else
		{
			std::cerr << Messages::given_str_empty << std::endl;

			return 0;
		}
	}

	std::string Tools::get_file_ln(const std::string &file, const int &ln_num) noexcept
	{
		if(Tools::file_exists(file))
		{
			if(ln_num >= 1)
			{
				std::ifstream inf(file);
				std::string str;
				int count = 1;

				if(inf.is_open())
				{
					while(!inf.eof())
					{
						std::string cache;
						std::getline(inf, cache);

						if(count == ln_num)
							return cache;
						++count;
					}
				}
				return str;
			}
			else
			{
				std::cerr << Messages::enter_pos_num_to_read_in_file(file) << std::endl;

				return "";
			}
		}
		else
		{
			Messages::file_non_existent(file);
			return "";
		}
	}

	int Tools::get_amnt_file_lns(const std::string &file) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);

			if(inf.is_open())
			{
				int x = 0;
				while(!inf.eof())
				{
					std::string cache;
					std::getline(inf, cache);

					if(!cache.empty())
						++x;
				}
				return x;
			}
		}
		else
			Messages::file_non_existent(file);

		return 0;
	}

	std::string Tools::get_exe_path() noexcept
	{
		char result[ PATH_MAX ];
		ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
		return std::string(result, (count > 0) ? count : 0);
	}

	std::string Tools::md5_hash(const std::string &seed) noexcept
	{
	    Poco::MD5Engine md5;
	    Poco::DigestOutputStream ds(md5);
	    ds << seed;
	    ds.close();

	    return Poco::DigestEngine::digestToHex(md5.digest());
	}

	std::string Tools::hmac_sha256_hash(const std::string &secret_key, const std::string &str) noexcept
	{
		Poco::HMACEngine<SHA256Engine> hmac{secret_key};
		hmac.update(str);

		return Poco::DigestEngine::digestToHex(hmac.digest());
	}

	std::string Tools::parse_url(const std::string &url, const std::string &escaped_chars) noexcept
	{
		std::string temp;
		Poco::URI::encode(url, escaped_chars, temp);

		return temp;
	}

	std::string Tools::encode_utf8(const std::wstring &wstr) noexcept
	{
		std::string utf8_encoded;

		//iterate through the whole string
		for(std::size_t j = 0; j < wstr.size(); ++j)
		{
			if(wstr.at(j) <= 0x7F)
				utf8_encoded += wstr.at(j);
			else if(wstr.at(j) <= 0x7FF)
			{
				//our template for unicode of 2 bytes
				int utf8 = 0b11000000'10000000;

				//get the first 6 bits and save them
				utf8 += wstr.at(j) & 0b00111111;

				/*
				 * get the last 5 remaining bits
				 * put them 2 to the left so that the 10 from 10xxxxxx (first byte) is not overwritten
				 */
				utf8 += (wstr.at(j) & 0b00000111'11000000) << 2;

				//append to the result
				std::string temp = Tools::to_hex(utf8);
				utf8_encoded.append(temp.insert(0, "\\x").insert(4, "\\x"));
			}
			else if(wstr.at(j) <= 0xFFFF)
			{
				//our template for unicode of 3 bytes
				int utf8 = 0b11100000'10000000'10000000;

				//get the first 6 bits and save them
				utf8 += wstr.at(j) & 0b00111111;

				/*
				 * get the next 6 bits
				 * put them 2 to the left so that the 10 from 10xxxxxx (first byte) is not overwritten
				 */
				utf8 += (wstr.at(j) & 0b00001111'11000000) << 2;

				/*
				 * get the last 4 remaining bits
				 * put them 4 to the left so that the 10xx from 10xxxxxx (second byte) is not overwritten
				 */
				utf8 += (wstr.at(j) & 0b11110000'00000000) << 4;

				//append to the result
				std::string temp = Tools::to_hex(utf8);
				utf8_encoded.append(temp.insert(0, "\\x").insert(4, "\\x").insert(8, "\\x"));
			}
			else if(wstr.at(j) <= 0x10FFFF)
			{
				//our template for unicode of 4 bytes
				int utf8 = 0b11110000'10000000'10000000'10000000;

				//get the first 6 bits and save them
				utf8 += wstr.at(j) & 0b00111111;

				/*
				 * get the next 6 bits
				 * put them 2 to the left so that the 10 from 10xxxxxx (first byte) is not overwritten
				 */
				utf8 += (wstr.at(j) & 0b00001111'11000000) << 2;

				/*
				 * get the next 6 bits
				 * put them 4 to the left so that the 10xx from 10xxxxxx (second byte) is not overwritten
				 */
				utf8 += (wstr.at(j) & 0b00000011'11110000'00000000) << 4;

				/*
				 * get the last 3 remaining bits
				 * put them 6 to the left so that the 10xxxx from 10xxxxxx (third byte) is not overwritten
				 */
				utf8 += (wstr.at(j) & 0b00011100'00000000'00000000) << 4;

				//append to the result
				std::string temp = Tools::to_hex(utf8);
				utf8_encoded.append(temp.insert(0, "\\x").insert(4, "\\x").insert(8, "\\x").insert(12, "\\x"));
			}
		}
		return utf8_encoded;
	}

	std::string Tools::to_oct(const int &val) noexcept
	{
	    std::string result;
	    std::stringstream ss;
	    ss << std::oct << val;
	    ss >> result;

	    return result;
	}

	std::string Tools::to_hex(const int &val) noexcept
	{
	    std::string result;
	    std::stringstream ss;
	    ss << std::hex << val;
	    ss >> result;

	    return result;
	}

	std::string Tools::gzip_compress(const std::string &data) noexcept
	{
		std::stringstream compressed;
		std::stringstream origin(data);

		boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
		out.push(boost::iostreams::gzip_compressor(boost::iostreams::gzip_params(boost::iostreams::gzip::best_compression)));
		out.push(origin);
		boost::iostreams::copy(out, compressed);

		return compressed.str();
	}

	std::string Tools::gzip_decompress(const std::string &data) noexcept
	{
		std::stringstream compressed(data);
		std::stringstream decompressed;

		try
		{
			boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
			out.push(boost::iostreams::gzip_decompressor());
			out.push(compressed);
			boost::iostreams::copy(out, decompressed);

			return decompressed.str();
		}
		catch(const std::exception &e)
		{
			std::cerr << Messages::not_gzip_compressed << std::endl;
			return "";
		}
	}

	bool Tools::is_gzipped(const std::string &data) noexcept
	{
		std::stringstream compressed(data);
		std::stringstream decompressed;

		try
		{
			boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
			out.push(boost::iostreams::gzip_decompressor());
			out.push(compressed);
			boost::iostreams::copy(out, decompressed);

			return true;
		}
		catch(const std::exception &e)
		{
			return false;
		}
	}

	std::string Tools::get_json_as_string(const rapidjson::Value &val) noexcept
	{
		rapidjson::StringBuffer sb;
		rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
		val.Accept(writer);

		return sb.GetString();
	}

	long long Tools::get_time_in_millisec() noexcept
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	long long Tools::get_time() noexcept
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	double Tools::get_time_w_millisec() noexcept
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000;
	}

	std::string Tools::get_date() noexcept
	{
		//get time
		std::time_t raw_time;
		std::time(&raw_time);
		struct std::tm *time_info;
		time_info = std::localtime(&raw_time);

		std::string temp = std::asctime(time_info);

		if(!temp.empty())
			temp.pop_back();

		return temp;
	}

	std::string Tools::get_timezone_offset() noexcept
	{
		//get time
		std::time_t raw_time;
		std::time(&raw_time);
		struct std::tm *time_info;
		time_info = std::localtime(&raw_time);

		char buf[6];
		std::strftime(buf, sizeof(buf), "%z", time_info);

		return buf;
	}

	int Tools::get_seed() noexcept
	{
		//get the last 9 chars of the number as this can never cause an integer overflow
		std::string temp = std::to_string(get_time_in_millisec());
		std::reverse(temp.begin(), temp.end());
		std::string result;

		for(std::size_t j = 0; j < temp.size(); ++j)
		{
			if(j < 9)
				result += temp.at(j);
			else
				break;
		}

		return std::stoi(result);
	}

	std::tm* Tools::get_tm() noexcept
	{
		//get time
		std::time_t raw_time;
		std::time(&raw_time);
		struct std::tm *time_info;
		time_info = std::localtime(&raw_time);

		return time_info;
	}
}
