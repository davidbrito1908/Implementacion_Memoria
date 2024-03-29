/* DAVID BRITO 30521360   */

#include <iostream>
using namespace std;


const int bloques = 4;
const int palabras = 1;

int memoria[palabras][bloques];
int memoriaVisitados[palabras][bloques];

void inicializarMemoria (){
    int i;
    for (i=0;i<bloques;i++){
        memoria[0][i]= -1;
        memoriaVisitados[0][i]= 0;
    }    
}

void escribirEnBloque(int bloque, int palabra, int direccion){
    memoria[palabra][bloque] = direccion;
}

int verificarBloque (int bloque, int direccion){
    int acierto;

    if (memoria[0][bloque] == direccion){
        acierto=1;
    }else{
        acierto=0;
    }
    return acierto;
}

int buscarLRUMemoria(){
    int i, indiceMenor=0;
    int menor = 500;

    for (i=0;i< bloques; i++){
        if (memoriaVisitados[0][i] < menor){
            menor = memoriaVisitados[0][i];
            indiceMenor=i;
        }
    }
    return (indiceMenor);
}

int verificarMemoria (int direccion, int *secuencia){
    int acierto=0,i=0, band=0;
    int bloqueSeleccionado;


    while(i < bloques && !band){
        if (memoriaVisitados[0][i] > 0){
            if (verificarBloque(i, direccion)){
                band=1;
                acierto=1;
                memoriaVisitados[0][i] = *secuencia;
            }
        }else{
            acierto=0;
            band=1;
            escribirEnBloque(i,0,direccion);
            memoriaVisitados[0][i] = *secuencia;
        }
        i++;
    }
    if (!band){
        bloqueSeleccionado = buscarLRUMemoria();
        escribirEnBloque(bloqueSeleccionado,0,direccion);
        memoriaVisitados[0][bloqueSeleccionado] = *secuencia;
    }
    *secuencia = *secuencia + 1;

    return acierto;
}



int main(){
    int secuencia = 1;
    int fallos=0, i=0, direccion,estado;
    string msg;
    inicializarMemoria();

    while(cin >> direccion){

        estado = verificarMemoria(direccion, &secuencia);
        if (!estado) {
            msg = "Fallo";
            fallos++;
        }else{
            msg = "Acierto";
        }
        cout << direccion << "   " << msg << "   " << memoria[0][0] << "   " << memoria[0][1] << "   " << memoria[0][2] << "   " << memoria[0][3] << "\n";
    }

    return 0;
}