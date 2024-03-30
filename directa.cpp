/* DAVID BRITO 30521360   */


#include <iostream>
#include <iomanip>
using namespace std;

class MemoriaCorrespondenciaDirecta{
    private:
        const static int bloques = 4;
        const static int palabras = 1;
    public:
        int memoriaDirecta[palabras][bloques];

        int getPalabras(){
            return this->palabras;
        }
        int getBloques(){
            return this->bloques;
        }

        void inicializarMemoria (){
            int i;
            for (i=0;i<this-> getBloques();i++){
                this-> memoriaDirecta[0][i]= -1;
            }    
        }

        void escribirEnBloque(int bloque, int palabra, int direccion){
            this-> memoriaDirecta[palabra][bloque] = direccion;
        }
        int determinarBloque (int direccion){
            return direccion % this-> getBloques();
        }

        int verificarBloque (int bloque, int direccion){
            int acierto;

            if (this-> memoriaDirecta[0][bloque] == direccion){
                acierto=1;
            }else{
                acierto=0;
            }

            this-> escribirEnBloque(bloque,0,direccion);

            return acierto;
        }
};



int main(){
    int fallos=0, i, direccion,bloque, estado;
    MemoriaCorrespondenciaDirecta memoria;
    string msg;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();

    cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    cout << setfill('-') << setw(90) << "\n";
    while(cin >> direccion){
        bloque = memoria.determinarBloque(direccion);
        estado = memoria.verificarBloque(bloque,direccion);

        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
            fallos++; //CONTAR FALLOS
        }else{
            msg = "Acierto";
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        for (i = 0; i < memoria.getBloques(); i++){
            if (memoria.memoriaDirecta[0][i]!=-1){
                datos[0][i]="Memoria[" + to_string(memoria.memoriaDirecta[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }
        // cout << setw(5) << direccion << setw(10) << msg << setw(15) << memoriaDirecta[0][0] << setw(15) << memoriaDirecta[0][1] << setw(15) << memoriaDirecta[0][2] << setw(15) << memoriaDirecta[0][3] << "\n";
        cout << setfill(' ') << setw(10) << direccion << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";

    }

    return 0;
}