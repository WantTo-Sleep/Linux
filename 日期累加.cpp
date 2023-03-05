#include <iostream>
using namespace std;

class Date
{
public:
    void Print()
    {
        printf("%04d-%02d-%02d\n", _year, _month, _day);
    }
    int GetMonthDay(int year, int month)
    {
        static int monthDay[13]={ 0,31,28,31,30,31,30,31,31,30,31,30,31 };
        if ((month == 2) && ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)))
        {
            return 29;
        }
        else
        {
            return monthDay[month];
        }
    }
    Date(int year = 1970, int month = 1, int day = 1)
        :_year(year)
        , _month(month)
        , _day(day)
    {}
    Date& operator+=(int day)
    {
        _day += day;
        day = GetMonthDay(_year, _month);
        while (_day > day)
        {
            ++_month;
            if (_month == 13)
            {
                ++_year;
                _month = 1;
            }
            _day -= day;
            day = GetMonthDay(_year, _month);
        }
        return *this;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main()
{
    int m = 0;
    cin >> m;
    while (m--)
    {
        int year, month, day;
        cin >> year >> month >> day;
        Date d(year, month, day);
        cin >> day;
        d += day;
        d.Print();
    }
}
