#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>

struct Data
{
	unsigned int	id;
	unsigned int	val;
};

class PmergeMe
{
	private:
		std::vector<unsigned int> _vector;
		std::deque<unsigned int> _deque;
	public:
		PmergeMe();
		PmergeMe(int argc, char **argv);
		~PmergeMe();
		PmergeMe(const Pmerge &src);
		PmergeMe& operator = (const PmergeMe &src);
		std::deque<unsigned int> getDeque() const;
		std::vector<unsigned int> getVector() const;
		int	isNum(char *str);
		int	power(int base, int exponent);

};




#endif

