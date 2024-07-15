// https://leetcode.cn/problems/evaluate-reverse-polish-notation/description/
class Solution
{
public:
    int evalRPN(vector<string>& tokens)
    {
        stack<int> st;
        int left = 0;
        int right = 0;
        for (auto& e: tokens)
        {
            if (e == "+")
            {
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left + right);
            }
            else if (e == "-")
            {
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left - right);
            }
            else if (e == "*")
            {
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left * right);
            }
            else if (e == "/")
            {
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left / right);
            }
            else
            {
                st.push(atoi(e.c_str()));
            }
        }
        return st.top();
    }
};