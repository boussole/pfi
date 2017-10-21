/**
 * \file    trie.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef TRIE_H_
#define TRIE_H_

#include <common/common.h>

namespace conq_trie {

template <typename T>
class StringTrieKey {
public:
	typedef std :: basic_string<T> type;

	/************************************
	 * \brief Access to subkey
	 ************************************/
	static const T piece(const std :: basic_string<T> & key, std :: size_t i) {
		return key[i];
	}

	/************************************
	 * \brief Length of all subkeys
	 ************************************/
	static size_t length(const std :: basic_string<T> & key) {
		return key.length();
	}
};

template <typename T>
class ByteTrieKey {
public:
	typedef T type;

	/************************************
	 * \brief Access to subkey
	 ************************************/
	static const T piece(const T & key, std :: size_t i) {
		BOOST_ASSERT(i < sizeof(T));
		int offset = (sizeof(T) - i - 1) * 8;
		T mask = 0xFF << offset;
		return (key & mask)/* >> offset*/;
	}

	/************************************
	 * \brief Length of all subkeys
	 ************************************/
	static size_t length(const T & key) {
		return sizeof(T);
	}
};

/**
 * \class Trie
 * \brief Trie simple implementation
 * \tparam T Subkey type
 * \tparam V Value type
 * \tparam
 */
template <typename T, typename V, template <typename> class KeyTraits>
class Trie {
public:
	struct Unit {
		Unit() :
		    _key(T()),
		    _value(V()),
		    _isValue(false),
		    _parent(nullptr)  {}

		Unit(const T & k) :
		    _key(k),
		    _value(V()),
		    _isValue(false),
		    _parent(nullptr) {}

		Unit(const T & k, const V & value) :
		    _key(k),
		    _value(value),
		    _isValue(true),
		    _parent(nullptr) {}

		Unit * addChild(const T & key)
		{
			_children.push_back(key);
			_children.back()._parent = this;
			return &_children.back();
		}

		Unit * addChild(const T & key, const V & value)
		{
			_children.push_back(Unit(key, value));
			_children.back()._parent = this;
			return &_children.back();
		}

		T _key;
		V _value;
		bool _isValue;
		Unit * _parent;
		std :: list<Unit> _children;
		typename std :: list<Unit> :: iterator _it;
	};

	typedef typename std :: list<Unit> :: iterator child;

	Trie() {}

	~Trie() {}

	/************************************
	 * \brief Insert new node to trie
	 ************************************/
	bool insert(const typename KeyTraits<T> :: type & key, const V & value);

	/************************************
	 * \brief Lookup value by key
	 ************************************/
	bool lookup(const typename KeyTraits<T> :: type & key, V & value);

	/************************************
	 * \brief Delete node from trie by key
	 ************************************/
	bool remove(const typename KeyTraits<T> :: type & key);

	/************************************
	 * \brief Print trie (for debug)
	 ************************************/
	void print() const
	{
		 std :: function <void(Unit * const, std :: size_t)> fn = [&](Unit * const u, std :: size_t l) {
			std :: cout << "level = " << l << ": ";

			for (std :: size_t indent = 0; indent < l; ++indent)
				std :: cout << " -> ";

			std :: cout << " \"" << u->_key << "\" (";
			if (u->_isValue)
				std :: cout << u->_value;
			else
				std :: cout << "empty (children = " << u->_children.size() << ")";
			std :: cout << ")" << std :: endl;

			BOOST_ASSERT((l == 0) || u->_isValue || u->_children.size());

			for (child it = u->_children.begin(); it != u->_children.end(); ++it)
				fn(&*it, l + 1);
		 };

		 std :: size_t l = 0;

		 std :: cout << __PRETTY_FUNCTION__ << std :: endl;
		 fn(const_cast<Unit * const>(&this->_root), l);
	}

protected:
	Unit _root;

private:
	/************************************
	 * \brief Find node by key
	 **************************************/
	Unit * lookup(const typename KeyTraits<T> :: type & key);
};

/************************************
 * \brief Insert new node to trie
 ************************************/
template <typename T, typename V, template <typename> class KeyTraits>
bool Trie<T, V, KeyTraits> :: insert(const typename KeyTraits<T> :: type & key, const V & value)
{
	Unit * curr = &_root;
	for (size_t level = 0; level < KeyTraits<T> :: length(key); ++level) {
		T subkey = KeyTraits<T> :: piece(key, level);
		bool found = false;
		for (child it = curr->_children.begin(); it != curr->_children.end(); ++it) {
			if (it->_key == subkey) {
				curr = &*it;
				found = true;
				break;
			}
		}
		// create tail
		if (!found) {
			do {
				curr = curr->addChild(KeyTraits<T> :: piece(key, level));
			} while (++level < KeyTraits<T> :: length(key));
			break;
		}
	}

	if (!curr->_isValue) {
		curr->_isValue = true;
		curr->_value = value;
		return true;
	}

	// debug only
	std :: cerr << __PRETTY_FUNCTION__ << ": fail insert key = \"" << key << "\" (already exists)\n";

	return false;
}

/************************************
 * \brief Lookup value by key
 ************************************/
template <typename T, typename V, template <typename> class KeyTraits>
bool Trie<T, V, KeyTraits> :: lookup(const typename KeyTraits<T> :: type & key, V & value)
{
	Unit * u = lookup(key);

	if (u) {
		value = u->_value;
		return true;
	}

	// debug
	std :: cerr << __PRETTY_FUNCTION__ << ": key \"" << key << "\" not found\n";

	return false;
}

/************************************
 * \brief Delete node from trie by key
 ************************************/
template <typename T, typename V, template <typename> class KeyTraits>
bool Trie<T, V, KeyTraits> :: remove(const typename KeyTraits<T> :: type & key)
{
	Unit * u = lookup(key);
	if (u) {
		u->_isValue = false;
		while ((u != &_root) && (u->_children.empty()) && (!u->_isValue)) {
			Unit * del = u;
			u = u->_parent;
			u->_children.erase(del->_it);
		};
		
		return true;
	}

    // debug only
	std :: cerr << __PRETTY_FUNCTION__ << ": fail remove key = \"" << key << "\" (doesn't exist)\n";

	return false;
}

/************************************
 * \brief Find node by key
 ***************************************/
template <typename T, typename V, template <typename> class KeyTraits>
typename Trie<T, V, KeyTraits> :: Unit * Trie<T, V, KeyTraits> :: lookup(const typename KeyTraits<T> :: type & key)
{
    // check root
    if ((_root._isValue) && (key == typename KeyTraits<T> :: type()))
        return &_root;

    Unit * curr = &_root;
    for (std :: size_t level = 0; level < KeyTraits<T> :: length(key); ++level) {
        T subkey = KeyTraits<T> :: piece(key, level);
        Unit * ch = nullptr;
        for (child it = curr->_children.begin(); it != curr->_children.end(); ++it) {
            if (it->_key == subkey) {
                curr = ch = &*it;
                curr->_it = it;
                break;
            }
        }
        if (!ch)
            return nullptr;
    }

    if (curr->_isValue)
		return curr;

	return nullptr;
}

} /* namespace conq_trie */

#endif /* TRIE_H_ */
