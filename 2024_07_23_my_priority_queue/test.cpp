#include <iostream>
#include "my_priority_queue.h"

int main()
{
	//sjx::priority_queue<int> pq;
	sjx::priority_queue<int, std::vector<int>, sjx::greater<int>> pq;
	// 26 9 19 75 23 15 40
	pq.push(26);
	pq.push(9);
	pq.push(19);
	pq.push(75);
	pq.push(23);
	pq.push(15);
	pq.push(40);

	while (!pq.empty())
	{
		std::cout << pq.top() << " ";
		pq.pop();
	}
	std::cout << std::endl;

	return 0;
}