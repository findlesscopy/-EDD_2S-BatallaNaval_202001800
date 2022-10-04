#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class NodoCola{
    public:
    int x,y;
    NodoCola*siguiente;
    NodoCola(){
        siguiente = NULL;
    }
};

class Cola{
    public:
    NodoCola*primero;
    NodoCola*ultimo;
    int size;

    Cola(){
        primero = NULL;
        ultimo = NULL;
        size = 0;   
    }
    void Insertar(int x, int y);
    void Peek();
    void Mostrar();
    void Graficar();
    private:
};

void Cola::Insertar(int x, int y){
    NodoCola*nuevo_nodo = new NodoCola();
    nuevo_nodo->x = x;
    nuevo_nodo->y = y;
    if(primero == NULL){
        primero = nuevo_nodo;
        primero->siguiente = NULL;
        ultimo = primero;
    }else{
        ultimo->siguiente = nuevo_nodo;
        nuevo_nodo->siguiente = NULL;
        ultimo = nuevo_nodo;
    }
}

void Cola::Mostrar(){
    NodoCola*actual = new NodoCola();
    actual = primero;
    cout<<"Tutorial: "<<endl;
    cout<<"     Ancho: "<<primero->x<<endl;
    cout<<"     Alto: "<<primero->y<<"\n"<<endl;
    if(primero != NULL){
        actual = actual->siguiente;
        while(actual!=NULL){
            
            cout<<" ["<<actual->x<<","<<actual->y<<"]-> ";
            actual = actual->siguiente;
        }
    }else{
        cout <<"La cola se encuentra vacia";
    }
}

void Cola::Peek(){
    cout<<primero->x<<" "<<primero->y<<endl;
}

void Cola::Graficar(){
    string dot = "digraph Pila{\nrankdir=LR;\nnode[shape=Mrecord];\n";
    string nodos = "Nodo[xlabel = Cola label= \"";
    NodoCola*temporal = primero;
    while(temporal!=NULL){
        if(temporal->siguiente == NULL){
            nodos+= std::to_string(temporal->x) +" "+std::to_string(temporal->y);
        }else{
            nodos+= std::to_string(temporal->x)+" "+std::to_string(temporal->y)+" | ";
        }
        temporal = temporal->siguiente;
    }
    nodos += "\"];\n";
    dot+= nodos;
    dot += "\n}";

    ofstream file;
    file.open("Cola.dot");
    file << dot;
    file.close();
    //------->generar png
    system(("dot -Tpng Cola.dot -o  Cola.png"));

    //------>abrir archivo
    system(("Cola.png"));
}