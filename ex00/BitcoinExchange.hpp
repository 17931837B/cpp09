#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> exchangeRates;
		BitcoinExchange();
	public:
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange& operator = (const BitcoinExchange &src);
};

#endif