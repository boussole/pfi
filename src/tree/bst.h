/**
 * \file    bst.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef BST_H_
#define BST_H_

namespace conq_tree {

namespace details {

struct _Bin_tree_node_base {
	/*******************************
	 * \brief Default contsructor
	 *******************************/
	_Bin_tree_node_base() : _l(nullptr), _r(nullptr), _p(nullptr)
	{
	}

	/*******************************
	 * \brief Destructor deletes children
	 *******************************/
	~_Bin_tree_node_base()
	{//	std :: cout << __PRETTY_FUNCTION__ << ": delete = " << _v << std :: endl;
		if (_l)
			delete _l;
		if (_r)
			delete _r;
	}

	/*******************************
	 * \brief Detach children
	 *******************************/
	void detach()
	{
		_r = _l = nullptr;
	}

	/*******************************
	 * \brief Change child
	 *******************************/
	void changeChild(_Bin_tree_node_base * o, _Bin_tree_node_base * n)
	{
		if (o == _l)
			_l = n;
		else
			_r = n;

		if (n)
			n->_p = this;
	}

	_Bin_tree_node_base * _l, * _r, * _p; /**< left, right children, parent (used to simplify algorithm) */
};

template <typename T>
struct _Bin_tree_node : public _Bin_tree_node_base {
	/*******************************
	 * \brief Constructor
	 *******************************/
	_Bin_tree_node()
	{
	}

	/*******************************
	 * \brief Initial constructor
	 *******************************/
	_Bin_tree_node(const T & v) : _Bin_tree_node_base(), _v(v)
	{
	}

	T _v;
};

/***********************************
 * \class iterator
 * \brief External access to nodes
 ***********************************/
template <typename T>
struct _Bin_tree_iterator
{
	typedef _Bin_tree_node<T>                  _Node;
	typedef _Bin_tree_iterator<T>              _Self;

	typedef T*                                 pointer;
	typedef T&                                 reference;

	_Bin_tree_iterator() :
	_node(nullptr) { }

	_Bin_tree_iterator(_Bin_tree_node_base * node) :
	_node (node) { }

	reference
	operator*()
	{ return static_cast<_Node *>(_node)->_v; }

	pointer
	operator->()
	{ return std::__addressof(static_cast<_Node *>(_node)->_v); }

	bool
	operator==(const _Bin_tree_iterator & rhs)
	{ return _node == rhs._node; }

	bool
	operator!=(const _Bin_tree_iterator & rhs)
	{ return _node != rhs._node; }

	_Self &
	operator=(_Bin_tree_node_base * node)
	{
		_node = node;
		return *this;
	}

	_Bin_tree_node_base *
	operator()()
	{ return _node; }

	_Bin_tree_node_base * _node;
};

} /** namespace details */


/****************************************
 * \class BST bst.h tree/bst.h
 * \brief Implemantation of binary search tree
 ***************************************/
template <typename T>
class BST {
protected:
	typedef details :: _Bin_tree_node<T>            _Node;

public:
	typedef details :: _Bin_tree_iterator<T>        iterator;

	/***********************************
	 * \brief Constructor initial interntals
	 ***********************************/
	BST() : _root(nullptr)
	{
	}

	/***********************************
	 * \brief Destructor clear heap data
	 ***********************************/
	virtual ~BST()
	{
		clear();
	}

	/***********************************
	 * \brief Empty check
	 ***********************************/
	bool isEmpty() { return _root == nullptr; }

	/***********************************
	 * \brief Clear tree
	 ***********************************/
	void clear() { delete _root; _root = nullptr; }

	/***********************************
	 * \brief Iterator of first element of tree (root)
	 ***********************************/
	iterator
	begin()
	{ return iterator(_root); }

	/***********************************
	 * \brief Iterator of after last element of tree (invalid)
	 ***********************************/
	iterator
	end()
	{ return iterator(nullptr); }

	/***********************************
	 * \brief Insert value
	 ***********************************/
	virtual bool insert(const T & v);

	/***********************************
	 * \brief Min value
	 ***********************************/
	iterator min()
	{
		if (isEmpty())
			return end();

		_Node * min = nullptr;
		for (min = _root; min->_l != nullptr; min = static_cast<_Node*>(min->_l));

		return iterator(min);
	}

	/***********************************
	 * \brief Max value
	 ***********************************/
	iterator max()
	{
		if (isEmpty())
			return end();

		_Node * max = nullptr;
		for (max = _root; max->_r != nullptr; max = static_cast<_Node*>(max->_r));

		return iterator(max);
	}

	/***********************************
	 * \brief          Previous element
	 * \parar [in out] Current element -> Previous element
	 ***********************************/
	iterator predecessor(iterator & it)
	{
		if (it == end())
			return end();

		if (it._node->_l) {
			for (it = it._node->_l; it._node->_r != nullptr; it = it._node->_r);
			return it;
		}

		iterator pred;
		for (pred = it._node->_p; pred != end(); pred = it._node->_p) {
			if (pred._node->_r == it._node)
				break;
			it = pred;
		}

		return pred;
	}

	/***********************************
	 * \brief          Next element
	 * \param [in out] Current element -> Next element
	 ***********************************/
	iterator successor(iterator & it)
	{
		if (it == end())
			return end();

		if (it._node->_r) {
			for (it = it._node->_r; it._node->_l != nullptr; it = it._node->_l);
			return it;
		}

		iterator succ;
		for (succ = it._node->_p; succ != end(); succ = it._node->_p) {
			if (succ._node->_l == it._node)
				break;
			it = succ;
		}

		return succ;
	}

	/**********************************
	 * \brief  Lookup value
	 * \return Iterator with value or invalid
	 **********************************/
	iterator lookup(const T & v)
	{
		iterator p = end(), node = lookup(v, p);

		return iterator(node);
	}

	/**********************************
	 * \brief In-order traversal
	 **********************************/
	void inOrderTraversal(bool(*cb)(T & v))
	{
		std :: function<bool(_Node*)> in_order = [&](_Node * u) {
			if (u == nullptr)
				return true;

			if (in_order(static_cast<_Node*>(u->_l)) && cb(u->_v) && in_order(static_cast<_Node*>(u->_r)))
				return true;

			return false;
		};

		in_order(_root);
	}

	/***********************************
	 * \brief Pre-order traversal
	 ***********************************/
	void preOrderTraversal(bool(*cb)(T & v))
	{
		std :: function<bool(_Node*)> pre_order = [&](_Node * u) {
			if (u == nullptr)
				return true;

			if (cb(u->_v) && pre_order(static_cast<_Node*>(u->_l)) && pre_order(static_cast<_Node*>(u->_r)))
				return true;

			return false;
		};

		pre_order(_root);
	}

	/**********************************
	 * \brief Post-order traversal
	 **********************************/
	void postOrderTraversal(bool(*cb)(T & v))
	{
		std :: function<bool(_Node*)> post_order = [&](_Node * u) {
			if (u == nullptr)
				return true;

			if (post_order(static_cast<_Node*>(u->_l)) && post_order(static_cast<_Node*>(u->_r)) && cb(u->_v))
				return true;

			return false;
		};

		post_order(_root);
	}

	/*********************************
	 * \brief Delete value
	 *********************************/
	virtual void remove(const T & v);

	/*********************************
	 * \brief Debug print in graphviz format
	 *        with internal check
	 *********************************/
	void printToFile(const char * fileName)
	{
		std::remove(fileName);

		std :: ofstream o(fileName);
		if (o.fail()) {
			std :: cout << "file opening fail " << fileName << std :: endl;
			return;
		}

		if (!_root)
			return;

		assert(_root->_p == nullptr);
		int null_idx = 0;
		std :: function<void(_Node*)> print_level = [&](_Node * u) {
			o << (std :: uint64_t)u << "[label=" << u->_v << "];" << std :: endl;
			if (u->_l) {
				assert(u->_l->_p == u);
				o << std::dec << (std :: uint64_t)u << " -> " << std :: dec << (std :: uint64_t)u->_l << ";" << std :: endl;
				print_level(static_cast<_Node*>(u->_l));
			}
			else
				o << std :: dec << (std :: uint64_t)u << " -> " << "n" << null_idx++ << ";" << std :: endl;

			if (u->_r) {
				assert(u->_r->_p == u);
				o << std :: dec << (std :: uint64_t)u << " -> " << std :: dec << (std :: uint64_t)u->_r << ";" << std :: endl;
				print_level(static_cast<_Node*>(u->_r));
			}
			else
				o << std :: dec << (std :: uint64_t)u << " -> " << "n" << null_idx++ << ";" << std :: endl;
		};

		o << "digraph bst {" << std :: endl;
		print_level(_root);
		// null ptr nodes
		if (null_idx > 0) {
			int i = 0;
			for (i = 0; i < null_idx - 1; ++i) {
				o << "n" << i << ",";
			}

			o << "n" << i << " [label=\"NIL\", shape=record];" << std :: endl;
		}

		o << "}";
	}

	/*********************************
	 * \brief Left rotation
	 *********************************/
	void leftRotation(iterator it)
	{
		if ((it() == nullptr) || (it()->_r == nullptr))
			return;

		iterator pivot = it()->_r;

		it()->_r = pivot()->_l;
		if (pivot()->_l) {
			it()->_r->_p = it();
		}

		pivot()->_l = it();

		if (it()->_p == nullptr) {
			_root = static_cast<_Node*>(pivot());
			pivot()->_p = nullptr;
		}
		else
			it()->_p->changeChild(it(), pivot());

		it()->_p = pivot();
	}

	/*********************************
	 * \brief Right rotation
	 *********************************/
	void rightRotation(iterator it)
	{
		if ((it() == nullptr) || (it()->_l == nullptr))
			return;

		//_Node * node = it(), * pivot = static_cast<_Node*>(it()->_l);
		iterator pivot = it()->_l;

		it()->_l = pivot()->_r;
		if (pivot()->_r) {
			it()->_l->_p = it();
		}

		pivot()->_r = it();

		if (it()->_p == nullptr) {
			_root = static_cast<_Node*>(pivot());
			pivot()->_p = nullptr;
		}
		else
			it()->_p->changeChild(it(), pivot());

		it()->_p = pivot();
	}

	/*********************************
	 * \brief Lowest common ancestor,
	 *        the lowest node in T that has
	 *        both v and w as descendants
	 *********************************/
	iterator lca(iterator & v, iterator & w);

	/*********************************
	 * \brief Maximal node in each level
	 *********************************/
	 void maxInLevels(std :: vector<T> & vec)
	 {
		if (isEmpty())
			return;

		int max = -1;

	 	std :: function<void(_Node *, int, std :: vector<T> &)> traversal =
			[&](_Node * n, int l, std :: vector<T> & v)->void {
				if (l > max) {
					v.push_back(n->_v);
					++max;
				}

				if (n->_r)
					traversal(static_cast<_Node*>(n->_r), l + 1, v);
				if (n->_l)
					traversal(static_cast<_Node*>(n->_l), l + 1, v);
			};

		traversal(_root, 0, vec);
	 }

	 /*********************************
	  * \brief   Snake traversal
	  * \details Left to right first traversal
	  *********************************/
	 void snakeTraversal(bool(*cb)(const T & v))
	 {
		std :: stack<_Node *> left, right;

		if (_root && cb(_root->_v)) {
			right.push(_root);
		}

		while (!left.empty() || !right.empty()) {
			for (; !left.empty(); left.pop()) {
				if (left.top()->_l) {
					_Node * n = static_cast<_Node *>(left.top()->_l);
					if (!cb(n->_v)) return;
					right.push(n);
				}

				if (left.top()->_r) {
					_Node * n = static_cast<_Node *>(left.top()->_r);
					if (!cb(n->_v)) return;
					right.push(n);
				}
			}

			for (; !right.empty(); right.pop()) {
				if (right.top()->_r) {
					_Node * n = static_cast<_Node *>(right.top()->_r);
					if (!cb(n->_v)) return;
					left.push(n);
				}

				if (right.top()->_l) {
					_Node * n = static_cast<_Node *>(right.top()->_l);
					if (!cb(n->_v)) return;
					left.push(n);
				}
			}
		}
	 }

	 /********************************
	  * \brief In-order traversal (iterative)
	  ********************************/
	 void inOrderTraversalI(bool(*cb)(const T & v))
	 {
		 std :: stack<_Node *> s;

		 _Node * n = _root;

		 while (n) {
			 if (n->_l) {
				 s.push(n);
				 n = static_cast<_Node *>(n->_l);
			 }
			 else {
				 if (!cb(n->_v)) return;
				 n = static_cast<_Node *>(n->_r);
				 while (!s.empty() && !n) {
					if (!cb(s.top()->_v)) return;
					n = static_cast<_Node *>(s.top()->_r);
					s.pop();
				 }
			 }
		 }
	 }

protected:
	/*********************************
	 * \brief Lookup value (internal usage)
	 *********************************/
	iterator lookup(const T & v, iterator & parent)
	{
		iterator it = _root;
		parent = end();

		while (it() && (*it != v)) {
			parent = it;
			it = (*it < v) ? it()->_r : it()->_l;
		}

		return it;
	}

protected:
	_Node * _root; /**< root */
};

/***********************************
 * \brief   Insert value
 * \details No exception here
 * \return  true | false as result of insert
 ***********************************/
template <typename T>
bool BST<T> :: insert(const T & v)
{
	_Node * u = new _Node(v);
	if (!u)
		return false;

	if (isEmpty()) {
		_root = u;
		return true;
	}

	_Node * it = _root;
	while (true) {
		if (v <= it->_v) {
			if (!it->_l) {
				it->_l = u;
				break;
			} else
				it = static_cast<_Node*>(it->_l);
		} else {
			if (!it->_r) {
				it->_r = u;
				break;
			} else
				it = static_cast<_Node*>(it->_r);
		}
	}

	u->_p = it;

	return true;
}

/*********************************
 * \brief Delete value
 *********************************/
template <typename T>
void BST<T> :: remove(const T & v)
{
	//_Node * del = lookup(v)._node;
	iterator del = lookup(v);
	if (del == nullptr)
		return;

	auto no_children = [&](iterator & d) {
		if (d()->_p)
			d()->_p->changeChild(d(), nullptr);
		else
			_root = nullptr;
		d()->detach();
		delete d();
	};

	auto one_child = [&](iterator & d, iterator child) {
		if (d()->_p)
			d()->_p->changeChild(d(), child());
		else {
			_root = static_cast<_Node*>(child());
			child()->_p = nullptr;
		}
		d()->detach();
		delete d();
	};

	auto children = [&](iterator & d) {
		iterator s = successor(d);
		*d = std :: move(*s);
		if (s()->_r)
			one_child(s, s()->_r);
		else
			no_children(s);
	};

	if (del._node->_l == nullptr)
		if (del._node->_r == nullptr)
			no_children(del);
		else
			one_child(del, del()->_r);
	else
		if (del._node->_r == nullptr)
			one_child(del, del()->_l);
		else
			children(del);
}

/*********************************
 * \brief Lowest common ancestor,
 *        the lowest node in T that has
 *        both v and w as descendants
 *********************************/
template <typename T>
typename BST<T> :: iterator BST<T> :: lca(typename BST<T> :: iterator & v, typename BST<T> :: iterator & w)
{
	std :: cout << __PRETTY_FUNCTION__ << ": Naive algorithm is not implemented\n";
/*
 *  Naive algorithm
 *
 *	1. Find depth of v and w
 *	2. If depth(v) != depth(u) move up one of them until length not equal
 *  3. Both up until v != w
 */
	return BST<T> :: end();
}

/*********************************
 * \brief Lowest common ancestor,
 *        the lowest node in T that has
 *        both v and w as descendants
 * \note  This is comparative algorithm
 *        for int type, it has O(log(N))
 **********************************/
template <>
BST<int> :: iterator BST<int> :: lca(BST<int> :: iterator & v, BST<int> :: iterator & w)
{
	std :: cout << __PRETTY_FUNCTION__ << ": comparative algoritm, ONLY for int type\n";

	assert((v != BST<int> :: end()) && (w != BST<int> :: end()));

	BST<int> :: iterator n = BST<int> :: begin();

	while (n != BST<int> :: end()) {
		if ((n == v) || (n == w)) 
			return n;

		BST<int> :: iterator n1 = (*v <= *n) ? n()->_l : n()->_r;
		BST<int> :: iterator n2 = (*w <= *n) ? n()->_l : n()->_r;

		assert((n1 != BST<int> :: end()) && (n2 != BST<int> :: end()));

		if (n1 != n2)
			return n;

		n = n1;
	}

    return BST<int> :: end();
}

/*************************************
 * \brief Going through common elements
 * \todo  Change implemention after
 *        const_iterator adding
 *************************************/
template <typename T>
void bstCommon(BST<T> & b1, BST<T> & b2, void (*fn)(const T & v))
{
	BST<int> :: iterator i1 = b1.min();
	BST<int> :: iterator i2 = b2.min();

	while ((i1 != b1.end())  && (i2 != b2.end())) {
		if (*i1 == *i2) {
			fn(*i1);
			i1 = b1.successor(i1);
			i2 = b2.successor(i2);
		} else if (*i1 > *i2) {
			i2 = b2.successor(i2);
		} else {
			i1 = b1.successor(i1);
		}
	}
}

} /* namespace conq_tree */

#endif /* BST_H_ */
