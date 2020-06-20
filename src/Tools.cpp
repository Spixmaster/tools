#include "tools/Tools.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
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
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/format.hpp>

namespace tools
{
	std::vector<std::string> Tools::get_args(const std::string &str) noexcept
	{
		std::vector<std::string> args;
		std::string word;

		for(std::size_t j = 0; j < str.length(); ++j)
		{
			//Deal with the last char of the last word.
			if(j == (str.length() - 1) && str.at(j) != ' ')
			{
				word += str.at(j);
				args.push_back(word);
				word = "";
				break;	//Otherwise, the next condition would be true.
			}

			//Add the chars.
			if(str.at(j) != ' ' && str.at(j) != '\n')
				word += str.at(j);

			/*
			 * Detect words.
			 * && !word.empty() is used as a condition so that several spaces do not add empty elements in the vector.
			 */
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
			//Deal with the last char of the last word.
			if(j == (str.length() - 1) && str.at(j) != ' ')
			{
				word += str.at(j);
				args.push_back(word);
				word = "";
				break;	//Otherwise, the next condition would be true.
			}

			//Add the chars.
			if(str.at(j) != ' ')
				word += str.at(j);
			//Detect the words.
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
				 * We need to do this as there is always a trailing \n at the end of the file.
				 * If we did not do this, the file would be filled with one more empty line each time.
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

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::string cur_ln;
					std::getline(inf, cur_ln);

					//Check whether the string appears in the file line.
					if(cur_ln.find(srch) != std::string::npos)
						continue;
					else
						cont.append(cur_ln + "\n");
				}

				/*
				 * We need to do this as there is always a trailing \n at the end of the file.
				 * If we did not do this, the file would be filled with one more empty line each time.
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

	bool Tools::is_pos_int(const std::string &str) noexcept
	{
		for(std::size_t j = 0; j < str.length(); ++j)
			if(!std::isdigit(str[j]))
				return false;

		if(!str.empty())
			return true;
		else
			return false;
	}

	bool Tools::is_pos_int(const char &ch) noexcept
	{
		if(!std::isdigit(ch))
			return false;

		return true;
	}

	std::string Tools::get_file_ln_w_srch(const std::string &file, const std::string &srch) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);
			std::string cur_ln;

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::getline(inf, cur_ln);

					//Check whether the string is found.
					if(cur_ln.find(srch) != std::string::npos)
						return cur_ln;
				}
			}

			return "";
		}
		else
		{
			Messages::file_non_existent(file);
			return "";
		}
	}

	std::string Tools::get_file_ln_w_key(const std::string &file, const std::string &key) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);
			std::string cur_ln;

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::getline(inf, cur_ln);

					std::string key_tmp = Tools::get_file_ln_key(cur_ln);

					if(key_tmp == key)
						return cur_ln;
				}
			}

			return "";
		}
		else
		{
			Messages::file_non_existent(file);
			return "";
		}
	}

	//todo
	std::string Tools::get_file_ln_w_val(const std::string &file, const std::string &val) noexcept
	{
		if(Tools::file_exists(file))
		{
			std::ifstream inf(file);
			std::string cur_ln;

			if(inf.is_open())
			{
				while(!inf.eof())
				{
					std::getline(inf, cur_ln);

					std::string val_tmp = Tools::get_file_ln_val(cur_ln);

					if(val_tmp == val)
						return cur_ln;
				}
			}

			return "";
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
		//Otherwise, the beginning could not even be a beginning.
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
		//Otherwise, the end could not even be an end.
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

		//The iteration starts at 1 to omit the first char
		for(std::size_t j = 1; j < str.length(); ++j)
			res.push_back(str.at(j));

		//This condition is needed as with .length() = 1 the for loop is not executed.
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
				Tools::write_err_log(Messages::enter_pos_num_to_read_in_file(file));
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
				Tools::write_err_log(Messages::enter_pos_num_to_read_in_file(file));
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

			//Get the amount of numerals at the end.
			int pos = 1; //This number is subtracted from the length of the string and increases with each iteration. By starting with one, we get the last char.
			int digits = 0; //The amount of digits of the number.

			//If there are no numerals at the end, digits equals 0.
			while(true)
			{
				if(Tools::is_pos_int(entry.at(entry.length() - pos)) || entry.at(entry.length() - pos) == '-')
				{
					if(entry.at(entry.length() - pos) != '-')
						++digits;
					else
					{
						is_neg = true;
						//It is broken here so that '-' cannot occur in the middle of a number.
						break;
					}

					++pos;
				}
				else
					break;
			}

			//If digits equals 0, it means that there was no number found.
			if(digits == 0)
			{
				Tools::write_err_log(Messages::no_num_str_end(entry));
				return 0;
			}

			//Get the number according to amount of digits.
			for(int j = 0; j < digits; ++j)
			{
				//The + 1 is needed for right indexing.
				const char numeral = entry.at(entry.length() - (j + 1));
				/*
				 * The value of the digit in the whole number needs to be considered.
				 * Example for the first iteration: j = 0 --> pow(10, 0) = 1
				 */
				number += static_cast<long long>(pow(10, j) * static_cast<long long>(numeral - 48));
			}

			//Consider the sign.
			if(is_neg)
				return -number;
			else
				return number;
		}
		else
		{
			Tools::write_err_log(Messages::given_str_empty);
			return -1;
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
				Tools::write_err_log(Messages::enter_pos_num_to_read_in_file(file));
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

		return -1;
	}

	std::string Tools::md5_hash(const std::string &seed) noexcept
	{
	    Poco::MD5Engine md5;
	    Poco::DigestOutputStream ds(md5);
	    ds << seed;
	    ds.close();
	    return Poco::DigestEngine::digestToHex(md5.digest());
	}

	std::string Tools::hmac_sha256_hash(const std::string &secret_key, const std::string &seed) noexcept
	{
		Poco::HMACEngine<SHA256Engine> hmac{secret_key};
		hmac.update(seed);
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

		//Iterate through the whole string.
		for(std::size_t j = 0; j < wstr.size(); ++j)
		{
			if(wstr.at(j) <= 0x7F)
				utf8_encoded += wstr.at(j);
			else if(wstr.at(j) <= 0x7FF)
			{
				//Our template for unicode of 2 bytes
				int utf8 = 0b11000000'10000000;

				//Get the first 6 bits and save them.
				utf8 += wstr.at(j) & 0b00111111;

				/*
				 * Get the last 5 remaining bits.
				 * Put them 2 to the left so that the 10 from 10xxxxxx (first byte) is not overwritten.
				 */
				utf8 += (wstr.at(j) & 0b00000111'11000000) << 2;

				//Append to the result.
				std::string temp = Tools::to_hex(utf8);
				utf8_encoded.append(temp.insert(0, "\\x").insert(4, "\\x"));
			}
			else if(wstr.at(j) <= 0xFFFF)
			{
				//Our template for unicode of 3 bytes
				int utf8 = 0b11100000'10000000'10000000;

				//Get the first 6 bits and save them.
				utf8 += wstr.at(j) & 0b00111111;

				/*
				 * Get the next 6 bits.
				 * Put them 2 to the left so that the 10 from 10xxxxxx (first byte) is not overwritten.
				 */
				utf8 += (wstr.at(j) & 0b00001111'11000000) << 2;

				/*
				 * Get the last 4 remaining bits.
				 * Put them 4 to the left so that the 10xx from 10xxxxxx (second byte) is not overwritten.
				 */
				utf8 += (wstr.at(j) & 0b11110000'00000000) << 4;

				//Append to the result.
				std::string temp = Tools::to_hex(utf8);
				utf8_encoded.append(temp.insert(0, "\\x").insert(4, "\\x").insert(8, "\\x"));
			}
			else if(wstr.at(j) <= 0x10FFFF)
			{
				//our template for unicode of 4 bytes
				int utf8 = 0b11110000'10000000'10000000'10000000;

				//Get the first 6 bits and save them.
				utf8 += wstr.at(j) & 0b00111111;

				/*
				 * Get the next 6 bits.
				 * Put them 2 to the left so that the 10 from 10xxxxxx (first byte) is not overwritten.
				 */
				utf8 += (wstr.at(j) & 0b00001111'11000000) << 2;

				/*
				 * Get the next 6 bits.
				 * Put them 4 to the left so that the 10xx from 10xxxxxx (second byte) is not overwritten.
				 */
				utf8 += (wstr.at(j) & 0b00000011'11110000'00000000) << 4;

				/*
				 * Get the last 3 remaining bits.
				 * Put them 6 to the left so that the 10xxxx from 10xxxxxx (third byte) is not overwritten.
				 */
				utf8 += (wstr.at(j) & 0b00011100'00000000'00000000) << 4;

				//Append to the result.
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
			Tools::write_err_log(Messages::not_gzip_compressed);
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

	std::string Tools::get_date(const std::time_t &time) noexcept
	{
		if(time >= 0)
		{
			//Get the time.
			std::time_t raw_time;

			if(time == 0)
				std::time(&raw_time);
			else
				raw_time = time;

			struct std::tm *time_info;
			time_info = std::localtime(&raw_time);

			std::string temp = std::asctime(time_info);

			if(!temp.empty())
				temp.pop_back();

			return temp;
		}
		else
		{
			Tools::write_err_log(Messages::not_pos_int);
			return "";
		}
	}

	std::string Tools::get_timezone_offset() noexcept
	{
		//Get the time.
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
		//Get the last 9 chars of the number as this can never cause an integer overflow.
		std::string tmp = std::to_string(get_time_in_millisec());
		std::reverse(tmp.begin(), tmp.end());
		std::string result;

		for(std::size_t j = 0; j < tmp.size(); ++j)
		{
			if(j < 9)
				result += tmp.at(j);
			else
				break;
		}

		return std::stoi(result);
	}

	std::tm* Tools::get_tm(const std::time_t &time) noexcept
	{
		if(time >= 0)
		{
			//Get the time.
			std::time_t raw_time;

			if(time == 0)
				std::time(&raw_time);
			else
				raw_time = time;

			struct std::tm *time_info;
			time_info = std::localtime(&raw_time);
			return time_info;
		}
		else
		{
			Tools::write_err_log(Messages::not_pos_int);
			struct std::tm *time_info;
			time_info = std::localtime(0);
			return time_info;
		}
	}

	//todo
	std::string Tools::get_file_ln_val(const std::string &ln) noexcept
	{
		if(!ln.empty())
		{
			std::string result;
			std::vector<std::string> args = Tools::get_args(ln);
			bool add = false; //The variable indicates when chars need to be added to the output string.

			for(std::size_t j = 0; j < args.size(); ++j)
			{
				if(add == true)
				{
					result.append(args.at(j));

					if(j != args.size() - 1)
						result.append(" ");
				}

				//This condition defines when the chars are added to the result string.
				if(Tools::ends_w(args.at(j), ":"))
					add = true;
			}

			return result;
		}
		else
		{
			Tools::write_err_log(Messages::given_str_empty);
			return "";
		}
	}

	std::string Tools::get_file_ln_key(const std::string &ln) noexcept
	{
		if(!ln.empty())
		{
			std::string result;
			std::vector<std::string> args = Tools::get_args(ln);

			for(std::size_t j = 0; j < args.size(); ++j)
			{
				result.append(args.at(j));

				if(j != args.size() - 1)
					result.append(" ");

				//This condition defines when the key is over.
				if(Tools::ends_w(args.at(j), ":") || Tools::ends_w(args.at(j), ": "))
				{
					//At this moment, we have: "key0 key1 key2: " or "key0 key1 key2:"
					while(tools::Tools::ends_w(result, ":") || tools::Tools::ends_w(result, " "))
						result.pop_back();

					return result;
				}
			}

			return "";
		}
		else
		{
			Tools::write_err_log(Messages::given_str_empty);
			return "";
		}
	}

	void Tools::write_err_log(const std::string &err_msg) noexcept
	{
		//Create the necessary folder.
		if(!tools::Tools::file_exists(Constants::folder_error_logs))
			Tools::mkdir(Constants::folder_error_logs);

		std::ofstream outf(Constants::file_err_log());
		outf << err_msg << std::endl;
		outf.close();
	}

	void Tools::write_err_log_tmp(const std::string &err_msg) noexcept
	{
		//Create the necessary folder.
		if(!tools::Tools::file_exists(Constants::folder_error_logs_tmp))
			Tools::mkdir(Constants::folder_error_logs_tmp);

		//Delete old temporary error logs.
		std::vector<std::string> files;
		int num_files = 0;

        for(const auto &entry : boost::make_iterator_range(boost::filesystem::directory_iterator(Constants::folder_error_logs_tmp), {}))
        {
        	files.push_back(entry.path().string());
        	++num_files;
        }

        //Sort the vector ascendingly.
        std::sort(files.begin(), files.end());

        if(!files.empty() && files.size() >= Constants::max_tmp_err_logs)
        	Tools::del_file(files.at(0));

        std::ofstream outf(Constants::file_err_log_tmp());
		outf << err_msg << std::endl;
		outf.close();
	}

	void Tools::del_file(const std::string &file) noexcept
	{
		if(std::remove(file.c_str()) != 0)
			Tools::write_err_log(Messages::file_del_err(file));
	}

	void Tools::mkdir(const std::string &path) noexcept
	{
		try
		{
			boost::filesystem::create_directories(path);
		}
		catch(const std::exception &e)
		{
			Tools::write_err_log(e.what());
		}
	}

	void Tools::rmdir(const std::string &path) noexcept
	{
		try
		{
			boost::filesystem::remove_all(path);
		}
		catch(const std::exception &e)
		{
			Tools::write_err_log(e.what());
		}
	}

	std::string Tools::exec(const char *cmd) noexcept
	{
	    std::array<char, 128> buffer;
	    std::string result;
	    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

	    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	        result += buffer.data();

	    //Remove the appended new line.
	    if(!result.empty())
	    	result.pop_back();

	    return result;
	}
}
