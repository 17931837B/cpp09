#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>

#define CSV_PATH "./data.csv"

class BitcoinExchange
{
	private:
		std::map<std::string, double> _bitInf;
		BitcoinExchange();
	public:
		BitcoinExchange(const char *path);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange& operator = (const BitcoinExchange &src);
		void	setData(const char *path);
		void	output(char *filename);
		double	getRate(std::string date);
		bool	isNum(const std::string &str);
		bool	isDate(std::string date);
		bool	isYear(std::string year);
		bool	isMonth(std::string month);
		bool	isDay(std::string year, std::string month, std::string day);
		bool	isVal(std::string val);
		bool	isDouble(std::string val);
};

#endif
