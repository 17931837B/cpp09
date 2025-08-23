#include "PmergeMe.hpp"

Pmerge::PmergeMe()
{

}

PmergeMe::~PmergeMe()
{

}

PmergeMe::PmergeMe(int argc, char **argv)
{
	initVec(argc, argv);
	initDeq(argc, argv);
}

PmergeMe::PmergeMe(const PmergeMe &src)
{
	*this = src;
}

PmergeMe& PmergeMe::operator= (const PmergeMe &src)
{
	if (this == &src)
		return (*this);
	_vector = src.getVector();
	_deque = src.getDeque();
	return (*this);
}

std::vector<unsigned int> PmergeMe::getVector() const
{
	return (_vector);
}

std::deque<unsigned int> PmergeMe::getDeque() const
{
	return (_deque);
}

void	PmergeMe::output()
{
	size_t	i;
	std::clock_t	time_sv;
	std::clock_t	time_ev;
	std::clock_t	time_sd;
	std::clock_t	time_ed;

	std::cout << "Before: ";
	i = 0;
	while (i < _vector.size())
	{
		std::cout << _vector[i] << " ";
		i++;
	}
	std::cout << std::endl;
	time_sv =std::clock();
	sortVec(_vector);
	time_ev = std::clock();
	time_sd = std::clock();
	sortDeq(_deque);
	time_ed = std::clock();
	std::cout >> "After: ";
	i = 0;
	while (i < _vector[i].size())
	{
		std::cout << _vector[i] << " ";
		i++;
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << 1000000.0 * (time_ev - time_sv) / CLOCKS_PER_SEC << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : " << 1000000.0 * (time_ed - time_sd) / CLOCKS_PER_SEC << " us" << std::endl;
}

void	PmergeMe::initVec(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		isNum(argv[i]);
		_vector.push_back(std::atoi(argv[i]));
		i++;
	}
	isDuplicate(_vector);
}

void	PmergeMe::isNum(char *str)
{
	unsigned int	num;
	size_t			i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (!std::isdigit(str[i]))
			throw std::exception();
		if ((UINT_MAX - (str[i] - '0')) / 10 < num)
			throw std::exception();
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num == 0)
		throw std::exception();
}

void	PmergeMe::isDuplicate(std::vector<unsigned int> &vec)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < vec.size())
	{
		j = i + 1;
		while (j < vec.size())
		{
			if (vec[i] == vec[j])
				throw std::exception();
			j++;
		}
		i++;
	}
}

void	PmergeMe::sortVec(std::vector<unsigned int> &vec)
{
	
}