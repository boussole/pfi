/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */


#include "graph.h"

using namespace std;
using namespace conq_graph;

#define IMPL VertexListImpl
//#define IMPL MatrixImpl

TICKET_FN(269)
{
	cout << "#" << ticket << ": graph implementation\n";

	Graph<int, IMPL> g(false);

	g.addVertex(0);
	g.addVertex(1);
	g.addEdge(0, 1, 10);
	g.addVertex(2);
	g.addEdge(1, 2, 20);
	g.addEdge(0, 2, 30);
	g.addEdge(2, 0, 40);
	g.addEdge(2, 2, 50);
	g.addEdge(2, 2, 60);
	g.printToFile("/tmp/test");
	g.delEdge(0, 2);

	cout << "++ from 0\n";
	for (Graph<int, IMPL> :: vertex_iterator v = g.begin();
	     v != g.end();
	     ++v)
	{
		cout << "v = " << v->_val << endl;

		for (Graph<int, IMPL> :: edge_iterator e = v.begin();
			     e != v.end();
			     e++)
		{
			cout << "\te = " << e->_weight << " neigh = " << v.neigh(e)->_val << endl;
		}
	}

	cout << "invalid vertex\n";
	for (Graph<int, IMPL> :: vertex_iterator v = g.begin(6);
	     v != g.end();
	     ++v)
	{
		cout << "v = " << v->_val << endl;
	}

	cout << "++ from last vertex\n";
	for (Graph<int, IMPL> :: vertex_iterator v = g.begin(2);
	    v != g.end();
	    ++v)
	{
		cout << "v = " << v->_val << endl;
	}

	cout << "-- from middle vertex\n";
	for (Graph<int, IMPL> :: vertex_iterator v = g.begin(1);
	     v != g.end();
	     --v)
	{
		cout << "v = " << v->_val << endl;
	}

	g.delEdge(0, 2);
	g.printToFile("/tmp/test1");
}

TICKET_FN(289)
{
	cout << "#" << ticket << ": breadth-first search\n";

	Graph<char, IMPL> g(false);
	g.addVertex('v');
	g.addVertex('r');
	g.addVertex('s');
	g.addVertex('w');
	g.addVertex('t');
	g.addVertex('x');
	g.addVertex('u');
	g.addVertex('y');
	g.addVertex('z');

	g.addEdge('v', 'r', 0);
	g.addEdge('r', 's', 0);
	g.addEdge('s', 'w', 0);
	g.addEdge('w', 't', 0);
	g.addEdge('w', 'x', 0);
	g.addEdge('t', 'u', 0);
	g.addEdge('x', 't', 0);
	g.addEdge('x', 'u', 0);
	g.addEdge('x', 'y', 0);
	g.addEdge('u', 'y', 0);

	g.printToFile("/tmp/289");

	g.bfs_traversal([](__details :: _Vertex_base<char> & v, bool new_component)->bool {
		string str;
		str += v._val;
		cout << "value = " << str << " color = " << (int)v._color << " d = " << v._d << endl;
		return true;
	});
}

TICKET_FN(290)
{
	cout << "#" << ticket << ": depth-first search\n";

	Graph<char, IMPL> g(true);

	g.addVertex('u');
	g.addVertex('v');
	g.addVertex('w');
	g.addVertex('x');
	g.addVertex('y');
	g.addVertex('z');

	g.addEdge('u', 'v');
	g.addEdge('u', 'x');
	g.addEdge('x', 'v');
	g.addEdge('v', 'y');
	g.addEdge('y', 'x');
	g.addEdge('w', 'y');
	g.addEdge('w', 'z');
	g.addEdge('z', 'z');

	g.printToFile("/tmp/290");

	g.dfs_traversal(nullptr, nullptr, [](__details :: _Vertex_base<char> & v)->bool {
		string str;
		str += v._val;
		cout << "value = " << str << " color = " << (int)v._color << " time = " << v._d << "/"  << v._f << endl;
		return true;
	});
}

TICKET_FN(292)
{
	cout << "#" << ticket << ": topological sort\n";

	Graph<std :: string, IMPL> g(true);

	g.addVertex("Трусы");
	g.addVertex("Носки");
	g.addVertex("Часы");
	g.addVertex("Брюки");
	g.addVertex("Туфли");
	g.addVertex("Рубашка");
	g.addVertex("Ремень");
	g.addVertex("Галстук");
	g.addVertex("Пиджак");

	g.addEdge("Трусы", "Туфли");
	g.addEdge("Трусы", "Брюки");
	g.addEdge("Носки", "Туфли");
	g.addEdge("Брюки", "Туфли");
	g.addEdge("Брюки", "Ремень");
	g.addEdge("Рубашка", "Ремень");
	g.addEdge("Рубашка", "Галстук");
	g.addEdge("Ремень", "Пиджак");
	g.addEdge("Галстук", "Пиджак");

	g.printToFile("/tmp/292");

	cout << "topology order:\n";
	g.topological_sort([](__details :: _Vertex_base<string> & v)->bool {
		cout << v._val << " ("<< v._d << "/"  << v._f << ")\n";
		return true;
	});
}

TICKET_FN(295)
{
	cout << "#" << ticket << ": prim mst\n";

	Graph<char, IMPL> g(false);

	g.addVertex('A');
	g.addVertex('B');
	g.addVertex('C');
	g.addVertex('D');
	g.addVertex('E');
	g.addVertex('F');
	g.addVertex('G');

	g.addEdge('A', 'B', 7);
	g.addEdge('A', 'D', 5);
	g.addEdge('B', 'C', 8);
	g.addEdge('B', 'D', 9);
	g.addEdge('B', 'E', 7);
	g.addEdge('C', 'E', 5);
	g.addEdge('D', 'E', 15);
	g.addEdge('D', 'F', 6);
	g.addEdge('E', 'F', 8);
	g.addEdge('E', 'G', 9);
	g.addEdge('F', 'G', 11);

	g.printToFile("/tmp/295");

	Graph<char, IMPL> mst(false);
	int w = g.prim_mst(mst);
	assert(w > 0);
	cout << "weight(mst) = " << w << endl;
	mst.printToFile("/tmp/295_res");

}

TICKET_FN(296)
{
	cout << "#" << ticket << ": kruskal mst\n";

	Graph<char, IMPL> g(false);

	g.addVertex('a');
	g.addVertex('b');
	g.addVertex('c');
	g.addVertex('d');
	g.addVertex('e');
	g.addVertex('f');
	g.addVertex('g');
	g.addVertex('h');
	g.addVertex('i');

	g.addEdge('a', 'b', 4);
	g.addEdge('b', 'c', 8);
	g.addEdge('c', 'd', 7);
	g.addEdge('d', 'e', 9);
	g.addEdge('e', 'f', 10);
	g.addEdge('f', 'g', 2);
	g.addEdge('g', 'h', 1);
	g.addEdge('h', 'a', 8);
	g.addEdge('b', 'h', 11);
	g.addEdge('h', 'i', 7);
	g.addEdge('i', 'c', 2);
	g.addEdge('i', 'g', 6);
	g.addEdge('c', 'f', 4);
	g.addEdge('d', 'f', 14);

	g.printToFile("/tmp/296");

	Graph<char, IMPL> mst(false);

	int w = g.kruskal_mst(mst);

	cout << "mst weight = " << w << endl;

	mst.printToFile("/tmp/296_res");
}

TICKET_FN(297)
{
	cout << "#" << ticket << ": graph weak components\n";

	Graph<char, IMPL> g(false);

	g.addVertex('A');
	g.addVertex('B');
	g.addVertex('C');
	g.addVertex('D');
	g.addVertex('E');
	g.addVertex('F');
	g.addVertex('G');

	g.addEdge('A', 'B');
	g.addEdge('B', 'C');
	g.addEdge('C', 'D');
	g.addEdge('F', 'G');

	g.printToFile("/tmp/297");

	int last_id = -1;
	g.weak_components([&](__details :: _Vertex_base<char> & v, int id)->bool {
			if (last_id != id) {
				cout << "\nnew component = " << id << ":";
				last_id = id;
			}
			cout << " " << v._val;
			return true;
		}
	);
	cout << "\n";
}

TICKET_FN(298)
{
	cout << "#" << ticket << ": strong components\n";

	Graph<char, IMPL> g(true);
	g.addVertex('a');
	g.addVertex('b');
	g.addVertex('c');
	g.addVertex('d');
	g.addVertex('e');
	g.addVertex('f');
	g.addVertex('g');
	g.addVertex('h');

	g.addEdge('a', 'b');
	g.addEdge('b', 'f');
	g.addEdge('b', 'e');
	g.addEdge('b', 'c');
	g.addEdge('e', 'a');
	g.addEdge('e', 'f');
	g.addEdge('f', 'g');
	g.addEdge('g', 'f');
	g.addEdge('c', 'g');
	g.addEdge('c', 'd');
	g.addEdge('d', 'c');
	g.addEdge('d', 'h');
	g.addEdge('h', 'd');
	g.addEdge('h', 'g');

	g.printToFile("/tmp/298");
	int last_id = -1;
	g.strong_components([&](__details :: _Vertex_base<char> & v, int id)->bool {
			if (last_id != id) {
				cout << "\nnew component = " << id << ":";
				last_id = id;
			}
			cout << " " << v._val;
			return true;
		}
	);
	cout << "\n";
}

TICKET_FN(299)
{
	cout << "#" << ticket << ": Dijkstra's algorithm\n";

	Graph<int, IMPL> g(false);

	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addVertex(5);
	g.addVertex(6);

	g.addEdge(1, 2, 7);
	g.addEdge(1, 3, 9);
	g.addEdge(1, 6, 14);
	g.addEdge(2, 3, 10);
	g.addEdge(2, 4, 15);
	g.addEdge(3, 6, 2);
	g.addEdge(3, 4, 11);
	g.addEdge(6, 5, 9);
	g.addEdge(5, 4, 6);

	g.printToFile("/tmp/299");

	std :: list<int> res;

	int path = g.short_path_dijkstra(1, 5, res);

	assert(path >= 0);

	cout << "path [ 1 -> 5 ] = " << path << ":";

	for (auto i : res) {
		cout << " -> " << i;
	}

	std :: cout << std :: endl;
}

int main(int argc, char *argv[])
{
	cout << "uncomment one of a ticket_* function\n";

//	ticket_299(argc, argv);

//	ticket_298(argc, argv);

//	ticket_297(argc, argv);

//	ticket_296(argc, argv);

//	ticket_295(argc, argv);

//	ticket_292(argc, argv);

//	ticket_290(argc, argv);

//	ticket_289(argc, argv);

//	ticket_269(argc, argv);

	return 0;
}
