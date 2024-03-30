/* DAVID BRITO 30521360   */


#include <iostream>
#include <iomanip>
using namespace std;


const int bloques = 4;
const int palabras = 1;

int memoriaDirecta[palabras][bloques];

void inicializarMemoria (){
    int i;
    for (i=0;i<bloques;i++){
        memoriaDirecta[0][i]= -1;
    }    
}

void escribirEnBloque(int bloque, int palabra, int direccion){
    memoriaDirecta[palabra][bloque] = direccion;
}
int determinarBloque (int direccion){
    return direccion % bloques;
}

int verificarBloque (int bloque, int direccion){
    int acierto;

    if (memoriaDirecta[0][bloque] == direccion){
        acierto=1;
    }else{
        acierto=0;
    }

    escribirEnBloque(bloque,0,direccion);

    return acierto;
}



int main(){
    int fallos=0, i, direccion,bloque, estado;
    string msg;
    string datos[palabras][bloques];

    inicializarMemoria();

    cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    cout << setfill('-') << setw(90) << "\n";
    while(cin >> direccion){
        bloque = determinarBloque(direccion);
        estado = verificarBloque(bloque,direccion);

        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
            fallos++; //CONTAR FALLOS
        }else{
            msg = "Acierto";
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        for (i = 0; i < bloques; i++){
            if (memoriaDirecta[0][i]!=-1){
                datos[0][i]="Memoria[" + to_string(memoriaDirecta[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }
        // cout << setw(5) << direccion << setw(10) << msg << setw(15) << memoriaDirecta[0][0] << setw(15) << memoriaDirecta[0][1] << setw(15) << memoriaDirecta[0][2] << setw(15) << memoriaDirecta[0][3] << "\n";
        cout << setfill(' ') << setw(10) << direccion << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";

    }

    return 0;
}