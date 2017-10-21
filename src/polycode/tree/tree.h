/**
 * \file    tree.h
 * \brief   N-Tree classes and operations
 * \details
 * \author  boussole
 */

#ifndef TREE_H_
#define TREE_H_

#include <common/common.h>

/**
 * \namespace conq_tree
 * \brief Group structures, classes and operations for N-tree
 */
namespace conq_tree {

/**
 * \class Tree tree.h <tree/tree.h>
 * \brief Implementation of n-tree
 *
 * \details Using this class it could be possible to build any type of tree.
 * At first of all user should init root node, after that using an iterator build another nodes
 * \tparam T Type of data in node
 */
template <typename T>
class Tree {
	/**
	 * \struct Node
	 * \brief Private details of implementation
	 */
	template <typename U>
	struct Node {
		Node() :
			_data(U()), _parent(NULL),
			_children(NULL), _prev(NULL), _next(NULL) {}

		Node(U val) :
			_data(val), _parent(NULL),
			_children(NULL), _prev(NULL), _next(NULL) {}

		~Node() { /* std :: cout << "delete data: " << _data << std :: endl; */  }

		U _data;
		Node * _parent;
		Node * _children;
		Node * _prev;
		Node * _next;
	};

public:
	/**
	 * \class iterator
	 * \brief User interface for moving through tree
	 */
	class iterator {
		friend class Tree;
	public:
		iterator() : _node(NULL) {}

		iterator(Node<T> * node) : _node(node) {}

		iterator(const iterator & it)
		{
			this->_node = it._node;
		}

		~iterator() {}

		iterator & operator++()
		{
			if (_node) {
				_node = _node->_next;
			}

			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp(*this);

			operator++();

			return tmp;
		}

		iterator & operator--()
		{
			if (_node) {
				_node = _node->_prev;
			}

			return *this;
		}

		iterator operator--(int)
		{
			iterator tmp(this);

			operator--();

			return tmp;
		}

		iterator & up()
		{
			if (_node) {
				_node = _node->_parent;
			}

			return *this;
		}

		iterator & down()
		{
			if (_node) {
				_node = _node->_children;
			}

			return *this;
		}

		iterator & operator=(const iterator & it)
		{
			if (this != &it) {
				this->_node = it._node;
			}

			return *this;
		}

		bool operator==(const iterator & it) { return _node == it._node; }

		bool operator!=(const iterator & it) { return !operator==(it); }

		T & operator*() { return _node->_data; }

		operator bool() { return _node; }

	private:
		Node<T> * operator->() { return _node; }

		Node<T> * operator&() { return _node; }

		Node<T> * _node;
	};

	Tree();

	virtual ~Tree();

	/**
	 * \brief Clear all child tree of root with himself
	 */
	void clear(iterator root);

	/**
	 * \brief Check empty of a tree
	 */
	bool isEmpty() { return (_root == 0); }

	/**
	 * \brief Create root node or init it by another value
	 */
	iterator init(const T & v)
	{
		if (!_root) {
			_root = new Node<T>();
		}

		_root->_data = v;

		return iterator(_root);
	}

	/**
	 * \brief Add new child node as a last node in a child list of it node
	 */
	iterator appendChild(const iterator & it, const T & v)
	{
		assert(it._node);

		Node<T> * child = new Node<T>(v);

		if (!it._node->_children) {
			it._node->_children = child;
		}
		else {
			Node<T> * ch = it._node->_children;

			while (ch->_next) {
				ch = ch->_next;
			}

			ch->_next = child;

			child->_prev = ch;
		}

		child->_parent = it._node;

		return iterator(child);
	}

	/**
	 * \brief Add new child node as a first node in a child list of it node
	 */
	iterator prependChild(const iterator & it, const T & v)
	{
		assert(it._node);

		Node<T> * child = new Node<T>(v);

		if (!it._node->_children) {
			it._node->_children = child;
		}
		else {
			it._node->_children->_prev = child;
			child->_next = it._node->_children;
			it._node->_children = child;
		}

		child->_parent = it._node;

		return iterator(child);
	}

/*	iterator addBefore(iterator & it) {

	}

	iterator addAfter(iterator & it) {

	}

	iterator destroy(iterator & it) {

	}*/

	/**
	 * \brief Return iterator to root of tree
	 */
	iterator begin() { return iterator(_root); }

	/**
	 * \brief Return invalid iterator
	 */
	iterator end() { return iterator(); }

	/**
	 * \brief Print tree to STDOUT by levels
	 */
	void printLevels();

protected:
	void printLevel(Node<T> * node, int level);

private:
	Node<T> * _root;
	bool _levelFound;
};

template <typename T>
Tree<T> :: Tree() : _root(NULL), _levelFound(false) {

}

template <typename T>
Tree<T> :: ~Tree() {
	if (_root) {
		clear(_root);
	}
}

template <typename T>
void Tree<T> :: clear(Tree<T> :: iterator root)
{
	while (root) {
		if (root->_children) {
			clear(root->_children);
		}

		delete &(root++);
	}
}

template <typename T>
void Tree<T> :: printLevel(Tree<T> :: Node<T> * node, int level)
{
	if (node) {
		if (level == 0) {
			_levelFound = true;
			std :: cout << node->_data << " ";
		}
		else {
			iterator it(node->_children);
			while (it) {
				printLevel(&(it++), level - 1);
			}
		}
	}

}

template <typename T>
void Tree<T> :: printLevels()
{
	int level = 0;
	_levelFound = true;

	while(_levelFound) {
		std :: cout << "level = " << level << " : ";
		_levelFound = false;
		printLevel(_root, level);
		std :: cout << std :: endl;
		level++;
	}
}

} /* namespace conq_tree */

#endif /* TREE_H_ */
