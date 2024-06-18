#include <iostream>
using namespace std;

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
            int acierto=0,i=0;
            while(!acierto && i<this->palabras){
                if (this->memoria[i][bloque] == direccion){
                    acierto=1;
                }else{
                    acierto=0;
                }
                i++;

            }
            return acierto;
        }

};

class MemoriaCompletamenteAsociativa: public Memoria{
    public:

        int buscarLRUMemoria(){
            int i, indiceMenor=0;
            int menor = 999999;

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

