#include <iostream>
#include <set>

int main()
{
	// 空の set に要素を追加する
	std::set<int> s;
	s.insert(3);
	s.insert(1);
	s.insert(4);
	s.insert(1);
	s.insert(5);
	s.insert(5);

	std::cout << "size: " << s.size() << '\n'; // size: 4

	for (const auto& elem : s)
	{
		std::cout << elem << ' '; // 1 3 4 5
	}

	std::cout << '\n';
}