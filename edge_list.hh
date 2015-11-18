
// Edge list graph representation.
//
// NOTE that this compiles, but is untested; use at your own risk.

#pragma once

#include <cassert>
#include <list>

// Forward declarations.
template <typename VERTEX_LABEL, typename EDGE_LABEL> class ELGraph;
template <typename VERTEX_LABEL, typename EDGE_LABEL> class ELEdge;

template <typename VERTEX_LABEL, typename EDGE_LABEL>
class ELVertex {
public:
  ELVertex(ELGraph<VERTEX_LABEL, EDGE_LABEL>* graph, int index, VERTEX_LABEL label) {
    assert(graph != nullptr);
    assert(index >= 0);
    _graph = graph;
    _index = index;
    _label = label;
  }

  int index() {
    return _index;
  }

  VERTEX_LABEL label() {
    return _label;
  }

  void set_label(VERTEX_LABEL label) {
    _label = label;
  }

  // Return a pointer to the edge connecting this with v, or nullptr
  // if no such edge exists.
  ELEdge<VERTEX_LABEL, EDGE_LABEL>* connector(ELVertex<VERTEX_LABEL, EDGE_LABEL>* v);

  // Return true if v is connected to this vertex by a single edge.
  bool is_adjacent(ELVertex<VERTEX_LABEL, EDGE_LABEL>* v) {
    return (connector(v) != nullptr);
  }

  // Return a list of all edges incident to this vertex.
  std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>* incident_list();

private:
  // We need a pointer to the whole graph so connector() and
  // incident_list() can access the edge list.
  ELGraph<VERTEX_LABEL, EDGE_LABEL> *_graph;
  
  int _index;
  VERTEX_LABEL _label;
};

template <typename VERTEX_LABEL, typename EDGE_LABEL>
class ELEdge {
public:
  ELEdge(ELVertex<VERTEX_LABEL, EDGE_LABEL> *s,
	 ELVertex<VERTEX_LABEL, EDGE_LABEL> *t,
	 EDGE_LABEL label) {
    assert(s != nullptr);
    assert(t != nullptr);
    assert(s != t);
    _s = s;
    _t = t;
    _label = label;
  }

  ELVertex<VERTEX_LABEL, EDGE_LABEL>* s() {
    return _s;
  }

  ELVertex<VERTEX_LABEL, EDGE_LABEL>* t() {
    return _t;
  }

  EDGE_LABEL label() {
    return _label;
  }

  void set_label(EDGE_LABEL label) {
    _label = label;
  }

  bool is_incident(ELVertex<VERTEX_LABEL, EDGE_LABEL> *v) {
    return (v == _s) || (v == _t);
  }

  ELVertex<VERTEX_LABEL, EDGE_LABEL>* opposite(ELVertex<VERTEX_LABEL, EDGE_LABEL>* v) {
    assert(is_incident(v));
    if (v == _s) {
      return _t;
    } else {
      return _s;
    }
  }

private:
  ELVertex<VERTEX_LABEL, EDGE_LABEL> *_s, *_t;
  EDGE_LABEL _label;
};
  
template <typename VERTEX_LABEL, typename EDGE_LABEL>
class ELGraph {
  friend class ELVertex<VERTEX_LABEL, EDGE_LABEL>;
public:
  ELGraph() { }

  ~ELGraph() {
    clear();
  }

  std::list<ELVertex<VERTEX_LABEL, EDGE_LABEL>*> vertex_list() {
    // copy the whole vertex list
    return new std::list<ELVertex<VERTEX_LABEL, EDGE_LABEL>*>(_vertices);
  }

  std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*> edge_list() {
    // copy the whole edge list
    return new std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>(_edges);
  }
  
  ELVertex<VERTEX_LABEL, EDGE_LABEL>* add_vertex(int index, VERTEX_LABEL label) {
    ELVertex<VERTEX_LABEL, EDGE_LABEL>* v = new ELVertex<VERTEX_LABEL, EDGE_LABEL>(this, index, label);
    _vertices.push_back(v);
    return v;
  }

  void erase_vertex(ELVertex<VERTEX_LABEL, EDGE_LABEL> *v) {
    // remove v from the vertex list
    _vertices.remove(v);

    // remove any edge incident to v from the edge list
    typename std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>::iterator i = _edges.begin();
    while (i != _edges.end()) {
      if (i->is_incident(v)) {
	delete *i;
	i = _edges.erase(i);
      } else {
	++i;
      }
    }

    // finally delete the vertex object itself
    delete v;
  }

  ELEdge<VERTEX_LABEL, EDGE_LABEL>* add_edge(ELVertex<VERTEX_LABEL, EDGE_LABEL> *s,
					     ELVertex<VERTEX_LABEL, EDGE_LABEL> *t,
					     EDGE_LABEL label) {
    ELEdge<VERTEX_LABEL, EDGE_LABEL> *e = new ELEdge<VERTEX_LABEL, EDGE_LABEL>(s, t, label);
    _edges.push_back(e);
    return e;
  }

  void erase_edge(ELEdge<VERTEX_LABEL, EDGE_LABEL>* e) {
    _edges.remove(e);
    delete e;
  }

  void clear() {
    // Delete each vertex object.
    for (typename std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>::iterator i = _vertices.begin();
	 i != _vertices.end();
	 ++i) {
      delete *i;
    }

    // Delete each edge object.
    for (typename std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>::iterator i = _edges.begin();
	 i != _edges.end();
	 ++i) {
      delete *i;
    }

    // Clear the lists (which now contain dangling pointers).
    _vertices.clear();
    _edges.clear();    
  }
  
private:
  std::list<ELVertex<VERTEX_LABEL, EDGE_LABEL>*> _vertices;
  std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*> _edges;
};


template <typename VERTEX_LABEL, typename EDGE_LABEL>
ELEdge<VERTEX_LABEL, EDGE_LABEL>* ELVertex<VERTEX_LABEL, EDGE_LABEL>::connector(ELVertex<VERTEX_LABEL, EDGE_LABEL>* v) {
  assert(v != nullptr);
  for (typename std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>::iterator i = _graph->_edges.begin();
       i != _graph->_edges.end();
       ++i) {
    if (i->is_incident(this) && i->is_incident(v)) {
      return *i;
    }
  }
  return nullptr;  
}
  
template <typename VERTEX_LABEL, typename EDGE_LABEL>
std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>* ELVertex<VERTEX_LABEL, EDGE_LABEL>::incident_list() {
  std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>* result = new std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>();
  for (typename std::list<ELEdge<VERTEX_LABEL, EDGE_LABEL>*>::iterator i = _graph->_edges.begin();
       i != _graph->_edges.end();
       ++i) {
    if (i->is_incident(this)) {
      result->push_back(*i);
    }
  }
  return result;
}
