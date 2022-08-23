#include <stddef.h>
#include <iostream>

using namespace std;

class Usuario{
    
    public:
        string nick;
        string password;
        float monedas;
        int edad;
        Usuario(string,string,float,int);
        Usuario() = default;
};

Usuario::Usuario(string _nick, string _password, float _monedas, int _edad){
    nick = _nick;
    password = _password;
    monedas = _monedas;
    edad = _edad;
}

class nodosimple {
public:
    Usuario usuario;
    nodosimple*sig;
    nodosimple() {
        sig = NULL;
    }
private:
};

class ListaSimple {
public:
    nodosimple*Inicio;

    ListaSimple() {
        Inicio = NULL;
    }
    void InsertarFinal(Usuario usuario);
    void InsertarEnOrden(Usuario usuario);
    void Imprimir();
private:
};


void ListaSimple::InsertarFinal(Usuario usuario) {
    nodosimple*nuevo = new nodosimple();
    nuevo->usuario = usuario;
    if (Inicio == NULL) {
        Inicio = nuevo;
    } else {
        nodosimple*auxActual = Inicio;

        while (auxActual != NULL) {
            if (auxActual->sig == NULL) {
                auxActual->sig = nuevo;
                break;
            }
            auxActual = auxActual->sig;
        }
    }


}

void ListaSimple::InsertarEnOrden(Usuario usuario) {
    nodosimple*nuevo = new nodosimple();
    nuevo->usuario = usuario;
    if (Inicio == NULL) {//Si la lista se encuentra vacia
        Inicio = nuevo;
    } else {//si la lista no esta vacia
        nodosimple*auxActual = Inicio;
        nodosimple*auxSiguiente;
        while (auxActual != NULL) {
            auxSiguiente = auxActual->sig;
            if (nuevo->usuario.edad < auxActual->usuario.edad) {//insertar al inicio de la lista por que es menor
                nuevo->sig = auxActual;
                Inicio = nuevo;
                break;
            } else if (auxSiguiente == NULL) {//insertar al final de la lista
                auxActual->sig = nuevo;
                break;
            } else if (nuevo->usuario.edad < auxSiguiente->usuario.edad) {//insertar en medio de la lista
                auxActual->sig = nuevo;
                nuevo->sig = auxSiguiente;
                break;
            }
            auxActual = auxActual->sig;
        }
    }
}

void ListaSimple::Imprimir() {
    nodosimple*aux = Inicio;
    while (aux != NULL) {
        cout <<"[" << aux->usuario.nick<<aux->usuario.password<<aux->usuario.monedas<<aux->usuario.edad << "]->";
        aux = aux->sig;
    }
    cout << ("NULL");
}


