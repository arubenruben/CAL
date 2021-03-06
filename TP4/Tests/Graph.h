/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

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
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
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

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {

    //Already Exists Vertex
    if(this->findVertex(in))
        return false;

    Vertex<T> * vertexAux= new Vertex<T>(in);

    this->vertexSet.push_back(vertexAux);

	return true;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {

    Vertex<T>* vertexOrigin=this->findVertex(sourc);

    if(vertexOrigin==NULL){
        cout <<"Vertex origin do not exists"<<endl;
        return false;
    }

    Vertex<T>* vertexDestination=this->findVertex(dest);

    if(vertexDestination==NULL){
        cout<<"Vertex Destination do not exists"<<endl;
        return false;
    }
    vertexOrigin->addEdge(vertexDestination,w);

	return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    Edge<T>edgeAux(d,w);
    this->adj.push_back(edgeAux);
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {

    Vertex<T>* vertexOrigin=this->findVertex(sourc);

    if(vertexOrigin==NULL){
        cout <<"Vertex origin do not exists"<<endl;
        return false;
    }

    Vertex<T>* vertexDestination=this->findVertex(dest);

    if(vertexDestination==NULL){
        cout<<"Vertex Destination do not exists"<<endl;
        return false;
    }

    return vertexOrigin->removeEdgeTo(vertexDestination);

}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {

    if(d==NULL){
        cout<<"Destination Vertex is NULL"<<endl;
        return false;
    }

    if(this==d){
        cout<<"Cannot remove a vertex to himself"<<endl;
        return  false;
    }

    for (typename vector<Edge<T>>::iterator i = this->adj.begin(); i != this->adj.end(); i++){

        //Other vertixes
        if((*i).dest!=d)
            continue;

        this->adj.erase(i);
        return true;

    }

	return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    // TODO (10 lines)
    // HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
    // HINT: take advantage of "removeEdgeTo" to remove incoming edges.

    //Iterate over all vertices ao remove the edges whose destination is this vertex

    Vertex <T> *vertexToRemove=this->findVertex(in);
    typename vector<Vertex<T>*>::iterator it;

    if(vertexToRemove==NULL){
        cout<<"The vertex to remove doesnt exist"<<endl;
        return false;
    }
    for (it = this->vertexSet.begin(); it != this->vertexSet.end(); it++){

        //The removal vertex
        if((*it)->info==in){
            break;
        }
    }
    //Remove
    if (it != vertexSet.end()) {
        for (Vertex<T>* vPtr : vertexSet)
            vPtr->removeEdgeTo(*it);
        delete (*it);
        vertexSet.erase(it);
        return true;
    }

    return false;
}

/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {

    vector<T> res;

    for (Vertex<T>* vPtr : vertexSet) {
        vPtr->visited = false;
    }

    for (Vertex<T>* vPtr : vertexSet) {
        if (!vPtr->visited) {
            res.push_back(vPtr->info);
            dfsVisit(vPtr, res);
        }
    }

	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {

    if(v==NULL){
        cout<<"DFS vertix null"<<endl;
        return;
    }

    v->visited= true;
    for (Edge<T> edge : v->adj) {
        if (!edge.dest->visited) {
            res.push_back(edge.dest->info);
            dfsVisit(edge.dest, res);
        }
    }
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {

    queue<Vertex<T>*> queueTemp;
    vector<T> arrayRet;

    Vertex<T>* vertexAux=findVertex(source);

	if(vertexAux==NULL){
        return arrayRet;
	}

	for(Vertex<T>* vertex: this->vertexSet){
        vertex->visited=false;
	}

	vertexAux->visited= true;

	queueTemp.push(vertexAux);

	while(!queueTemp.empty()){

	    vertexAux=queueTemp.front();
	    queueTemp.pop();
        arrayRet.push_back(vertexAux->info);

        for(Edge<T> edg:vertexAux->adj){

	        if(edg.dest->visited==false){
                edg.dest->visited=true;
	            queueTemp.push(edg.dest);
	        }
	    }
	}
	return arrayRet;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {

    vector<T> res;
    queue<Vertex<T>*> queueTempNoIndegree;

	for(Vertex<T>* vertex:this->vertexSet){
        vertex->indegree=0;
	}

	for(Vertex<T>*vertex:this->vertexSet){

	    for(Edge<T> edge:vertex->adj){
	        edge.dest->indegree++;
	    }

	}

	for(Vertex<T>*vertex:this->vertexSet){
	    if(vertex->indegree==0)
	        queueTempNoIndegree.push(vertex);
	}

	while(!queueTempNoIndegree.empty()){
        Vertex<T>*vertex=queueTempNoIndegree.front();
        queueTempNoIndegree.pop();
        res.push_back(vertex->info);

        for(Edge<T> edge:vertex->adj){

            Vertex<T>*dest=edge.dest;

            //Subtract before test if becomes an indegree 0 vertex
            if(dest->indegree>0){
                dest->indegree--;
            }

            if(dest->indegree==0)
                queueTempNoIndegree.push(dest);
        }
	}

	if(res.size()!=this->vertexSet.size()){
	    cout<<"Graph is not a DAG. Cannot order Topologicaly"<<endl;
	    //Erase the vector
	    res.clear();
	    return res;
	}

	return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	// TODO (28 lines, mostly reused)
	return 0;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
	// TODO (9 lines, mostly reused)
	// HINT: use the auxiliary field "processing" to mark the vertices in the stack.
	return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	// TODO (12 lines, mostly reused)
	return true;
}

#endif /* GRAPH_H_ */
