/**
 * \file    graph.cpp
 * \brief
 * \details
 * \author  conquistador
 */

#include "graph.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <functional>

using namespace std;

/**
 * \brief Default constructor
 */
Graph :: Graph()
{

}

/**
 * \brief Constructor creates graph size
 */
Graph :: Graph(size_t vertexSz)
{
	newGraph(vertexSz);
}

/**
 * \brief Copy-constructor
 */
Graph :: Graph(const Graph &rhs)
{
	if (this != &rhs) {
		_Self :: clear();
		*this = rhs;
	}
}

/**
 * \brief Destructor
 */
Graph :: ~Graph()
{

}

/**
 * \brief Operator =, assign only graph matrix
 */
Graph & Graph :: operator=(const Graph &rhs)
{
	if (&rhs == this)
		return *this;

	_Self :: operator =(rhs);

	_vertex.clear();

	_vertex.resize(rhs._vertex.size());

	return *this;
}

/**
 * \brief Add edge or change bidirectional
 */
void Graph :: addEdge(size_t from, size_t to, bool bidirectional)
{
	assert(from < _Self :: size() && to < _Self :: size());

	assert(from != to);

	_Self :: operator[](from)[to] = true;

	if (bidirectional)
		_Self :: operator[](to)[from] = true;
	else
		_Self :: operator[](to)[from] = false;
}

/**
 * \brief Del edge
 */
void Graph :: delEdge(size_t from, size_t to, bool bidirectional)
{
	assert(from < _Self :: size() && to < _Self :: size());

	_Self :: operator[](from)[to] = false;

	if (bidirectional)
		_Self :: operator[](to)[from] = false;
}

/**
 * \brief Create new graph with vertexSz
 */
void Graph :: newGraph(size_t vertexSz)
{
	assert(vertexSz > 0);

	_Self :: clear();

	_Self :: resize(vertexSz);

	_vertex.clear();

	_vertex.resize(vertexSz);

	for (std :: size_t i = 0; i < vertexSz; ++i)
		_Self :: operator[](i).resize(vertexSz);
}

/**
 * \brief Print graph to graphviz format
 */
bool Graph :: print(const string &filename)
{
	remove(filename.c_str());

	ofstream out(filename.c_str());

	if (!out.is_open()) {
		cerr << __PRETTY_FUNCTION__ << ": can't open output file\n";
		return false;
	}

	out << "digraph g {" << endl;

	// print vertex
	for (size_t i = 0; i < _Self :: size(); ++i) {
		out << i << ";" << endl;
		for (size_t j = 0; j < _Self :: size(); ++j) {
			if (_Self :: operator[](i)[j]) {
				if (isBidirectionalEdge(i, j)) {
					if (i < j)
						out << "edge [dir=none]" << endl <<  i << " -> " << j << endl;
				}
				else
					out << "edge [dir=forward]" << endl << i << " -> " << j << endl;
			}
		}
	}

	out << "}" << endl;

	return true;
}

/**
 * \brief Check bidirectional or not
 */
bool Graph :: isBidirectionalEdge(std :: size_t from, std :: size_t to)
{
	assert(from < _Self :: size() && to < _Self :: size());

	return _Self :: operator[](from)[to] && _Self :: operator[](to)[from];
}

/**
 * \brief Depth-first search
 */
bool Graph :: dfs(size_t v, list<size_t> &track)
{
	if (_vertex[v]._color == Vertex :: BLACK)
		return true;
	else if (_vertex[v]._color == Vertex :: GREY) {
		track.push_back(v);
		return false;
	}

#if 0
	size_t prev = track.back();
#endif

	track.push_back(v);

	_vertex[v]._color = Vertex :: GREY;

	// at first of all go to not Birirectional
	for (std :: size_t j = 0; j < _Self :: size() * 2; ++j) {
		size_t real_j = j % _Self :: size();
		if (_Self :: operator[](v)[real_j]) {
			// first pass
			if (real_j == j && isBidirectionalEdge(v, real_j))
				continue;
#if 0
			if (isBidirectionalEdge(v, real_j) && (real_j == prev))
				continue;
#endif
			if (!dfs(real_j, track))
				return false;
		}
	}

	track.pop_back();

	_vertex[v]._color = Vertex :: BLACK;

	return true;
}

/**
 * \brief Find cycle
 */
bool Graph :: findCycle(std :: list<std :: size_t> &cycle)
{
	size_t v = 0;

	clearVertexDesc();

	while (v < _Self :: size()) {
		if (!dfs(v, cycle)) {
			for (std :: size_t i = 0; i < cycle.size(); ++i) {
				if (cycle.front() == cycle.back())
					return true;
				cycle.pop_front();
			}
		}

		cycle.clear();

		++v;
	}

	return false;
}

/**
 * \brief Make graph acyclic
 * \todo  Optimize it, no need to search cycle at start vertex
 *        we can use last vertex before fixed cycle
 */
bool Graph :: solve(Graph &acyclic)
{
	acyclic = *this;

	list<size_t> cycle;
	while (acyclic.findCycle(cycle)) {
		list<size_t> :: iterator b = cycle.begin();
		list<size_t> :: iterator e = b;
		++e;

		while (e != cycle.end()) {
			if (acyclic.isBidirectionalEdge(*b, *e)) {
				acyclic.addEdge(*e, *b);
				break;
			}
			++b;
			++e;
		}

		if (e == cycle.end()) {
			acyclic.clear();
			return false;
		}

		cycle.clear();
	}

	return true;
}

/**
 * \brief Print matrix (debug)
 */
void Graph :: print()
{
	cout << "graph:\n";
	for (size_t i = 0; i < _Self :: size(); ++i) {
		for (size_t j = 0; j < _Self :: size(); ++j) {
			cout << " " << _Self :: operator[](i)[j];
		}
		cout << endl;
	}
}
