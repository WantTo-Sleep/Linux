// https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5?tpId=13&&tqId=11179&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking

/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
#include <vector>
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (pRootOfTree == nullptr) return nullptr;
        vector<TreeNode*> nodes;
        inOrder(pRootOfTree, nodes);
        TreeNode* head = nullptr;
        for (size_t i = 0; i < nodes.size(); ++i) {
            nodes[i]->left = head;
            head = nodes[i];
        }
        head = nullptr;
        for (size_t i = nodes.size() - 1; i > 0; --i) {
            nodes[i]->right = head;
            head = nodes[i];
        }
        nodes[0]->right = head;
        return nodes[0];
    }
private:
    void inOrder(TreeNode* root, vector<TreeNode*>& nodes) {
        if (root->left) inOrder(root->left, nodes);
        nodes.push_back(root);
        if (root->right) inOrder(root->right, nodes);
    }
};
