#include <iostream>
#include <cmath>
using namespace std;

class Memoria{
    protected:
        const static int bloques = 8;
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

        void escribirEnBloque(int bloque, int palabra, int etiqueta){
            this->memoria[palabra][bloque] = etiqueta;
        }

        int verificarBloque (int bloque, int etiqueta){
            int acierto=0,i=0;
            while(!acierto && i<this->palabras){
                if (this->memoria[i][bloque] == etiqueta){
                    acierto=1;
                }else{
                    acierto=0;
                }
                i++;

            }
            return acierto;
        }

        void descomponerBinario(int dato, int* etiqueta, int *bloque, int *palabra){
            int offsetBloques= log2(this->getBloques());
            int offsetPalabras = log2(this->getPalabras());
            *etiqueta = dato >> offsetBloques + offsetPalabras;
            *bloque = (dato >> offsetPalabras) % this->getBloques();
            *palabra = dato % this->getPalabras();
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
        void descomponerBinario(int dato, int* etiqueta, int *palabra){
            //int offsetBloques= log2(this->getBloques());
            int offsetPalabras = log2(this->getPalabras());
            *etiqueta = dato >> offsetPalabras;
            //*bloque = (dato >> offsetPalabras) % this->getBloques();
            *palabra = dato % this->getPalabras();
        }

        int procesar(int dato, int *secuencia){
            int acierto=0, band = 0, etiqueta, palabra, i;
            this->descomponerBinario(dato, &etiqueta, &palabra);
            int bloques= this->bloques;
            i=0;
            while ( i< bloques && !band){
                if(this->memoriaVisitados[palabra][i] > 0){
                    if(this->verificarBloque(i, etiqueta)){
                        band=1;
                        acierto=1;
                        this-> memoriaVisitados[palabra][i] = *secuencia;
                    }
                }
                else{
                    acierto=0;
                    band=1;
                    this-> escribirEnBloque(i,palabra,etiqueta);
                    this-> memoriaVisitados[palabra][i] = *secuencia;
                }
                i++;
            }

            if (!band){
                int pos = LRU(bloques, palabra);
                this-> escribirEnBloque(pos,palabra,etiqueta);
                this-> memoriaVisitados[palabra][pos] = *secuencia;
            }
            *secuencia = *secuencia + 1;

            return acierto;
        }

        int LRU(int bloques, int palabra){
            int i, indiceMenor=0;
            int menor = this-> memoriaVisitados[palabra][0];

            for (i=0;i< bloques; i++){
                if (this-> memoriaVisitados[palabra][i] < menor){
                    menor = this-> memoriaVisitados[palabra][i];
                    indiceMenor=i;
                }
            }
            return (indiceMenor);
        }




};

class MemoriaAsociativaPorConjuntos: public Memoria{
    private:
        int vias = 2;
        int conjuntos = this->bloques / this->vias;

    public:
        int getConjuntos(){
            return this->conjuntos;
        }
        void setConjuntos(int cantidad){
            this->conjuntos = cantidad;
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


        void descomponerBinario(int dato, int* etiqueta, int *conjunto, int *palabra){
            int offsetConjuntos= log2(this->getConjuntos());
            int offsetPalabras = log2(this->getPalabras());
            *etiqueta = dato >> offsetConjuntos + offsetPalabras;
            *conjunto = (dato >> offsetPalabras) % this->getConjuntos();
            *palabra = dato % this->getPalabras();
        }

        int procesar(int dato, int *secuencia){
            int acierto=0, band = 0, etiqueta, conjunto, palabra, i;
            this->descomponerBinario(dato, &etiqueta, &conjunto, &palabra);
            int bloques= this->bloques / this->conjuntos;
            i=0;
            while ( i< bloques && !band){
                if(this->memoriaVisitados[palabra][bloques * conjunto + i] > 0){
                    if(this->verificarBloque(bloques * conjunto + i, etiqueta)){
                        band=1;
                        acierto=1;
                        this-> memoriaVisitados[palabra][bloques * conjunto + i] = *secuencia;
                    }
                }
                else{
                    acierto=0;
                    band=1;
                    this-> escribirEnBloque(bloques * conjunto + i,palabra,etiqueta);
                    this-> memoriaVisitados[palabra][bloques * conjunto + i] = *secuencia;
                }
                i++;
            }

            if (!band){
                int pos = LRU(conjunto, bloques, palabra);
                this-> escribirEnBloque(pos,palabra,etiqueta);
                this-> memoriaVisitados[palabra][pos] = *secuencia;
            }
            *secuencia = *secuencia + 1;

            return acierto;
        }

        int LRU(int conjunto, int bloques, int palabra){
            int i, indiceMenor=0;
            int menor = this-> memoriaVisitados[palabra][bloques * conjunto];

            for (i=0;i< bloques; i++){
                if (this-> memoriaVisitados[palabra][bloques * conjunto + i] < menor){
                    menor = this-> memoriaVisitados[palabra][bloques * conjunto + i];
                    indiceMenor=i;
                }
            }
            return (bloques * conjunto + indiceMenor);
        }

};

class MemoriaCorrespondenciaDirecta: public Memoria{

    public:
        int determinarBloque (int direccion){
            return direccion % this-> getBloques();
        }
        int procesar(int dato){
            int etiqueta,bloque,palabra, acierto;
            this->descomponerBinario(dato, &etiqueta, &bloque, &palabra);
            if (this-> memoria[palabra][bloque] == etiqueta){
                acierto = 1;
            }else{
                acierto = 0;
            }
            this->escribirEnBloque(bloque,palabra,etiqueta);

            return acierto;
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

