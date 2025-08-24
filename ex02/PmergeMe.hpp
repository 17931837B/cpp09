#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <climits>

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
		PmergeMe(const PmergeMe &src);
		PmergeMe& operator = (const PmergeMe &src);
		std::deque<unsigned int> getDeque() const;
		std::vector<unsigned int> getVector() const;
		void	output();
		void	initVec(int argc, char **argv);
		void	initDeq(int argc, char **argv);
		void	isNum(char *str);
		void	isDuplicate(std::vector<unsigned int> &vec);
		void	sortVec(std::vector<unsigned int> &vec);
		void	sortDeq(std::deque<unsigned int> &deq);
		int		power(int n, int m);
		void	insertVec(std::vector<unsigned int>& vec, unsigned int a, int left, int right);
		void	insertDeq(std::deque<unsigned int>& deq, unsigned int a, int left, int right);
		int		getSmallIndexVec(unsigned int val, std::vector<Data>& small);
		int		getSmallIndexDeq(unsigned int val, std::deque<Data>& small);
		int		findLeftVec(std::vector<unsigned int>& vec, unsigned int val);
		int		findLeftDeq(std::deque<unsigned int>& deq, unsigned int val);
};




#endif

