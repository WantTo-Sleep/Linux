#include <iostream>
#include "my_queue.h"

int main()
{
	sjx::queue<int> q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.push(5);

	while (!q1.empty())
	{
		std::cout << q1.front() << ' ';
		std::cout << q1.back() << ' ';
		std::cout << q1.size() << std::endl;
		q1.pop();
	}
	return 0;
}