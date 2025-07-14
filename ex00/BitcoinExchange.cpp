#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const char *path)
{
	setData(path);
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	*this = copy;
}

BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange &src)
{
	if (this == &src)
		return (*this);
	_bitInf = src._bitInf;
	return (*this);
}

