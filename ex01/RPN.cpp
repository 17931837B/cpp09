#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN::RPN(const RPN &src)
{
	*this = src;
}

RPN& RPN::operator= (const RPN &src)
{
	if (this == &src)
		return (*this);
	_stack = src.getStack();
	return (*this);
}

std::stack<int, std::list<int> > RPN::getStack() const
{
	return (_stack);
}

void	RPN::Calculate(std::string input)
{
	char	num;
	bool	isSpace = true;
	std::string::iterator	it;

	if (input.empty())
		throw std::exception();
	it = input.begin();
	while (it != input.end())
	{
		if (std::isspace(*it))
		{
			if (isSpace == true)
				throw std::exception();
			isSpace = true;
			it++;
			continue ;
		}
		else
		{
			if (isSpace == false)
				throw std::exception();
			isSpace = false;
		}
		num = (*it);
		if (std::isdigit(*it))
			_stack.push((*it) - '0');
		else
		{
			if (_stack.size() < 2)
				throw std::exception();
			else
			{
				if (*it == '+')
					this->add();
				else if (*it == '-')
					this->sub();
				else if (*it == '*')
					this->mul();
				else if (*it == '/')
					this->div();
				else
					throw std::exception();
			}
		}
		it++;
	}
	if (_stack.size() != 1)
		throw std::exception();
	if (std::isdigit(num))
		throw std::exception();
	std::cout << _stack.top() << std::endl;
	_stack.pop();
}

void	RPN::add()
{
	int	num1;
	int	num2;
	int	res;

	num1 = _stack.top();
	_stack.pop();
	num2 = _stack.top();
	_stack.pop();
	if ((num1 > 0 && num2 > 0 && INT_MAX - num2 < num1) || (num1 < 0 && num2 < 0 && INT_MIN - num1 > num2))
		throw std::exception();
	res = num2 + num1;
	_stack.push(res);
}

void	RPN::sub()
{
	int	num1;
	int	num2;
	int	res;

	num1 = _stack.top();
	_stack.pop();
	num2 = _stack.top();
	_stack.pop();
	if ((num1 < 0 && num2 > INT_MAX + num1) || (num1 > 0 && num2 < INT_MIN + num1))
		throw std::exception();
	res = num2 - num1;
	_stack.push(res);
}

void	RPN::mul()
{
	int	num1;
	int	num2;
	int	res;

	num1 = _stack.top();
	_stack.pop();
	num2 = _stack.top();
	_stack.pop();
	if (num1 == 0)
	{
		_stack.push(0);
		return ;
	}
	if (INT_MAX / num1 < num2 || INT_MIN / num1 > num2)
		throw std::exception();
	res = num1 * num2;
	_stack.push(res);
}

void	RPN::div()
{
	int	num1;
	int	num2;
	int	res;

	num1 = _stack.top();
	_stack.pop();
	num2 = _stack.top();
	_stack.pop();
	if (num1 == 0)
		throw std::exception();
	if (num2 == INT_MIN && num1 == -1)
		throw std::exception();
	res = num2 / num1;
	_stack.push(res);
}
