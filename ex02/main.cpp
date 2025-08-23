#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: number of arguments." << std::endl;
		return (1);
	}
	try 
	{
		PmergeMe	pm(argc, argv);
		pm.output();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error" << '\n';
	}
	return (0);
}