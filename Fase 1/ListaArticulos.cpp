#include <iostream>
#include <cstdlib>
#include <windows.h> 
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

class Articulo{
    
    public:
        string id,categoria,nombre,src;
        int precio;
        int edad;
        Articulo(string,string,int,string,string);
        Articulo() = default;
        ~Articulo();
};

Articulo::Articulo(string _id, string _categoria, int _precio, string _nombre, string _src){
    id = _id;
    categoria = _categoria;
    precio = _precio;
    nombre = _nombre;
    src = _src;
}
Articulo::~Articulo(){

}

class NodoArticulo{
    public:	
    Articulo articulo;
    NodoArticulo*siguiente;
    NodoArticulo*anterior;
    NodoArticulo() {
        siguiente = NULL;
        anterior = NULL;
    }
};

class ListaArticulos {
public:
    NodoArticulo*primero;
    NodoArticulo*ultimo;
    int size;

    ListaArticulos() {
        primero = NULL;
        ultimo = NULL;
        size = 0;
    }
    void InsertarArticulo(Articulo articulo);
    void ImprimirIFArticulo();
    void ImprimirFIArticulo();
    void OrdenarArticulos();
private:
};

void ListaArticulos::InsertarArticulo(Articulo articulo) {
    NodoArticulo*nuevo = new NodoArticulo();
    nuevo->articulo = articulo;
    if (primero == NULL) {//Si la lista se encuentra vacia
        primero = nuevo;
        ultimo = nuevo;
        primero->siguiente = primero;
        primero->anterior = ultimo;
        size++;
    } else {//si la lista no esta vacia
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        nuevo->siguiente = primero;
        ultimo = nuevo;
        primero->anterior = ultimo;
        size++;
    }
}

void ListaArticulos::OrdenarArticulos() {
    NodoArticulo*s,*t;
    int v, i;
    string vv,vvv,vvvv,vvvvv;
    if(primero == ultimo && primero == NULL){
        cout<< "La lista está vacía"<<endl;
        return;
    }
    s = primero;
    for(i =0;i<size;i++){
        t = s->siguiente;
        while (t !=primero){
            if(s->articulo.precio > t->articulo.precio){
                v = s->articulo.precio;
                vv =s->articulo.id;
                vvv = s->articulo.categoria;
                vvvv = s->articulo.nombre;
                vvvvv = s->articulo.src;
                s->articulo = t->articulo;
                t->articulo.precio = v;
                t->articulo.id = vv;
                t->articulo.categoria = vvv;
                t->articulo.nombre = vvvv;
                t->articulo.src = vvvvv;
            }
            t = t->siguiente;
        }
        s = s->siguiente;
    }
    cout << ("Lista Ordenada\n");
}

void ListaArticulos::ImprimirIFArticulo() {
    NodoArticulo*aux = primero;
    cout<<"ID"<<" "<<"Categoria"<<" "<<"Precio"<<" "<<"Nombre"<<" "<<"src"<< "\n";
    while (aux != NULL) {
        cout << aux->articulo.id<<" "<<aux->articulo.categoria<<" "<<aux->articulo.precio<<" "<<aux->articulo.nombre<<" "<<aux->articulo.src<< "\n";
        aux = aux->siguiente;
        if(aux == primero){
            break;
        }
    }
    //cout << ("Primero");
    //cout << (size);
}

void ListaArticulos::ImprimirFIArticulo() {
    NodoArticulo*aux = ultimo;
    cout<<"ID"<<" "<<"Categoria"<<" "<<"Precio"<<" "<<"Nombre"<<" "<<"src"<< "\n";
    while (aux != NULL) {
        cout <<aux->articulo.id<<" "<<aux->articulo.categoria<<" "<<aux->articulo.precio<<" "<<aux->articulo.nombre<<" "<<aux->articulo.src<< "\n";
        aux = aux->anterior;
        if(aux == ultimo){
            break;
        }
    }
}