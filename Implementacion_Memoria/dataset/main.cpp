#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "memorias.cpp"
#include <ctime> 
using namespace std;


int main(){
    int secuencia = 1;
    int dimension=0,estado;


    MemoriaCompletamenteAsociativa memoria;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();

    //cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    //cout << setfill('-') << setw(90) << "\n";
    
    
    long n=0;
    string msg;
    long fallos=0,i;
    string linea;
    //while(n < dimension){
    

    unsigned t0,  t1;
    
    t0=clock();
    cin>>linea; //LEER PRIMERA LINEA
    while(cin>>linea){
        //estado = memoria.procesar(imagenes[n].getEmocion(), &secuencia);
        int tam = linea.size();
        for(i=0;i<tam;i++){
            if ((linea[i] != ',') && (linea[i]!= '\n')){
                estado = memoria.procesar(linea[i], &secuencia);
                //estado = memoria.procesar(linea[i]);
                //MENSAJE FALLO O ACIERTO
                if (!estado) {
                    msg = "Fallo";
                    fallos++; //CONTAR FALLOS
                }else{
                    msg = "Acierto";
                }

                //PREBUSQUEDA DEL SIGUIENTE ELEMENTO
                if(i<tam-1 &!estado){
                    estado = memoria.procesar(linea[i+1], &secuencia);
                } 
                n++;
            }
        }
        //cout << "fin linea";
       
    }

    double porcentaje =100 -((fallos *100) / n);
    cout << "Fallos:" << fallos << endl;
    cout << "Cantidad de elementos:" << n << endl;
    cout << "Porcentaje de aciertos es de:" << porcentaje << "%"<<endl;

    t1 = clock();
    
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;







    return 0;
}