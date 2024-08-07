// https://leetcode.cn/problems/construct-string-from-binary-tree/

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
    string tree2str(TreeNode* root) {
        string result;
        _tree2str(root, result);
        return result;
    }
private:
    void _tree2str(TreeNode* root, string& str) {
        str += to_string(root->val);

        if (nullptr != root->left) {
            str += '(';
            _tree2str(root->left, str);
            str += ')';
        }
        else if (nullptr != root->right) {
            str += "()";
        }

        if (nullptr != root->right) {
            str += '(';
            _tree2str(root->right, str);
            str += ')';
        }
    }
};