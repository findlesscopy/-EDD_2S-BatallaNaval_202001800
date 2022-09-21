#include <stddef.h>
#include <iostream>
#include <algorithm>
#include <windows.h> 
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Compra{
    
    public:
        string idCompra,nombre;
        int cantidad;
        Compra(string,string,int);
        Compra() = default;
        ~Compra();
    private:
};

Compra::Compra(string _idCompra, string _nombre, int _cantidad){
    idCompra = _idCompra;
    nombre = _nombre;
    cantidad = _cantidad; 
}

Compra::~Compra(){

}

int correlativo = 1;
class NodoAVL{
public:
   
    Compra compra;
    int id;
    int altura;
    
    NodoAVL* izquierda;
    NodoAVL* derecha;
    

    NodoAVL(Compra _compra) {
        compra = _compra;
        izquierda = NULL;
        derecha = NULL;
        altura = 0;
        id = correlativo++;
    }
private:
};

class AVL {
public:
    NodoAVL* raiz;

    AVL() {
        raiz = NULL;
    }
    
    int MAXIMO(int valor1, int valor2);
    int altura(NodoAVL* nodo);
    void insertar(Compra compra);
    NodoAVL* add(Compra compra, NodoAVL* nodo);
    NodoAVL* rotacionizquierda(NodoAVL* nodo);
    NodoAVL* rotacionderecha(NodoAVL* nodo);
    NodoAVL* rotaciondoblederecha(NodoAVL* nodo);
    NodoAVL* rotaciondobleizquierda(NodoAVL* nodo);
    void mostrarOrdenDescendente();
    NodoAVL* in_orden(NodoAVL* nodo);
    void graficar();
    string getCodigoInterno(NodoAVL* nodo);
private:
};
  
int AVL::MAXIMO(int valor1, int valor2){
    if(valor1>valor2){
        return valor1;
    }else{
        return valor2;
    }
}

int AVL::altura(NodoAVL* nodo){
    if(nodo == NULL){
        return -1;
    }else{
        return nodo->altura;
    }
}

void AVL::insertar(Compra compra){
    raiz = add(compra, raiz); 
}

NodoAVL* AVL::add(Compra compra, NodoAVL* nodo){
    if(nodo == NULL){
        return new NodoAVL(compra);
    }else{
        if(compra.idCompra < nodo->compra.idCompra){
            nodo->izquierda = add(compra, nodo->izquierda);
            if(altura(nodo->derecha)-altura(nodo->izquierda)== -2){
                if(compra.idCompra < nodo->izquierda->compra.idCompra){
                    nodo = rotacionizquierda(nodo);
                }else{
                    nodo = rotaciondobleizquierda(nodo);
                }
            }
        }else if(compra.idCompra > nodo->compra.idCompra){
            nodo->derecha = add(compra, nodo->derecha);
            if(altura(nodo->derecha)-altura(nodo->izquierda)== 2){
                if(compra.idCompra > nodo->derecha->compra.idCompra){
                    nodo = rotacionderecha(nodo);
                }else{
                    nodo = rotaciondoblederecha(nodo);
                }
            }
        }else{
            cout << "No se puede agregar";
        }
    }
    nodo->altura = MAXIMO(altura(nodo->izquierda),altura(nodo->derecha))+1;
    return nodo;
}

NodoAVL* AVL::rotacionizquierda(NodoAVL *nodo){
    NodoAVL* aux = nodo->izquierda;
    nodo->izquierda = aux->derecha;
    aux->derecha = nodo;

    nodo->altura = MAXIMO(altura(nodo->derecha),altura(nodo->izquierda))+1;
    aux->altura = MAXIMO(altura(nodo->izquierda), nodo->altura)+1;
    return aux;
}

NodoAVL* AVL::rotacionderecha(NodoAVL* nodo){
    NodoAVL* aux = nodo->derecha;
    nodo->derecha = aux->izquierda;
    aux->izquierda = nodo;

    nodo->altura = MAXIMO(altura(nodo->derecha),altura(nodo->izquierda))+1;
    aux->altura = MAXIMO(altura(nodo->derecha), nodo->altura)+1;
    return aux;
}

NodoAVL* AVL::rotaciondoblederecha(NodoAVL* nodo){
    nodo->derecha = rotacionizquierda(nodo->derecha);
    return rotacionderecha(nodo);
}

NodoAVL* AVL::rotaciondobleizquierda(NodoAVL* nodo){
    nodo->izquierda = rotacionderecha(nodo->izquierda);
    return rotacionizquierda(nodo);
}

void AVL::graficar(){
    string codigodot = "";
    codigodot += "digraph G{label = \"Arbol AVL\" fontname=\"Arial Black\" fontsize=\"25pt\";\nnode [shape = box, style=filled, fillcolor=seashell2];\n"+ getCodigoInterno(raiz)+"\n}"; 
        
    //cout << codigodot;
    //------->escribir archivo
    ofstream file;
    file.open("AVL.dot");
    file << codigodot;
    file.close();
    //------->generar png
    system(("dot -Tpng AVL.dot -o  AVL.png"));

    //------>abrir archivo
    system(("AVL.png"));
}

string AVL::getCodigoInterno(NodoAVL* nodo){
    string codigodot = "";
        
    if((nodo->izquierda== NULL) && (nodo->derecha == NULL)){
        codigodot += "nodo" + std::to_string(nodo->id)+ "[ label = \""+ nodo->compra.idCompra +"\""+ "];\n";
    }else{
        codigodot += "nodo" +std::to_string(nodo->id)+"[ label = \""+ nodo->compra.idCompra +"\""+"];\n";
    }
    if(nodo->izquierda!=NULL){
        codigodot+= getCodigoInterno(nodo->izquierda) +"nodo"+std::to_string(nodo->id) + ":C0->nodo" + std::to_string(nodo->izquierda->id)+"\n";
    }
    if(nodo->derecha!=NULL){
        codigodot+= getCodigoInterno(nodo->derecha)+"nodo"+std::to_string(nodo->id)+":C1->nodo"+std::to_string(nodo->derecha->id)+"\n";                    
    }
    return codigodot;
}