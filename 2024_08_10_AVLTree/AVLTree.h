#pragma once

namespace sjx
{
	template<typename T>
	struct AVLTreeNode
	{
		T _value;
		struct AVLTreeNode* _left;
		struct AVLTreeNode* _right;
		struct AVLTreeNode* _parent;
		// 平衡因子
		int _bf;

		AVLTreeNode(const T& value) :_value(value), _left(nullptr), _right(nullptr), _parent(nullptr), _bf(0) {}
	};

	template<typename T>
	class AVLTree
	{
		typedef AVLTreeNode<T> Node;
	public:
		AVLTree() :_root(nullptr) {}

		bool Insert(const T& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(value);
				return true;
			}
			// 找到要插入的位置
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (value < cur->_value)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (value > cur->_value)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}

			// 插入结点，链接
			cur = new Node(value);
			cur->_parent = parent;
			if (value < parent->_value) parent->_left = cur;
			else parent->_right = cur;

			// 更新平衡因子
			while (parent)
			{
				if (cur == parent->_left) --parent->_bf;
				else ++parent->_bf;

				// 继续向上更新
				if (parent->_bf == 0) break;
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else
				{
					// 平衡因子异常
					if (parent->_bf == -2)
					{
						// parent的左子树的左子树高度增加，右单旋
						if (cur->_bf == -1)
						{
							RotateR(parent);
						}
						else
						{
							// parent的左子树的右子树高度增加，左右双旋
							RotateLR(parent);
						}
					}
					else if (parent->_bf == 2)
					{
						// parent的右子树的右子树高度增加，左单旋
						if (cur->_bf == 1)
						{
							RotateL(parent);
						}
						else
						{
							// parent的右子树的左子树高度增加，右左双旋
							RotateRL(parent);
						}
					}
					break;
				}
			}
			return true;
		}

		void Inorder()
		{
			_Inorder(_root);
		}
	private:
		void RotateR(Node* parent)
		{
			Node* cur = parent->_left;
			Node* grandpa = parent->_parent;
			// cur的左子树高度增加，进行右单旋
			// 更新结点的左右指针指向
			// grandpa指向cur，parent的左指向cur的右，cur的右指向parent
			if (grandpa == nullptr) _root = cur;
			else if (grandpa->_left == parent) grandpa->_left = cur;
			else if (grandpa != nullptr && grandpa->_right == parent) grandpa->_right = cur;
			parent->_left = cur->_right;
			cur->_right = parent;

			// 更新父指针: parent, cur, cur->right
			parent->_parent = cur;
			cur->_parent = grandpa;
			// 原来cur->right已经变成了parent->left;
			if (parent->_left != nullptr)
			{
				parent->_left->_parent = parent;
			}
			// 更新平衡因子
			cur->_bf = 0;
			parent->_bf = 0;
		}
		void RotateL(Node* parent)
		{
			Node* grandpa = parent->_parent;
			Node* cur = parent->_right;

			// 更新结点的左右子指针
			// granda指向cur，parent的右指向cur的左，cur的左指向parent
			if (grandpa == nullptr) _root = cur;
			else if (parent == grandpa->_left) grandpa->_left = cur;
			else if (parent == grandpa->_right) grandpa->_right = cur;
			parent->_right = cur->_left;
			cur->_left = parent;

			// 更新结点的父指针
			// parent指向cur，cur指向grandpa，原cur的左指向parent
			parent->_parent = cur;
			cur->_parent = grandpa;
			// 原cur的左变为了parent的右
			if (parent->_right != nullptr) parent->_right->_parent = parent;

			// 更新平衡因子
			parent->_bf = cur->_bf = 0;
		}
		void RotateLR(Node* parent)
		{
			Node* grandpa = parent->_parent;
			Node* childL = parent->_left;
			Node* childLR = childL->_right;
			int bf = childLR->_bf;

			// 更新结点的左右子指针
			if (grandpa == nullptr) _root = childLR;
			else if (parent == grandpa->_left) grandpa->_left = childLR;
			else if (parent == grandpa->_right) grandpa->_right = childLR;
			parent->_left = childLR->_right;
			childL->_right = childLR->_left;
			childLR->_left = childL;
			childLR->_right = parent;

			// 更新结点父指针
			parent->_parent = childLR;
			childL->_parent = childLR;
			childLR->_parent = grandpa;
			if (childL->_right != nullptr) childL->_right->_parent = childL;
			if (parent->_left != nullptr) parent->_left->_parent = parent;

			// 更新平衡因子，如果childLR就是新插入的结点，则此时平衡
			parent->_bf = childL->_bf = childLR->_bf = 0;
			if (bf != 0)
			{
				if (bf == -1) parent->_bf = 1;
				else childL->_bf = -1;
			}

		}
		void RotateRL(Node* parent)
		{
			Node* grandpa = parent->_parent;
			Node* childR = parent->_right;
			Node* childRL = childR->_left;
			int bf = childRL->_bf;

			// 更新结点的左右子指针
			if (grandpa == nullptr) _root = childRL;
			else if (parent == grandpa->_left) grandpa->_left = childRL;
			else if (parent == grandpa->_right) grandpa->_right = childRL;
			parent->_right = childRL->_left;
			childR->_left = childRL->_right;
			childRL->_left = parent;
			childRL->_right = childR;

			// 更新结点父指针
			parent->_parent = childRL;
			childR->_parent = childRL;
			childRL->_parent = grandpa;
			if (parent->_right != nullptr) parent->_right->_parent = parent;
			if (childR->_left != nullptr) childR->_left->_parent = childR;

			// 更新平衡因子
			parent->_bf = childR->_bf = childRL->_bf = 0;
			if (bf != 0)
			{
				if (bf == -1) childR->_bf = 1;
				else parent->_bf = -1;
			}
		}
		void _Inorder(Node* root)
		{
			if (root == nullptr) return;
			_Inorder(root->_left);
			std::cout << root->_value << ' ';
			_Inorder(root->_right);
		}
		Node* _root;
	};
}