/**
 * \file    graph.h
 * \brief
 * \details
 * \author  conquistador
 */
#ifndef MAKE_ACYCLIC_GRAPH_GRAPH_H_
#define MAKE_ACYCLIC_GRAPH_GRAPH_H_

#include <vector>
#include <string>
#include <list>
#include <vector>

class Graph : public std :: vector<std :: vector<bool> >
{
	typedef std :: vector<std :: vector<bool> > _Self;

	struct Vertex {
		enum Color { WHITE, GREY, BLACK };
		Vertex() : _color(WHITE)
		{}

		void clear()
		{
			_color = WHITE;
		}

		Color _color;
	};

public:
	/**
	 * \brief Default constructor
	 */
	Graph();

	/**
	 * \brief Constructor creates graph size
	 */
	Graph(std :: size_t vertexSz);

	/**
	 * \brief Copy-constructor
	 */
	Graph(const Graph &rhs);

	/**
	 * \brief Destructor
	 */
	virtual ~Graph();

	/**
	 * \brief Operator =, assign only graph matrix
	 */
	Graph &operator=(const Graph &rhs);

	/**
	 * \brief Add edge or change bidirectional
	 */
	void addEdge(std :: size_t from, std :: size_t to, bool bidirectional = false);

	/**
	 * \brief Del edge
	 */
	void delEdge(std :: size_t from, std :: size_t to, bool bidirectional = false);

	/**
	 * \brief Create new graph with vertexSz
	 */
	void newGraph(std :: size_t vertexSz);

	/**
	 * \brief Print graph to graphviz format
	 */
	bool print(const std :: string &filename);

	/**
	 * \brief Print matrix (debug)
	 */
	void print();

	/**
	 * \brief Check bidirectional or not
	 */
	bool isBidirectionalEdge(std :: size_t from, std :: size_t to);

	/**
	 * \brief Find cycle
	 */
	bool findCycle(std :: list<std :: size_t> &cycle);

	/**
	 * \brief Make graph acyclic
	 */
	bool solve(Graph &acyclic);

protected:
	/**
	 * \brief  Depth-first search
	 * \return TRUE - success, FALSE - cycle
	 */
	bool dfs(std :: size_t v, std :: list<std :: size_t> &track);

	/**
	 * \brief Clear all vertex descriptor
	 */
	void clearVertexDesc()
	{
		for (std :: size_t i = 0; i < _vertex.size(); ++i)
			_vertex[i].clear();
	}

	/**
	 * \brief   Find cycle with context save
	 * \details 1. Don't clear cycle list, just return start of cycle
	 *          2. Don't clear _vertex, just tail of fixed cycle
	 * \note    Optimization
	 */
	// std :: size_t __findCycle(size_t &v)

private:
	vector<Vertex> _vertex; //< description
};

#endif /* MAKE_ACYCLIC_GRAPH_GRAPH_H_ */
