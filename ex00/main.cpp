#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "arguments are different." << std::endl;
		return (1);
	}
	BitcoinExchange btc(CSV_PATH);
	btc.output(argv[1]);
	return (0);
}