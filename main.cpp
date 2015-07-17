#include "AFN.hpp"

int main()  {
    int i, j, X, Y, A, T, F, D;

    // leido en la AFN 
    ifstream fin("AFN.txt");

    fin >> N >> M; //Numero Total de estados, Numero de simbolos a usar

    AFNs = new AFN[N];
    fin >> F;
    for(i=0; i<F; i++)    {
        fin >> X;
        AFN_finalESTADOS.insert(X);
    }
    fin >> T;
    while(T--)   {
        fin >> X >> A >> Y;
        for(i=0; i<Y; i++)  {
            fin >> j;
            AFNs[X].transiciones[A][i] = j;
        }
    }
    fin.close();

    // construir el AFD correspondiente
    D = 1;
    AFDESTADOSs.push_back(new AFDESTADOS);
    AFDESTADOSs[0]->contieneAFNs[0] = 1;
    EpsilonCerradu(0, AFDESTADOSs[0]->contieneAFNs);
    for(j=0; j<N; j++)
        if(AFDESTADOSs[0]->contieneAFNs[j] == 1 && AFN_finalESTADOS.find(j) != AFN_finalESTADOS.end())  {
            AFDESTADOSs[0]->finalestado = true; AFD_finalESTADOS.push_back(0); break;
        }
    incompleteAFDESTADOSs.push(0);
    while(!incompleteAFDESTADOSs.empty()) {
        X = incompleteAFDESTADOSs.front(); incompleteAFDESTADOSs.pop();
        for(i=1; i<=M; i++)  {
            NFAmove(AFDESTADOSs[X]->contieneAFNs, i, AFDESTADOSs[X]->transiciones[i]);
            EpsilonCerradu(AFDESTADOSs[X]->transiciones[i], AFDESTADOSs[X]->transiciones[i]);
            for(j=0; j<D; j++)
                if(AFDESTADOSs[X]->transiciones[i] == AFDESTADOSs[j]->contieneAFNs)  {
                   AFDESTADOSs[X]->symbolictransiciones[i] = j;    break;
                }
            if(j == D)   {
                AFDESTADOSs[X]->symbolictransiciones[i] = D;
                AFDESTADOSs.push_back(new AFDESTADOS);
                AFDESTADOSs[D]->contieneAFNs = AFDESTADOSs[X]->transiciones[i];
                for(j=0; j<N; j++)
                    if(AFDESTADOSs[D]->contieneAFNs[j] == 1 && AFN_finalESTADOS.find(j) != AFN_finalESTADOS.end())  {
                        AFDESTADOSs[D]->finalestado = true; AFD_finalESTADOS.push_back(D); break;
                    }
                incompleteAFDESTADOSs.push(D);
                D++;
            }
        }
    }

    // escribir el correspondiente AFD
    ofstream fout("AFD.txt");
    fout << D << " " << M << "\n" << AFD_finalESTADOS.size();
    for(vector<int>::iterator it=AFD_finalESTADOS.begin(); it!=AFD_finalESTADOS.end(); it++)
        fout << " " << *it;
    fout << "\n";
    for(i=0; i<D; i++)  {
        for(j=1; j<=M; j++)
            fout << i << " " << j << " " << AFDESTADOSs[i]->symbolictransiciones[j] << "\n";
    }
    fout << "hola!";
    fout.close();
    cout<<"Programa de conversion de un Automata Finito No determinista(NFA) \n"<<endl;
    cout<<"A un Automata Finito Determista(AFD)"<<endl; 
	cout<<"Se genero un archivo AFD.txt con el automata convertido"<<endl;
    return 0;
}
