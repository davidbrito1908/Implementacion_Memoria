/* DAVID BRITO 30521360   */


#include <iostream>
#include <iomanip>
#include "memorias.cpp"
using namespace std;

int main(){
    int fallos=0, i, direccion,bloque, estado;
    MemoriaCorrespondenciaDirecta memoria;
    string msg;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();

    cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    cout << setfill('-') << setw(90) << "\n";
    while(cin >> direccion){
        estado = memoria.procesar(direccion);
        //bloque = memoria.determinarBloque(direccion);
        //estado = memoria.verificarBloque(bloque,direccion);

        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
            fallos++; //CONTAR FALLOS
        }else{
            msg = "Acierto";
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        for (i = 0; i < memoria.getBloques(); i++){
            if (memoria.memoria[0][i]!=-1){
                datos[0][i]="Memoria[" + to_string(memoria.memoria[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }
        // cout << setw(5) << direccion << setw(10) << msg << setw(15) << memoriaDirecta[0][0] << setw(15) << memoriaDirecta[0][1] << setw(15) << memoriaDirecta[0][2] << setw(15) << memoriaDirecta[0][3] << "\n";
        cout << setfill(' ') << setw(10) << direccion << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";

    }

    return 0;
}