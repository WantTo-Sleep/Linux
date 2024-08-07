// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> p_ancestor;
        vector<TreeNode*> q_ancestor;

        findAncestor(root, p, p_ancestor);
        findAncestor(root, q, q_ancestor);

        size_t len = p_ancestor.size();
        len = len < q_ancestor.size() ? len : q_ancestor.size();
        for (size_t i = 0; i < len; ++i) {
            if (p_ancestor[i] != q_ancestor[i]) {
                return p_ancestor[i - 1];
            }
        }
        return p_ancestor[len - 1];
    }
private:
    bool findAncestor(TreeNode* root, TreeNode* find, vector<TreeNode*>& ancestor) {
        if (root == nullptr) return false;

        ancestor.push_back(root);
        if (root == find) return true;
        if (findAncestor(root->left, find, ancestor) == false) {
            if (findAncestor(root->right, find, ancestor) == false) {
                ancestor.pop_back();
                return false;
            }
        }
        return true;
    }
};