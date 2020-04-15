/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {

    queue<Vertex<T>*> queueAux;

    Vertex<T> * auxVertex;

    for(Vertex<T>* vertex:this->vertexSet){

        if(vertex->info==orig)
            auxVertex=vertex;

        vertex->dist=INF;
        vertex->path=NULL;
    }

    if(auxVertex==NULL){
        cout<<"This source vertex does not exist"<<endl;
        return;
    }

    auxVertex->dist=0;

    queueAux.push(auxVertex);

    while (!queueAux.empty()){

        auxVertex=queueAux.front();

        queueAux.pop();

        for(Edge<T> edgeAdj:auxVertex->adj){

            Vertex<T> * adjVertex=edgeAdj.dest;

            if(adjVertex->getDist()==INF){
                queueAux.push(adjVertex);
                adjVertex->dist=auxVertex->getDist()+1;
                adjVertex->path=auxVertex;
            }
        }

    }

}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {

    Vertex<T> * vertexOrigin=NULL;

    MutablePriorityQueue<Vertex<T>> queueAux;

    for(Vertex<T>* vertex:this->vertexSet){

        if(vertex->getInfo()==origin)
            vertexOrigin=vertex;

        vertex->dist=INF;
        vertex->path=NULL;
    }

    if(vertexOrigin==NULL){
        cout<<"This source vertex does not exist"<<endl;
        return;
    }

    vertexOrigin->dist=0;

    queueAux.insert(vertexOrigin);


    while (!queueAux.empty()){

        Vertex<T>* vertexSource=queueAux.extractMin();

        for(Edge<T> edge:vertexSource->adj){

            bool notInQueue = edge.dest->dist == numeric_limits<double>::max();

            Vertex<T> *vertexAdj = edge.dest;

            //If it improve, then... refresh
            if(vertexAdj->getDist()>vertexSource->getDist()+edge.weight){

                vertexAdj->dist=vertexSource->getDist()+edge.weight;
                vertexAdj->path=vertexSource;

                if(notInQueue){
                    queueAux.insert(vertexAdj);
                }else{
                    queueAux.decreaseKey(vertexAdj);
                }
            }
        }




    }









}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;

	Vertex<T>* vertexAux=this->findVertex(dest);
	Vertex<T>* vertexPath=vertexAux->getPath();
    res.push_back(vertexAux->info);

	if(vertexAux==NULL){
	    cout<<"Cannot get path to: dest vertex is NULL"<<endl;
        res.clear();
        return res;

	}

	while(vertexPath!=NULL){
	    res.push_back(vertexPath->info);
	    vertexPath=vertexPath->getPath();
	}

    std::reverse(res.begin(), res.end());

    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
