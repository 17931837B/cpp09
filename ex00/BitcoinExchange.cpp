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

void	BitcoinExchange::setData(const char *path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string line;
		std::string date;
		std::string value;
		std::getline(file, line);
		while (std::getline(file, line))
		{
			std::stringstream s(line);
			std::getline(s, date, ',');
			std::getline(s, value);
			_bitInf[date] = std::strtod(value.c_str(), NULL);
		}
		file.close();
	}
	else
		std::cerr << "Can't open file." << std::endl;
}