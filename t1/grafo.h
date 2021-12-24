// this is the header file for class graph, this include a all function to construct the graph
#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Grafo{
    public:
        list<int> *vizinhos; // Lista contendo as arestas
        int V; // Quantidade de vértices
        int M; // Quantidade de arestas
        int *grauDeEntrada; //grau de entrada
        Grafo(int V, int M); 
        void adicionarAresta(int v1, int v2); 
        bool existeAresta(int v1, int v2); 
       
    };


#endif