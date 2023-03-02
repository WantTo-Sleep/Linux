#include <iostream>
using namespace std;

class Date
{
public:
	friend istream& operator>>(istream& in, Date& d);

	// 获取某年某月的天数
	int GetMonthDay(int year, int month)const
	{
		static int monthDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

		if ((month == 2) && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)))
		{
			return 29;
		}
		return monthDay[month];
	}

	// 日期+=天数
	Date& operator+=(int day)
	{
		if (day < 0)
		{
			*this -= -day;
		}
		_day += day;
		day = GetMonthDay(_year, _month);
		while (_day > day)
		{
			++_month;
			if (_month > 12)
			{
				_month = 1;
				++_year;
			}
			_day -= day;
			day = GetMonthDay(_year, _month);
		}
		return *this;
	}

	// 日期-=天数
	Date& operator-=(int day)
	{
		if (day < 0)
		{
			*this += -day;
		}
		_day -= day;
		while (_day < 1)
		{
			--_month;
			if (_month < 1)
			{
				--_year;
				_month = 12;
			}
			day = GetMonthDay(_year, _month);
			_day += day;
		}
		return *this;
	}
	// >运算符重载
	bool operator>(const Date& d)const
	{
		if (_year > d._year)
			return true;
		else if (_year == d._year && _month > d._month)
			return true;
		else if (_year == d._year && _month == d._month && _day > d._day)
			return true;
		return false;
	}

	// ==运算符重载
	bool operator==(const Date& d)const
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}

	// >=运算符重载
	bool operator>=(const Date& d)const
	{
		return *this > d || *this == d;
	}

	// <运算符重载
	bool operator<(const Date& d)const
	{
		return !(*this >= d);
	}

	// <=运算符重载
	bool operator <= (const Date& d)const;

	// !=运算符重载
	bool operator != (const Date& d)const
	{
		return !(*this == d);
	}

	// 日期-日期 返回天数
	int operator-(const Date& d)const
	{
		Date big = *this;
		Date small = d;
		if (big < small)
		{
			big = d;
			small = *this;
		}
		int day = 1;
		int gap = (big._year - small._year) * 100 + 50;
		while (big != small)
		{
			while (big > small)
			{
				day += gap;
				small += gap;
			}
			gap /= 2;
			while (big < small)
			{
				day -= gap;
				small -= gap;
			}
		}

		return day;
	}

private:
	int _year;
	int _month;
	int _day;
};

istream& operator>>(istream& in, Date& d)
{
    int x = 0;
    cin >> x;
    d._day = x % 100;
    x /= 100;
    d._month = x % 100;
    d._year = x / 100;
    return in;
}


int main()
{
    Date d1, d2;
    cin >> d1 >> d2;
	cout<< d1 - d2 << endl;
    return 0;
}