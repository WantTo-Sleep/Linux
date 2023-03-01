#include <iostream>
using namespace std;

class Date
{
public:
    friend istream& operator>>(istream& in, Date& d);
    int GetMonthDay(int year, int month)
    {
        static int MonthDay[13]={ 0,31,28,31,30,31,30,31,31,30,31,30,31 };
        if ((month == 2) && ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)))
        {
            return 29;
        }
        else
        {
            return MonthDay[month];
        }
    }

    int GetYearDay()
    {
        int sum = _day;
        for (int i = 1; i < _month; ++i)
        {
            sum += GetMonthDay(_year, i);
        }
        return sum;
    }

private:
    int _year;
    int _month;
    int _day;
};

istream& operator>>(istream& in, Date& d)
{
    in >> d._year >> d._month >> d._day;
    return in;
}

int main()
{
    Date d;
    cin >> d;
    cout << d.GetYearDay() << endl;
    return 0;
}