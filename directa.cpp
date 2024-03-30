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
    inicializarMemoria();

    cout << setw(5) << "dir" << setw(5) << "A/F" << setw(5) << "B0" << setw(5) << "B1" << setw(5) << "B2" << setw(5) << "B3" << "\n";
    while(cin >> direccion){
        bloque = determinarBloque(direccion);
        estado = verificarBloque(bloque,direccion);

        if (!estado) {
            msg = "F";
            fallos++;
        }else{
            msg = "A";
        }
        cout << setw(5) << direccion << setw(5) << msg << setw(5) << memoriaDirecta[0][0] << setw(5) << memoriaDirecta[0][1] << setw(5) << memoriaDirecta[0][2] << setw(5) << memoriaDirecta[0][3] << "\n";
    }

    return 0;
}