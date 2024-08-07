// https://leetcode.cn/problems/binary-tree-postorder-traversal/description/

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> rightTree;
        TreeNode* cur = root;
        TreeNode* prev = nullptr;

        while (true) {
            while (cur) {
                rightTree.push(cur);
                cur = cur->left;
            }
            if(!rightTree.empty()) {
                cur = rightTree.top();
                rightTree.pop();
            }
            else break;
            if (cur->right == nullptr || cur->right == prev) {
                result.push_back(cur->val);
                prev = cur;
                cur = nullptr;
            }
            else {
                rightTree.push(cur);
                cur = cur->right;
            }
        }
        return result;
    }
};