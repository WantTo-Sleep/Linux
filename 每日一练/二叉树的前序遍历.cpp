// https://leetcode.cn/problems/binary-tree-preorder-traversal/description/

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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> rightTree;
        TreeNode* cur = root;
        // 先遍历根，再存右树，再遍历左树
		// 左树遍历完从栈中拿出右树遍历
        while (nullptr != cur) {
            result.push_back(cur->val);
            rightTree.push(cur->right);
            cur = cur->left;
            while (!rightTree.empty()) {
                if (nullptr == cur) {
                    cur = rightTree.top();
                    rightTree.pop();
                }
                else break;
            }
        }
        return result;
    }
};