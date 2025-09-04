#include "PmergeMe.hpp"

void	test(const int argc, char **argv)
{
	try 
	{
		PmergeMe	pm(argc, argv);
		pm.output();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error" << '\n';
	}
}

int	main(int argc, char **argv)
{
	// if (std::strcmp(argv[1], "test") == 0)
	// {
	// 	argc += 1;
	// 	std::cout << "-----test1-----\n";
	// 	char* test_argv[] = {
	// 		const_cast<char*>("dummy"), 
	// 		const_cast<char*>("1"), 
	// 		const_cast<char*>("3"), 
	// 		const_cast<char*>("2")
	// 	};
	// 	test(4, test_argv);
	// 	std::cout << "-----test2-----\n";
	// 	char* test_argv2[] = {
	// 		const_cast<char*>("dummy"), 
	// 		const_cast<char*>("4"), 
	// 		const_cast<char*>("3"), 
	// 		const_cast<char*>("2"),
	// 		const_cast<char*>("2")
	// 	};
	// 	test(5, test_argv2);
	// 	std::cout << "-----test3-----\n";
	// 	char* test_argv3[] = {
	// 		const_cast<char*>("dummy"), 
	// 		const_cast<char*>("4"), 
	// 		const_cast<char*>("3"), 
	// 		const_cast<char*>("2"),
	// 		const_cast<char*>("a")
	// 	};
	// 	test(5, test_argv3);
	// 	return (0);
	// }
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
