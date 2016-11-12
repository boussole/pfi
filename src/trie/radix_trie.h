/**
 * \file    radix_trie.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef RADIX_TRIE_H_
#define RADIX_TRIE_H_

#include <common/common.h>
#include "trie.h"

namespace conq_trie {

template <typename V>
class RadixTrie : public Trie<std :: string, V, conq_trie :: StringTrieKey> {
	typedef typename Trie<std :: string, V, conq_trie :: StringTrieKey> :: Unit Unit;
	typedef typename Trie<std :: string, V, conq_trie :: StringTrieKey> :: child child;
public:
	RadixTrie() {}
	~RadixTrie() {}

	/**********************************
	 * \brief Insert new or update node
	 **********************************/
	void insert(const std :: string & key, const V & value);

	/**********************************
	 * \brief Lookup value by key
	 **********************************/
	bool lookup(const std :: string & key, V & value);

	/**********************************
	 * \brief Delete node by key
	 **********************************/
	bool remove(const std :: string & key);

private:
	/************************************
	 * \brief Split unit for two keys
	 ************************************/
	inline void split(Unit * u, std :: size_t splitPos)
	{
		// move children
		std :: list<Unit> children(std :: move(u->_children));
		// add new unit
		Unit * sub_u = u->addChild(u->_key.substr(splitPos, u->_key.length() - splitPos));
		// change parent of children
		for_each(children.begin(), children.end(), [&](Unit & u) { u._parent = sub_u; });
		// set children to new unit
		sub_u->_children = std :: move(children);
		// split key
		u->_key.resize(splitPos);
		// move value to new unit if it needs
		if (u->_isValue) {
			u->_isValue = false;
			sub_u->_isValue = true;
			sub_u->_value = std :: move(u->_value);
		}
	}

	/************************************
	 * \brief Find node by key
	 **************************************/
	Unit * lookup(const std :: string & key)
	{
		std :: size_t pos = 0;
		Unit * curr = &this->_root;

		while (curr) {
			Unit * ch = nullptr;
			for (child it = curr->_children.begin(); it != curr->_children.end(); ++it) {
				std :: size_t i = 0;
				for (; pos < key.length() && i < it->_key.length() && it->_key[i] == key[pos]; ++pos, ++i);
				// matches have been found
				if (i > 0) {
					// incomplete match
					if (i < it->_key.length())
						return nullptr;
					else if (pos == key.length() && it->_isValue) {
						it->_it = it;
						return &*it;
					}

					ch = &*it;
					ch->_it = it;
					break;
				}
			}

			curr = ch;
		}

		return nullptr;
	}
};

/**********************************
 * \brief Insert new or update node
 **********************************/
template <typename V>
void RadixTrie<V> :: insert(const std :: string & key, const V & value)
{
	std :: size_t pos = 0;
	Unit * curr = &this->_root;
	bool stop = false;

	while (!stop) {
		Unit * ch = nullptr;
		for (child it = curr->_children.begin(); it != curr->_children.end(); it++) {
			std :: size_t i = 0;
			for (; ((pos < key.length()) && (i < it->_key.length()) && (key[pos] == it->_key[i])); ++pos, ++i);
			// child found
			if (i > 0) {
				ch = &*it;
				// split child key - stop search
				if (i < it->_key.length()) {
					split(ch, i);
					// new branch
					if (pos < key.length())
						ch = it->addChild(key.substr(pos, key.length() - pos), value);
					stop = true;
				}

				// stop search in case of in result position
				if (pos == key.length()) {
					ch->_isValue = true;
					ch->_value = value;
					stop = true;
				}

				curr = ch;
				break;
			}
		}

		if (!ch) {
			curr->addChild(key.substr(pos, key.length() - pos), value);
			stop = true;
		}
	}
}

/**********************************
 * \brief Lookup value by key
 **********************************/
template <typename V>
bool RadixTrie<V> :: lookup(const std :: string & key, V & value)
{
	Unit * u = lookup(key);

	if (u) {
		value = u->_value;
		return true;
	}

	std :: cerr << __PRETTY_FUNCTION__ << ": key \"" << key << "\" not found\n";

	return false;
}

/**********************************
 * \brief Delete node by key
 **********************************/
template <typename V>
bool RadixTrie<V> :: remove(const std :: string & key)
{
	Unit * u = lookup(key);

	if (!u) {
		std :: cerr << __PRETTY_FUNCTION__ << ": key \"" << key << "\" not found\n";
		return false;
	}

	u->_isValue = false;
	//u->_value.clear();

	// delete leaf
	if (u->_children.empty()) {
		Unit * del = u;
		u = u->_parent;
		u->_children.erase(del->_it);
	}

	// compress down single leaf
	if (u) {
		while ((u != &this->_root) && (u->_children.size() == 1) && (!u->_isValue)) {
			u->_key += u->_children.front()._key;
			u->_isValue = u->_children.front()._isValue;
			u->_value = std :: move(u->_children.front()._value);
			std :: list<Unit> children = std :: move(u->_children.front()._children);
			std :: for_each(children.begin(), children.end(), [&](Unit & ch) { ch._parent = u; });
			u->_children = std :: move(children);
		}
	}

	return true;
}

} /* namespace conq_trie */

#endif /* RADIX_TRIE_H_ */
