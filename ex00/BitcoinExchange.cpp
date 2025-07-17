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
		std::string	line;
		std::string	date;
		std::string	value;
		std::getline(file, line);
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::getline(ss, date, ',');
			std::getline(ss, value);
			_bitInf[date] = std::strtod(value.c_str(), NULL);
		}
		file.close();
	}
	else
		std::cerr << "Can't open file." << std::endl;
}

void	BitcoinExchange::output(char *filename)
{
	std::ifstream infile(filename);
	std::string	line;
	std::string	date;
	std::string	value;
	double	rate;
	if (infile.is_open())
	{
		std::getline(infile, line);
		while (getline(infile, line))
		{
			std::stringstream ss(line);
			std::getline(ss, date, '|');
			if (!isDate())
			{
				std::cerr << "date is wrong." << std::endl;
				continue;
			}
			std::getline(ss, value);
		}
	}
}

bool	isNum(const std::string &str)
{
	size_t	i = 0;
	while (i < str.length())
	{
		if (str[i] < '0' || '9' < str[i])
			return (false);
		i++;
	}
	return (true);
}

bool	BitcoinExchange::isDate(std::string date)
{
	std::string	year;
	std::string	month;
	std::string	day;
	std::stringstream	ss(date);
	if (!std::getline(ss, year, '-') && !isNum(year))
		return (false);
	if (!std::getline(ss, month, '-') && !isNum(month))
		return (false);
	if (!std::getline(ss, day, '-') && !isNum(day))
		return (false);
	if (!isYear(year) || !isMonth(month) || !isDay(day))
		return (false);
}