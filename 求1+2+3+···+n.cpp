class Solution
{
public:
    int Sum_Solution(int n)
    {
        Sum arr[n];
        return _sum;
    }

private:
    class Sum
    {
    public:
        Sum()
        {
            _sum += _n;
            ++_n;
        }
    };
    static int _sum;
    static int _n;
};
int Solution::_sum = 0;
int Solution::_n = 1;
