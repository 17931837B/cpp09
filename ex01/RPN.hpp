#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <list>
#include <climits>

class RPN
{
	private:
		std::stack<int, std::list<int> >	_stack;
	public:
		RPN();
		~RPN();
		RPN(const RPN &src);
		RPN& operator = (const RPN &src);
		std::stack<int, std::list<int> > getStack() const;
		void	Calculate(std::string input);
		void	add();
		void	sub();
		void	mul();
		void	div();
};

#endif