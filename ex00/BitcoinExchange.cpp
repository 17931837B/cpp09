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
			if (!ss)
			{
				std::cerr << "format is wrong." << std::endl;
				continue ;
			}
			if (!isVal(value))
				continue ;
			rate = getRate(date);
			if (rate == -1)
			{
				std::cerr << "value is wrong." << std::endl;
				continue ;
			}
			std::cout << date << "=>" << value << " = " << rate * std::strtod(value.c_str(), NULL) << std::endl;
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
	return (true);
}

bool	BitcoinExchange::isYear(std::string year)
{
	int	num = std::atoi(year.c_str());
	if (num < 2009)
		return (false);
	return (true);
}

bool	BitcoinExchange::isMonth(std::string month)
{
	int	num = std::atoi(month.c_str());
	if (num < 1 || 12 < num)
		return (false);
	return (true);
}

bool	BitcoinExchange::isDay(std::string year, std::string month, std::string day)
{
	int	num_y = std::atoi(year.c_str());
	int	num_m = std::atoi(month.c_str());
	int	num_d = std::atoi(day.c_str());

	if (num_m == 2)
	{
		if (num_d < 1 || 29 < num_d)
			return (false);
	}
	else if (num_m == 4 || num_m == 6 || num_m == 9 || num_m == 11)
	{
		if (num_d < 1 || 30 < num_d)
			return (false);
	}
	else
	{
		if (num_d < 1 || 29 < num_d)
			return (false);
	}
	if (!(num_y % 4 == 0 && (num_y % 100 != 0 || num_y % 400 == 0)) && num_d == 29)
		return (false);
	return (true);
}

bool	BitcoinExchange::isVal(std::string val)
{
	int	dot_pos = 0;
	size_t	i;
	if (val[0] != ' ')
		return (false);
	if (num[1] == '-')
		i = 2;
	else
		i = 1;
}