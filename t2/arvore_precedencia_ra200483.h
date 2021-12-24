#ifndef ARVORE_PRECEDENCIA_RA200483_H
#define ARVORE_PRECEDENCIA_RA200483_H
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include "grafo.hpp"

bool arvore_precedencia(int n,int m,int w,Grafo g, string mensagem, int RA, int pred[],int dist[]);
#endif