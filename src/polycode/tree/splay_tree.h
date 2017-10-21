/**
 * \file    splay_tree.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

#include "bst.h"

namespace conq_tree {

template <typename T>
class SplayTree : public BST<T> {
	typedef typename BST<T> :: _Node    _Node;

	typedef typename BST<T> :: iterator iterator;
public:
	/****************************
	 * \brief Constructor
	 ****************************/
	SplayTree() {}

	/****************************
	 * \brief Destructor
	 ****************************/
	virtual ~SplayTree() {}

	/***********************************
	 * \brief Insert value
	 ***********************************/
	bool insert(const T & v);

	/*********************************
	 * \brief Delete value
	 *********************************/
	void remove(const T & v);

protected:
	/****************************
	 * \brief Up node to the root
	 ****************************/
	void splay(iterator & it);
};

/****************************
 * \brief Up node to the root
 ****************************/
template <typename T>
void SplayTree<T> :: splay(iterator & it)
{
	assert(it() != nullptr);

	// do it while we are not in the root
	while (it()->_p) {
		// zig case
		if (it()->_p->_p == nullptr) {
			/**
			 * left zig
			 *   p
			 *  /
			 * u
			 */
			if (it()->_p->_l == it())
				this->rightRotation(it()->_p);
			/**
			 * right zig
			 * p
			 *  \
			 *   u
			 */
			else
				this->leftRotation(it()->_p);
		}
		// right zig-zig or zig-zag
		else if (it()->_p->_l == it()) {
			if (it()->_p->_p->_l == it()->_p) {
				/**
				 * right zig-zig
				 *     g
				 *    / 1 action
				 *   p
				 *  / 2 action
				 * u
				 */
				this->rightRotation(iterator(it()->_p->_p));
				this->rightRotation(iterator(it()->_p));
			}
			else {
				assert(it()->_p->_p->_r == it()->_p);
				/**
				 * right zig-zag
				 * g
				 *  \ 2 action
				 *   p
				 *  / 1 action
				 * u
				 */
				this->rightRotation(iterator(it()->_p));
				this->leftRotation(iterator(it()->_p));
			}
		}
		// left zig-zig or zig-zag
		else {
			assert(it()->_p->_r == it());
			if (it()->_p->_p->_r == it()->_p) {
				/**
				 * left zig-zig
				 * g
				 *  \ 1 - action
				 *   p
				 *    \ 2 - action
				 *     u
				 */
				this->leftRotation(iterator(it()->_p->_p));
				this->leftRotation(iterator(it()->_p));
			}
			else {
				assert(it()->_p->_p->_l == it()->_p);
				/**
				 * left zig-zag
				 *     g
				 *    / 2 - action
				 *   p
				 *    \ 1 - action
				 *     u
				 */
				this->leftRotation(iterator(it()->_p));
				this->rightRotation(iterator(it()->_p));
			}
		}
	}
}

/***********************************
 * \brief Insert value
 ***********************************/
template <typename T>
bool SplayTree<T> :: insert(const T & v)
{
	_Node * n = new _Node(v);
	if (!n)
		return false;

	iterator p, it = BST<T> :: lookup(v, p);

	// we don't have value in tree
	if (it == this->end()) {
		// we have the empty tree
		if (p == this->end()) {
			BST<T> :: _root = n;
			return true;
		}
		it = p;
	}

	// move value or parent value to root
	splay(it);

	iterator l, r;

	// all tree is greater than v
	if (*it <= v) {
		l = it;
		r = it()->_r;
		it()->_r = nullptr;
	} else {
		l = it()->_l;
		r = it();
		it()->_l = nullptr;
	}

	if (l != this->end()) {
		n->_l = l();
		l()->_p = n;
	}

	if (r != this->end()) {
		n->_r = r();
		r()->_p = n;
	}

	this->_root = n;

	return true;
}

/*********************************
 * \brief Delete value
 *********************************/
template <typename T>
void SplayTree<T> :: remove(const T & v)
{
	iterator parent, it = this->lookup(v, parent);

	if (it == this->end())
		return;

	splay(it);

	// split tree
	iterator l = it()->_l, r = it()->_r;

	// delete node
	it()->detach();
	delete it();
	this->_root = nullptr;

	// left isn't empty
	if (l != this->end()) {
		l()->_p = nullptr;
		// right isn't empty
		if (r != this->end()) {
			// merge with max(l) in root
			for (; l()->_r; l = l()->_r);
			splay(l);
			this->_root = static_cast<_Node*>(l());
			l()->_r = r();
			r()->_p = l();
		}
		// right is empty
		else
			this->_root = static_cast<_Node*>(l());
	} else if (r != this->end()){
		r()->_p = nullptr;
		this->_root = static_cast<_Node*>(r());
	}
}

} /* namespace conq_tree */

#endif /* SPLAY_TREE_H_ */
