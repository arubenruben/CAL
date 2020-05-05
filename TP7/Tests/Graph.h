/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
	T info;
	vector<Edge<T> *> outgoing;  // adj
	vector<Edge<T> *> incoming;
	Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
	Vertex(T in);

	bool visited;  // for path finding
	Edge<T> *path; // for path finding

public:
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
	Edge<T> * e = new Edge<T>(this, dest, c, f);
	this->outgoing.push_back(e);
	dest->incoming.push_back(e);
	return e;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
	return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	Vertex<T> * orig;
	Vertex<T> * dest;
	double capacity;
	double flow;
	Edge(Vertex<T> *o, Vertex<T> *d, double c, double f=0);

public:
	double getFlow() const;
	Vertex<T> *getDest() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f): orig(o), dest(d), capacity(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
	return flow;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
	return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	Vertex<T>* findVertex(const T &inf) const;
public:
	vector<Vertex<T> *> getVertexSet() const;
	Vertex<T> *addVertex(const T &in);
	Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f=0);

    bool findAugmentationPath(Vertex<T> *origin, Vertex<T> *dest);
    void testAndVisit(queue<Vertex<T>*> * queueAux,Edge<T>* edge,Vertex<T>* dest,int Residual);
    double findMinResidualAlongPath(Vertex<T>* origin, Vertex<T>* dest);

    void augmentFlowAlongPath(Vertex<T>* origin, Vertex<T>* dest, double minimalResidualToApply);
    void resetFlows();
    void fordFulkerson(T source, T target);
};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
	auto s = findVertex(sourc);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	else
		return s->addEdge(d, c, f);
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
	for (auto v : vertexSet)
		if (v->info == inf)
			return v;
	return nullptr;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}


/**
 * Finds the maximum flow in a graph using the Ford Fulkerson algorithm
 * (with the improvement of Edmonds-Karp).
 * Assumes that the graph forms a flow network from source vertex 's'
 * to sink vertex 't' (distinct vertices).
 * Receives as arguments the source and target vertices (identified by their contents).
 * The result is defined by the "flow" field of each edge.
 */

template <class T>

void Graph<T>::resetFlows(){

    for(Vertex<T> * vertex: this->vertexSet){
        for(Edge<T> *edge:vertex->outgoing){
            edge->flow=0;
        }
    }
}

template <class T>

bool Graph<T>::findAugmentationPath(Vertex<T> * origin, Vertex<T> * dest){

    queue<Vertex<T>*> queueAux;

    for(Vertex<T>* vertex:this->vertexSet){
        vertex->visited=false;
    }

    origin->visited=true;
    queueAux.push(origin);

    while (!queueAux.empty()&&!dest->visited){

        Vertex<T>* vertexAux=queueAux.front();
        queueAux.pop();

        for(Edge<T>* edge: vertexAux->incoming){
            testAndVisit(&queueAux,edge,edge->orig,edge->flow);
        }

        for(Edge<T>* edge: vertexAux->outgoing){
            testAndVisit(&queueAux,edge,edge->dest,edge->capacity-edge->flow);
        }

    }
    return dest->visited;
}

template <class T>
void Graph<T>::testAndVisit(queue<Vertex<T>*>* queueAux,Edge<T>* edge,Vertex<T>* dest,int residual){

    if(!dest->visited&&residual>0){
        dest->visited=true;
        dest->path=edge;
        queueAux->push(dest);
    }

    return;
}
template <class T>

double Graph<T>::findMinResidualAlongPath(Vertex<T>* origin, Vertex<T>* dest){
    double minimalResidual=INF;
    Vertex<T>* iterator=dest;

    while (iterator->info!=origin->info){
        Edge<T>* edgeAux=iterator->path;

        if(edgeAux->dest->info==iterator->info){
            if((edgeAux->capacity-edgeAux->flow)<minimalResidual){
                minimalResidual=edgeAux->capacity-edgeAux->flow;

            }
            iterator=edgeAux->orig;
        }

        else{
            if(edgeAux->flow<minimalResidual){
                minimalResidual=edgeAux->flow;
            }
            iterator=edgeAux->dest;

        }
    }
    return minimalResidual;
}

template <class T>
void Graph<T>::augmentFlowAlongPath(Vertex<T>* origin, Vertex<T>* dest, double minimalResidualToApply){

    Vertex<T>* iterator=dest;

    while (iterator->info!=origin->info){
        Edge<T>* edgeAux=iterator->path;

        if(edgeAux->dest->info==iterator->info){
            edgeAux->flow+=minimalResidualToApply;
            iterator=edgeAux->orig;
        }else{
            edgeAux->flow-=minimalResidualToApply;
            iterator=edgeAux->dest;
        }
    }
    return;
}

template <class T>

void Graph<T>::fordFulkerson(T source, T target) {

    double maximumFlow=0;
    resetFlows();

    Vertex<T> *origin=findVertex(source);
    Vertex<T> *dest=findVertex(target);

    if(origin==NULL || dest==NULL){
        cout<<"Origin or destination has a null reference"<<endl;
        return;
    }

    while(findAugmentationPath(origin,dest)){
        double minimalResidual=findMinResidualAlongPath(origin,dest);
        augmentFlowAlongPath(origin,dest,minimalResidual);
        maximumFlow+=minimalResidual;
    }
}

#endif /* GRAPH_H_ */