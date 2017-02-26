#include <iostream>
#include "micro_vector.h"
//#include "micro_list.h"
#include "micro_algorithm.h"
#include "micro_iterator.h"
//#include <list>
int main()
{
	MicroSTL::Vector<int> v(2, 4);
	v.push_back(3);
	v.insert(v.begin(), 1);
	v.push_back(5);
	v.insert(v.begin(), 0);
	v.push_back(6);
	v.erase(v.begin(), v.begin() + 3);
	v.insert(v.begin() + 1, 2);
	v.insert(v.begin(), 2, 8);
	MicroSTL::Vector<int> s = v;
	for (size_t i = 0; i < s.size(); ++i) {
		std::cout << s[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}