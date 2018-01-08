/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  conquistador
 */

#include "graph.h"

#include <iostream>

using namespace std;

void __test(Graph &g, const char *id)
{
	std :: list<size_t> cycle;

	if (g.findCycle(cycle)) {
		cout << id << ": cycle:";
		for (list<size_t> :: iterator it = cycle.begin(); it != cycle.end(); ++it)
			cout << " " << *it;
		cout << std :: endl;
	}
	else
		cout << id << ": cycle not found\n";

	g.print(string("/tmp/") + id + ".dot");

	Graph acyclic;
	if (g.solve(acyclic)) {
		acyclic.print(string("/tmp/") + id + "_solved.dot");
	}
	else
		cout << id << ": impossible remove cycles\n";
}

int main()
{
	Graph g(5);
	g.addEdge(0, 1, true);
	g.addEdge(1, 2, true);
	g.addEdge(3, 0);
	g.addEdge(3, 4, true);
	g.addEdge(2, 4);
	__test(g, "1");

	//---------------------
	g.clear();
	g.newGraph(5);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(3, 0);
	g.addEdge(4, 3, true);
	g.addEdge(2, 4);
	__test(g, "2");

	//---------------------
	g.clear();
	g.newGraph(4);
	g.addEdge(0, 1, true);
	g.addEdge(0, 2, true);
	g.addEdge(0, 3, true);
	g.addEdge(1, 2, true);
	g.addEdge(1, 3, true);
	g.addEdge(2, 3, true);
	__test(g, "3");

	//---------------------
	g.clear();
	g.newGraph(7);
	g.addEdge(0, 1);
	g.addEdge(2, 1);
	g.addEdge(1, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 5);
	g.addEdge(5, 2);
	g.addEdge(6, 0);
	g.addEdge(2, 3);
	g.addEdge(1, 6);
	__test(g, "4");

	//---------------------
	g.clear();
	g.newGraph(7);
	g.addEdge(0, 1);
	g.addEdge(2, 1);
	g.addEdge(1, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 5, true);
	g.addEdge(5, 2);
	g.addEdge(6, 0);
	g.addEdge(2, 3);
	g.addEdge(1, 6, true);
	__test(g, "5");

	//----------------------
	g.newGraph(9);
	g.addEdge(0, 1, true);
	g.addEdge(2, 1, true);
	g.addEdge(2, 3, true);
	g.addEdge(3, 8, true);
	g.addEdge(3, 6, true);
	g.addEdge(0, 7, true);
	g.addEdge(1, 7, true);
	g.addEdge(2, 7, true);
	g.addEdge(6, 7, true);
	g.addEdge(4, 6, true);
	g.addEdge(5, 4, true);
	__test(g, "6");

	//----------------------
	g.addEdge(1, 7);
	g.addEdge(2, 7);
	__test(g, "7");

	//----------------------
	g.newGraph(4);
	g.addEdge(0, 1);
	g.addEdge(1, 2, true);
	g.addEdge(3, 2);
	g.addEdge(3, 0);
	g.addEdge(1, 3);
	__test(g, "8");

	//-----------------------
	g.addEdge(0, 1, true);
	__test(g, "9");

	//------------------------
	g.newGraph(3);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(0, 2, true);
	__test(g, "10");

	return 0;
}

