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
    long fallos=0;
    char linea;

    unsigned t0,  t1;
    t0=clock();
    //LEER EL DATASET CARACTER A CARACTER
    linea=cin.get();
    estado = memoria.procesar(linea, &secuencia); //ASOCIATIVA O POR CONJUNTOS
    //estado = memoria.procesar(linea); //CORRESPONDENCIA DIRECTA
    if(!estado){
        //PREBUSQUEDA DEL SIGUIENTE ELEMENTO (SI EL ACTUAL ES UN FALLO)
        linea=cin.get();
        if (linea != ',' && linea != '\n'){
            estado = memoria.procesar(linea, &secuencia); //ASOCIATIVA O POR CONJUNTOS
            //estado = memoria.procesar(linea); //CORRESPONDENCIA DIRECTA
        }

    }
    while(linea!=EOF){

        linea = cin.get();
        if (linea != '\n' && linea != ','){
            estado = memoria.procesar(linea, &secuencia); //ASOCIATIVA O POR CONJUNTOS
            //estado = memoria.procesar(linea); //CORRESPONDENCIA DIRECTA
            if (!estado) {
                fallos++; //CONTAR FALLOS
                
                //PREBUSQUEDA DEL SIGUIENTE ELEMENTO (SI EL ACTUAL ES UN FALLO)
                linea=cin.get();
                if (linea != ',' && linea != '\n'){
                    n++;
                    estado = memoria.procesar(linea, &secuencia); //ASOCIATIVA O POR CONJUNTOS
                    //estado = memoria.procesar(linea); //CORRESPONDENCIA DIRECTA
                }
            }
            n++; //CONTAR ELEMENTOS PROCESADOS        
        }
    }
    double porcentaje = 100 -((fallos *100) / n); //PORCENTAJE DE ACIERTOS
    cout << "Fallos:" << fallos << endl; //NUMERO DE FALLOS
    cout << "Cantidad de elementos:" << n << endl; //NUMERO DE ELEMENTOS PROCESADOS
    cout << "Porcentaje de aciertos es de:" << porcentaje << "%"<<endl;

    t1 = clock();
    
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << endl << "Tiempo de ejecucion: " << time << endl; //TIEMPO DE EJECUCION

    return 0;
}