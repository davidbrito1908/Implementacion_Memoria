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
    int dimension=0,estado,n;


    // ---------NUEVO------------
    char *addr, *file_name; 
    int fd;
    struct stat file_st;
    char seekchar, newchar;
    //const char archivo = "fer2013.csv";

    //file_name = &archivo;

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
  
    for(size_t i = 0; i < file_st.st_size; i++) /* replace characters  */
    {
        if (addr[i] == seekchar) 
       (    addr[i] = newchar) ;
    } 
     
    //printf("\nfile contents after:\n%s \n", addr); /* write file contents after modification */
    /*ifstream file("fer2013.csv");
    if (!file.is_open()) {
        cerr << "Error" << endl;
        return 1;
    }


    string line;
    int row = 0;

    while (getline(file, line) && row < MAX_ROWS) {
        stringstream ss(line);
        string cell;
        int col = 0;
        while (getline(ss, cell, ',') && col < MAX_COLS) {
            datas[row][col] = cell;
            col++;
        }
        row++;
        dimension++;
    }
    file.close();*/
    int row=0;

    /*for (int i = 1; i < row; i++) {
        imagen act;
        act.construir(stoi(datas[i][0]), (datas[i][1]), datas[i][2]);
        imagenes[i]=act;

    }*/
    MemoriaCompletamenteAsociativa memoria;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();

    //cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    //cout << setfill('-') << setw(90) << "\n";
    

    n=0;
    string msg;
    int fallos=0,i;
    while(n < file_st.st_size){
        estado = memoria.verificarMemoria(addr[n], &secuencia);
        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
            fallos++; //CONTAR FALLOS
        }else{
            msg = "Acierto";
        }

        //PREBUSQUEDA DEL SIGUIENTE ELEMENTO
        if(n<file_st.st_size-1 && !estado){
            estado = memoria.verificarMemoria(addr[n+1], &secuencia);
        }

        //DATO A ESCRIBIR: MEMORIA[DATO] O '-' SI ESTA VACIO
        /*for (i = 0; i < memoria.getBloques(); i++){
            if (memoria.memoriaVisitados[0][i]>0){
                datos[0][i]="Memoria[" + to_string(memoria.memoria[0][i]) + "]";
            }else{
                datos[0][i]="-";
            }
        }*/
        //cout << setfill(' ') << setw(10) << imagenes[n].getEmocion() << setw(18) << msg << setw(15) << datos[0][0] << setw(15) << datos[0][1] << setw(15) << datos[0][2] << setw(15) << datos[0][3] << "\n";
        n++;
    }

    cout << "Fallos:" << fallos << endl;
    cout << "Cantidad de elementos:" << file_st.st_size << endl;
    cout << "Porcentaje de aciertos es de:" << ((file_st.st_size-fallos)*100) / file_st.st_size << "%";







    return 0;
}