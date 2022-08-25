#include <cstdlib>
#include <iostream>

#include "SHA256.cpp"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"

#include "ListaDobleCircular.cpp"
#include "ListaDeListas.cpp"
#include "Cola.cpp"
#include "ListaArticulos.cpp"

using namespace std;
using json = nlohmann::json;
 
ListaDobleCircular lista_usuarios;
ListaDeListas lista_de_articulos;
Cola cola_tutorial;
ListaArticulos lista_articulos_ordenada;
Usuario usuario;
Articulo articulo;


int helpers() {
    void CargaMasiva(string direccion);
    void RegistroUsuario(string nick, string password, int monedas, int edad);
    void Reportes();
    void Login(string nick, string password);
    return 0;
}

void CargaMasiva(string direccion){
    //Intancias de Listas
    
    //Lectura de archivo y parseo
    std::ifstream f(direccion);
    json data = json::parse(f);
    //Carga de Usuarios a Lista
    for(int i = 0; i < data.at("usuarios").size(); i++) {
        string nick = data.at("usuarios")[i].at("nick");
        string password = data.at("usuarios")[i].at("password");

        SHA256 sha;
        sha.update(password);
        uint8_t * digest = sha.digest();

        //std::cout << SHA256::toString(digest) << std::endl;

        delete[] digest; // Don't forget to free the digest!

        string monedas = data.at("usuarios")[i].at("monedas");
        int monedas1 = stoi(monedas);
        string edad = data.at("usuarios")[i].at("edad");
        int edad1 = stoi(edad);
        //std::cout<< nick<<" "<<password<<" "<<monedas1<<" "<<edad1 << std::endl;
        usuario = Usuario(nick, SHA256::toString(digest),monedas1,edad1); 
        lista_usuarios.Insertar(usuario);
    }
    //lista_usuarios.GenerarGrafo();


    //Carga de Articulos a Lista de Listas
    for(int i = 0; i < data.at("articulos").size(); i++) {
        string id = data.at("articulos")[i].at("id");
        string categoria = data.at("articulos")[i].at("categoria");
        string precio = data.at("articulos")[i].at("precio");
        string nombre = data.at("articulos")[i].at("nombre");
        string src = data.at("articulos")[i].at("src");
        
        int precio1 = stoi(precio);

        //std::cout<< id<<" "<<categoria<<" "<<precio1<<" "<<nombre<<" "<<src<<std::endl;
        lista_de_articulos.InsertarCategoria(categoria);
        lista_de_articulos.InsertarArticulo(categoria, id, precio1, nombre, src);
        articulo = Articulo(id, categoria, precio1, nombre, src);
        lista_articulos_ordenada.InsertarArticulo(articulo);
        
    }

    //lista_de_articulos.ImprimirArticulos();
    //lista_de_articulos.GenerarGrafo();


    //Carga de Tutorial

    string ancho = data["tutorial"]["ancho"];
    int ancho1 = stoi(ancho);
    string alto = data["tutorial"]["alto"];
    int alto1 = stoi(alto);
    //insertando la primera de la cola
    cola_tutorial.Insertar(ancho1,alto1);
    //cout<<data["tutorial"]["movimientos"].size();
    for(int i = 0; i < data["tutorial"]["movimientos"].size(); i++) {
        //std::cout<< id<<" "<<categoria<<" "<<precio1<<" "<<nombre<<" "<<src<<std::endl;
        string x = data["tutorial"]["movimientos"][i].at("x");
        int x1 = stoi(x);
        string y = data["tutorial"]["movimientos"][i].at("y");
        int y1 = stoi(y);
        cola_tutorial.Insertar(x1,y1);
        
    }
    //cola_tutorial.Graficar();
}

void RegistroUsuario(string nick, string password, int monedas, int edad){
    
    SHA256 sha;
    sha.update(password);
    uint8_t * digest = sha.digest();

    //std::cout << SHA256::toString(digest) << std::endl;

    delete[] digest; // Don't forget to free the digest!

    usuario = Usuario(nick, SHA256::toString(digest),monedas,edad); 
    lista_usuarios.Insertar(usuario);

    //lista_usuarios.ImprimirFI(); 
}

void Login(string nick, string password){
    
    SHA256 sha;
    sha.update(password);
    uint8_t * digest = sha.digest();

    //std::cout << SHA256::toString(digest) << std::endl;

    delete[] digest; // Don't forget to free the digest!

    if(lista_usuarios.BuscarUsuarioLogin(nick, SHA256::toString(digest)) == false){
        cout << "Login failed" << endl;
    }else{
        int opcion;
        do{
        system("cls");
        cout << "Login successful" << endl;
        cout << "---------=====Menu=====---------"<<endl;
        cout << "| 1. Editar Informacion         |"<<endl;
        cout << "| 2. Eliminar Cuenta            |"<<endl;
        cout << "| 3. Ver Tutorial               |"<<endl;
        cout << "| 4. Ver Articulos de la tienda |"<<endl;
        cout << "| 5. Realizar movimientos       |"<<endl;
        cout << "| 6. Logout                     |"<<endl;
        cout << "---------==============---------"<<endl;
        cin >> opcion;
        switch(opcion){
            case 1 : 
                cout <<"Editar Informacion "<<endl;
                lista_usuarios.Editar(nick,SHA256::toString(digest));
                system("pause");
                break;
            case 2 :
                cout <<"Eliminar Cuenta "<<endl;
                lista_usuarios.Eliminar(nick,SHA256::toString(digest));
                system("pause");
                break;
            case 3 :
                cout <<"Ver Tutorial"<<endl;
                cola_tutorial.Mostrar();
                system("pause");
                break;
            case 4 :
                cout <<"Ver Articulos de la tienda"<<endl;
                lista_de_articulos.ImprimirArticulos();
                system("pause");
                break;
            case 5 :
                cout <<"Realizar movimientos"<<endl;
                system("pause");
                break;
            default :
                cout << "Opcion no valida"<<endl;
                system("pause");
                break;
        }
        system("cls");
    }while (opcion<=5);   
    }
}

void Reportes(){
    int opcion;
    do{
    system("cls");
    cout << "Login successful" << endl;
    cout << "---------=====Menu=====---------"<<endl;
    cout << "| 1. Ver Lista Doble Circular   |"<<endl;
    cout << "| 2. Orden Ascendente Usuarios  |"<<endl;
    cout << "| 3. Orden Descendente Usuarios |"<<endl;
    cout << "| 4. Ver Lista de Listas        |"<<endl;
    cout << "| 5. Orden Ascendete Articulos  |"<<endl;
    cout << "| 6. Orden Descendente Articulos|"<<endl;
    cout << "| 7. Ver Cola                   |"<<endl;
    cout << "| 8. Ver Lista de Pilas         |"<<endl;
    cout << "| 9. Salir                      |"<<endl;
    cout << "---------==============---------"<<endl;
    cin >> opcion;
    switch(opcion){
        case 1 : 
            cout <<"Generando Grafica"<<endl;
            lista_usuarios.GenerarGrafo();
            system("pause");
            break;
        case 2 :
            cout <<"Ordenando..."<<endl;
            lista_usuarios.Ordenar();
            lista_usuarios.ImprimirIF();
            system("pause");
            break;
        case 3 :
            cout <<"Ordenando..."<<endl;
            lista_usuarios.ImprimirFI();
            system("pause");
            break;
        case 4 :
            cout <<"Generando Grafica"<<endl;
            lista_de_articulos.GenerarGrafo();
            system("pause");
            break;
        case 5 :
            cout <<"Ordenando..."<<endl;
            lista_articulos_ordenada.OrdenarArticulos();
            lista_articulos_ordenada.ImprimirIFArticulo();
            system("pause");
            break;
        case 6 :
            cout <<"Ordenando..."<<endl;
            lista_articulos_ordenada.ImprimirFIArticulo();
            system("pause");
            break;
        case 7 :
            cout <<"Generando Grafica"<<endl;
            cola_tutorial.Graficar();
            system("pause");
            break;
        case 8 :
            cout <<"Generando Grafica"<<endl;
            cola_tutorial.Graficar();
            system("pause");
            break;
        default :
            cout << "Opcion no valida"<<endl;
            system("pause");
            break;
    }
    system("cls");
}while (opcion<=8);   
}

