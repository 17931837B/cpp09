#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "arguments are different." << std::endl;
		return (1);
	}
	BitcoinExchange test(CSV_PATH);
	std::cout << argv[1] << std::endl;
	return (0);
}