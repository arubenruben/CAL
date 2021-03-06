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
	void unweightedShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPathTo(const T &dest) const;

	// Fp05 - all pairs
	vector<vector<T>> distMinMatrix;
	vector<vector<int>> pathMatrix;

	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

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

    Vertex<T> * startVertex=this->findVertex(orig);

    if(startVertex==NULL){
        cout<<"BellmanFord start vertex is NULL";
        return;
    }

    //Pre process
    for(Vertex<T>* vertex: this->vertexSet ){
        vertex->dist=INF;
        vertex->path=NULL;
    }

    startVertex->dist=0;

    for(int i=0;i<this->vertexSet.size();i++){

        for(int j=0;j<this->vertexSet.size();j++){

            Vertex<T>* origin=this->vertexSet.at(j);

            for(Edge<T> edge: origin->adj){

                Vertex<T> *dest = edge.dest;
                //If the cost to this point gets better
                if(dest->dist > (origin->dist + edge.weight)) {
                    dest->dist = origin->dist + edge.weight;
                    dest->path = origin;
                }
            }
        }
    }

    for(int j=0;j<this->vertexSet.size();j++){

        Vertex<T>* origin=this->vertexSet.at(j);

        for(Edge<T> edge:origin->adj){

            Vertex<T>* dest=edge.dest;
            //If the cost to this point gets better, in the last iteration, it is an error
            if(dest->dist > (origin->dist + edge.weight)) {
                cout<<"Bellman-Ford has cicles"<<endl;
                return;
            }
        }
    }
    return;
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

    int numVertex=this->getNumVertex();

    this->distMinMatrix.resize(numVertex);
    this->pathMatrix.resize(numVertex);

    for(auto & ele:this->distMinMatrix) ele.resize(numVertex);
    for(auto & ele:this->pathMatrix) ele.resize(numVertex);


    //Pre processing
    for(int i=0;i<numVertex;i++){

        for(int j=0;j<numVertex;j++){
            this->distMinMatrix.at(i).at(j)=999999;
            this->pathMatrix.at(i).at(j)=-1;
        }
    }

    //Transform graph information with matrix dimention
    for(int i=0;i<vertexSet.size();i++){

        this->distMinMatrix.at(i).at(i)=0;

        for(const Edge<T> edge:vertexSet.at(i)->adj){

            //Need index for either the start either the destination vertexs to setup the matrix

            int destIndex=-1;
            Vertex<T>* dest=edge.dest;

            for(int i=0;i<numVertex;i++){
                if(dest->info==this->vertexSet.at(i)->info)
                    destIndex=i;
            }

            if(destIndex==-1){
                cout<<"Error preprocessing FloyWarshall, indexs for the matrix were negative"<<endl;
                return;
            }

            this->distMinMatrix.at(i).at(destIndex)=edge.weight;
            this->pathMatrix.at(i).at(destIndex)=i;
        }

    }

    //Matrix setuped, floydWarshall algorithm starts


    for(int k=0;k<numVertex;k++){

        for(int i=0;i<numVertex;i++){

            for(int j=0;j<numVertex;j++){

                if(this->distMinMatrix.at(i).at(j)>(this->distMinMatrix.at(i).at(k)+this->distMinMatrix.at(k).at(j))){
                    this->distMinMatrix.at(i).at(j)=this->distMinMatrix.at(i).at(k)+this->distMinMatrix.at(k).at(j);
                    this->pathMatrix.at(i).at(j)=this->pathMatrix.at(k).at(j);
                }
            }
        }
    }
    return;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;

    int originIndex=-1, destIndex=-1;

    for(int i=0;i<vertexSet.size();i++){

        if(this->vertexSet.at(i)->info==orig){

            originIndex=i;

        }else if(this->vertexSet.at(i)->info==dest){

            destIndex=i;
        }
    }

    if(originIndex==-1||destIndex==-1){
        cout<<"Error getting the index for the floydPath"<<endl;
        return res;
    }

    res.push_back(dest);
    int previousIndex=this->pathMatrix.at(originIndex).at(destIndex);

    while (previousIndex >= 0) {
        res.push_back(vertexSet.at(previousIndex)->info);
        previousIndex = this->pathMatrix[originIndex][previousIndex];
    }

    reverse(res.begin(),res.end());

	return res;
}


#endif /* GRAPH_H_ */
