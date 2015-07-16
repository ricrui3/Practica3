#ifndef __AFN_HPP__
#define __AFN_HPP__

#include <cstdio>
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <set>
#define MAX_AFN_ESTADOS 10
#define MAX_SIMBOLOS_SIZE 10
using namespace std;

// Representacion de un estado AFN
class AFN {
    public:
        int transiciones[MAX_SIMBOLOS_SIZE][MAX_AFN_ESTADOS];
        AFN()  {
            for(int i=0; i<MAX_SIMBOLOS_SIZE; i++)
                for(int j=0; j<MAX_AFN_ESTADOS; j++)
                    transiciones[i][j] = -1;
        }
} *AFNs;

// Representacion de un estado AFD
struct AFDESTADOS {
    bool finalestado;
    bitset<MAX_AFN_ESTADOS> contieneAFNs;
    bitset<MAX_AFN_ESTADOS> transiciones[MAX_SIMBOLOS_SIZE];
    int symbolictransiciones[MAX_SIMBOLOS_SIZE];
};

set <int> AFN_finalESTADOS;
vector <int> AFD_finalESTADOS;
vector <AFDESTADOS*> AFDESTADOSs;
queue <int> incompleteAFDESTADOSs;
int N, M;   //N - > Numero de ESTADOS , M -> Tamano del alfabeto de entrada


// encuentra el cierre épsilon del estado "estado" NFA y la almacena en el "cierre "
void EpsilonCerradu(int estado, bitset<MAX_AFN_ESTADOS> &cierre )    {
    for(int i=0; i<N && AFNs[estado].transiciones[0][i] != -1; i++)
        if(cierre[AFNs[estado].transiciones[0][i]] == 0)    {
            cierre[AFNs[estado].transiciones[0][i]] = 1;
            EpsilonCerradu(AFNs[estado].transiciones[0][i], cierre);
        }
}

// encuentra el cierre epsilon de un conjunto de NFA declara "estado" y lo almacena en el "cierre "
void EpsilonCerradu(bitset<MAX_AFN_ESTADOS> estado, bitset<MAX_AFN_ESTADOS> &cierre) {
    for(int i=0; i<N; i++)
        if(estado[i] == 1)
            EpsilonCerradu(i, cierre);
}

// devuelve un bit que representa el conjunto de eESTADOS del AFN podria estar en después de mover
// X de estado en símbolo de entrada A
void NFAmove(int X, int A, bitset<MAX_AFN_ESTADOS> &Y)   {
    for(int i=0; i<N && AFNs[X].transiciones[A][i] != -1; i++)
        Y[AFNs[X].transiciones[A][i]] = 1;
}

// devuelve un bit que representa el conjunto de eESTADOS del AFN podría estar en después de mover
// desde el conjunto de eESTADOS X en el símbolo de entrada A
void NFAmove(bitset<MAX_AFN_ESTADOS> X, int A, bitset<MAX_AFN_ESTADOS> &Y)   {
    for(int i=0; i<N; i++)
        if(X[i] == 1)
            NFAmove(i, A, Y);
}


#endif
