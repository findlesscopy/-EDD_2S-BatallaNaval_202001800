#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Usuario{
    
    public:
        int id;
        string nick;
        string password;
        int monedas;
        int edad;
        Usuario(int,string,string,int,int);
        Usuario() = default;
        ~Usuario();
};

Usuario::Usuario(int _id, string _nick, string _password, int _monedas, int _edad){
    id = _id;
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
    string ImprimirIF();
    string ImprimirFI();
    void Ordenar();
    bool BuscarUsuario(string nick);
    bool BuscarUsuarioLogin(string nick, string password);
    void Eliminar(string nick, string password);
    void Editar(string nick, string password);
    void GenerarGrafo();
private:
};

void ListaDobleCircular::Insertar(Usuario usuario) {
    NodoCircular*nuevo = new NodoCircular();
    nuevo->usuario = usuario;
    if (primero == NULL) {//Si la lista se encuentra vacia
        if(BuscarUsuario(usuario.nick)){
            primero = nuevo;
            ultimo = nuevo;
            primero->siguiente = primero;
            primero->anterior = ultimo;
            size++;
            cout<<"Usuario registrado exitosamente"<<endl;
        }else{
            cout<<"El usuario con el nick: "<<usuario.nick<<" ya existe"<<endl;
        }
    } else {//si la lista no esta vacia
        if(BuscarUsuario(usuario.nick)){
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            nuevo->siguiente = primero;
            ultimo = nuevo;
            primero->anterior = ultimo;
            size++;
            cout<<"Usuario registrado exitosamente"<<endl;
        }else{
            cout<<"El usuario con el nick: "<<usuario.nick<<" ya existe"<<endl;
        }
    }
}

string ListaDobleCircular::ImprimirIF() {
    
    if(primero == NULL)
        return "[\n]";

    NodoCircular*aux = primero;
    string salida = "";
    while (aux != NULL) {
        
        salida += "{\"id\": \""+ to_string(aux->usuario.id)+"\",\"nick\": \""+ aux->usuario.nick+"\",\"monedas\": \""+ to_string(aux->usuario.monedas)+"\",\"edad\": \""+ to_string(aux->usuario.edad)+"\"}";
        aux = aux->siguiente;
        if(aux != primero){
            salida += ",\n";
        }
        if(aux == primero)
            break;
        
    }
    return "[\n "+ salida + "\n]";
}

string ListaDobleCircular::ImprimirFI() {
    if(primero == NULL)
        return "[\n]";

    NodoCircular*aux = ultimo;
    string salida = "";
    while (aux != NULL) {
        
        salida += "{\"id\": \""+ to_string(aux->usuario.id)+"\",\"nick\": \""+ aux->usuario.nick+"\",\"monedas\": \""+ to_string(aux->usuario.monedas)+"\",\"edad\": \""+ to_string(aux->usuario.edad)+"\"}";
        aux = aux->siguiente;
        if(aux != ultimo){
            salida += ",\n";
        }
        if(aux == ultimo)
            break;
        
    }
    return "[\n "+ salida + "\n]";
    
}

void ListaDobleCircular::Ordenar() {
    NodoCircular*s,*t;
    int v, i,vvvvv;
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
                vvvvv = s->usuario.id;
                v = s->usuario.edad;
                vv =s->usuario.monedas;
                vvv = s->usuario.nick;
                vvvv = s->usuario.password;
                
                s->usuario = t->usuario;
                t->usuario.id = vvvvv;
                t->usuario.edad = v;
                t->usuario.monedas = vv;
                t->usuario.nick = vvv;
                t->usuario.password = vvvv;
            }
            t = t->siguiente;
        }
        s = s->siguiente;
    }
    cout << ("Lista Ordenada\n");
}

bool ListaDobleCircular::BuscarUsuario(string nick){
    NodoCircular*temporal = primero;

    int count = 0, flag = 0, value;
    
    if(temporal==NULL){
        return -1;
    }else{
        while(temporal->siguiente != primero){
            count++;

            if(temporal->usuario.nick == nick){
                flag = 1;
                count--;
                break;
            }
            temporal = temporal->siguiente;
        }
        if(temporal->usuario.nick == nick){
            count++;
            flag = 1;
        }
    }
    return (flag==1)? false: true;
}

bool ListaDobleCircular::BuscarUsuarioLogin(string nick,string password){
    NodoCircular*temporal = primero;

    int count = 0, flag = 0, value;
    
    if(temporal==NULL){
        return -1;
    }else{
        while(temporal->siguiente != primero){
            count++;

            if(temporal->usuario.nick == nick && temporal->usuario.password == password){
                flag = 1;
                count--;
                
                break;
            }
            temporal = temporal->siguiente;
        }
        if(temporal->usuario.nick == nick && temporal->usuario.password == password){
            count++;
            flag = 1;
            
        }
    }
    return (flag==1)? true: false;
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
                //cout << "\n Nodo con los datos ( " << nick <<" "<< password << " ) Encontrado";
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
                cout<<"\nCuenta eliminada XXXXX"<<endl;
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
    NodoCircular*actual = new NodoCircular();
    actual = primero;
    bool encontrado = false;
    string nuevo_nick;
    char nueva_password[100];
    int nueva_edad;
    if(primero!=NULL){
        do{
            cout<<actual->usuario.nick<<" "<<nick<<" "<<actual->usuario.password<<" "<<password<<endl;
            if(actual->usuario.nick == nick && actual->usuario.password == password){
                //cout<<"\nNodo encontrado con los datos: "<<"Nick: "<<actual->usuario.nick<<" Password: "<<actual->usuario.password<<" Edad: "<<actual->usuario.edad<<endl;
                cout<<"\nIngrese nuevo dato para el nick"<<endl;
                cin >> nuevo_nick;
                actual->usuario.nick = nuevo_nick;
                cout<<"\nIngrese nuevo dato para password"<<endl;
                cin >> nueva_password;
                string password_encriptada = SHA256(nueva_password);
                
                actual->usuario.password = password_encriptada;
                cout<<"\nIngrese nuevo dato para edad"<<endl;
                cin >> nueva_edad;
                actual->usuario.edad = nueva_edad;

                cout<<"\nDatos modificados correctamente"<<endl;
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
        nodos += "N"+std::to_string(numnodo)+"[label=\""+std::to_string(tmp->usuario.id)+"\n"+tmp->usuario.nick+"\n"+tmp->usuario.password+"\n"+std::to_string(tmp->usuario.monedas)+"\n"+std::to_string(tmp->usuario.edad) + + +"\" ];\n";
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


    //cout << dot;
    //------->escribir archivo
    ofstream file;
    file.open("ListaDobleCircular.dot");
    file << dot;
    file.close();
    //------->generar png
    system(("dot -Tpng ListaDobleCircular.dot -o  ListaDobleCircular.png"));

    //------>abrir archivo
    system(("ListaDobleCircular.png"));
}