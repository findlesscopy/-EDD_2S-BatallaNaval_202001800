#include <stddef.h>
#include <iostream>
#include <algorithm>
#include <windows.h> 
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

class Usuario{
    
    public:
        string nick;
        string password;
        int monedas;
        int edad;
        Usuario(string,string,int,int);
        Usuario() = default;
        ~Usuario();
};

Usuario::Usuario(string _nick, string _password, int _monedas, int _edad){
    nick = _nick;
    password = _password;
    monedas = _monedas;
    edad = _edad;
}
Usuario::~Usuario(){

}

class NodoB {
public:
    Usuario usuario;
    //Apuntadores dentro de la rama
    NodoB* siguiente;
    NodoB* anterior;

    //apuntadores al inicio de otra rama
    NodoB* derecha;
    NodoB* izquierda;

    NodoB(Usuario _usuario) {
        usuario = _usuario;
        siguiente = NULL;
        anterior = NULL;
        derecha = NULL;
        izquierda = NULL;
    }
private:

};

class ArbolB {
public:
    int orden_arbol = 4;
    NodoB* raiz;

    ArbolB() {
        raiz = NULL;
    }
    void insertar(Usuario usuario);
    pair<NodoB*, pair<bool, bool>> insertarCrearRama(NodoB* nodo, NodoB* rama);
    NodoB* dividir(NodoB* rama);
    pair<NodoB*, bool>  insertarEnRama(NodoB* primero, NodoB* nuevo);
    bool esHoja(NodoB* primero);
    int contador(NodoB* primero);
    void Grafo();
    string GrafoArbolAbb(NodoB*rama);
    string GrafoRamas(NodoB*rama);
    string GrafoConexionRamas(NodoB*rama);
private:

};

void ArbolB::insertar(Usuario usuario) {
    NodoB* nodo = new NodoB(usuario);
    if (raiz == NULL) {
        raiz = nodo;
    } else {
        pair < NodoB*, pair<bool, bool>> ret = insertarCrearRama(nodo, raiz);
        NodoB* obj = ret.first;
        if ((ret.second.first || ret.second.second) && obj != NULL) {//si se divide la rama o se inserta al inicio, la raiz cambia
            cout << "se cambia de rama principal ID:" << obj->usuario.nick << "\n";
            raiz = obj;
        }
    }
}

/**
 * Metodo recorre el arbol e inserta los valores nuevos, verifica si es necesario dividir ramas
 *
 * @param NodoB* nodo es el nodo a insertar
 * @param NodoB* rama es la rama en la cual se inicia la busqueda de la posicion donde insertarlo
 * 
 * @retun retorna un listado de elementos que nos permiten identificar lo siguiente:
 * 
 * NodoB*: nodo inicial de la rama donde se inserto un elemento
 * 
 * bool: true or false indicando si una rama se dividio en dos nuevas
 * 
 * bool: true or false indicando si el inicio de la rama cambio debio a un insert al inicio.
 */
pair<NodoB*, pair<bool, bool>> ArbolB::insertarCrearRama(NodoB* nodo, NodoB* rama) {
    pair < NodoB*, pair<bool, bool>> ResultadoRama;
    ResultadoRama.first = NULL; //nodo Inicial de la rama
    ResultadoRama.second.first = false; //indica si se dividio la rama
    ResultadoRama.second.second = false; //indica si se modifica el inicio de la rama
    if (esHoja(rama)) {//si el nodo es hoja se inseta directamente dentro de ella
        pair < NodoB*, bool> resultado = insertarEnRama(rama, nodo); //insertamos el nuevo elemento dentro de la rama actual
        ResultadoRama.first = resultado.first; //posee la rama con el valor ya insertado
        ResultadoRama.second.second = resultado.second; //posee el resultado de si se modifico el inicio en el insert anterior
        if (contador(resultado.first) == orden_arbol) {//si la rama posee mas elementos de los permitidos se divide
            cout << "La rama debe dividirse\n";
            ResultadoRama.first = dividir(resultado.first); //dividimos la rama y obtenemos una nueva rama con sus respectivos apuntadores
            ResultadoRama.second.first = true; //identificar que la rama se dividio
        }
    } else {//si el nodo es rama se debe buscar la posicion donde insertarlo
        NodoB*temp = rama;
        do {
            if (nodo->usuario.nick == temp->usuario.nick) {//valor ya insertado, no se permiten repeditos
                cout << "insertarCrearRama(), El ID " << nodo->usuario.nick << " ya existe\n";
                return ResultadoRama;
            } else if (nodo->usuario.nick < temp->usuario.nick) {
                pair < NodoB*, pair<bool, bool>> ResultadoInsert = insertarCrearRama(nodo, temp->izquierda);
                if (ResultadoInsert.second.second && ResultadoInsert.first != NULL) {//si se modifico el inicio de la rama
                    ResultadoRama.second.second = true;
                    temp->izquierda = ResultadoInsert.first;
                }
                if (ResultadoInsert.second.first) {//se dividio la subrama
                    pair < NodoB*, bool> auxInsert = insertarEnRama(rama, ResultadoInsert.first);
                    rama = auxInsert.first;
                    if (auxInsert.second) {
                        ResultadoRama.first = rama;
                    }
                    if (contador(rama) == orden_arbol) {
                        ResultadoRama.first = dividir(rama);
                        ResultadoRama.second.first = true;
                    }
                }
                return ResultadoRama;
            } else if (temp->siguiente == NULL) {
                pair < NodoB*, pair<bool, bool>> ResultadoInsert = insertarCrearRama(nodo, temp->derecha);
                if (ResultadoInsert.second.second && ResultadoInsert.first != NULL) {//si se modifico el inicio de la rama
                    ResultadoRama.second.second = true;
                    temp->derecha = ResultadoInsert.first;
                }
                if (ResultadoInsert.second.first) {//se dividio la subrama
                    pair < NodoB*, bool> auxInsert = insertarEnRama(rama, ResultadoInsert.first);
                    rama = auxInsert.first;
                    if (auxInsert.second) {
                        ResultadoRama.first = rama;
                    }
                    if (contador(rama) == orden_arbol) {
                        ResultadoRama.first = dividir(rama);
                        ResultadoRama.second.first = true;
                    }
                }
                return ResultadoRama;
            }
            temp = temp->siguiente;
        } while (temp != NULL);
    }
    return ResultadoRama;
}

NodoB* ArbolB::dividir(NodoB* rama) {
    Usuario val = Usuario("","",-1,-1);
    NodoB*temp = NULL;
    NodoB*Nuevito = NULL;
    NodoB*aux = rama;

    NodoB*rderecha = NULL;
    NodoB*rizquierda = NULL;

    int cont = 0;
    while (aux != NULL) {
        cont++;
        //implementacion para dividir unicamente ramas de 4 nodos
        if (cont < 3) {
            val = Usuario(aux->usuario.nick,aux->usuario.password,aux->usuario.monedas,aux->usuario.edad);
            temp = new NodoB(val);
            temp->izquierda = aux->izquierda;
            if (cont == 2) {
                temp->derecha = aux->siguiente->izquierda;
            } else {
                temp->derecha = aux->derecha;
            }
            rizquierda = insertarEnRama(rizquierda, temp).first;
        } else if (cont == 3) {
            val = Usuario(aux->usuario.nick,aux->usuario.password,aux->usuario.monedas,aux->usuario.edad);
            Nuevito = new NodoB(val);
        } else {
            val = Usuario(aux->usuario.nick,aux->usuario.password,aux->usuario.monedas,aux->usuario.edad);;
            temp = new NodoB(val);
            temp->izquierda = aux->izquierda;
            temp->derecha = aux->derecha;
            rderecha = insertarEnRama(rderecha, temp).first;
        }
        aux = aux->siguiente;
    }
    Nuevito->derecha = rderecha;
    Nuevito->izquierda = rizquierda;
    return Nuevito;
}

pair<NodoB*, bool> ArbolB::insertarEnRama(NodoB* primero, NodoB* nuevo) {
    pair < NodoB*, bool> ret;
    ret.second = false;
    if (primero == NULL) {
        //primero en la lista
        ret.second = true;
        primero = nuevo;
    } else {
        //recorrer e insertar
        NodoB* aux = primero;
        while (aux != NULL) {
            if (aux->usuario.nick == nuevo->usuario.nick) {//------------->ya existe en el arbol
                cout << "insertarEnRama(), El ID " << nuevo->usuario.nick << " ya existe\n";
                break;
            } else {
                if (aux->usuario.nick > nuevo->usuario.nick) {//------------->) {
                    if (aux == primero) {//------------->insertar al inicio
                        aux->anterior = nuevo;
                        nuevo->siguiente = aux;
                        //ramas del nodo
                        aux->izquierda = nuevo->derecha;
                        nuevo->derecha = NULL;
                        ret.second = true;
                        primero = nuevo;
                        break;
                    } else {//------------->insertar en medio;
                        nuevo->siguiente = aux;
                        //ramas del nodo
                        aux->izquierda = nuevo->derecha;
                        nuevo->derecha = NULL;

                        nuevo->anterior = aux->anterior;
                        aux->anterior->siguiente = nuevo;
                        aux->anterior = nuevo;
                        break;
                    }
                } else if (aux->siguiente == NULL) {//------------->insertar al final
                    aux->siguiente = nuevo;
                    nuevo->anterior = aux;
                    break;
                }
            }
            aux = aux->siguiente;
        }

    }
    ret.first = primero;

    return ret;
}

/*
 * Metodo para verificar si es hoja
 * Un nodo hoja no pose apuntadores a otros nodos hacia izquierda o derecha
 */
bool ArbolB::esHoja(NodoB* primero) {
    NodoB* aux = primero;
    while (aux != NULL) {
        cout << "[" << aux->usuario.nick << "]->";
        if (aux->izquierda != NULL || aux->derecha != NULL) {
            return false;
        }
        aux = aux->siguiente;
    }
    cout << "Null\n";
    return true;
}

/*Metodo para contar los elementos de una rama*/
int ArbolB::contador(NodoB* primero) {
    int contador = 0;
    NodoB* aux = primero;
    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

//================================Grafo solo del arbol b=====================

void ArbolB::Grafo() {
    string dotFull = "";
    //escribir dot

    dotFull += "digraph G {\n";
    dotFull += "node[shape=record]\n";
    dotFull += "\t\t//Agregar Nodos Rama\n";
    dotFull += GrafoArbolAbb(raiz);
    //agregar conexiones de ramas
    dotFull += "\t\t//Agregar conexiones\n";
    dotFull += GrafoConexionRamas(raiz);

    dotFull += "}";

    //------->escribir archivo
    ofstream file;
    file.open("Pruebas.dot");
    file << dotFull;
    file.close();

    //------->generar png
    system(("dot -Tpng Pruebas.dot -o  Pruebas.png"));

    //------>abrir archivo
    system(("Pruebas.png"));

}

string ArbolB::GrafoArbolAbb(NodoB* rama) {
    string dot = "";
    if (rama != NULL) {
        //agrear rama actual
        dot += GrafoRamas(rama);
        //agregar las ramas siguientes recursivamente
        NodoB*aux = rama;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                dot += GrafoArbolAbb(aux->izquierda);
            }
            if (aux->siguiente == NULL) {
                if (aux->derecha != NULL) {
                    dot += GrafoArbolAbb(aux->derecha);
                }
            }
            aux = aux->siguiente;
        }
    }
    return dot;
}

string ArbolB::GrafoRamas(NodoB*rama) {
    string dot = "";
    stringstream auxTXT;
    if (rama != NULL) {
        //============================================agregar rama=================================
        NodoB*aux = rama;
        auxTXT.str("");
        auxTXT << rama;
        dot = dot + "R" + auxTXT.str() + "[label=\"";
        int r = 1;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                dot = dot + "<C" + to_string(r) + ">|";
                r++;
            }
            if (aux->siguiente != NULL) {
                dot = dot + aux->usuario.nick + "\n " +aux->usuario.password + "\n " + to_string(aux->usuario.monedas) + "\n " + to_string(aux->usuario.edad) +"|";
            } else {
                dot = dot + aux->usuario.nick + "\n " +aux->usuario.password + "\n " + to_string(aux->usuario.monedas) + "\n " + to_string(aux->usuario.edad);
                if (aux->derecha != NULL) {
                    dot = dot + "|<C" + to_string(r) + ">";
                }
            }
            aux = aux->siguiente;
        }
        dot = dot + "\"];\n";
    }
    return dot;
}

string ArbolB::GrafoConexionRamas(NodoB*rama) {
    string dot = "";
    stringstream auxTXT;
    if (rama != NULL) {
        //============================================agregar rama=================================
        NodoB*aux = rama;
        auxTXT << rama;
        string actual = "R" + auxTXT.str();
        int r = 1;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                auxTXT.str("");
                auxTXT << aux->izquierda;
                dot += actual + ":C" + to_string(r) + "->" + "R" + auxTXT.str() + ";\n";
                r++;
                dot += GrafoConexionRamas(aux->izquierda);
            }
            if (aux->siguiente == NULL) {
                if (aux->derecha != NULL) {
                    auxTXT.str("");
                    auxTXT << aux->derecha;
                    dot += actual + ":C" + to_string(r) + "->" + "R" + auxTXT.str() + ";\n";
                    r++;
                    dot += GrafoConexionRamas(aux->derecha);
                }
            }
            aux = aux->siguiente;
        }
    }
    return dot;
}