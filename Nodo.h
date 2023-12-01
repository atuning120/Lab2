#include <iostream>
using namespace std;
class Nodo{
    private:
    int puntuacion;
    int columna;

    public:
    Nodo(int,int);
    ~Nodo();
    void setPuntuacion(int);
    void setColumna(int);
    int getPuntuacion();
    int getColumna();
};
Nodo::Nodo(int column,int puntos){
    this->columna=column;
    this->puntuacion=puntos;
}
Nodo::~Nodo(){}
void Nodo::setPuntuacion(int puntos){
    this->puntuacion=puntos;
}
void Nodo::setColumna(int col){
    this->columna=col;
}
int Nodo::getColumna(){
    return this->columna;
}
int Nodo::getPuntuacion(){
    return this->puntuacion;
}
