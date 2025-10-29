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
		std::cerr << "Error: could not open file." << std::endl;
}

void	BitcoinExchange::output(char *filename)
{
	std::ifstream infile(filename);
	std::string	line;
	std::string	date;
	std::string	value;
	double		rate;

	if (infile.is_open())
	{
		std::getline(infile, line);
		while (getline(infile, line))
		{
			std::stringstream ss(line);
			std::getline(ss, date, '|');
			if (!isDate(date))
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue;
			}
			std::getline(ss, value);
			if (!ss)
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue ;
			}
			if (!isVal(value))
				continue ;
			rate = getRate(date);
			if (rate == -1)
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue ;
			}
			std::cout << date << "=> " << value << " = " << rate * std::strtod(value.c_str(), NULL) << std::endl;
		}
	}
}

double	BitcoinExchange::getRate(std::string date)
{
	date = date.substr(0, date.size() - 1);
	std::map<std::string, double>::iterator it = _bitInf.find(date);
	if (it == _bitInf.end())
	{
		_bitInf[date] = 0;
		it = _bitInf.find(date);
		if (it == _bitInf.begin())
		{
			_bitInf.erase(date);
			return (-1);
		}
		it--;
		_bitInf.erase(date);
	}
	return (it->second);
}

bool	BitcoinExchange::isNum(const std::string &str)
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

	if (!std::getline(ss, year, '-') || !isNum(year) || year.length() != 4)
		return (false);
	if (!std::getline(ss, month, '-') || !isNum(month) || month.length() != 2)
		return (false);
	if (!std::getline(ss, day, ' ') || !isNum(day) || day.length() != 2)
		return (false);
	if (!isYear(year) || !isMonth(month) || !isDay(year, month, day))
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

	if (num_d < 1)
		return (false);
	if (num_m == 2)
	{
		if (num_y % 4 == 0 && (num_y % 100 != 0 || num_y % 400 == 0))
		{
			if (29 < num_d)
				return (false);
		}
		else
		{
			if (28 < num_d)
				return (false);
		}
	}
	else if (num_m == 4 || num_m == 6 || num_m == 9 || num_m == 11)
	{
		if (30 < num_d)
			return (false);
	}
	else
	{
		if (31 < num_d)
			return (false);
	}
	return (true);
}

bool	BitcoinExchange::isDouble(std::string val)
{
	int	dot_pos = 0;
	size_t	i;

	if (val[0] != ' ')
		return (false);
	if (val[1] == '-')
		i = 2;
	else
		i = 1;
	while (i < val.length())
	{
		if (val[i] == '.')
		{
			if (dot_pos == 0)
				dot_pos = i;
			else
				return (false);
		}
		else if (val[i] < '0' || '9' < val[i])
			return (false);
		i++;
	}
	return (true);
}

bool	BitcoinExchange::isVal(std::string val)
{
	double	num_v;

	if (!isDouble(val))
	{
		std::cerr << "Error: not a double number." << std::endl;
		return (false);
	}
	num_v = std::strtod(val.c_str(), NULL);
	if (num_v < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	else if (1000 < num_v)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
}
