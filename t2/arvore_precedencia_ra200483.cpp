#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "grafo.hpp"

//Estratégia gulosa:
// utilizando a estratégia gulosa para achar o menor distancia e achando o indice do próximo vertice
int menorDistancia(int dist[], bool sptSet[],Grafo g){
   
    int min = INT_MAX, min_index;
    for (int v = 0; v < g.V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
// função para printar a solução como desejado
void printSolution(int dist[],Grafo g){
    cout <<"Vertice \tDistancia do vertice ate a origem" << endl;
    for (int i = 0; i < g.V; i++)
        cout  << i << " \t\t"<<dist[i]<< endl;
}

// função para calcular a distancia de todos os vertices em relação ao vertice de origem que foi setado como 0
// utiliza da estrategia gulosa para escolher o proximo vertice que ele vai navegar para calcular a distancia
void dijkstraAdaptado(Grafo g, int origem, int dist[]){
    int v=0;
    int vertice_destino; // utilizado para calcular a distancia, sendo este o representante do vertice destino 
    int peso; // peso da aresta 
    list<pair<int, int> >:: iterator it;
    bool sptSet[g.V];
    // inicialização do sptSet (shortest path tree set)  e inicialização do vetor dist com valores infinitos
    for (int i = 0; i < g.V; i++){
        dist[i] = INT_MAX, sptSet[i] = false;    
    }
    dist[origem] = 0; // setando a distancia da origem até a origem como zero por default

    for (int count = 0; count < g.V - 1; count++) {
        // utilizando a solução gulosa para calcular o proximo vertice que sera percorrido para calcular a menor distancia distancia
        int u = menorDistancia(dist, sptSet,g); 
        sptSet[u] = true; // setar ele como visitado

        // interar pela lista de adjacencia
        for (auto it = g.adj[u].begin(); it!=g.adj[u].end(); it++){
            // como estamos utilizando uma tupla temos que pegar os dados como < aresta destino, peso da aresta> 
            vertice_destino= it->first;
            peso=it->second;

            // calculo da menor distância
            if (!sptSet[vertice_destino] && peso && dist[u] != INT_MAX&& dist[u] + peso < dist[vertice_destino]){
                dist[vertice_destino] = dist[u] + peso;
            }
            
        }
       
    }
    // função para printar a solução
    printSolution(dist,g);
}

// função para printar o grafo para verificar se está tudo correto com a leitura do grafo
// OBS: ESSA função não faz parte da solução ela só auxilia para o entendimento do codigo
void printGraph(Grafo g){
    int v,w;
    list<pair<int, int> >:: iterator it;
    for (int u = 0; u < g.V; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = g.adj[u].begin(); it!=g.adj[u].end(); it++){
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight ="
                 << w << "\n";
        }
        cout << "\n";
    }
}

bool arvore_precedencia(int n,int m,int w,Grafo g, string mensagem, int RA, int pred[],int dist[]){
    dijkstraAdaptado(g,0,dist);
    return true;
}