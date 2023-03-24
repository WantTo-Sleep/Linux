// 写一个递归函数，不使用 * 运算符
// 实现两个正整数的相乘。可以使用加号、减号、位移，但要吝啬一些。
class Solution
{
public:
    int multiply(int A, int B)
    {
        if (A > B)
            swap(A, B);
        if (A == 1)
            return B;
        return B + multiply(A - 1, B);
    }
};