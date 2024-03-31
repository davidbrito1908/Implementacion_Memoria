/* DAVID BRITO 30521360    */
/* ANDRES GUBAIRA 31006669 */

#include <iostream>
#include <iomanip>
using namespace std;
#define N 100

class Memoria{
    protected:
        const static int bloques = 4;
        const static int palabras = 1;

    public:
        int memoria[palabras][bloques];
        int memoriaVisitados[palabras][bloques];

        int getPalabras(){
            return this->palabras;
        }
        int getBloques(){
            return this->bloques;
        }
        void inicializarMemoria (){
            int i;
            for (i=0;i<this->bloques;i++){
                this->memoria[0][i]= -1;
                this->memoriaVisitados[0][i]= 0;
            }    
        }

        void escribirEnBloque(int bloque, int palabra, int direccion){
            this->memoria[palabra][bloque] = direccion;
        }

        int verificarBloque (int bloque, int direccion){
            int acierto;

            if (this->memoria[0][bloque] == direccion){
                acierto=1;
            }else{
                acierto=0;
            }
            return acierto;
        }

};

class MemoriaCompletamenteAsociativa: public Memoria{
    public:

        int buscarLRUMemoria(){
            int i, indiceMenor=0;
            int menor = 500;

            for (i=0;i< this->getBloques(); i++){
                if (this-> memoriaVisitados[0][i] < menor){
                    menor = this-> memoriaVisitados[0][i];
                    indiceMenor=i;
                }
            }
            return (indiceMenor);
        }

        int verificarMemoria (int direccion, int *secuencia){
            int acierto=0,i=0, band=0;
            int bloqueSeleccionado;


            while(i < this->bloques && !band){
                if (this-> memoriaVisitados[0][i] > 0){
                    if (this->verificarBloque(i, direccion)){
                        band=1;
                        acierto=1;
                        this-> memoriaVisitados[0][i] = *secuencia;
                    }
                }else{
                    acierto=0;
                    band=1;
                    this->escribirEnBloque(i,0,direccion);
                    this-> memoriaVisitados[0][i] = *secuencia;
                }
                i++;
            }
            if (!band){
                bloqueSeleccionado = this-> buscarLRUMemoria();
                this-> escribirEnBloque(bloqueSeleccionado,0,direccion);
                this-> memoriaVisitados[0][bloqueSeleccionado] = *secuencia;
            }
            *secuencia = *secuencia + 1;

            return acierto;
        }

};

class MemoriaAsociativaPorConjuntos: public Memoria{
    private:
        int conjuntos = 2;

    public:
        int getConjuntos(){
            return this->conjuntos;
        }

        int determinarConjunto (int direccion){
            return direccion % this->getConjuntos();
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

class MemoriaCorrespondenciaDirecta: public Memoria{

    public:
        int determinarBloque (int direccion){
            return direccion % this-> getBloques();
        }

        int verificarBloque (int bloque, int direccion){
            int acierto;

            if (this-> memoria[0][bloque] == direccion){
                acierto=1;
            }else{
                acierto=0;
            }

            this-> escribirEnBloque(bloque,0,direccion);

            return acierto;
        }
};






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
        estado = memoria1.verificarMemoria(datosMemoria[j], &secuencia);
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
        bloque = memoria2.determinarBloque(datosMemoria[j]);
        estado = memoria2.verificarBloque(bloque,datosMemoria[j]);

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

        conjunto = memoria3.determinarConjunto(datosMemoria[j]);
        estado = memoria3.verificarConjunto(conjunto,datosMemoria[j], &secuencia);

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