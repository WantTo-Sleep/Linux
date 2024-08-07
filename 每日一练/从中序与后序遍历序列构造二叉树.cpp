// https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int posti = postorder.size() - 1;
        return _buildTree(inorder, postorder, posti, 0, inorder.size() - 1);
    }
private:
    TreeNode* _buildTree(vector<int>& inorder, vector<int>& postorder, int& posti, int left, int right) {
        if (posti < 0 || left > right) return nullptr;

        TreeNode* cur = new TreeNode(postorder[posti]);
        int rooti = right;
        while (rooti >= left) {
            if (postorder[posti] == inorder[rooti]) break;
            --rooti;
        }
        --posti;

        cur->right = _buildTree(inorder, postorder, posti, rooti + 1, right);
        cur->left = _buildTree(inorder, postorder, posti, left, rooti - 1);
        
        return cur;
    }
};