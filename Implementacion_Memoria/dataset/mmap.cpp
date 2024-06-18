#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "memorias.cpp"
//LIBRERIAS PARA MMAP
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main(){
    int secuencia = 1;
    int estado;

    char *addr, *file_name; 
    int fd;
    struct stat file_st;
    char seekchar, newchar;

    unsigned t0,  t1;
    t0=clock(); //INICIAR A MEDIR EL TIEMPO DE EJECUCION

    if( -1 == (fd = open("fer2013.csv", O_RDWR))) /* open file in read/write mode*/
    {
        perror("Error opened file \n");
        exit(1);
    }
  
    fstat(fd, &file_st); /* Load file status */
    
    addr = (char *)mmap(NULL,file_st.st_size, PROT_READ, MAP_SHARED, fd, 0); /* map file  */ //LECTURA CON MMAP
    if(addr == MAP_FAILED) /* check mapping successful */
    {
        perror("Error  mapping \n");
        exit(1);
    }

    //ESCOGER TIPO DE MEMORIA A UTILIZAR
    MemoriaCompletamenteAsociativa memoria;
    //MemoriaCorrespondenciaDirecta memoria;
    //MemoriaAsociativaPorConjuntos memoria;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();

    string msg;
    long fallos=0,elementos=0,n=0;
    int coma=0;
    //MIENTRAS NO SE LLEGUE AL TAMAÑO DEL ARCHIVO SE LEE EL CARACTER
    while(n < file_st.st_size){
        if ((addr[n] != ',') && (addr[n] != '\n')){
            estado = memoria.procesar(addr[n], &secuencia); //PARA MEMORIA ASOCIATIVA Y POR CONJUNTOS
            //estado = memoria.procesar(addr[n]);           //PARA CORRESPONDENCIA DIRECTA
            
            //SUMAR FALLO O ACIERTO
            if (!estado) {
                fallos++; //CONTAR FALLOS

                //PREBUSQUEDA DEL SIGUIENTE ELEMENTO (SI EL ELEMENTO ACTUAL PROVOCÓ UN FALLO)
                if(n < file_st.st_size-1){
                    if (addr[n+1] != ',' && addr[n+1]!='\n'){
                        estado = memoria.procesar(addr[n+1], &secuencia); //ASOCIATIVA Y POR CONJUNTOS
                        //estado = memoria.procesar(addr[n+1]); //CORRESPONDENCIA DIRECTA
                    }           
                }
            }
            elementos++; //NUMERO DE ELEMENTOS PROCESADOS
        }
        n++; //NUMERO TOTAL DE CARACTERES
    }
    //cout << "n =" << n << endl;
    double porcentaje = 100 -((fallos *100) / elementos); //PORCENTAJE DE ACIERTOS
    cout << "Fallos:" << fallos << endl; //CANTIDAD DE FALLOS
    cout << "Cantidad de elementos:" << elementos << endl; //CANTIDAD DE ELEMENTOS PROCESADOS
    cout << "Porcentaje de aciertos es de:" << porcentaje << "%";


    t1 = clock();
    
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << endl << "Tiempo de ejecucion: " << time << endl; // TIEMPO DE EJECUCION


    return 0;
}