/* DAVID BRITO 30521360   */


#include <iostream>
#include <iomanip>
using namespace std;


const int bloques = 4;
const int conjuntos = 2;
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
int determinarConjunto (int direccion){
    return direccion % conjuntos;
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

int buscarLRU(int conjunto){
    int i, indiceMenor=0;
    int menor = 500;

    for (i=0;i< bloques/conjuntos; i++){
        if (memoriaVisitados[0][(bloques/conjuntos) * conjunto + i] < menor){
            menor = memoriaVisitados[0][(bloques/conjuntos) * conjunto + i];
            indiceMenor=i;
        }
    }
    return (bloques / conjuntos * conjunto + indiceMenor);
}

int verificarConjunto (int conjunto, int direccion, int *secuencia){
    int acierto=0,i=0, band=0;
    int bloqueSeleccionado;


    while(i < bloques / conjuntos && !band){
        if (memoriaVisitados[0][(bloques/conjuntos) * conjunto + i] > 0){
            if (verificarBloque((bloques/conjuntos) * conjunto + i, direccion)){
                band=1;
                acierto=1;
                memoriaVisitados[0][(bloques/conjuntos) * conjunto + i] = *secuencia;
            }
        }else{
            acierto=0;
            band=1;
            escribirEnBloque((bloques/conjuntos) * conjunto + i,0,direccion);
            memoriaVisitados[0][(bloques/conjuntos) * conjunto + i] = *secuencia;
        }
        i++;
    }
    if (!band){
        bloqueSeleccionado = buscarLRU(conjunto);
        escribirEnBloque(bloqueSeleccionado,0,direccion);
        memoriaVisitados[0][bloqueSeleccionado] = *secuencia;
    }
    *secuencia = *secuencia + 1;

    return acierto;
}



int main(){
    int secuencia = 1;
    int fallos=0, i=0, direccion,conjunto, estado;
    string msg;
    string datos[palabras][bloques];

    inicializarMemoria();
    int elementos = bloques / conjuntos;

    cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Conjunto 0" << setw(15) << "Conjunto 0" << setw(15) << "Conjunto 1" << setw(15) << "Conjunto 1" << "\n";
    cout << setfill('-') << setw(90) << "\n";
    while(cin >> direccion){

        conjunto = determinarConjunto(direccion);
        estado = verificarConjunto(conjunto,direccion, &secuencia);

        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
            fallos++;
        }else{
            msg = "Acierto";
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        for (i = 0; i < bloques; i++){
            if (memoriaVisitados[0][i]>0){
                datos[0][i]="Memoria[" + to_string(memoria[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }

        // cout << setw(5) << direccion << setw(10) << msg << setw(15) << memoria[0][0] << setw(15) << memoria[0][1] << setw(15) << memoria[0][2] << setw(15) << memoria[0][3] << "\n";
        cout << setfill(' ') << setw(10) << direccion << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";

    }

    return 0;
}