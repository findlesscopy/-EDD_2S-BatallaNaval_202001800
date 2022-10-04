#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/http_header.h>

#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <iomanip>
#include <fstream>

#include "nlohmann/json.hpp"
#include "Estructuras/SHA256.cpp"
#include "Estructuras/ListaSimple.cpp"
#include "Estructuras/ListaDobleCircular.cpp"
#include "Estructuras/ListaDeListas.cpp"
#include "Estructuras/Cola.cpp"
#include "Estructuras/ListaArticulos.cpp"
#include "Estructuras/ListaDePilas.cpp"
#include "Estructuras/ArbolB.cpp"
#include "Estructuras/AVL.cpp"
ListaDobleCircular lista_usuarios;
ListaDeListas lista_de_articulos;
Cola cola_tutorial;
ListaArticulos lista_articulos_ordenada;
Usuario usuario;
Articulo articulo;
ListaDePilas lista_movimientos;
ArbolB btree;
AVL avltree;
Compra compra;

using namespace Pistache;
using json = nlohmann::json;
 
void hello(const Rest::Request& request, Http::ResponseWriter response) 
{
    response.send(Http::Code::Ok, "Prueba!");
}

void postDatos(const Rest::Request& request, Http::ResponseWriter response) 
{
    json data = json::parse(request.body().c_str());
    try{
        //Carga de Usuarios a Lista
        for(int i = 0; i < data.at("usuarios").size(); i++) {
            string id = data.at("usuarios")[i].at("id");
            int id1 = stoi(id);
            string nick = data.at("usuarios")[i].at("nick");
            string password = data.at("usuarios")[i].at("password");
            char password1[1000];
            strcpy(password1,password.c_str());
            string password_encriptada = SHA256(password1);
            string monedas = data.at("usuarios")[i].at("monedas");
            int monedas1 = stoi(monedas);
            string edad = data.at("usuarios")[i].at("edad");
            int edad1 = stoi(edad);
            usuario = Usuario(id1,nick,password_encriptada,monedas1,edad1); 
            lista_usuarios.Insertar(usuario);
            btree.insertar(usuario);
        
        }
        lista_usuarios.Ordenar();
        //btree.Grafo();
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
        
        
        response.send(Http::Code::Ok, "Datos cargados correctamente");
    }
    catch(const std::exception& e)
    {
        response.send(Http::Code::Internal_Server_Error, "Errorasdasdasd");
    }
    
    
    
}

void getAscendente(const Rest::Request& request, Http::ResponseWriter response) {
    
    string text = lista_usuarios.ImprimirIF();
    response.send(Http::Code::Ok, text);
}

void getDescendente(const Rest::Request& request, Http::ResponseWriter response) {

    string text = lista_usuarios.ImprimirFI();
    response.send(Http::Code::Ok, text);
}

void getLogin(const Rest::Request& request, Http::ResponseWriter response) {
    
    string nick = request.hasParam(":nick") ? request.param(":nick").as<string>():"No nick dado";
    string password = request.hasParam(":password") ? request.param(":password").as<string>():"No password dado";
    char password1[1000];
    strcpy(password1,password.c_str());
    string password_encriptada = SHA256(password1);
    string respuestaxd = "";
    if(lista_usuarios.BuscarUsuarioLogin(nick,password_encriptada)){
        respuestaxd = "Si";
    }else{
        respuestaxd = "No";
    }
    response.send(Http::Code::Ok, respuestaxd);
}

void getGrafoB(const Rest::Request& request, Http::ResponseWriter response) {

    btree.Grafo();
    response.send(Http::Code::Ok, "Ok");
}

void getArticulos(const Rest::Request& request, Http::ResponseWriter response) {

    string data = lista_articulos_ordenada.ImprimirFIArticulo();
    
    
    response.send(Http::Code::Ok, data);
}

void postCompra(const Rest::Request& request, Http::ResponseWriter response) {
    json data = json::parse(request.body().c_str());
    
    
    string id = data.at("id");
    string nombre = data.at("nombre");
    string cantidad = data.at("cantidad");
    int cantidad1 = stoi(cantidad);
    compra = Compra(id,nombre,cantidad1);
    avltree.insertar(compra);
    avltree.graficar();

    response.send(Http::Code::Ok, "Compra agregada");
}

int main(int argc, char* argv[]) 
{
    using namespace Rest;

    Router router;      // POST/GET/etc. route handler
    Port port(8080);    // port to listen on
    Address addr(Ipv4::any(), port);
    std::shared_ptr<Http::Endpoint> endpoint = std::make_shared<Http::Endpoint>(addr);
    auto opts = Http::Endpoint::options().threads(1).maxRequestSize(4096000000);   // how many threads for the server
    endpoint->init(opts);

    Routes::Get(router, "/", Routes::bind(&hello));
    Routes::Post(router, "/Datos", Routes::bind(&postDatos));
    Routes::Get(router, "/UsuariosAsc/", Routes::bind(&getAscendente));
    Routes::Get(router, "/UsuariosDes/", Routes::bind(&getDescendente));
    Routes::Get(router, "/Login/:nick?/:password?", Routes::bind(&getLogin));
    Routes::Get(router, "/Grafo/B", Routes::bind(&getGrafoB));
    Routes::Get(router, "/Articulos/", Routes::bind(&getArticulos));
    Routes::Post(router, "/Compra", Routes::bind(&postCompra));

    endpoint->setHandler(router.handler());
    endpoint->serve();
    return 0;
}