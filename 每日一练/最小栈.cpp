//https://leetcode.cn/problems/min-stack/description/

class MinStack 
{
public:
    MinStack()
    {

    }
    
    void push(int val)
    {
        _st.push(val);
        if (_min.empty() || _min.top()._val > val)
        {
            _min.push({val, 1});
        }
        else if (_min.top()._val == val)
        {
            ++_min.top()._count;
        }
    }
    
    void pop()
    {
        if (_st.top() == _min.top()._val)
        {
            if (--_min.top()._count == 0)
            {
                _min.pop();
            }
        }
        _st.pop();
    }
    
    int top()
    {
        return _st.top();
    }
    
    int getMin()
    {
        return _min.top()._val;
    }
private:
    struct node
    {
        int _val;
        int _count;
        node(int val = 0, int count = 0): _val(val), _count(count) {}
    };
    stack<int> _st;
    stack<node> _min;
};