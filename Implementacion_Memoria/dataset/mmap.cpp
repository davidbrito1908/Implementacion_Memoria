#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "memorias.cpp"

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;


const int MAX_ROWS = 36000;
const int MAX_COLS = 3;

class imagen{
    private:
        int emocion;
        string data,uso;

    public:
        void construir(int e, string data, string uso){
            this->emocion = e;
            this->data=data;
            this->uso=uso;
        }

        int getEmocion(){
            return this-> emocion;
        }
        string getUso(){
            return this-> uso;
        }
};

imagen imagenes[MAX_ROWS];
string datas[MAX_ROWS][MAX_COLS];

int main(){
    int secuencia = 1;
    int dimension=0,estado;


    // ---------NUEVO------------
    char *addr, *file_name; 
    int fd;
    struct stat file_st;
    char seekchar, newchar;
    //const char archivo = "fer2013.csv";

    //file_name = &archivo;
    unsigned t0,  t1;
    t0=clock();

//if( -1 == (fd = open(file_name, O_RDWR))) /* open file in read/write mode*/
    if( -1 == (fd = open("fer2013.csv", O_RDWR))) /* open file in read/write mode*/
    {
        perror("Error opened file \n");
        exit(1);
    }
  
    fstat(fd, &file_st); /* Load file status */
  
    addr = (char *)mmap(NULL,file_st.st_size, PROT_WRITE, MAP_SHARED, fd, 0); /* map file  */
    if(addr == MAP_FAILED) /* check mapping successful */
    {
        perror("Error  mapping \n");
        exit(1);
    }

    //printf("\nfile contents before:\n%s \n", addr); /* write current file contents */
  
    //for(size_t i = 0; i < file_st.st_size; i++) /* replace characters  */
    /*{
        if (addr[i] == seekchar) 
       (    addr[i] = newchar) ;
    }
    */
     
 
    int row=0;

    MemoriaCompletamenteAsociativa memoria;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();

    //cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    //cout << setfill('-') << setw(90) << "\n";
    


    string msg;
    long fallos=0,elementos=0,n=0;
    int band=0;
    while(!band && n<file_st.st_size){
        band= addr[n] == '\n';
        n++;
    }
    while(n < file_st.st_size){
        if ((addr[n] != ',') && (addr[n] != '\n')){
            estado = memoria.procesar(addr[n], &secuencia);
            //MENSAJE FALLO O ACIERTO
            if (!estado) {
                msg = "Fallo";
                fallos++; //CONTAR FALLOS
            }else{
                msg = "Acierto";
            }

            //PREBUSQUEDA DEL SIGUIENTE ELEMENTO
            if(n<file_st.st_size-1 && !estado){
                estado = memoria.procesar(addr[n+1], &secuencia);
            }
            elementos++;
        }
        n++;
    }
    cout << "n =====" << n << endl;
    double porcentaje = 100 -((fallos *100) / elementos);
    cout << "Fallos:" << fallos << endl;
    cout << "Cantidad de elementos:" << elementos << endl;
    cout << "Porcentaje de aciertos es de:" << porcentaje << "%";


    t1 = clock();
    
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;




    return 0;
}