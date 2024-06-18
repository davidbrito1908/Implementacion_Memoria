#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "memorias.cpp"
#include <ctime> 
using namespace std;


int main(){
    int secuencia = 1;
    int estado;

    //ESCOGER TIPO DE MEMORIA A UTTILIZAR
    MemoriaCompletamenteAsociativa memoria;
    //MemoriaAsociativaPorConjuntos memoria;
    //MemoriaCorrespondenciaDirecta memoria;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();
    
    long n=0;
    //string msg;
    long fallos=0,i;
    string linea;

    unsigned t0,  t1;
    t0=clock();
    //cin>>linea; //LEER PRIMERA LINEA
    //LEER EL DATASET LINEA A LINEA
    while(cin>>linea){
        int tam = linea.size();
        //RECORRER LA LINEA CARACTER A CARACTER
        for(i=0;i<tam;i++){
            if ((linea[i] != ',') && (linea[i]!= '\n')){

                estado = memoria.procesar(linea[i], &secuencia); //ASOCIATIVA O POR CONJUNTOS
                //estado = memoria.procesar(linea[i]); //CORRESPONDENCIA DIRECTA
                //SUMAR FALLO
                if (!estado) {
                    //msg = "Fallo";
                    fallos++; //CONTAR FALLOS
                }else{
                    //msg = "Acierto";
                }

                //PREBUSQUEDA DEL SIGUIENTE ELEMENTO (SI EL ACTUAL ES UN FALLO)
                if(i<tam-1 &!estado){
                    estado = memoria.procesar(linea[i+1], &secuencia);
                } 
                n++; //CONTAR ELEMENTOS PROCESADOS
            }
        }
    }

    double porcentaje =100 -((fallos *100) / n); //PORCENTAHE DE ACIERTOS
    cout << "Fallos:" << fallos << endl; //NUMERO DE FALLOS
    cout << "Cantidad de elementos:" << n << endl; //NUMERO DE ELEMENTOS PROCESADOS
    cout << "Porcentaje de aciertos es de:" << porcentaje << "%"<<endl;

    t1 = clock();
    
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << endl << "Tiempo de ejecucion: " << time << endl; //TIEMPO DE EJECUCION

    return 0;
}