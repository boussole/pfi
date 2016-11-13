/**
 * \file    graph.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <common/common.h>
#include <memory>
#include <map>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/tuple/tuple_comparison.hpp>

namespace conq_graph {

namespace __details {
	template <typename T>
	struct _Vertex_base
	{
		enum class Color { White, Grey, Black };

		_Vertex_base() : _color(Color :: White) {}

		_Vertex_base(const T & val) : _color(Color :: White), _val(val) {}

		virtual ~_Vertex_base() {}

		bool operator==(const _Vertex_base & rhs)
		{ return _val == rhs._val; }

		Color _color;
		T _val;
		int _d, _f, _componentId, _lowLink;
		bool _flag; // different goals
		struct _Vertex_base * _prev;
	};

	struct _Edge_base
	{
		_Edge_base(int w) : _weight(w) {}
		int _weight;
	};
}

/**
 * \class GraphImpl
 * \brief Graph representative interface
 */
template <typename T>
class GraphImpl
{
public:
	/**
	 * \brief Contructor
	 */
	GraphImpl(bool directed) : _directed(directed), _vertexQuantity(0) {}

	/**
	 * \brief Destructor
	 */
	virtual ~GraphImpl() {}

	/**
	 * \brief Add vertex
	 */
	virtual bool addVertex(const T & v) = 0;

	/**
	 * \brief Del vertex
	 */
	virtual bool delVertex(const T & v) = 0;

	/**
	 * \brief Add edge between two vertexes
	 */
	virtual bool addEdge(const T & from, const T & to, int weight = 0) = 0;

	/**
	 * \brief Del edge between two vertexes
	 */
	virtual bool delEdge(const T & from, const T & to) = 0;

	/**
	 * \brief Print to file using
	 */
	virtual void printToFile(const char * filename) = 0;

	/**
	 * \brief Vertex quantity
	 */
	int vertexQuantity() const
	{ return _vertexQuantity; }

protected:
	/**
	 * \brief Go for each vertex
	 */
	virtual void forEach(bool (*fn)(__details :: _Vertex_base<T> & v)) = 0;

	bool _directed;
	int _vertexQuantity;
};

/**
 * \class VertexList
 * \brief Representative graph in vertex list
 */
template <typename T>
class VertexListImpl : public GraphImpl<T>
{
	template <typename V> struct Vertex;

	template <typename V>
	struct Edge : public __details :: _Edge_base
	{
		Edge(int w, std::shared_ptr<Vertex<V> > & v) : __details :: _Edge_base(w), _v(v) {}
		std::shared_ptr<Vertex<V> > _v;
	};

	template <typename V>
	struct Vertex : public __details :: _Vertex_base<V>
	{
		typedef std :: list<Edge<V> > _EdgeList;

		Vertex(const V & v)
		{ __details :: _Vertex_base<V> :: _val = v; }

		void addEdgeTo(std::shared_ptr<Vertex<V> > & v, int weight = 0)
		{
			for (typename _EdgeList :: iterator it = _e.begin(); it != _e.end(); ++it) {
				if (it->_v == v) {
					it->_weight = weight;
					return;
				}
			}

			_e.push_back(Edge<V>(weight, v));
		}

		void delEdgeTo(std::shared_ptr<Vertex<V> > & v)
		{
			for (typename _EdgeList :: iterator it = _e.begin(); it != _e.end(); ++it) {
				if (it->_v == v) {
					_e.erase(it);
					break;
				}
			}
		}

		_EdgeList _e;
	};

	typedef std :: vector<std::shared_ptr<Vertex<T> > > _VertexList;

public:
	class vertex_iterator;
	class edge_iterator
	{
		friend class vertex_iterator;
	public:
		edge_iterator() {}

		edge_iterator(const edge_iterator & rhs) : _it(rhs._it) {}

		~edge_iterator() {}

		edge_iterator & operator++()
		{
			++_it;
			return *this;
		}

		edge_iterator operator++(int)
		{
			edge_iterator tmp(*this);
			++_it;
			return tmp;
		}

		edge_iterator & operator--()
		{
			--_it;
			return *this;
		}

		edge_iterator operator--(int)
		{
			edge_iterator tmp(*this);
			--_it;
			return tmp;
		}

		__details :: _Edge_base * operator->()
		{ return static_cast<__details :: _Edge_base *>(&(*_it)); }

		T & operator*()
		{ return _it->_v->_val; }

		bool operator==(const edge_iterator & rhs)
		{ return _it == rhs._it; }

		bool operator!=(const edge_iterator & rhs)
		{ return _it != rhs._it; }

	protected:
		edge_iterator(const typename Vertex<T> :: _EdgeList :: iterator & it) : _it(it) {}
		typename Vertex<T> :: _EdgeList :: iterator _it;
	};

	class vertex_iterator
	{
		friend class VertexListImpl<T>;
	public:
		vertex_iterator(const vertex_iterator & rhs)
		{
			_start = rhs._start;
			_pos = rhs._pos;
			_vertexList = rhs._vertexList;
		}

		~vertex_iterator()
		{}

		/**
		 * \warning Don't do --, ++ in case of start != 0 position
		 */
		vertex_iterator & operator++()
		{
			if (_pos == -1)
				return *this;

			if (_start == 0) {
				++_pos;
				if (_pos >= static_cast<int>(_vertexList->size()))
					_pos = -1;
			}
			else {
				_pos = (_pos + 1) % _vertexList->size();
				if (_pos == _start)
					_pos = -1;
			}

			return *this;
		}

		/**
		 * \warning Don't do ++, -- in case of start != 0 position
		 */
		vertex_iterator & operator--()
		{
			if (_pos == -1)
				return *this;

			if (_start == 0) {
				--_pos;
				if (_pos < 0)
					_pos = -1;
			}
			else {
				if (_pos == 0)
					_pos = _vertexList->size() - 1;
				else
					--_pos;

				if (_pos == _start)
					_pos = -1;
			}

			return *this;
		}

		__details :: _Vertex_base<T> * operator->()
		{
			assert(_pos != -1);
			return static_cast<__details :: _Vertex_base<T> *>((*_vertexList)[_pos].get());
		}

		__details :: _Vertex_base<T> & operator*()
		{
			assert(_pos != -1);
			return *static_cast<__details :: _Vertex_base<T> *>((*_vertexList)[_pos].get());
		}

		bool operator==(const vertex_iterator & rhs)
		{ return _pos == rhs._pos; }

		bool operator!=(const vertex_iterator & rhs)
		{ return _pos != rhs._pos; }

		edge_iterator begin()
		{
			assert(_pos != -1);
			return edge_iterator((*_vertexList)[_pos]->_e.begin());
		}

		edge_iterator end()
		{
			assert(_pos != -1);
			return edge_iterator((*_vertexList)[_pos]->_e.end());
		}

		vertex_iterator neigh(edge_iterator & e)
		{
			vertex_iterator it;

			for (std :: size_t i = 0; i < _vertexList->size(); ++i) {
				if ((*_vertexList)[i]->_val == *e) {
					it._vertexList = _vertexList;
					it._start = it._pos = i;
					break;
				}
			}

			return it;
		}

	protected:
		vertex_iterator(const _VertexList & v = _VertexList(), int start = 0) :
			_vertexList(new _VertexList(v)),
			_start(start),
			_pos(start)
		{}

		std :: shared_ptr<_VertexList> _vertexList;
		int _start, _pos;
	};

	/**
	 * \brief Contructor
	 */
	VertexListImpl(bool directed) :
		GraphImpl<T>(directed)
	{}

	/**
	 * \brief Destructor
	 */
	~VertexListImpl()
	{}

	/**
	 * \brief Add vertex
	 */
	bool addVertex(const T & v)
	{
		for (typename _VertexList :: const_iterator it = _v.begin(); it != _v.end(); ++it) {
			if ((*it)->_val == v)
				return false;
		}

		_v.push_back(std::make_shared<Vertex<T> >(v));

		++this->_vertexQuantity;

		return true;
	}

	/**
	 * \brief Del vertex
	 */
	bool delVertex(const T & v)
	{
		for (typename _VertexList :: iterator d = _v.begin(); d != _v.end(); ++d) {
			// remove from edges
			if ((*d)->_val == v) {
				for (typename _VertexList :: iterator it = _v.begin(); it != _v.end(); ++it) {
					if (d != it)
						(*it)->delEdgeTo(*d);
				}
				_v.erase(d);
			}
			--this->_vertexQuantity;
			return true;
		}

		return false;
	}

	/**
	 * \brief Add edge between two vertexes
	 */
	bool addEdge(const T & from, const T & to, int weight = 0)
	{
		for (typename _VertexList :: iterator f = _v.begin();
		     f != _v.end(); ++f)
		{
			if ((*f)->_val == from) {
				for (typename _VertexList :: iterator t = _v.begin(); t != _v.end(); ++t) {
					if ((*t)->_val == to) {
						(*f)->addEdgeTo(*t, weight);
						if (!GraphImpl<T> :: _directed)
							(*t)->addEdgeTo(*f, weight);
						return true;
					}
				}
			}
		}

		return false;
	}

	/**
	 * \brief Del edge between two vertexes
	 */
	bool delEdge(const T & from, const T & to)
	{
		for (typename _VertexList :: iterator f = _v.begin();
		     f != _v.end(); ++f)
		{
			if ((*f)->_val == from) {
				for (typename _VertexList :: iterator t = _v.begin(); t != _v.end(); ++t) {
					if ((*t)->_val == to) {
						(*f)->delEdgeTo(*t);
						if (!GraphImpl<T> :: _directed)
							(*t)->delEdgeTo(*f);
						return true;
					}
				}
			}
		}

		return false;
	}

	/**
	 * \brief Print to file using
	 */
	void printToFile(const char * filename)
	{
		std::remove(filename);

		std :: ofstream o(filename);
		if (o.fail()) {
			std :: cout << "file opening fail " << filename << std :: endl;
			return;
		}

		if (GraphImpl<T> :: _directed) {
			o << "digraph g {" << std :: endl;
			for (typename _VertexList :: iterator v = _v.begin(); v != _v.end(); ++v)
			{
				o << (std :: uint64_t)v->get() << "[label=" << (*v)->_val << "];" << std :: endl;
				for (typename Vertex<T> :: _EdgeList :: iterator e = (*v)->_e.begin(); e != (*v)->_e.end(); ++e) {
					o << (std :: uint64_t)v->get() << " -> " << (std :: uint64_t)e->_v.get() << " [label=" << e->_weight << "]" << std :: endl;
				}
			}
		}
		else {
			forEach([](__details :: _Vertex_base<T> & v)->bool {
				v._color = __details :: _Vertex_base<T> :: Color :: White;
				return true;
			});

			o << "graph g {" << std :: endl;
			for (typename _VertexList :: iterator v = _v.begin(); v != _v.end(); ++v)
			{
				o << (std :: uint64_t)v->get() << "[label=" << (*v)->_val << "];" << std :: endl;
				for (typename Vertex<T> :: _EdgeList :: iterator e = (*v)->_e.begin(); e != (*v)->_e.end(); ++e) {
					if (e->_v->_color == __details :: _Vertex_base<T> :: Color :: White) {
						o << (std :: uint64_t)v->get() << " -- " << (std :: uint64_t)e->_v.get() << " [label=" << e->_weight << "]" << std :: endl;
					}
				}
				(*v)->_color = __details :: _Vertex_base<T> :: Color :: Black;
			}
		}

		o << "}" << std :: endl;
	}

	/**
	 * \brief Start vertex traversal
	 */
	vertex_iterator begin()
	{
		return vertex_iterator(_v);
	}

	/**
	 * \brief Start vertex traversal from vertex
	 */
	vertex_iterator begin(const T & v)
	{
		for (std :: size_t i = 0; i < _v.size(); ++i) {
			if (_v[i]->_val == v)
				return vertex_iterator(_v, i);
		}

		return end();
	}

	/**
	 * \brief Vertex after the last
	 */
	vertex_iterator end()
	{
		return vertex_iterator(_VertexList(), -1);
	}

protected:
	/**
	 * \brief Go for each vertex
	 */
	void forEach(bool (*fn)(__details :: _Vertex_base<T> & v))
	{
		for (typename _VertexList :: iterator v = _v.begin(); v != _v.end(); ++v) {
			if (!fn(*static_cast<__details :: _Vertex_base<T> *>(v->get())))
				break;
		}
	}

private:
	_VertexList _v;
};

/**
 * \class MatrixImpl
 * \brief Matrix representative of graph
 */
template <typename T>
class MatrixImpl : public GraphImpl<T>
{
	template <typename V>
	struct Vertex : public __details :: _Vertex_base<V> {
		Vertex(const V & val) :  __details :: _Vertex_base<V>(val), _empty(false) {}
		Vertex & operator=(const V & val)
		{ __details :: _Vertex_base<V>(val)->_val = val; return *this; }
		bool _empty;
	};

	typedef std :: vector<Vertex<T> > _VertexList;
	typedef boost::numeric::ublas::matrix<int> _EdgeList;
public:
	class vertex_iterator;
	class edge_iterator
	{
		friend class vertex_iterator;
	public:
		edge_iterator() : _vId(-1), _neighId(-1) {}

		edge_iterator(const edge_iterator & rhs) :
			_vId(rhs._vId),
			_neighId(rhs._neighId),
			_edgeStub(rhs._edgeStub._weight),
			_edge(rhs._edge)
		{}

		~edge_iterator() {}

		edge_iterator & operator++()
		{
			if (_neighId != -1) {
				while (++_neighId < static_cast<int>(_edge->size1())) {
					if ((*_edge)(_vId, _neighId) != std :: numeric_limits<int> :: min()) {
						return *this;
					}
				}
				_neighId = -1;
			}

			return *this;
		}

		edge_iterator operator++(int)
		{
			edge_iterator tmp(*this);
			operator++();
			return tmp;
		}

		edge_iterator & operator--()
		{
			if (_neighId != -1) {
				while (--_neighId >= 0) {
					if ((*_edge)(_vId, _neighId) != std :: numeric_limits<int> :: min()) {
						return *this;
					}
				}
				_neighId = -1;
			}

			return *this;
		}

		edge_iterator operator--(int)
		{
			edge_iterator tmp(*tmp);
			operator--();
			return tmp;
		}

		__details :: _Edge_base * operator->()
		{
			_edgeStub._weight = (*_edge)(_vId, _neighId);
			return &_edgeStub;
		}
//
//		T & operator*()
//		{ return _it->_v->_val; }
//
		bool operator==(const edge_iterator & rhs)
		{ return (_vId == rhs._vId) && (_neighId == rhs._neighId); }

		bool operator!=(const edge_iterator & rhs)
		{ return (_neighId != rhs._neighId); }

	protected:
		edge_iterator(std :: shared_ptr<_EdgeList> & edge, int vId) :
			_vId(vId),
			_neighId(0),
			_edgeStub(std :: numeric_limits<int> :: min()),
			_edge(edge)
		{
			if (vId == -1) {
				_neighId = -1;
				return;
			}

			for (; _neighId < static_cast<int>(_edge->size1()); ++_neighId) {
				if ((*_edge)(_vId, _neighId) != std :: numeric_limits<int> :: min())
					return;
			}

			_neighId = -1;
		}

		int _vId, _neighId;
		__details :: _Edge_base _edgeStub;
		std :: shared_ptr<_EdgeList> _edge;
	};

	class vertex_iterator
	{
		friend class MatrixImpl<T>;
	public:
		vertex_iterator(const vertex_iterator & rhs)
		{
			_start = rhs._start;
			_pos = rhs._pos;
			_vertexList = rhs._vertexList;
			_edgeList = rhs._edgeList;
		}

		~vertex_iterator()
		{}

		/**
		 * \warning Don't do --, ++ in case of start != 0 position
		 */
		vertex_iterator & operator++()
		{
			if (_pos == -1)
				return *this;

			do {
				if (_start == 0) {
					++_pos;
					if (_pos >= static_cast<int>(_vertexList->size())) {
						_pos = -1;
						break;
					}
				}
				else {
					_pos = (_pos + 1) % _vertexList->size();
					if (_pos == _start) {
						_pos = -1;
						break;
					}
				}
			} while ((*_vertexList)[_pos]._empty);

			return *this;
		}

		/**
		 * \warning Don't do ++, -- in case of start != 0 position
		 */
		vertex_iterator & operator--()
		{
			if (_pos == -1)
				return *this;
			do {
				if (_start == 0) {
					--_pos;
					if (_pos < 0) {
						_pos = -1;
						break;
					}
				}
				else {
					if (_pos == 0)
						_pos = _vertexList->size() - 1;
					else
						--_pos;

					if (_pos == _start) {
						_pos = -1;
						break;
					}
				}
			} while ((*_vertexList)[_pos]._empty);

			return *this;
		}

		__details :: _Vertex_base<T> * operator->()
		{
			assert(_pos != -1 && (*_vertexList)[_pos]._empty == false);
			return static_cast<__details :: _Vertex_base<T> *>(&(*_vertexList)[_pos]);
		}

		__details :: _Vertex_base<T> & operator*()
		{
			assert(_pos != -1);
			return *static_cast<__details :: _Vertex_base<T> *>(&(*_vertexList)[_pos]);
		}

		bool operator==(const vertex_iterator & rhs)
		{ return _pos == rhs._pos; }

		bool operator!=(const vertex_iterator & rhs)
		{ return _pos != rhs._pos; }

		edge_iterator begin()
		{
			assert(_pos != -1);
			return edge_iterator(_edgeList, _pos);
		}

		edge_iterator end()
		{
			assert(_pos != -1);
			return edge_iterator(_edgeList, -1);
		}

		vertex_iterator neigh(edge_iterator & e)
		{
			vertex_iterator it;
			assert((_pos == e._vId) && (e._neighId != -1));
			it._vertexList = _vertexList;
			it._edgeList = _edgeList;
			it._start = it._pos = e._neighId;

			return it;
		}

	protected:
		vertex_iterator(const _VertexList & v = _VertexList(), const _EdgeList & e = _EdgeList(), int start = 0) :
			_vertexList(new _VertexList(v)),
			_edgeList(new _EdgeList(e)),
			_start(start),
			_pos(start)
		{}

		std :: shared_ptr<_VertexList> _vertexList;
		std :: shared_ptr<_EdgeList> _edgeList;
		int _start, _pos;
	};

	/**
	 * \brief Contructor
	 */
	MatrixImpl(bool directed) :
		GraphImpl<T>(directed) {}

	/**
	 * \brief Destructor
	 */
	virtual ~MatrixImpl() {}

	/**
	 * \brief Add vertex
	 */
	bool addVertex(const T & v)
	{
		std :: size_t free_idx = _vertex.size();
		for (std :: size_t i = 0; i < _vertex.size(); ++i) {
			if (_vertex[i]._empty)
				free_idx = i;
			else if (_vertex[i]._val == v)
				return false;
		}

		// no more place, resize matrix
		if (free_idx == _vertex.size()) {
			_vertex.push_back(v);
			_edge.resize(_vertex.size(), _vertex.size());
			for (std :: size_t j = 0; j < _edge.size1(); ++j) {
				_edge(free_idx, j) = std :: numeric_limits<int> :: min();
				_edge(j, free_idx) = std :: numeric_limits<int> :: min();
			}
		}
		else {
			_vertex[free_idx]._val = v; // move is better
			_vertex[free_idx]._empty = false;
			assert(_edge(free_idx, free_idx) == std :: numeric_limits<int> :: min());
		}

		++this->_vertexQuantity;

		return true;
	}

	/**
	 * \brief Del vertex
	 */
	bool delVertex(const T & v)
	{
		std :: size_t i = 0;
		for (; i < _vertex.size(); ++i) {
			if (_vertex[i]._val == v)
				break;
		}

		if (i < _vertex.size()) {
			_vertex[i]._empty = true;
			for (std :: size_t j = 0; j < _edge.size1(); ++j) {
				_edge(i, j) = std :: numeric_limits<int> :: min();
				_edge(j, i) = std :: numeric_limits<int> :: min();
			}

			--this->_vertexQuantity;

			return true;
		}

		return false;
	}

	/**
	 * \brief Add edge between two vertexes
	 */
	bool addEdge(const T & from, const T & to, int weight = 0)
	{
		std :: size_t f = 0, t = 0;
		for (; f < _vertex.size(); ++f) {
			if (_vertex[f]._val == from)
				break;
		}

		for (; t < _vertex.size(); ++t) {
			if (_vertex[t]._val == to)
				break;
		}

		if (f < _vertex.size() && t < _vertex.size()) {
			_edge(f, t) = weight;
			if (!GraphImpl<T> :: _directed)
				_edge(t, f) = weight;
			else
				_edge(t, f) = std :: numeric_limits<int> :: min();
			return true;
		}

		return false;
	}

	/**
	 * \brief Del edge between two vertexes
	 */
	bool delEdge(const T & from, const T & to)
	{
		std :: size_t f = 0, t = 0;
		for (; f < _vertex.size(); ++f) {
			if (_vertex[f]._val == from)
				break;
		}

		for (; t < _vertex.size(); ++t) {
			if (_vertex[t]._val == to)
				break;
		}

		if (f < _vertex.size() && t < _vertex.size()) {
			_edge(f, t) = std :: numeric_limits<int> :: min();
			if (!GraphImpl<T> :: _directed)
				_edge(t, f) = std :: numeric_limits<int> :: min();
			return true;
		}

		return false;
	}

	/**
	 * \brief Print to file using
	 */
	void printToFile(const char * filename)
	{
		std::remove(filename);

		std :: ofstream o(filename);
		if (o.fail()) {
			std :: cout << "file opening fail " << filename << std :: endl;
			return;
		}

		if (GraphImpl<T> :: _directed) {
			o << "digraph g {" << std :: endl;
			for (std :: size_t v = 0; v < _vertex.size(); ++v) {
				if (!_vertex[v]._empty) {
					o << (std :: uint64_t)&_vertex[v] << "[label=" << _vertex[v]._val << "];" << std :: endl;
					for (std :: size_t e = 0; e < _edge.size1(); ++e) {
						if (_edge(v, e) != std :: numeric_limits<int> :: min()) {
							o << (std :: uint64_t)&_vertex[v] << " -> " << (std :: uint64_t)&_vertex[e] << " [label=" << _edge(v, e) << "]" << std :: endl;
						}
					}
				}
			}
		}
		else {
			o << "graph g {" << std :: endl;
			for (std :: size_t v = 0; v < _vertex.size(); ++v) {
				if (!_vertex[v]._empty) {
					o << (std :: uint64_t)&_vertex[v] << "[label=" << _vertex[v]._val << "];" << std :: endl;
					for (std :: size_t e = v; e < _vertex.size(); ++e) {
						if (_edge(v, e) != std :: numeric_limits<int> :: min())
							o << (std :: uint64_t)&_vertex[v] << " -- " << (std :: uint64_t)&_vertex[e] << " [label=" << _edge(v, e) << "]" << std :: endl;
					}
				}
			}
		}

		o << "}" << std :: endl;
	}

	/**
	 * \brief Start vertex traversal
	 */
	vertex_iterator begin()
	{
		return vertex_iterator(_vertex, _edge);
	}

	/**
	 * \brief Start vertex traversal from vertex
	 */
	vertex_iterator begin(const T & v)
	{
		for (std :: size_t i = 0; i < _vertex.size(); ++i) {
			if (_vertex[i]._val == v)
				return vertex_iterator(_vertex, _edge, i);
		}

		return end();
	}

	/**
	 * \brief Vertex after the last
	 */
	vertex_iterator end()
	{
		return vertex_iterator(_VertexList(), _EdgeList(), -1);
	}
protected:
	/**
	 * \brief Go for each vertex
	 */
	void forEach(bool (*fn)(__details :: _Vertex_base<T> & v))
	{
		for (auto &i : _vertex) {
			if (!fn(*static_cast<__details :: _Vertex_base<T> *>(&i)))
				break;
		}
	}

private:
	_VertexList _vertex;
	_EdgeList _edge; //< quadratic matrix always
};

/**
 * \class Graph
 * \brief Common representative of graph
 */
template <typename T, template <typename> class Impl>
class Graph : public Impl<T>
{
	typedef typename Impl<T> :: vertex_iterator _Vertex;
	typedef typename Impl<T> :: edge_iterator _Edge;
public:
	/**
	 * \brief Constructor
	 */
	Graph(bool directed) : Impl<T>(directed) {}

	/**
	 * \brief Destructor
	 */
	virtual ~Graph() {}

	/**
	 * \brief BFS traversal
	 */
	void bfs_traversal(std :: function<bool(__details :: _Vertex_base<T> &, bool)> fn)
	{
		std :: list<typename Impl<T> :: vertex_iterator> queue;

		Impl<T> :: forEach([](__details :: _Vertex_base<T> & v)->bool {
			v._color = __details :: _Vertex_base<T> :: Color :: White;
			v._d = 0;
			return true;
		});

		for (_Vertex v = Impl<T> :: begin(); v != Impl<T> :: end(); ++v)
		{
			if (v->_color != __details :: _Vertex_base<T> :: Color :: White)
				continue;

			bool new_component = true;
			v->_color = __details :: _Vertex_base<T> :: Color :: Grey;
			v->_d = 0;
			queue.push_front(v);

			while (!queue.empty()) {
				_Vertex it = queue.back();
				queue.pop_back();

				// user callback
				if (!fn(*it, new_component))
					return;

				new_component = false;
				for (_Edge e = it.begin(); e != it.end(); ++e)
				{
					_Vertex neigh = it.neigh(e);
					if (neigh->_color == __details :: _Vertex_base<T> :: Color :: White) {
						neigh->_color = __details :: _Vertex_base<T> :: Color :: Grey;
						neigh->_d = it->_d + 1;
						queue.push_front(neigh);
					}
				}

				it->_color = __details :: _Vertex_base<T> :: Color :: Black;
			}
		}
	}

	/**
	 * \brief DFS traversal
	 */
	void dfs_traversal(std :: function<void(__details :: _Vertex_base<T> &)> pre,
	                   std :: function<void(__details :: _Vertex_base<T> &, __details :: _Vertex_base<T> &, bool)> edge,
	                   std :: function<bool(__details :: _Vertex_base<T> &)> post)
	{
		int time = 0;

		std :: function<bool(_Vertex)> research =
			[&](typename Impl<T> :: vertex_iterator v) {
				if (v->_color == __details :: _Vertex_base<T> :: Color :: White) {
					// new discovered vertex
					if (pre)
						pre(*v);
					v->_color = __details :: _Vertex_base<T> :: Color :: Grey;
					v->_d = ++time;
					for (_Edge e = v.begin(); e != v.end(); ++e) {
						_Vertex neigh = v.neigh(e);
						if (edge)
							edge(*v, *neigh, false);
						if (!research(neigh))
							return false;
						if (edge)
							edge(*v, *neigh, true);
					}
					// stop discovering vertex
					v->_color = __details :: _Vertex_base<T> :: Color :: Black;
					v->_f = ++time;
					if (!post(*v))
						return false;
				}

				return true;
			};

		Impl<T> :: forEach([](__details :: _Vertex_base<T> & v)->bool {
			v._color = __details :: _Vertex_base<T> :: Color :: White;
			v._d = v._f = 0;
			return true;
		});


		for (typename Impl<T> :: vertex_iterator vertex = Impl<T> :: begin();
		     vertex != Impl<T> :: end(); ++vertex)
		{
			if (!research(vertex))
				break;
		}
	}

	/**
	 * \brief Topological sort
	 */
	void topological_sort(std :: function<bool(__details :: _Vertex_base<T> &)> fn)
	{
		assert(Impl<T> :: _directed == true);

		std :: list<__details :: _Vertex_base<T> > ts;

		std :: function<bool(__details :: _Vertex_base<T> &)> collect_fn =
			[&](__details :: _Vertex_base<T> & v)->bool {
				ts.push_front(v);
				return true;
			}
		;

		Graph<T, Impl> :: dfs_traversal(nullptr, nullptr, collect_fn);

		for (auto &i : ts) {
			if (!fn(i))
				break;
		}
	}

	/**
	 * \brief Prim algorithm for minimum spanning tree
	 */
	int prim_mst(Graph<T, Impl> & mst)
	{
		int weight = 0;

		Impl<T> :: forEach([](__details :: _Vertex_base<T> & v)->bool {
			v._color = __details :: _Vertex_base<T> :: Color :: White;
			return true;
		});

		std :: function<bool(std :: pair<_Vertex, _Edge> &, std :: pair<_Vertex, _Edge> &)> compare =
			[](std :: pair<_Vertex, _Edge> & l, std :: pair<_Vertex, _Edge> & r) {
				return l.second->_weight > r.second->_weight;
			};

		_Vertex v = this->begin();
		std :: vector<std :: pair<_Vertex, _Edge> > candidate;
		while (v != this->end()) {
			v->_color = __details :: _Vertex_base<T> :: Color :: Black;
			for (_Edge e = v.begin(); e != v.end(); ++e) {
				if (v.neigh(e)->_color == __details :: _Vertex_base<T> :: Color :: White) {
					candidate.push_back(std :: make_pair(v, e)); std::push_heap(candidate.begin(), candidate.end(), compare);
				}
			}

			v = this->end();
			while (!candidate.empty()) {
				std :: pair<_Vertex, _Edge> tmp = candidate.front();
				std::pop_heap(candidate.begin(), candidate.end(), compare); candidate.pop_back();
				_Vertex neigh = tmp.first.neigh(tmp.second);
				if (neigh->_color == __details :: _Vertex_base<T> :: Color :: White) {
					mst.addVertex(tmp.first->_val);
					mst.addVertex(neigh->_val);
					mst.addEdge(tmp.first->_val, neigh->_val, tmp.second->_weight);
					weight += tmp.second->_weight;
					v = neigh;
					break;
				}
			}
		}

		return weight;
	}

	/**
	 * \brief Kruskal's algorithm for minimum spanning tree
	 */
	int kruskal_mst(Graph<T, Impl> & mst)
	{
		int weight = 0;

		Impl<T> :: forEach([](__details :: _Vertex_base<T> & v)->bool {
			v._color = __details :: _Vertex_base<T> :: Color :: White;
			return true;
		});

		std :: function<bool(std :: pair<_Vertex, _Edge> &, std :: pair<_Vertex, _Edge> &)> compare =
			[](std :: pair<_Vertex, _Edge> & l, std :: pair<_Vertex, _Edge> & r) {
				return l.second->_weight > r.second->_weight;
			};

		// create component sets
		std :: vector<std :: pair<_Vertex, _Edge> > eh;
		std::map<T, int> rank;
		std::map<T, T> parent;
		boost::disjoint_sets<
		        boost :: associative_property_map<std::map<T, int> >,
		        boost :: associative_property_map<std::map<T, T> > > ds(
		                boost :: make_assoc_property_map(rank),
		                boost :: make_assoc_property_map(parent));

		for (_Vertex v = this->begin(); v != this->end(); ++v) {
			ds.make_set(v->_val);
			mst.addVertex(v->_val);
			for (_Edge e = v.begin(); e != v.end(); ++e) {
				if (v.neigh(e)->_color == __details :: _Vertex_base<T> :: Color :: White) {
					eh.push_back(std :: make_pair(v, e)); std::push_heap(eh.begin(), eh.end(), compare);
				}
			}
			v->_color = __details :: _Vertex_base<T> :: Color :: Black;
		}

		while (!eh.empty()) {
			std :: pair<_Vertex, _Edge> edge = eh.front();
			std :: pop_heap(eh.begin(), eh.end(), compare); eh.pop_back();
			_Vertex neigh = edge.first.neigh(edge.second);
			T u = ds.find_set(edge.first->_val), v = ds.find_set(neigh->_val);
			if (u != v) {
				weight += edge.second->_weight;
				mst.addEdge(edge.first->_val, neigh->_val, edge.second->_weight);
				ds.link(u, v);
			}
		}

		return weight;
	}

	/**
	 * \brief Find all weak components
	 */
	void weak_components(std :: function<bool(__details :: _Vertex_base<T> &, int)> fn)
	{
		if (Impl<T> :: _directed) {
			std :: cout << "not implemented for directed\n";
			return;
		}

		Impl<T> :: forEach([](__details :: _Vertex_base<T> & v)->bool {
			v._color = __details :: _Vertex_base<T> :: Color :: White;
			v._componentId = 0;
			return true;
		});

		int component_id = 0;
		bfs_traversal([&](__details :: _Vertex_base<T> & v, bool new_component)->bool {
			if (new_component)
				component_id++;
			fn(v, component_id);
			return true;
		});
	}

	/**
	 * \brief Find all strong components
	 */
	void strong_components(std :: function<bool(__details :: _Vertex_base<T> &, int)> fn)
	{
		int component = 0, lowLink = 0;
		std :: stack<__details :: _Vertex_base<T> *> s;

		std :: function<void(__details :: _Vertex_base<T> &)> pre =
			[&](__details :: _Vertex_base<T> & v) {
				v._lowLink = lowLink++;
				s.push(&v);
			}
		;

		std :: function<void(__details :: _Vertex_base<T> &, __details :: _Vertex_base<T> &, bool)> edge =
			[&](__details :: _Vertex_base<T> & from, __details :: _Vertex_base<T> & to, bool back) {
				if (back && (to._lowLink < from._lowLink)) {
					from._flag = false;
					from._lowLink = to._lowLink;
				}
			}
		;

		std :: function<bool(__details :: _Vertex_base<T> &)> post =
			[&](__details :: _Vertex_base<T> & v)->bool {
				if (v._flag) {
					__details :: _Vertex_base<T> * x = nullptr;
					do {
						x = s.top();
						s.pop();
						x->_lowLink = std :: numeric_limits<int> :: max();
						fn(*x, component);
					} while (&v != x);
					component++;
				}
				return true;
			}
		;

		Impl<T> :: forEach([](__details :: _Vertex_base<T> & v)->bool {
			v._color = __details :: _Vertex_base<T> :: Color :: White;
			v._componentId = v._lowLink = 0;
			v._flag = true;
			return true;
		});

		dfs_traversal(pre, edge, post);
	}

	/**
	 * \brief Find short way by Dijkstra's algorithm
	 */
	int short_path_dijkstra(const T & start, const T & finish, std :: list<T> & path)
	{
		std :: vector<_Vertex> q;

		std :: function<bool(_Vertex &, _Vertex &)> compare =
			[](_Vertex & l, _Vertex & r) {
				return l->_d > r->_d;
			}
		;

		__details :: _Vertex_base<T> * s = nullptr, * f = nullptr;

		for (_Vertex v = Impl<T> :: begin(); v != Impl<T> :: end(); ++v) {
			if (v->_val == start) {
				v->_d = 0;
				s = &*v;
			}
			else
				v->_d = std :: numeric_limits<int> :: max();

			if (v->_val == finish)
				f = &*v;

			v->_prev = nullptr;
			v->_color = __details :: _Vertex_base<T> :: Color :: White;
			q.push_back(v);
		}

		if (!s || !f)
			return -1;

		std :: make_heap(q.begin(), q.end(), compare);

		while (!q.empty()) {
			_Vertex v = q.front();
			v->_color = __details :: _Vertex_base<T> :: Color :: Black;
			std :: pop_heap(q.begin(), q.end(), compare); q.pop_back();
			// relax neighbours
			for (_Edge e = v.begin(); e != v.end(); ++e) {
				_Vertex neigh = v.neigh(e);
				if (neigh->_color == __details :: _Vertex_base<T> :: Color :: White) {
					int d = v->_d + e->_weight;
					if (d < neigh->_d) {
						neigh->_d = d;
						neigh->_prev = &*v;
					}
				}
			}

			std :: make_heap(q.begin(), q.end(), compare);
		}

		int res = f->_d;

		while (f) {
			path.push_front(f->_val);
			f = f->_prev;
		}

		return res;
	}
};

} /* namespace conq_graph */

#endif /* GRAPH_H_ */
