#include <iostream>
#include <cstdlib>
#include <windows.h> 
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class NodoInterno{
    public:
    string id;
    int precio;
    string nombre;
    string src;
    NodoInterno*sig;
    NodoInterno() {
        sig = NULL;
    }
};

class NodoPrincipal{
    public:	
    string categoria;
    NodoPrincipal*siguiente;
    NodoInterno*abajo;
    NodoPrincipal() {
        siguiente = NULL;
        abajo = NULL;
    }
};



class ListaDeListas {
public:
    NodoPrincipal*primero;
    NodoPrincipal*ultimo;
    int size;

    ListaDeListas() {
        primero = NULL;
        ultimo = NULL;
        size = 0;
    }
    void InsertarCategoria(string categoria);
    void InsertarArticulo(string categoria, string id, int precio, string nombre, string src);
    bool Buscar(string categoria);    
    void ImprimirCategorias();
    void ImprimirArticulos();
    void GenerarGrafo();
private:
};

void ListaDeListas::InsertarCategoria(string categoria) {
    NodoPrincipal*tmp = new NodoPrincipal();
    tmp->categoria = categoria;
    if (primero == NULL) {//Si la lista se encuentra vacia
        if(Buscar(categoria)){
        primero = tmp;
        ultimo = primero;
        primero->siguiente = ultimo;
        ultimo->siguiente = primero;
        size++;
        }
    } else {//si la lista no esta vacia
        if(Buscar(categoria)){
            ultimo->siguiente = tmp;
            ultimo = tmp;
            ultimo->siguiente = primero;
            size++;
        }
        
    }
}

void ListaDeListas::InsertarArticulo(string categoria, string id, int precio, string nombre, string src){
    NodoPrincipal*tmp2 = primero;
    while(tmp2!=NULL){ 
        if(tmp2->categoria == categoria){
            NodoInterno*nuevo_articulo = new NodoInterno();
            nuevo_articulo->id = id;
            nuevo_articulo->precio = precio;
            nuevo_articulo->nombre = nombre;
            nuevo_articulo->src = src;
            NodoInterno*inicio_articulos = tmp2->abajo;
            tmp2->abajo = nuevo_articulo;
            nuevo_articulo->sig = inicio_articulos;
            break;
        }
        tmp2 = tmp2->siguiente;
    }
    if(tmp2 == NULL){
        cout <<"No se encontro la categoria dada";
    }

}

void ListaDeListas::ImprimirCategorias(){
    NodoPrincipal*tmp = primero;
    while(tmp!=NULL){ 
        cout << tmp->categoria<<" ";
        tmp = tmp->siguiente;
        if(tmp == primero){
            break;
        }
    }
}
void ListaDeListas::ImprimirArticulos(){
    NodoPrincipal*temporal = primero;
    while(temporal!=NULL){ 
        cout << "\n------------========Categoria: " << temporal->categoria<<"========------------";
        
        NodoInterno*temporal_articulos = temporal->abajo;

        while(temporal_articulos!=NULL){
            cout <<"\n"<< temporal_articulos->id<<" "<<temporal_articulos->nombre<<" "<< std::to_string(temporal_articulos->precio)<<" "<<temporal_articulos->src;
            
            temporal_articulos = temporal_articulos->sig;
            
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

bool ListaDeListas::Buscar(string categoria){
    NodoPrincipal*temporal = primero;

    int count = 0, flag = 0, value;
    
    if(temporal==NULL){
        return -1;
    }else{
        while(temporal->siguiente != primero){
            count++;

            if(temporal->categoria == categoria){
                flag = 1;
                count--;
                break;
            }
            temporal = temporal->siguiente;
        }
        if(temporal->categoria == categoria){
            count++;
            flag = 1;
        }
    }
    return (flag ==1)? false: true;
}

void ListaDeListas::GenerarGrafo(){
    string dot = "digraph G{\nlabel=\" Lista de Listas \";\nnode [shape=box fontsize=12];\n";
    NodoPrincipal*temporal_categoria = primero;
    string nodos_categoria = "";
    string nodos_articulos = "";
    string conexiones_categoria = "";
    string conexiones_articulos = "";
    string conexiones_categoria_articulos = "";
    int num_nodo_categoria = 1000;
    int num_nodo_articulos = 100;
    while(temporal_categoria != NULL){
        int aux_num_categoria = num_nodo_categoria + 1000;
        int aux_num_categoria2 = num_nodo_categoria+1;
        int aux_num_categoria3 = num_nodo_categoria+1;

        nodos_categoria += "N" + std::to_string(num_nodo_categoria) + "[label=\"" + temporal_categoria->categoria + "\" ];\n";
        NodoInterno*temporal_articulos = temporal_categoria->abajo;
        int aux_num_articulos = 1;
        while(temporal_articulos != NULL){
            nodos_articulos += "N" + std::to_string(num_nodo_articulos) + (std::to_string(aux_num_articulos))+"[label=\"" + temporal_articulos->id +"\n"+temporal_articulos->nombre +"\n"+ std::to_string(temporal_articulos->precio) +"\n"+temporal_articulos->src+ "\" ];\n";
            temporal_articulos = temporal_articulos->sig;
            if(temporal_articulos == NULL){
                conexiones_categoria_articulos += "N" + std::to_string(num_nodo_categoria) + " -> N" + std::to_string(aux_num_categoria2) + ";\n";

            }else{
                conexiones_articulos  += "N" + std::to_string(num_nodo_articulos)+(std::to_string(aux_num_articulos)) + " -> N" + std::to_string(aux_num_categoria3+1) + ";\n";
            }

            aux_num_articulos++;
            aux_num_categoria3++;
        }
        num_nodo_articulos = num_nodo_articulos +100;
        temporal_categoria = temporal_categoria->siguiente;
        if(temporal_categoria == primero){
            break;
        }else{
            conexiones_categoria += "N" + std::to_string(num_nodo_categoria) + " -> N" + std::to_string(aux_num_categoria) + ";\n";

            num_nodo_categoria = num_nodo_categoria +1000;
        }
    }
    if(temporal_categoria == NULL){
        cout<<"No se ecnotro la categoria"<<endl;
    }


    dot += nodos_categoria+"\n";
    dot += nodos_articulos+"\n";
    //agregando conexiones
    dot += "N"+ std::to_string(num_nodo_categoria)+"->N1000\n";
    dot += "{rank=same;\n"+conexiones_categoria+"\n}";
    dot += "{\n"+conexiones_categoria_articulos+"\n}";
    dot += "{\n"+conexiones_articulos+"\n}\n}";

    //cout << dot;
    //------->escribir archivo
    ofstream file;
    file.open("ListaDeListas.dot");
    file << dot;
    file.close();
    //------->generar png
    system(("dot -Tpng ListaDeListas.dot -o  ListaDeListas.png"));

    //------>abrir archivo
    system(("ListaDeListas.png"));
}