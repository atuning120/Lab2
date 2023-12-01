//Cristian Ignacio Nuñez Nuñez
//21.387.541-8
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <climits>
#include "Nodo.h"
using namespace std;
int menu();
int pedirDificultad();
void mostrarTrablero(vector<vector<int>>&);
bool turnoPlayer(vector<vector<int>>&);
void turnoMaquina(vector<vector<int>>&,int,bool);
bool verificarTableroLleno(vector<vector<int>>&);
int analizarVictoria(vector<vector<int>>&);
bool partida(vector<vector<int>>*,int,bool);
vector<vector<int>>* leerArchivoTablero();
void respaldarTablero(vector<vector<int>>,int,bool);
void limpiarTablero();
int obtenerDificultad();
bool obtenerPuntos();
void guardarPuntos(int,int);
Nodo* minimax(vector<vector<int>>,bool,int);
bool pedirPoda();
Nodo* minimaxSinPoda(vector<vector<int>>,bool,int);
bool leerPoda();
//Main
int main()
{   
    //Ficha jugador = -1 = O
    //Ficha cpu = 1 = x
    //Crear tablero de 6x7
    vector<vector<int>> *tablero= new vector(6,vector<int>(7));
    //Mostrar el menu inicial
    int menuu=menu();
    while(menuu!=4){
        //identificador de victoria
        int dificultad;
        //Nueva partida
        if(menuu==1){   
            tablero= new vector(6,vector<int>(7));
            cout<<"NUEVA PARTIDA"<<endl;
            bool poda=pedirPoda();
            dificultad= pedirDificultad();
            if(partida(tablero,dificultad,poda)==true){
                limpiarTablero();
                tablero= new vector(6,vector<int>(7));
            }
        //continuar partida guardada
        }else if(menuu==2){
            tablero=leerArchivoTablero();
            if(tablero!=NULL){
                dificultad=obtenerDificultad();
                if(partida(tablero,dificultad,leerPoda())==true){
                    limpiarTablero();
                    tablero= new vector(6,vector<int>(7));
                }   
            }
        //Ver puntuacion
        }else if(menuu==3){
            cout<<"Ver puntuacion: "<<endl;
            obtenerPuntos();
        }
        menuu=menu();
    }
    //Salir del juego
    cout<<endl<<"Saliste del juego";
    return 0;
}
//Menu inicial
int menu(){ 
    int opcion=0;
    cout<<"*****Menu*****"<<endl;
    cout<<"1. nueva partida"<<endl;
    cout<<"2. continuar partida guardada"<<endl;
    cout<<"3. ver puntuacion"<<endl;
    cout<<"4. salir"<<endl;
    cout<<"****************"<<endl;
    cout<<"Opcion: ";
    cin>>opcion;
    while(opcion<1 || opcion>4){
        system("cls");
        cout<<"Error. dato invalido"<<endl;
        cout<<"*****Menu*****"<<endl;
        cout<<"1. nueva partida"<<endl;
        cout<<"2. continuar partida"<<endl;
        cout<<"3. ver puntuacion"<<endl;
        cout<<"4. salir"<<endl;
        cout<<"****************"<<endl;
        cout<<"Opcion: ";
        cin>>opcion;
    }
    return opcion;
}
//Pedir dificultad
int pedirDificultad(){
    int opcion=0;
    cout<<endl<<"*****dificultades*****"<<endl;
    cout<<"1. facil"<<endl;
    cout<<"2. medio"<<endl;
    cout<<"3. dificil"<<endl;
    cout<<"****************"<<endl;
    cout<<"Opcion: ";
    cin>>opcion;
    while(opcion<1 || opcion>3){
        system("cls");
        cout<<"Error. dato invalido"<<endl;
        cout<<"*****dificultades*****"<<endl;
        cout<<"1. facil"<<endl;
        cout<<"2. medio"<<endl;
        cout<<"3. dificil"<<endl;
        cout<<"****************"<<endl;
        cout<<"Opcion: ";
        cin>>opcion;   
    }
    return opcion;
}
//Mostrar Tablero
void mostrarTrablero(vector<vector<int>> &tablero){
    for(int i=0;i<tablero.size();i++){
        for(int j=0;j<tablero[1].size();j++){
            if(tablero[i][j]==0){
                cout<<"* ";
            }else if(tablero[i][j]==-1){
                cout<<"O ";
            }else if(tablero[i][j]==1){
                cout<<"x ";
            }
        }
        cout<<endl;
    }
    cout<<"-------------"<<endl;
    for(int i=0;i<7;i++){
        cout<<(i+1)<<" ";
    }
    cout<<endl<<endl;
}
//Turono del juegador
bool turnoPlayer(vector<vector<int>> &tablero){
    int opcion;
    cout<<"Ingesa la columna(9 para salir): ";
    cin>>opcion;
    //Control de errores
    if(opcion ==9){
        return false;
    }
    while(opcion<1 || opcion>7 || tablero[0][opcion-1]!=0){
        if(opcion==9){
            return false;
        }
        cout<<"Error, opcion invalida...";
        cout<<"Ingesa la columna(9 para salir): ";
        cin>>opcion;
    }
    int n;
    for(int i=5;i>=0;i--){
        if(tablero[i][(opcion-1)]==0){
            n=i;
            break;
        }
    }
    tablero[n][(opcion-1)]=-1;
    return true;
}
//Turno maquina
void turnoMaquina(vector<vector<int>> &tablero, int dificultad, bool poda){
    Nodo* mejorJugada;
    //Con poda
    if(poda==true){
        //Nivel facil
        if(dificultad==1){
            mejorJugada=minimax(tablero,false,2);
        //nivel medio
        }else if(dificultad==2){
            mejorJugada=minimax(tablero,true,4);
        //nivel dificil
        }else if(dificultad==3){
            mejorJugada=minimax(tablero,true,6);
        }
    //Sin poda
    }else if(poda==false){
        //Nivel facil
        if(dificultad==1){
            mejorJugada=minimaxSinPoda(tablero,false,2);
        //nivel medio
        }else if(dificultad==2){
            mejorJugada=minimaxSinPoda(tablero,true,4);
        //nivel dificil
        }else if(dificultad==3){
            mejorJugada=minimaxSinPoda(tablero,true,6);
        }
    }
    //realizar la jugada
    int columna=mejorJugada->getColumna();
    int fila;
    for(int i=5;i>=0;i--){
        if(tablero[i][columna]==0){
            fila=i;
            break;
        }
    }
    tablero[fila][columna]=1;
}
//Verificar si el tablero está lleno
bool verificarTableroLleno(vector<vector<int>> &tablero){
    int n=0;
    for(int i=0;i<7;i++){
        if(tablero[0][i]!=0){
            n++;
        }
    }
    if(n==7){
        return true;
    }
    return false;
}
//Analizar si alguna entidad gana
int analizarVictoria(vector<vector<int>>& tablero){
    //Verificar quien gana en el plano horizontal
    for(int i=0;i<6;i++){ 
        for(int j=0;j<4;j++){
            vector<int> cuatro={tablero[i][j],tablero[i][j+1],tablero[i][j+2],tablero[i][j+3]};
            int ganador=0;
            for(int a=0;a<cuatro.size();a++){
                ganador+=cuatro[a];
            }
            //si hay 4 piezas seguidas del player, entonces gana el player
            if(ganador==-4){
                return -1;

            //Si hay 4 piezas seguidas de la cpu, entonces gana la cpu
            }else if(ganador==4){
                return 1;
            }
        }
    }
    //Verificar quien gana en el plano vertical
    for(int i=0;i<7;i++){
        for(int j=0;j<3;j++){
            vector<int> cuatro={tablero[j][i],tablero[j+1][i],tablero[j+2][i],tablero[j+3][i]};
            int ganador=0;
            for(int a=0;a<cuatro.size();a++){
                ganador+=cuatro[a];
            }
            //si hay 4 piezas seguidas del player, entonces gana el player
            if(ganador==-4){
                return -1;
            //Si hay 4 piezas seguidas de la cpu, entonces gana la cpu
            }else if(ganador==4){
                return 1;
            }
        }
    }
    //Verificar quien gana en el plano diagonal
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            //diagonal decreciante
            vector<int> decreciente={tablero[i][j],tablero[i+1][j+1],tablero[i+2][j+2],tablero[i+3][j+3]};
            int valorD=0;
            for(int a=0;a<decreciente.size();a++){
                valorD+=decreciente[a];
            }
            //diagonal creciente
            vector<int> creciente={tablero[i+3][j],tablero[i+2][j+1],tablero[i+1][j+2],tablero[i][j+3]};
            int valorC=0;
            for(int a=0;a<creciente.size();a++){
                valorC+=creciente[a];
            }
            //verificar victoria
            if(valorC==4 || valorD==4){
                return 1;
            }else if(valorC==-4 || valorD==-4){
                return -1;
            }
        }
    }
    return 0;
} 
//Partida
bool partida(vector<vector<int>>*tablero,int dificultad,bool poda){
    int victoria;
    mostrarTrablero(*tablero);
    while(true){
        //Turno del jugador
        if(turnoPlayer(*tablero)==false){
            return false;
        }
        victoria= analizarVictoria(*tablero);
        if(victoria==-1){
            mostrarTrablero(*tablero);
            cout<<"Gano el Player"<<endl;
            guardarPuntos(-1,dificultad);
            return true;
        }
        if(verificarTableroLleno(*tablero)){
            mostrarTrablero(*tablero);
            cout<<"Emplate"<<endl;
            guardarPuntos(0,dificultad);
            return true;
        }
        //Turno de la maquina
        turnoMaquina(*tablero,dificultad,poda);
        victoria= analizarVictoria(*tablero);
        if(victoria==1){
            mostrarTrablero(*tablero);
            cout<<"Gano la CPU"<<endl;
            guardarPuntos(1,dificultad);
            return true;
        }
        if(verificarTableroLleno(*tablero)){
            mostrarTrablero(*tablero);
            cout<<"Empate"<<endl;
            guardarPuntos(0,dificultad);
            return true;
        }
        mostrarTrablero(*tablero);
        respaldarTablero(*tablero,dificultad,poda);
    }
    return true;
}
//ver si hay un tablero guardado
vector<vector<int>>* leerArchivoTablero(){
    vector<vector<int>> *tabla= new vector<vector<int>>;
    //leer el archivo
    ifstream archivo;
    archivo.open("tablero.csv",ios::in);
    char delimitador=';';
    string linea;
    //Control de apertura del archivo
    if(!archivo.is_open()){
        cout<<"El archivo del tablero no fue encontrado"<<endl;
        return NULL;
    }
    for(int i=0;i<6;i++){
        //leer lineas
        getline(archivo,linea);
        stringstream registro(linea);
        //control de errores e inconsistencias del tablero
        if(linea.empty()){
            cout<<"No se encontro la partida guardada\n(Solo se guardan las partidas que se dejan a la mitad del, las partidas finalizadas no se guardan)"<<endl;
            return NULL;
        }
        vector<string> partes;
        for(string dato;getline(registro,dato,';');){
            partes.push_back(dato);
        }   
        vector<int> fila; 
        //Armando el tablero que estaba guardado
        for(int m=0;m<partes.size();m++){
            if(partes[m]=="0"){
                fila.push_back(0);
            }else if(partes[m]=="1"){
                fila.push_back(1);
            }else if(partes[m]=="-1"){
                fila.push_back(-1);
            }
        }
        tabla->push_back(fila);                                            
    }
    archivo.close();
    //retornar el tablero guardado
    return tabla;
}
//Guardar la informacion en los archivos csv
void respaldarTablero(vector<vector<int>>tablero,int dificultad,bool poda){
    int podaa;
    if(poda==true){
        podaa=1;
    }else if(poda==false){
        podaa=2;
    }
    ofstream archivo("tablero.csv",ios::trunc);
    for(int i=0;i<6;i++){
        archivo<<tablero[i][0]<<";"<<tablero[i][1]<<";"<<tablero[i][2]<<";"<<tablero[i][3]<<";"<<tablero[i][4]<<";"<<tablero[i][5]<<";"<<tablero[i][6]<<"\n";
    }
    archivo<<dificultad<<"\n";
    archivo<<podaa;
    archivo.close(); 
}
//Eliminar todo lo que hay en el archivo tablero.csv
void limpiarTablero(){
    ofstream archivo("tablero.csv");
    archivo.close();
}
//obtener la dificultad del archivo guardado
int obtenerDificultad(){
    //leer el archivo
    ifstream archivo;
    archivo.open("tablero.csv",ios::in);
    string linea;
    //Control de apertura del archivo
    if(!archivo.is_open()){
        cout<<"El archivo del tablero no fue encontrado"<<endl;
        return -1;
    }
    for(int i=0;i<6;i++){
        //leer lineas
        getline(archivo,linea);  
        vector<int> fila;                                            
    }
    getline(archivo,linea);
    archivo.close();
    if(linea=="1"){
        return 1;
    }else if(linea=="2"){
        return 2;
    }else if(linea=="3"){
        return 3;
    }
    //retornar el tablero guardado
    return -1;
}
//ver los puntos
bool obtenerPuntos(){
    //leer el archivo
    ifstream archivo;
    archivo.open("puntos.csv",ios::in);
    string linea;
    //Control de apertura del archivo
    if(!archivo.is_open()){
        cout<<"El archivo del tablero no fue encontrado"<<endl;
        return false;
    }
    getline(archivo,linea);
    cout<<"Cantidad de partidas: "<<linea<<endl;
    for(int i=0;i<3;i++){
        getline(archivo,linea);
        stringstream registro(linea);
        vector<string> partes;
        for(string dato;getline(registro,dato,';');){
            partes.push_back(dato);
        }
        switch(i){
            case 0:
                cout<<"***Modalidad Facil***"<<endl;
                break;
            case 1:
                cout<<"***Modalidad Media***"<<endl;
                break;
            case 2:
                cout<<"***Modalidad Dificil***"<<endl;
                break;
        }
        cout<<"ganadas por jugador: "<<partes[0]<<endl;
        cout<<"ganadas por la cpu : "<<partes[1]<<endl;
        cout<<"Empate             : "<<partes[2]<<endl;
    }
    cout<<"************************"<<endl;
    archivo.close();
    return true; 
}
//actualizar las puntuaciones
void guardarPuntos(int quien,int dificultad){
    ifstream archivo;
    archivo.open("puntos.csv",ios::in);
    string linea;
    getline(archivo,linea);
    //recoger la informacion actual
    int cantidad=stoi(linea);
    vector<int> facil;
    vector<int> medio;
    vector<int> dificil;
    for(int i=0;i<3;i++){
        getline(archivo,linea);
        stringstream registro(linea);
        for(string dato;getline(registro,dato,';');){
            if(i==0){
                facil.push_back(stoi(dato));
            }else if(i==1){
                medio.push_back(stoi(dato));
            }else if(i==2){
                dificil.push_back(stoi(dato));
            }
        }
    }
    archivo.close();
    //actualizar la informacion
    cantidad++;
    if(dificultad==1){
        if(quien==-1){
            facil[0]+=1;
        }else if(quien==0){
            facil[2]+=1;
        }else if(quien==1){
            facil[1]+=1;
        }
    }else if(dificultad==2){
        if(quien==-1){
            medio[0]+=1;
        }else if(quien==0){
            medio[2]+=1;
        }else if(quien==1){
            medio[1]+=1;
        }
    }else if(dificultad==3){
        if(quien==-1){
            dificil[0]+=1;
        }else if(quien==0){
            dificil[2]+=1;
        }else if(quien==1){
            dificil[1]+=1;
        }
    }
    ofstream archivo1("puntos.csv",ios::trunc);
    archivo1<<cantidad<<"\n";
    archivo1<<facil[0]<<";"<<facil[1]<<";"<<facil[2]<<"\n";
    archivo1<<medio[0]<<";"<<medio[1]<<";"<<medio[2]<<"\n";
    archivo1<<dificil[0]<<";"<<dificil[1]<<";"<<dificil[2]<<"\n";
    archivo.close();
}
//averiguar cual es la mejor jugada para la maquina
Nodo* minimax(vector<vector<int>> tablero,bool turno,int profundidad){
    Nodo* mejorCaso= new Nodo(-1,0);
    //Caso base;
    if(profundidad==0 || verificarTableroLleno(tablero)==true){
        return mejorCaso;
    }
    int fila;
    int mayor=-9999999;
    int columna;
    //Jugada ficticia de la CPU
    if(turno==false){
        //Buscar de las 7 columnas, en cual se puede jugar
        for(int i=0;i<7;i++){
            int puntos=0;
            //probar en las columnas que no esten llenas
            if(tablero[0][i]==0){
                //Buscar la posicion en fila donde si se pueda depositar una ficha
                for(int j=5;j>=0;j--){
                    if(tablero[j][i]==0){
                        fila=j;
                        break;
                    }
                }
                //Realizar la jugada
                tablero[fila][i]=1;
                //analizar el caso
                int victoria=analizarVictoria(tablero);
                if(victoria==0){
                    puntos+=(2*profundidad)+minimax(tablero,true,profundidad-1)->getPuntuacion();
                    if(puntos>mayor){
                        mayor=puntos;
                        columna=i;
                    }
                }else if(victoria==1){
                    puntos=20*profundidad;
                    mejorCaso->setPuntuacion(puntos);
                    mejorCaso->setColumna(i);
                    return mejorCaso;
                }
                //quitar la jugada
                tablero[fila][i]=0;

            }
        }
    //Jugada ficticia del jugador
    }else if(turno==true){
        //Buscar de las 7 columnas, en cual se puede jugar
        for(int i=0;i<7;i++){
            int puntos=0;
            //probar en las columnas que no esten llenas
            if(tablero[0][i]==0){
                //Buscar en que fila de la columna i se puede hacer la jugada
                for(int j=5;j>=0;j--){
                    if(tablero[j][i]==0){
                        fila=j;
                        break;
                    }
                }
                //realizar la jugada ficiticia
                tablero[fila][i]=-1;
                //Analizar la jugada
                int victoria=analizarVictoria(tablero);
                if(victoria==0){
                    puntos+=(1*profundidad)+minimax(tablero,false,profundidad-1)->getPuntuacion();
                    if(puntos>mayor){
                        mayor=puntos;
                        columna=i;
                    } 
                }else if(victoria==-1){
                    puntos=20*profundidad;
                    mejorCaso->setPuntuacion(puntos);
                    mejorCaso->setColumna(i);
                    return mejorCaso;
                }
                //quitar la jugada
                tablero[fila][i]=0;
            }
        }
    }
    //retornar el mejor caso
    mejorCaso->setColumna(columna);
    mejorCaso->setPuntuacion(mayor);
    return mejorCaso;
}
//solicitar con poda o sin poda
bool pedirPoda(){
    int opcion;
    cout<<"****Con poda*****"<<endl;
    cout<<"1. si"<<endl;
    cout<<"2. no"<<endl;
    cout<<"Ingresa la opcion: ";
    cin>>opcion;
    while(opcion<1 || opcion>2){
        cout<<"Opcion invalida, ingresa otra opcion: "<<endl;
        cin>>opcion;
    }
    if(opcion==1){
        return true;
    }
    return false;
}
//minimax sin poda
Nodo* minimaxSinPoda(vector<vector<int>> tablero,bool turno,int profundidad){
    Nodo* mejorCaso= new Nodo(-1,0);
    //Caso base;
    if(profundidad==0 || verificarTableroLleno(tablero)==true){
        return mejorCaso;
    }
    int fila;
    int mayor=-9999999;
    int columna;
    //Jugada ficticia de la CPU
    if(turno==false){
        //Buscar de las 7 columnas, en cual se puede jugar
        for(int i=0;i<7;i++){
            int puntos=0;
            //probar en las columnas que no esten llenas
            if(tablero[0][i]==0){
                //Buscar la posicion en fila donde si se pueda depositar una ficha
                for(int j=5;j>=0;j--){
                    if(tablero[j][i]==0){
                        fila=j;
                        break;
                    }
                }
                //Realizar la jugada
                tablero[fila][i]=1;
                //analizar el caso
                int victoria=analizarVictoria(tablero);
                if(victoria==0){
                    puntos+=(2*profundidad)+minimax(tablero,true,profundidad-1)->getPuntuacion();
                    if(puntos>mayor){
                        mayor=puntos;
                        columna=i;
                    }
                }else if(victoria==1){
                    puntos=(20*profundidad)+minimaxSinPoda(tablero,true,profundidad-1)->getPuntuacion();
                    if(puntos>mayor){
                        mayor=puntos;
                        columna=i;
                    }
                }
                //quitar la jugada
                tablero[fila][i]=0;

            }
        }
    //Jugada ficticia del jugador
    }else if(turno==true){
        //Buscar de las 7 columnas, en cual se puede jugar
        for(int i=0;i<7;i++){
            int puntos=0;
            //probar en las columnas que no esten llenas
            if(tablero[0][i]==0){
                //Buscar en que fila de la columna i se puede hacer la jugada
                for(int j=5;j>=0;j--){
                    if(tablero[j][i]==0){
                        fila=j;
                        break;
                    }
                }
                //realizar la jugada ficiticia
                tablero[fila][i]=-1;
                //Analizar la jugada
                int victoria=analizarVictoria(tablero);
                if(victoria==0){
                    puntos+=(1*profundidad)+minimax(tablero,false,profundidad-1)->getPuntuacion();
                    if(puntos>mayor){
                        mayor=puntos;
                        columna=i;
                    } 
                }else if(victoria==-1){
                    puntos=(20*profundidad)+minimaxSinPoda(tablero,true,profundidad-1)->getPuntuacion();
                    if(puntos>mayor){
                        mayor=puntos;
                        columna=i;
                    }
                }
                //quitar la jugada
                tablero[fila][i]=0;
            }
        }
    }
    //retornar el mejor caso
    mejorCaso->setColumna(columna);
    mejorCaso->setPuntuacion(mayor);
    return mejorCaso;
}
//extraer si es poda del csv
bool leerPoda(){
    //leer el archivo
    ifstream archivo;
    archivo.open("tablero.csv",ios::in);
    string linea;
    //Control de apertura del archivo
    if(!archivo.is_open()){
        cout<<"El archivo del tablero no fue encontrado"<<endl;
        return -1;
    }
    for(int i=0;i<7;i++){
        //leer lineas
        getline(archivo,linea);  
        vector<int> fila;                                            
    }
    getline(archivo,linea);
    archivo.close();
    if(linea=="1"){
        return true;
    }
    return false;
}