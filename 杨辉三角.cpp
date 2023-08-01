class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        // 生成numRows行
        vector<vector<int>> vv(numRows);
		
        // 初始化每行，分配对应的长度，并将每行第一个和最后一个数置1
        for (size_t i = 0; i < vv.size(); ++i)
        {
            vv[i].resize(i + 1);
            vv[i][0] = vv[i][i] = 1;
        }
        // 填补空缺位置
        for (size_t i = 2; i < vv.size(); ++i)
        {
            for (size_t j = 1; j + 1 < vv[i].size(); ++j)
            {
                vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
            }
        }

        return vv;
    }
};