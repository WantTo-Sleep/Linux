// https://www.nowcoder.com/practice/987f2981769048abaf6180ed63266bb2?tpId=196&tqId=39583&ru=/exam/oj

// 简单优化
class Solution {
    int m, n;
    bool vis[101][101] = { false };

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
  public:
    bool exist(vector<string>& board, string word) {
        m = board.size();
        n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    if (dfs(board, i, j, word, 0)) return true;
                }
            }
        }
        return false;
    }
    bool dfs(vector<string>& board, int i, int j, string& word, int pos) {
        if (pos == word.size() - 1) {
            return true;
        }
        vis[i][j] = true;
        for (int k = 0; k < 4; k++) {
            int a = i + dx[k], b = j + dy[k];
            if (a >= 0 && a < m && b >= 0 && b < n && !vis[a][b] && board[a][b] == word[pos + 1]) {
                if (dfs(board, a, b, word, pos + 1)) return true;
            }
        }
        vis[i][j] = false;
        return false;
    }
};

// my code
// class Solution {
//   public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param board string字符串vector
//      * @param word string字符串
//      * @return bool布尔型
//      */
//     bool exist(vector<string>& board, string word) {
//         // test用来记录那些位置已经走过
//         vector<vector<bool>> test(board.size());
//         for (auto& e : test) {
//             e.resize(board[0].size(), false);
//         }

//         // 找到第一个符合的字母，递归调用
//         for (size_t i = 0; i < board.size(); ++i) {
//             for (size_t j = 0; j < board[i].size(); ++j) {
//                 if (board[i][j] == word[0]) {
//                     test[i][j] = true;
//                     bool flag = _exist(board, test, word, i, j, 1);
//                     if (flag) {
//                         return true;
//                     }
//                     test[i][j] = false;
//                 }
//             }
//         }
//         return false;
//     }
//   private:
//     bool _exist(const vector<string>& board, vector<vector<bool>>& test, const string& word, size_t i, size_t j, size_t pos) {
//         if (pos >= word.size()) {
//             return true;
//         }
//         // 检测当前位置上下左右是否有符合条件的字母
//         if (i > 0 && !(test[i - 1][j]) && (board[i - 1][j] == word[pos])) {
//             test[i - 1][j] = true;
//             bool flag = _exist(board, test, word, i - 1, j, pos + 1);
//             if (flag) {
//                 return true;
//             }
//             test[i - 1][j] = false;
//         }
//         if (j > 0 && !(test[i][j - 1]) && (board[i][j - 1] == word[pos])) {
//             test[i][j - 1] = true;
//             bool flag = _exist(board, test, word, i, j - 1, pos + 1);
//             if (flag) {
//                 return true;
//             }
//             test[i][j - 1] = false;
//         }
//         if (i + 1 < board.size() && !(test[i + 1][j]) && (board[i + 1][j] == word[pos])) {
//             test[i + 1][j] = true;
//             bool flag = _exist(board, test, word, i + 1, j, pos + 1);
//             if (flag) {
//                 return true;
//             }
//             test[i + 1][j] = false;
//         }
//         if (j + 1 < board[0].size() && !(test[i][j + 1]) && (board[i][j + 1] == word[pos])) {
//             test[i][j + 1] = true;
//             bool flag = _exist(board, test, word, i, j + 1, pos + 1);
//             if (flag) {
//                 return true;
//             }
//             test[i][j + 1] = false;
//         }
//         return false;
//     }
// };