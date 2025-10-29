#include "PmergeMe.hpp"

static int count_vec = 0;

PmergeMe::PmergeMe()
{

}

PmergeMe::~PmergeMe()
{
	// std::cout << count_vec << std::endl;
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
    struct timeval start_v, end_v;
    struct timeval start_d, end_d;

	std::cout << "Before: ";
	i = 0;
	while (i < _vector.size())
	{
		std::cout << _vector[i] << " ";
		i++;
	}
	std::cout << std::endl;
	gettimeofday(&start_v, NULL);
	sortVec(_vector);
	gettimeofday(&end_v, NULL);
	gettimeofday(&start_d, NULL);
	sortDeq(_deque);
	gettimeofday(&end_d, NULL);
	std::cout << "After: ";
	i = 0;
	while (i < _vector.size())
	{
		std::cout << _vector[i] << " ";
		i++;
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << (end_v.tv_sec - start_v.tv_sec) * 1000000.0 + (end_v.tv_usec - start_v.tv_usec) << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : " << (end_d.tv_sec - start_d.tv_sec) * 1000000.0 + (end_d.tv_usec - start_d.tv_usec) << " us" << std::endl;
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

void	PmergeMe::initDeq(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		_deque.push_back(std::atoi(argv[i]));
		i++;
	}
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

void PmergeMe::sortVec(std::vector<unsigned int> &vec)
{
	int							mid = vec.size() / 2;
	std::vector<unsigned int>	big(mid);
	std::vector<Data>			small(vec.size() - mid);
	size_t						i;
	size_t						j;
	int							jacobsthal_index;
	size_t						current_limit;
	size_t						previous_limit;
	bool						has_straggler = false;
	int							small_i;
	int							left;

	if (vec.size() <= 1)
		return ;
	i = 0;
	j = 0;
	while (i < vec.size() - 1)
	{
		if (vec[i] < vec[i + 1])
		{
			big[j] = vec[i + 1];
			small[j].id = big[j];
			small[j].val = vec[i];
		}
		else
		{
			big[j] = vec[i];
			small[j].id = big[j];
			small[j].val = vec[i + 1];
		}
		i += 2;
		j++;
	}
	if (vec.size() % 2 == 1)
	{
		small[mid].id = UINT_MAX;
		small[mid].val = vec.back();
		has_straggler = true;
	}
	sortVec(big);
	vec.clear();
	vec.insert(vec.end(), big.begin(), big.end());
	if (!small.empty())
	{
		unsigned int a1_val = big[0];
		int small1_i = getSmallIndexVec(a1_val, small);

		if (small1_i != -1)
		{
			unsigned int b1_val = small[small1_i].val;
			vec.insert(vec.begin(), b1_val);
			small.erase(small.begin() + small1_i);
		}
	}
	jacobsthal_index = 2;
	previous_limit = 1;
	while (small.size())
	{
		current_limit = (power(2, jacobsthal_index + 1) + power(-1, jacobsthal_index)) / 3;
		if (current_limit > big.size())
			current_limit = big.size();
		i = current_limit;
		while (i > previous_limit)
		{
			small_i = getSmallIndexVec(big[i - 1], small);
			if (small_i != -1)
			{
				left = findLeftVec(vec, small[small_i].id);
				insertVec(vec, small[small_i].val, 0, left);
				small.erase(small.begin() + small_i);
			}
			i--;
		}
		if (current_limit == big.size() && has_straggler)
		{
			for (size_t k = 0; k < small.size(); k++)
			{
				if (small[k].id == UINT_MAX)
				{
					insertVec(vec, small[k].val, 0, vec.size());
					small.erase(small.begin() + k);
					has_straggler = false;
					break;
				}
			}
		}
		if (current_limit == big.size())
			break;
		previous_limit = current_limit;
		jacobsthal_index++;
	}
}

void PmergeMe::sortDeq(std::deque<unsigned int> &deq)
{
	int							mid = deq.size() / 2;
	std::deque<unsigned int>	big(mid);
	std::deque<Data>			small(deq.size() - mid);
	size_t						i;
	size_t						j;
	int							jacobsthal_index;
	size_t						current_limit;
	size_t						previous_limit;
	bool						has_straggler = false;
	int							small_i;
	int							left;

	if (deq.size() <= 1)
		return ;
	i = 0;
	j = 0;
	while (i < deq.size() - 1)
	{
		if (deq[i] < deq[i + 1])
		{
			big[j] = deq[i + 1];
			small[j].id = big[j];
			small[j].val = deq[i];
		}
		else
		{
			big[j] = deq[i];
			small[j].id = big[j];
			small[j].val = deq[i + 1];
		}
		i += 2;
		j++;
	}
	if (deq.size() % 2 == 1)
	{
		small[mid].id = UINT_MAX;
		small[mid].val = deq.back();
		has_straggler = true;
	}
	sortDeq(big);
	deq.clear();
	deq.insert(deq.end(), big.begin(), big.end());
	if (!small.empty())
	{
		unsigned int a1_val = big[0];
		int small1_i = getSmallIndexDeq(a1_val, small);

		if (small1_i != -1)
		{
			unsigned int b1_val = small[small1_i].val;
			deq.insert(deq.begin(), b1_val);
	    	small.erase(small.begin() + small1_i);
	    }
	}
	jacobsthal_index = 2;
	previous_limit = 1;
	while (small.size())
	{
		current_limit = (power(2, jacobsthal_index + 1) + power(-1, jacobsthal_index)) / 3;
		if (current_limit > big.size())
			current_limit = big.size();
		i = current_limit;
		while (i > previous_limit)
		{
			small_i = getSmallIndexDeq(big[i - 1], small);
			if (small_i != -1)
			{
				left = findLeftDeq(deq, small[small_i].id);
				insertDeq(deq, small[small_i].val, 0, left);
				small.erase(small.begin() + small_i);
			}
			i--;
		}
		if (current_limit == big.size() && has_straggler)
		{
			for (size_t k = 0; k < small.size(); k++)
			{
				if (small[k].id == UINT_MAX)
				{
					insertDeq(deq, small[k].val, 0, deq.size());
					small.erase(small.begin() + k);
					has_straggler = false;
					break;
				}
			}
		}
		if (current_limit == big.size())
			break;
		previous_limit = current_limit;
		jacobsthal_index++;
	}
}

int	PmergeMe::power(int n, int m)
{
	int	res;
	int	i;

	res = 1;
	i = 0;
	while (i < m)
	{
		res *= n;
		i++;
	}
	return (res);
}

void	PmergeMe::insertVec(std::vector<unsigned int>& vec, unsigned int a, int left, int right)
{
	int	mid;

	count_vec++;
	if (left >= right)
	{
		vec.insert(vec.begin() + left, a);
		return ;
	}
	mid = left + (right - left) / 2;
	if (a < vec[mid])
		insertVec(vec, a, left, mid);
	else
		insertVec(vec, a, mid + 1, right);
}

void	PmergeMe::insertDeq(std::deque<unsigned int>& deq, unsigned int a, int left, int right)
{
	int	mid;

	if (left >= right)
	{
		deq.insert(deq.begin() + left, a);
		return ;
	}
	mid = left + (right - left) / 2;
	if (a < deq[mid])
		insertDeq(deq, a, left, mid);
	else
		insertDeq(deq, a, mid + 1, right);
}

int	PmergeMe::getSmallIndexVec(unsigned int val, std::vector<Data>& small)
{
	size_t	i;

	i = 0;
	while (i < small.size())
	{
		if (small[i].id == val)
			return (i);
		i++;
	}
	return (-1);
}

int	PmergeMe::getSmallIndexDeq(unsigned int val, std::deque<Data>& small)
{
	size_t	i;

	i = 0;
	while (i < small.size())
	{
		if (small[i].id == val)
			return (i);
		i++;
	}
	return (-1);
}

int	PmergeMe::findLeftVec(std::vector<unsigned int>& vec, unsigned int val)
{
	int	i;
	std::vector<unsigned int>::iterator it = vec.begin();

	i = 0;
	while (it != vec.end())
	{
		if (vec[i] == val)
			return (i);
		i++;
		it++;
	}
	return (0);
}

int	PmergeMe::findLeftDeq(std::deque<unsigned int>& deq, unsigned int val)
{
	int	i;
	std::deque<unsigned int>::iterator it = deq.begin();

	i = 0;
	while (it != deq.end())
	{
		if (deq[i] == val)
			return (i);
		i++;
		it++;
	}
	return (0);
}
