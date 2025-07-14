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
		std::map<std::string, float> _bitInf;
		BitcoinExchange();
	public:
		BitcoinExchange(const char *path);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange& operator = (const BitcoinExchange &src);
		void	setData(const char *path);
		void	output(char *filename);

};

#endif