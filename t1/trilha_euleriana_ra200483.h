#ifndef TRILHA_EULERIANA_RA200483_H
#define TRILHA_EULERIANA_RA200483_H
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include "grafo.h"

bool trilha_euleriana(int n,int m,Grafo g,int origem[],int destino[],int trilha[],string mensagem,int RA);
#endif