#include "Date.h"

void Date::Print()
{
	cout << _year << "/" << _month << "/" << _day << endl;
}


int Date::GetMonthDay(int year, int month)
{
	static int monthDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	if ((month == 2) && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)))
	{
		return 29;
	}
	return monthDay[month];
}

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
	cout << "Date(int year = 1900, int month = 1, int day = 1)" << endl;
	if (month < 1 || month>13 || day<1 || day>GetMonthDay(_year, _month))
	{
		cout << "ÊäÈë´íÎó" << endl;
	}
}

Date::~Date()
{
	cout << "~Date()" << endl;
	_year = 0;
	_month = 0;
	_day = 0;
}

Date::Date(const Date& d)
{
	cout << "Date(const Date& d)" << endl;

	_year = d._year;
	_month = d._month;
	_day = d._day;
}

Date& Date::operator=(const Date& d)
{
	cout << "operator=()" << endl;
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}

Date& Date::operator+=(int day)
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

Date Date::operator+(int day)
{
	Date d(*this);
	d += day;

	return d;
}

Date& Date::operator-=(int day)
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

Date Date::operator-(int day)
{
	Date d(*this);
	d -= day;
	return d;
}

bool Date::operator>(const Date& d)
{
	if (_year > d._year)
		return true;
	else if (_year == d._year && _month > d._month)
		return true;
	else if (_year == d._year && _month == d._month && _day > d._day)
		return true;
	return false;
}

bool Date::operator==(const Date& d)
{
	return _year == d._year && _month == d._month && _day == d._day;
}

bool Date::operator>=(const Date& d)
{
	return *this > d || *this == d;
}

bool Date::operator<(const Date& d)
{
	return !(*this >= d);
}

bool Date::operator<=(const Date& d)
{
	return !(*this > d);
}

bool Date::operator != (const Date& d)
{
	return !(*this == d);
}

Date& Date::operator++()
{
	*this += 1;
	return *this;
}

Date Date::operator++(int)
{
	Date d(*this);
	*this += 1;
	return d;
}

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

Date Date::operator--(int)
{
	Date d(*this);
	*this -= 1;
	return d;
}

int Date::operator-(const Date& d)
{
	Date big = *this;
	Date small = d;
	if (big < small)
	{
		big = d;
		small = *this;
	}
	int day = 0;
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