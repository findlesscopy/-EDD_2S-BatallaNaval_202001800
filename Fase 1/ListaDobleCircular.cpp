#include <iostream>
#include <cstdlib>
#include <windows.h> 
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

class Usuario{
    
    public:
        string nick;
        string password;
        float monedas;
        int edad;
        Usuario(string,string,float,int);
        Usuario() = default;
        ~Usuario();
};

Usuario::Usuario(string _nick, string _password, float _monedas, int _edad){
    nick = _nick;
    password = _password;
    monedas = _monedas;
    edad = _edad;
}
Usuario::~Usuario(){

}

class NodoCircular{
    public:	
    Usuario usuario;
    NodoCircular*siguiente;
    NodoCircular*anterior;
    NodoCircular() {
        siguiente = NULL;
        anterior = NULL;
    }
};

class ListaDobleCircular {
public:
    NodoCircular*primero;
    NodoCircular*ultimo;
    int size;

    ListaDobleCircular() {
        primero = NULL;
        ultimo = NULL;
        size = 0;
    }
    void Insertar(Usuario usuario);
    void ImprimirIF();
    void ImprimirFI();
    void Ordenar();
    void Eliminar(string nick, string password);
    void Editar(string nick, string password);
    void GenerarGrafo();
private:
};

void ListaDobleCircular::Insertar(Usuario usuario) {
    NodoCircular*nuevo = new NodoCircular();
    nuevo->usuario = usuario;
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

void ListaDobleCircular::ImprimirIF() {
    NodoCircular*aux = primero;
    while (aux != NULL) {
        cout <<"[" << aux->usuario.nick<<" "<<aux->usuario.password<<" "<<aux->usuario.monedas<<" "<<aux->usuario.edad << "]->";
        aux = aux->siguiente;
        if(aux == primero){
            break;
        }
    }
    cout << ("Primero");
    cout << (size);
}

void ListaDobleCircular::ImprimirFI() {
    NodoCircular*aux = ultimo;
    while (aux != NULL) {
        cout <<"[" << aux->usuario.nick<<" "<<aux->usuario.password<<" "<<aux->usuario.monedas<<" "<<aux->usuario.edad << "]->";
        aux = aux->anterior;
        if(aux == ultimo){
            break;
        }
    }
    cout << ("Primero");
    cout << (size);
}

void ListaDobleCircular::Ordenar() {
    NodoCircular*s,*t;
    int v, i;
    float vv;
    string vvv,vvvv;
    if(primero == ultimo && primero == NULL){
        cout<< "La lista está vacía"<<endl;
        return;
    }
    s = primero;
    for(i =0;i<size;i++){
        t = s->siguiente;
        while (t !=primero){
            if(s->usuario.edad > t->usuario.edad){
                v = s->usuario.edad;
                vv =s->usuario.monedas;
                vvv = s->usuario.nick;
                vvvv = s->usuario.password;
                s->usuario = t->usuario;
                t->usuario.edad = v;
                t->usuario.monedas = vv;
                t->usuario.nick = vvv;
                t->usuario.password = vvvv;
            }
            t = t->siguiente;
        }
        s = s->siguiente;
    }
    cout << ("Lista Ordenada");
}

void ListaDobleCircular::Eliminar(string nick, string password) {
    NodoCircular*actual = new NodoCircular();
    actual = primero;
    NodoCircular* anterior = new NodoCircular();
    anterior = NULL;
    bool encontrado = false;
    
    if(primero!=NULL){
        do{
            if(actual->usuario.nick == nick && actual->usuario.password == password){
                cout << "\n Nodo con los datos ( " << nick <<" "<< password << " ) Encontrado";
                if(actual==primero){
                    primero = primero->siguiente;
                    primero->anterior = ultimo;
                    ultimo->siguiente = primero;
                }else if(actual == ultimo){
                    ultimo = anterior;
                    ultimo->siguiente = primero;
                    primero->anterior = ultimo;
                }else{
                    anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = anterior;
                }
                cout<<"\nNodo eliminado"<<endl;
                size--;
                encontrado = true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }while(actual != primero && encontrado != true);
            if(!encontrado){
                cout<<"Nodo no encontrado"<<endl;
            }
    }else{
        cout<<"La lista se encuentra vacia"<<endl;
    }
   
}

void ListaDobleCircular::Editar(string nick, string password) {
    NodoCircular* actual = new NodoCircular();
    actual = primero;
    bool encontrado = false;
    string nuevo_nick, nueva_password;
    int nueva_edad;
    if(primero!=NULL){
        do{
            if(actual->usuario.nick == nick && actual->usuario.password == password){
                cout<<"\nNodo encontrado con los datos: "<<"Nick: "<<actual->usuario.nick<<" Password: "<<actual->usuario.password<<" Edad: "<<actual->usuario.edad<<endl;
                cout<<"\nIngrese nuevo dato para el nick"<<endl;
                cin >> nuevo_nick;
                actual->usuario.nick = nuevo_nick;
                cout<<"\nIngrese nuevo dato para password"<<endl;
                cin >> nueva_password;
                actual->usuario.password = nueva_password;
                cout<<"\nIngrese nuevo dato para edad"<<endl;
                cin >> nueva_edad;
                actual->usuario.edad = nueva_edad;

                cout<<"\nNodo Modificado"<<endl;
                encontrado = true;
            }
            actual = actual->siguiente;
        }while(actual != primero && encontrado != true);
            if(!encontrado){
                cout<<"Nodo no encontrado"<<endl;
            }
    }else{
        cout<<"La lista se encuentra vacia"<<endl;
    }
}

void ListaDobleCircular::GenerarGrafo() {
    string dot = "";
    dot+="digraph G{\nlabel=\" Lista Doble Circular Inicio-Fin \";\nnode [shape=box];\n";
    NodoCircular*tmp = primero;
    string conexiones ="";
    string nodos = "";
    int numnodo = 0;
    while(tmp!= NULL){
        nodos += "N"+std::to_string(numnodo)+"[label=\""+tmp->usuario.nick + "\" ];\n";
        int auxnum = numnodo +1;
        tmp = tmp->siguiente;
        if(tmp == primero){
            break;
        }else{
            conexiones += "N"+std::to_string(numnodo)+"->N"+std::to_string(auxnum)+"[dir=forward];\n";
            conexiones += "N"+std::to_string(numnodo)+"->N"+std::to_string(auxnum)+"[dir=back];\n";
            numnodo++;
        }
    }
    conexiones+="N"+std::to_string(numnodo)+"->N0[dir=forward];\n";
    conexiones+="N"+std::to_string(numnodo)+"->N0[dir=back];\n";
    dot += "//agregando nodos\n";
    dot += nodos+"\n";
    dot += "//agregando conexiones o flechas\n";
    dot += "{rank=same;\n"+conexiones+"\n}\n}";


    cout << dot;
    //------->escribir archivo
    ofstream file;
    file.open("Pruebas.dot");
    file << dot;
    file.close();
    //------->generar png
    system(("dot -Tpng Pruebas.dot -o  Pruebas.png"));

    //------>abrir archivo
    system(("Pruebas.png"));
}