/* DAVID BRITO 30521360   */


#include <iostream>
#include <iomanip>
using namespace std;

class MemoriaAsociativaPorConjuntos{
    private:
        const static int bloques = 4;
        const static int palabras = 1;
        int conjuntos = 2;

    public:
        int memoria[palabras][bloques];
        int memoriaVisitados[palabras][bloques];

         int getPalabras(){
            return this->palabras;
        }
        int getBloques(){
            return this->bloques;
        }
        int getConjuntos(){
            return this->conjuntos;
        }

        void inicializarMemoria (){
            int i;
            for (i=0;i<this->getBloques();i++){
                this-> memoria[0][i]= -1;
                this-> memoriaVisitados[0][i]= 0;
            }    
        }

        void escribirEnBloque(int bloque, int palabra, int direccion){
            this-> memoria[palabra][bloque] = direccion;
        }
        int determinarConjunto (int direccion){
            return direccion % this->getConjuntos();
        }

        int verificarBloque (int bloque, int direccion){
            int acierto;

            if (this-> memoria[0][bloque] == direccion){
                acierto=1;
            }else{
                acierto=0;
            }
            return acierto;
        }

        int buscarLRU(int conjunto){
            int i, indiceMenor=0;
            int menor = 500;

            for (i=0;i< this->bloques/this->conjuntos; i++){
                if (this-> memoriaVisitados[0][(this-> bloques/this-> conjuntos) * conjunto + i] < menor){
                    menor = this-> memoriaVisitados[0][(this-> bloques/this-> conjuntos) * conjunto + i];
                    indiceMenor=i;
                }
            }
            return (this-> bloques / this-> conjuntos * conjunto + indiceMenor);
        }

        int verificarConjunto (int conjunto, int direccion, int *secuencia){
            int acierto=0,i=0, band=0;
            int bloqueSeleccionado;


            while(i < this-> bloques / this-> conjuntos && !band){
                if (this-> memoriaVisitados[0][(this-> bloques/this-> conjuntos) * conjunto + i] > 0){
                    if (this-> verificarBloque((this-> bloques/this-> conjuntos) * conjunto + i, direccion)){
                        band=1;
                        acierto=1;
                        this-> memoriaVisitados[0][(this-> bloques/this-> conjuntos) * conjunto + i] = *secuencia;
                    }
                }else{
                    acierto=0;
                    band=1;
                    this-> escribirEnBloque((this-> bloques/this-> conjuntos) * conjunto + i,0,direccion);
                    this-> memoriaVisitados[0][(this-> bloques/this-> conjuntos) * conjunto + i] = *secuencia;
                }
                i++;
            }
            if (!band){
                bloqueSeleccionado = this-> buscarLRU(conjunto);
                this-> escribirEnBloque(bloqueSeleccionado,0,direccion);
                this-> memoriaVisitados[0][bloqueSeleccionado] = *secuencia;
            }
            *secuencia = *secuencia + 1;

            return acierto;
        }



};

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