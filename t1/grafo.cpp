#include "grafo.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


Grafo::Grafo(int V, int M){
	this->V = V; 
    this->M = M;
	vizinhos = new list<int>[V]; 
	grauDeEntrada = new int[V];
	for (int i = 0; i < V; i++)
	grauDeEntrada[i] = 0;

}
void Grafo::adicionarAresta(int v1, int v2){
	vizinhos[v1].push_back(v2);
	(grauDeEntrada[v2])++;
}

bool Grafo::existeAresta(int v1, int v2){
	if(find(vizinhos[v1].begin(), vizinhos[v1].end(), v2) != vizinhos[v1].end())
		return true;
	return false;
}

