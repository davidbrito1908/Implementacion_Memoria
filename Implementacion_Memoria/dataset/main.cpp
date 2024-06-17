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
string datas[MAX_ROWS][MAX_COLS];

int main(){
    int secuencia = 1;
    int dimension=0,estado,n;

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
    file.close();

    for (int i = 1; i < row; i++) {
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
    string linea;
    //while(n < dimension){
    while(cin>>linea){
        //estado = memoria.procesar(imagenes[n].getEmocion(), &secuencia);
        estado = memoria.procesar((int)linea, &secuencia);
        //MENSAJE FALLO O ACIERTO
        if (!estado) {
            msg = "Fallo";
            fallos++; //CONTAR FALLOS
        }else{
            msg = "Acierto";
        }

        //PREBUSQUEDA DEL SIGUIENTE ELEMENTO
        /*if(n<dimension-1){
            estado = memoria.procesar(imagenes[n+1].getEmocion(), &secuencia);
        }*/
        n++;
    }

    cout << "Fallos:" << fallos << endl;
    cout << "Cantidad de elementos:" << dimension << endl;
    cout << "Porcentaje de aciertos es de:" << ((dimension-fallos)*100) / dimension << "%";







    return 0;
}