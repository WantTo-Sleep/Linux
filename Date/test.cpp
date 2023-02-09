#include "Date.h"

void Test1()
{
	Date d1(2023, 2, 9);
	Date d2(2024, 1, 1);

	printf("%d\n", d2 - d1);

	////cout << (d2 > d1) << endl;
	//cout << (d1 >= d2) << endl;

	//d2 += 5;
	//cout << (d1 >= d2) << endl;

	//d2 += 5;
	//cout << (d1 >= d2) << endl;

	//(d1++).Print();
	//d1.Print();

	//(++d1).Print();
	//d1.Print();

	//(d2--).Print();
	//d2.Print();

	//(++d2).Print();
	//d2.Print();

	return;
}

int main()
{
	Test1();
	return 0;
}