// https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/description/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        queue<TreeNode*> node;
        node.push(root);

        while (!node.empty()) {
            size_t len = node.size();
            result.push_back(vector<int>());
            auto& tmp = result.back();
            for (size_t i = 0; i < len; ++i) {
                auto& _root = node.front();
                if (_root != nullptr) {
                    tmp.push_back(_root->val);
                    node.push(_root->left);
                    node.push(_root->right);
                }
                node.pop();
            }
        }
        result.pop_back();
        reverse(result.begin(), result.end());
        return result;
    }
};