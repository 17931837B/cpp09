#include "RPN.hpp"

void	test(const char *str)
{
	RPN	rpnT;
	try
	{
		rpnT.Calculate(str);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error" << '\n';
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: number of arguments." << std::endl;
		return (1);
	}
	try
	{
		RPN	rpn;
		rpn.Calculate(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error" << '\n';
	}

	test("8 9 * 9 - 9 - 9 - 4 - 1 +");
	test("7 7 * 7 -");
	test("1 2 * 2 / 2 * 2 4 - +");
	test("(1 + 1)");
	test("10 1 /");
	test("1 +");
	test("1 2 3 * -");
	test("1 2 %");
	test("a 1 +");
	test("1 2 a");
	test("1 0 /");
	test("5 5 - 1 /");
	test("");
	test("1  1 +");
	test("2 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 * * * * * * * * * * * * * * 1 - *");
	test("2 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 * * * * * * * * * * * * * * 1 - * 1 +");
	test("2 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 * * * * * * * * * * * * * * 1 - * 2 +");
	test("0 2 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 * * * * * * * * * * * * * * 1 - * 1 + - 1 -");
	test("0 2 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 * * * * * * * * * * * * * * 1 - * 1 + - 2 -");
	return (0);
}