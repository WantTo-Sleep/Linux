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
		// ƽ������
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
			// �ҵ�Ҫ�����λ��
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

			// �����㣬����
			cur = new Node(value);
			cur->_parent = parent;
			if (value < parent->_value) parent->_left = cur;
			else parent->_right = cur;

			// ����ƽ������
			while (parent)
			{
				if (cur == parent->_left) --parent->_bf;
				else ++parent->_bf;

				// �������ϸ���
				if (parent->_bf == 0) break;
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else
				{
					// ƽ�������쳣
					if (parent->_bf == -2)
					{
						// parent�����������������߶����ӣ��ҵ���
						if (cur->_bf == -1)
						{
							RotateR(parent);
						}
						else
						{
							// parent�����������������߶����ӣ�����˫��
							RotateLR(parent);
						}
					}
					else if (parent->_bf == 2)
					{
						// parent�����������������߶����ӣ�����
						if (cur->_bf == 1)
						{
							RotateL(parent);
						}
						else
						{
							// parent�����������������߶����ӣ�����˫��
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
			// cur���������߶����ӣ������ҵ���
			// ���½�������ָ��ָ��
			// grandpaָ��cur��parent����ָ��cur���ң�cur����ָ��parent
			if (grandpa == nullptr) _root = cur;
			else if (grandpa->_left == parent) grandpa->_left = cur;
			else if (grandpa != nullptr && grandpa->_right == parent) grandpa->_right = cur;
			parent->_left = cur->_right;
			cur->_right = parent;

			// ���¸�ָ��: parent, cur, cur->right
			parent->_parent = cur;
			cur->_parent = grandpa;
			// ԭ��cur->right�Ѿ������parent->left;
			if (parent->_left != nullptr)
			{
				parent->_left->_parent = parent;
			}
			// ����ƽ������
			cur->_bf = 0;
			parent->_bf = 0;
		}
		void RotateL(Node* parent)
		{
			Node* grandpa = parent->_parent;
			Node* cur = parent->_right;

			// ���½���������ָ��
			// grandaָ��cur��parent����ָ��cur����cur����ָ��parent
			if (grandpa == nullptr) _root = cur;
			else if (parent == grandpa->_left) grandpa->_left = cur;
			else if (parent == grandpa->_right) grandpa->_right = cur;
			parent->_right = cur->_left;
			cur->_left = parent;

			// ���½��ĸ�ָ��
			// parentָ��cur��curָ��grandpa��ԭcur����ָ��parent
			parent->_parent = cur;
			cur->_parent = grandpa;
			// ԭcur�����Ϊ��parent����
			if (parent->_right != nullptr) parent->_right->_parent = parent;

			// ����ƽ������
			parent->_bf = cur->_bf = 0;
		}
		void RotateLR(Node* parent)
		{
			Node* grandpa = parent->_parent;
			Node* childL = parent->_left;
			Node* childLR = childL->_right;
			int bf = childLR->_bf;

			// ���½���������ָ��
			if (grandpa == nullptr) _root = childLR;
			else if (parent == grandpa->_left) grandpa->_left = childLR;
			else if (parent == grandpa->_right) grandpa->_right = childLR;
			parent->_left = childLR->_right;
			childL->_right = childLR->_left;
			childLR->_left = childL;
			childLR->_right = parent;

			// ���½�㸸ָ��
			parent->_parent = childLR;
			childL->_parent = childLR;
			childLR->_parent = grandpa;
			if (childL->_right != nullptr) childL->_right->_parent = childL;
			if (parent->_left != nullptr) parent->_left->_parent = parent;

			// ����ƽ�����ӣ����childLR�����²���Ľ�㣬���ʱƽ��
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

			// ���½���������ָ��
			if (grandpa == nullptr) _root = childRL;
			else if (parent == grandpa->_left) grandpa->_left = childRL;
			else if (parent == grandpa->_right) grandpa->_right = childRL;
			parent->_right = childRL->_left;
			childR->_left = childRL->_right;
			childRL->_left = parent;
			childRL->_right = childR;

			// ���½�㸸ָ��
			parent->_parent = childRL;
			childR->_parent = childRL;
			childRL->_parent = grandpa;
			if (parent->_right != nullptr) parent->_right->_parent = parent;
			if (childR->_left != nullptr) childR->_left->_parent = childR;

			// ����ƽ������
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