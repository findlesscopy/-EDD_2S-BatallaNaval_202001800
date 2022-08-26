#include <iostream>
#include <cstdlib>
#include <windows.h> 
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class NodoPila{
    public:
    int x, y;
    NodoPila*abajo;
    NodoPila(){
        abajo = NULL;
    }
};

class Pila{
    public: 
    NodoPila*cima;
    int size;
    Pila(){
        cima = NULL;
        size = 0;
    }
    void push(int x, int y);
    void pop();
    void peek();
    void GenerarGrafo();
};

void Pila::push(int x, int y){
    NodoPila*temporal = new NodoPila();
    temporal->x = x;
    temporal->y = y;
    temporal->abajo = cima;
    cima = temporal;
}

void Pila::pop(){
    NodoPila*temporal = cima;
    cima = NULL;
    cima = temporal->abajo;
    temporal = NULL;
}

void Pila::peek(){
    cout <<cima->x<<" "<<cima->y<<endl;
}

void Pila::GenerarGrafo(){

}