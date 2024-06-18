/* DAVID BRITO 30521360   */


#include <iostream>
#include <iomanip>
#include "memorias.cpp"
using namespace std;

int main(){
    int secuencia = 1;
    int fallos=0, i=0, direccion,conjunto, estado;
    MemoriaAsociativaPorConjuntos memoria;
    string msg;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();
    int elementos = memoria.getBloques() / memoria.getConjuntos();

    cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Conjunto 0" << setw(15) << "Conjunto 0" << setw(15) << "Conjunto 1" << setw(15) << "Conjunto 1" << "\n";
    cout << setfill('-') << setw(90) << "\n";
    while(cin >> direccion){

        conjunto = memoria.determinarConjunto(direccion);
        estado = memoria.verificarConjunto(conjunto,direccion, &secuencia);

        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
            fallos++;
        }else{
            msg = "Acierto";
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        for (i = 0; i < memoria.getBloques(); i++){
            if (memoria.memoriaVisitados[0][i]>0){
                datos[0][i]="Memoria[" + to_string(memoria.memoria[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }

        // cout << setw(5) << direccion << setw(10) << msg << setw(15) << memoria[0][0] << setw(15) << memoria[0][1] << setw(15) << memoria[0][2] << setw(15) << memoria[0][3] << "\n";
        cout << setfill(' ') << setw(10) << direccion << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";

    }

    return 0;
}