#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include "grafo.h"

//Lista global que eh usada para achar a trilha trilha_euleriana
// foi uma solucao para adicionar os valores na recursao
std::list<int> trilha_list;

// calculo do dfs normalization
// funcao usado para o calculo se o grafo é fortemente conectado
void DFS(Grafo g,int n,bool verticeVisitados[]){
    verticeVisitados[n]=true;
    list<int>:: iterator it;
    for(it=g.vizinhos[n].begin();it!=g.vizinhos[n].end();++it){
      
        if(!verticeVisitados[*it]){
            DFS(g,*it,verticeVisitados);
        }
    }
}
// funcao auxiliar para calcular o grafo transposto -> usado na funcao para calcular se o grafo eh fortemente 
// conectado
Grafo grafoTransposto(Grafo g,int n){
    Grafo gtrans(g.M,g.V);
    list<int>:: iterator it;
    for(int i=0;i<g.V;i++){
        for(it=g.vizinhos[i].begin();it!=g.vizinhos[i].end();++it){
            gtrans.vizinhos[*it].push_back(i);
            (gtrans.grauDeEntrada[i])++;
        }
    }
    return gtrans;
}
// função que checa se o grafo é fortemente conectado
bool isStrongConnected(Grafo g,int n){
    bool verticeVisitados[n];
    for(int i=0;i<n;i++){
        verticeVisitados[i]=false;
    }
    for(int i=0;i<n;i++){
        if(g.vizinhos[i].size()==i){
            break;
        }
        DFS(g,i,verticeVisitados);
        
    }

    for (int i = 0; i < g.V; i++){
        if (g.vizinhos[i].size() > 0 && verticeVisitados[i] == false){
            return false;
         }
    }
    Grafo gtrans= grafoTransposto(g,n);
    bool verticeVisitadosTransposto[n];
    for(int i=0;i<n;i++){
        verticeVisitadosTransposto[i]=false;
    }
    for(int i=0;i<n;i++){
        DFS(gtrans,i,verticeVisitadosTransposto);
    }
    for (int i = 0; i < g.V; i++){
        if (gtrans.vizinhos[i].size() > 0 && verticeVisitadosTransposto[i] == false){
            return false;
         }
    }
    
    return true;
}
// funcao para calcular o primeiro elemento que iniciará a trilha euleriana
int acha_vertice_de_comeco(Grafo g){
    list<int>:: iterator it;
    // retorna se o começo for unico
    int start;
    for(int i=0;i<g.V;i++){
        if(g.vizinhos[i].size()-g.grauDeEntrada[i]==1){
            return i;
        }
        if(g.vizinhos[i].size()>0){
            start=g.vizinhos[i].size();
        }

    }
    //retorna zero por default
    return start;
}
// calcula os graude de entrada e saida para cada vertice do grafo e coloca eles nas respectivas ordens em um vetor
// usado para facilitar as contas na hora de calcular o caminho euleriano
void calcular_grau_de_entrada_e_saida_de_cada_vertice(int vin[],int vout[],Grafo g){
    for(int i=0; i <g.V;i++){
        vout[i] = g.vizinhos[i].size();
        vin[i]=g.grauDeEntrada[i];

    }
}
// funcao auxiliar para obter um elemento na lista de adjacencia
int get_element_on_list(Grafo g,int index,int position){
    list<int>:: iterator it=g.vizinhos[index].begin();
     for(int i=0;i<position;i++){
        ++it;
     }
     return *it;
}

// calcula a trilha euleriana
void dfs_modify(Grafo g,int start,int vout[],int vin[]){
    int next_vertice;
    int vertice_start=start;
    while(vout[start]!=0){
        vout[start]=vout[start]-1;
        int position=vout[start];
        next_vertice=get_element_on_list(g,vertice_start,position);
        dfs_modify(g,next_vertice,vout,vin);       
    }
    trilha_list.push_back(start);
}
// insere os valores nos vetores iniciais
void insert_trilha(list<int> trilhaLista,int origem[],int destino[],int trilha[]){
    int i=0;
    int j=0;
    int last;
    for(auto v : trilhaLista){
        if(i==0){
            last=v;
            origem[i]=v;
            trilha[i]=i;
            i++;
        }else{
            origem[i]=v;
            trilha[i]=i;
            destino[j]=v;
            i++;
            j++;
        }
    }
    destino[j]=last;
}
// printa a trilha
void print_trilha(int origem[],int destino[],int trilha[]){
   // irá printar a seguinte ordem : Indice aresta da trilha - Origem[i]  - destino[i]
    for(int i=0;i<trilha_list.size();i++){
        cout<<trilha[i]<<" "<<origem[i]<< " "<< destino[i];
        cout<<"\n";
    }
}



bool trilha_euleriana(int n,int m,Grafo g,int origem[],int destino[],int trilha[],string mensagem,int RA){
    
    // PRIMEIRA CONDICAO: checa se o grau de entrada é diferente do grau de saida
    for(int i=0;i<g.V;i++){
        if(g.vizinhos[i].size()!=g.grauDeEntrada[i]){
            mensagem+="Erro: Existe vertice inviavel\n";
            cout<<mensagem;
            return false;
        }
    }
    
    // SEGUNDA CONDICAO: checa g é fortemente conexo
    if(isStrongConnected(g,n)== false){
        mensagem+="Erro:Grafo nao eh fortemente conexo\n";
        cout<<mensagem;
        return false;
    }
  
  

    // para facilitar as manipulações colocar em dois vetores 
    // os graus de entrada e saida se de cada vertice
    int vin[g.V];
    int vout[g.V];
    calcular_grau_de_entrada_e_saida_de_cada_vertice(vin,vout, g);


    //Agora que sabemos que existe um caminho euleriano é necessário calcular a
    // origem destino e da trilha em si
    origem[0]=acha_vertice_de_comeco(g);
    int start=origem[0];
    dfs_modify(g,start,vout,vin);
    trilha_list.reverse();
    trilha_list.pop_back();
    insert_trilha(trilha_list,origem,destino,trilha);
    print_trilha(origem,destino,trilha);


    return true;
}


    

