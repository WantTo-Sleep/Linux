#pragma once

template<typename K, typename V>
struct BSTreeNode
{
	K _key;
	V _val;
	struct BSTreeNode* _left;
	struct BSTreeNode* _right;

	BSTreeNode(K key, V val = V()) : _key(key), _val(val), _left(nullptr), _right(nullptr) {}
};


template<typename K, typename V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	BSTree() : _root(nullptr) {}

	bool Insert(K key, V val = V())
	{
		if (_root == nullptr)
		{
			_root = new Node(key, val);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		if (key < parent->_key)
		{
			parent->_left = new Node(key, val);
		}
		else
		{
			parent->_right = new Node(key, val);
		}
		return true;
	}

	Node* Find(K key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}
		return cur;
	}

	void InOrder()
	{
		_InOrder(_root);
	}

private:
	void _InOrder(Node* root)
	{
		if (root == nullptr) return;
		_InOrder(root->_left);
		std::cout << root->_key << ": " << root->_val << std::endl;
		_InOrder(root->_right);
	}
	Node* _root;

};