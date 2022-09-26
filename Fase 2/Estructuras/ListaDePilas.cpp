#include <iostream>
#include <cstdlib>
#include <windows.h> 
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class NodoPila{
    public:
    int x,y;
    NodoPila*abajo;
    NodoPila(){
        abajo = NULL;
    }
    private:
};

class NodoCabecera{
    public:
    string nick;
    NodoCabecera*siguiente;
    NodoPila*abajo;
    NodoCabecera(){
        siguiente = NULL;
        abajo = NULL;
    }
    private:
};


class ListaDePilas{
    public:
    NodoCabecera*primero;
    NodoPila*cima;
    int size;
    ListaDePilas(){
        primero = NULL;
        size = 0;
    }
    void InsertarCabecera(string nick);
    bool BuscarEncabezado(string nick);
    void PushPila(string nick,int x,int y);
    void PopPila();
    void GenerarGrafo();
    void ImprimirCabeceras();
    void ImprimirPilas();
    private:
};

void ListaDePilas::InsertarCabecera(string nick){
    NodoCabecera*temporal = new NodoCabecera();
   
    if(BuscarEncabezado(nick)){
        temporal->nick = nick;
        temporal->siguiente = primero;
        primero = temporal;
        size++;
    }
}

void ListaDePilas::PushPila(string nick, int x, int y){
    NodoCabecera*temporal = primero;
    while(temporal != NULL){
        //cout << temporal->nick << " " <<nick <<endl;
        if(temporal->nick == nick){
            NodoPila*nueva_pila = new NodoPila();
            nueva_pila->x = x;
            nueva_pila->y = y;
            nueva_pila->abajo = cima;
            cima = nueva_pila;
            NodoPila*inicio_pila = temporal->abajo;
            temporal->abajo = nueva_pila;
            nueva_pila->abajo = inicio_pila;
            break;
        }
        temporal = temporal->siguiente;
    }
    if(temporal == NULL){
        cout <<"No se encontro la categoria dada";
    }
    
}

void ListaDePilas::ImprimirCabeceras() {
    NodoCabecera*aux = primero;
    while (aux != NULL) {
        cout <<"[" << aux->nick<<"]->";
        aux = aux->siguiente;
    }
    //cout << ("NULL");
}

void ListaDePilas::ImprimirPilas(){
    NodoCabecera*temporal = primero;
    while(temporal!=NULL){ 
        cout << "\n------------========Nick: " << temporal->nick<<"========------------";
        
        NodoPila*temporal_pila = temporal->abajo;

        while(temporal_pila!=NULL){
            cout <<"\n"<< std::to_string(temporal_pila->x)<<" "<<std::to_string(temporal_pila->y)<<endl;
            
            temporal_pila = temporal_pila->abajo;
            
        }
        temporal = temporal->siguiente;
        if(temporal == primero){
            break;
        }
    }
    if(temporal == NULL){
        cout <<"No se encontro la categoria" << endl;
    }
}


bool ListaDePilas::BuscarEncabezado(string nick){
    NodoCabecera*temporal = primero;
    int flag = 0;
    while(temporal != NULL) {
        if (temporal->nick == nick) {
            flag = 1;
            break;
        }
        temporal = temporal->siguiente;
    }
    return (flag ==1)? false : true; 
}
    
void ListaDePilas::GenerarGrafo(){
    string dot = "digraph G{\nlabel=\" Lista de Pilas \";\nnode [shape=box fontsize=12 arrowsize=0.1] ;\n";
    NodoCabecera*temporal_cabecera = primero;
    string nodos_cabecera = "";
    string nodos_pilas = "";
    string conexiones_cabecera = "";
    string conexiones_pilas = "";
    string conexiones_cabecera_pilas = "";
    int num_nodo_cabecera = 1000;
    int num_nodo_pilas = 100;
    while(temporal_cabecera != NULL){
        int aux_num_cabecera = num_nodo_cabecera + 1000;
        int aux_num_cabecera2 = num_nodo_cabecera+1;
        int aux_num_cabecera3 = num_nodo_cabecera+1;

        nodos_cabecera += "N" + std::to_string(num_nodo_cabecera) + "[label=\"" + temporal_cabecera->nick + "\" ];\n";
        NodoPila*temporal_pilas = temporal_cabecera->abajo;
        int aux_num_pilas = 1;
        while(temporal_pilas != NULL){
            nodos_pilas += "N" + std::to_string(num_nodo_pilas) + (std::to_string(aux_num_pilas))+"[arrowsize = 1, label=\"" + std::to_string(temporal_pilas->x )+"\n"+std::to_string(temporal_pilas->y)+ "\" ];\n";
            temporal_pilas = temporal_pilas->abajo;
            if(temporal_pilas == NULL){
                conexiones_cabecera_pilas += "N" + std::to_string(num_nodo_cabecera) + " -> N" + std::to_string(aux_num_cabecera2) + ";\n";

            }else{
                conexiones_pilas  += "N" + std::to_string(num_nodo_pilas)+(std::to_string(aux_num_pilas)) + " -> N" + std::to_string(aux_num_cabecera3+1) + ";\n";
            }

            aux_num_pilas++;
            aux_num_cabecera3++;
        }
        num_nodo_pilas = num_nodo_pilas +100;
        temporal_cabecera = temporal_cabecera->siguiente;
        if(temporal_cabecera == primero){
            break;
        }else{
            conexiones_cabecera += "N" + std::to_string(num_nodo_cabecera) + " -> N" + std::to_string(aux_num_cabecera) + ";\n";

            num_nodo_cabecera = num_nodo_cabecera +1000;
        }
    }
    if(temporal_cabecera == NULL){
        cout<<"No se ecnotro la categoria"<<endl;
    }


    dot += nodos_cabecera+"\n";
    dot += nodos_pilas+"\n";
    //agregando conexiones
    //dot += "N"+ std::to_string(num_nodo_cabecera)+"->N1000\n";
    dot += "{rank=same;\n"+conexiones_cabecera+"\n}";
    dot += "{\n"+conexiones_cabecera_pilas+"\n}";
    dot += "{\n"+conexiones_pilas+"\n}\n}";

    //cout << dot;
    //------->escribir archivo
    ofstream file;
    file.open("ListaDePilas.dot");
    file << dot;
    file.close();
    //------->generar png
    system(("dot -Tpng ListaDePilas.dot -o  ListaDePilas.png"));

    //------>abrir archivo
    system(("ListaDePilas.png"));
}
