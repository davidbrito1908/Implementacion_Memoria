#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "memorias.cpp"
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
string data[MAX_ROWS][MAX_COLS];

int main(){
    int secuencia = 1;
    int dimension=0,estado,n;


    ifstream file("fer2013.csv");
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
            data[row][col] = cell;
            col++;
        }
        row++;
        dimension++;
    }
    file.close();

    for (int i = 1; i < row; i++) {
        imagen act;
        act.construir(stoi(data[i][0]), (data[i][1]), data[i][2]);
        imagenes[i]=act;

    }
    MemoriaCompletamenteAsociativa memoria;
    string datos[memoria.getPalabras()][memoria.getBloques()];

    memoria.inicializarMemoria();

    //cout << setw(10) << "Direccion" << setw(18) << "Acierto/Fallo" << setw(15) << "Bloque 0" << setw(15) << "Bloque 1" << setw(15) << "Bloque 2" << setw(15) << "Bloque 3" << "\n";
    //cout << setfill('-') << setw(90) << "\n";
    

    n=0;
    string msg;
    int fallos=0,i;
    while(n < dimension){
        estado = memoria.verificarMemoria(imagenes[n].getEmocion(), &secuencia);
        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
            fallos++; //CONTAR FALLOS
        }else{
            msg = "Acierto";
        }

        //PREBUSQUEDA DEL SIGUIENTE ELEMENTO
        if(n<dimension-1){
            estado = memoria.verificarMemoria(imagenes[n+1].getEmocion(), &secuencia);
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
    cout << "Cantidad de elementos:" << dimension << endl;
    cout << "Porcentaje de aciertos es de:" << ((dimension-fallos)*100) / dimension << "%";







    return 0;
}