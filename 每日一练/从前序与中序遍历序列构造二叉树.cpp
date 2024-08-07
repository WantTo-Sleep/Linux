// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int prei = 0;
        return _buildTree(preorder, inorder, prei, 0, inorder.size() - 1);
    }
private:
    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, int& prei, int left, int right) {
        if (prei >= preorder.size() || right < left) return nullptr;

        TreeNode* cur = new TreeNode(preorder[prei]);
        size_t rooti = left;
        while (rooti <= right) {
            if (preorder[prei] == inorder[rooti]) break;
            ++rooti;
        }
        ++prei;
        cur->left = _buildTree(preorder, inorder, prei, left, rooti - 1);
        cur->right = _buildTree(preorder, inorder, prei, rooti + 1, right);
        return cur;
    }
};