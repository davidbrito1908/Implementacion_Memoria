/* DAVID BRITO 30521360    */
/* ANDRES GUBAIRA 31006669 */

#include <iostream>
#include <iomanip>
#include "memorias.cpp"
using namespace std;
#define N 100


int main(){

    int dato;
    int secuencia = 1;
    int dimension = 0, i=0, direccion,bloque,estado,conjunto;
    string msg;
    MemoriaCompletamenteAsociativa memoria1;
    MemoriaCorrespondenciaDirecta memoria2;
    MemoriaAsociativaPorConjuntos memoria3;

    memoria1.inicializarMemoria();
    memoria2.inicializarMemoria();
    memoria3.inicializarMemoria();
    string datos[memoria1.getPalabras()][memoria1.getBloques()];

    //LLENADO DEL VECTOR CON LAS DIRECCIONES DE MEMORIA
    int datosMemoria[N];
    while(cin >> dato){
        datosMemoria[dimension] = dato;
        dimension++;
    }

    //ESCRITURA DE LA MEMORIA COMPLETAMENTE ASOCIATIVA
    int j = 0;
    cout << "Memoria completamente asociativa\n";
    cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    cout << setfill('-') << setw(90) << "\n";
    while(j < dimension){
        estado = memoria1.procesar(datosMemoria[j], &secuencia);
        
        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
        }else{
            msg = "Acierto";
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        for (i = 0; i < memoria1.getBloques(); i++){
            if (memoria1.memoriaVisitados[0][i]>0){
                datos[0][i]="Memoria[" + to_string(memoria1.memoria[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }
        j++;
        cout << setfill(' ') << setw(10) << datosMemoria[j-1] << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";
    }

    //ESCRITURA DE LA MEMORIA POR CORRESPONDENCIA DIRECTA
    j = 0;
    cout << "\n \n \nMemoria por correspondencia directa\n";
    cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    cout << setfill('-') << setw(90) << "\n";
    while(j < dimension){
        estado = memoria2.procesar(datosMemoria[j]);

        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
        }else{
            msg = "Acierto";
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        for (i = 0; i < memoria2.getBloques(); i++){
            if (memoria2.memoria[0][i]!=-1){
                datos[0][i]="Memoria[" + to_string(memoria2.memoria[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }
        j++;
        cout << setfill(' ') << setw(10) << datosMemoria[j-1] << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";

    }

    //ESCRITURA DE LA MEMORIA ASOCIATIVA POR CONJUNTOS
    j = 0;
    cout << "\n \n \nMemoria asociativa por conjuntos\n";
    cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Conjunto 0" << setw(15) << "Conjunto 0" << setw(15) << "Conjunto 1" << setw(15) << "Conjunto 1" << "\n";
    cout << setfill('-') << setw(90) << "\n";
    while(j < dimension){
        estado = memoria3.procesar(datosMemoria[j], &secuencia);

        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
        }else{
            msg = "Acierto";
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        for (i = 0; i < memoria3.getBloques(); i++){
            if (memoria3.memoriaVisitados[0][i]>0){
                datos[0][i]="Memoria[" + to_string(memoria3.memoria[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }

        j++;
        cout << setfill(' ') << setw(10) << datosMemoria[j-1] << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";
    }

    return 0;
}
