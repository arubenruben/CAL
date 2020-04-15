#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
// TODO: Implement here exercise 1!
// ...
    GraphViewer *gv=new GraphViewer(600,600,true);

    //Definir background antes de criar a janela
    gv->setBackground("../resources/background.jpg");
    gv->createWindow(600,600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");


    gv->addNode(0);
    gv->addNode(1);
    gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
    gv->addEdge(1,0,1, EdgeType::DIRECTED);
    gv->removeNode(0);

    gv->addNode(2);

    gv->addEdge(2,0,2, EdgeType::DIRECTED);
    gv->setVertexLabel(2, "Isto nao e um no");
    gv->setEdgeLabel(2, "Isto e meia aresta");
    gv->setVertexColor(2, "green");
    gv->setEdgeColor(2, "yellow");
    //rearrange dá
    gv->rearrange();
}

void exercicio2()
{
// TODO: Implement here exercise 2!
// ...
    GraphViewer *gv = new GraphViewer(600, 600, false);

    gv->setBackground("../resources/background.jpg");
    gv->createWindow(600,600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");



    gv->addNode(0, 300, 50);
    gv->addNode(1, 318, 58);
    gv->addNode(2, 325, 75);
    gv->addNode(3, 318, 93);
    gv->addNode(4, 300, 100);
    gv->addNode(5, 282, 93);
    gv->addNode(6, 275, 75);
    gv->addNode(7, 282, 58);
    gv->addNode(8, 150, 200);
    gv->addNode(9, 300, 200);
    gv->addNode(10, 450, 200);
    gv->addNode(11, 300, 400);
    gv->addNode(12, 200, 550);
    gv->addNode(13, 400, 550);

    gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
    gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
    gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
    gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
    gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
    gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
    gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
    gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);
    gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
    gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
    gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
    gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
    gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
    gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);


    gv->rearrange();

    sleep(2);

    gv->removeNode(12);
    gv->removeNode(13);

    sleep(2);
    gv->rearrange();

    gv->addNode(14,250,550);
    gv->addNode(15,350,550);

    gv->addEdge(14, 11, 14, EdgeType::UNDIRECTED);
    gv->addEdge(15, 11, 15, EdgeType::UNDIRECTED);

    sleep(2);
    gv->rearrange();



}

void exercicio3()
{
// TODO: Implement here exercise 3!
// To read map files, use relative paths:
// Vertices data: "../resources/mapa1/nos.txt"
// Edges data: "../resources/mapa1/arestas.txt"
// ...

    ifstream infileVertex("../resources/mapa1/nos.txt");
    ifstream infileEdges("../resources/mapa1/arestas.txt");

    GraphViewer *gv = new GraphViewer(600, 600, false);

    gv->setBackground("../resources/background.jpg");
    gv->createWindow(600,600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    vector<string> tokens;
    string line;
    string token;


    while(getline(infileVertex,line)){

        stringstream lineStrStream(line);

        while (getline(lineStrStream,token,';')){
            tokens.push_back(token);
        }
        gv->addNode(atoi(tokens.at(0).c_str()),atoi(tokens.at(1).c_str()),atoi(tokens.at(2).c_str()));
        tokens.clear();
    }

    while(getline(infileVertex,line)){

        stringstream lineStrStream(line);

        while (getline(lineStrStream,token,';')){
            tokens.push_back(token);
        }
        gv->addEdge(atoi(tokens.at(0).c_str()),atoi(tokens.at(1).c_str()),atoi(tokens.at(2).c_str()),EdgeType::UNDIRECTED);
        tokens.clear();
    }

    gv->rearrange();


}

int main() {

    //exercicio1();
    //exercicio2();
    exercicio3();
    /*
     * Uncomment the line below to run Exercise 1

    exercicio1();

    /*
      * Uncomment the line below to run Exercise 2
      */
    //exercicio2();

    /*
      * Uncomment the line below to run Exercise 3
      */
	//
	//exercicio3();

	getchar();
	return 0;
}
