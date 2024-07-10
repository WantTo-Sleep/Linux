// https://www.nowcoder.com/practice/d77d11405cc7470d82554cb392585106?tpId=13&&tqId=11174&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pushV int整型vector 
     * @param popV int整型vector 
     * @return bool布尔型
     */
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV)
    {
        // write code here
        stack<int> st;
        size_t popI = 0;
        for (auto& e : pushV)
        {
            st.push(e);
            while (!st.empty() && st.top() == popV[popI])
            {
                st.pop();
                ++popI;
            }
        }

        return st.empty();
    }
};