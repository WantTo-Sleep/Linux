// https://leetcode.cn/problems/binary-tree-inorder-traversal/description/

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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> rightTree;
        TreeNode* cur = root;

        while (true) {
            // 找到最左的孩子，也就是第一个要遍历的结点
            while (cur) {
                rightTree.push(cur);
                cur = cur->left;
            }
            while (!rightTree.empty()) {
                cur = rightTree.top();
                rightTree.pop();
                if (cur != nullptr) break;
            }
            
            if (cur != nullptr) {
                result.push_back(cur->val);
                cur = cur->right;
            }
            else break;
        }
        return result;
    }
};