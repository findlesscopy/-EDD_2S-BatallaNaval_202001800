
#include <cstdlib>
#include <iostream>
#include <string>

#include "ListaDobleCircular.cpp"
#include "ListaDeListas.cpp"
#include "Cola.cpp"

#include "SHA256.cpp"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;
 
int main(int argc, char** argv) {
/*
    ListaSimple pruebas;
    Usuario usuario;
    usuario = Usuario("Jose","findleaklsdas",12346,15); 
    pruebas.InsertarEnOrden(usuario);
    usuario = Usuario("Manuel","findleaklsdas",12346,18);
    pruebas.InsertarEnOrden(usuario);
    usuario = Usuario("Ibarra","findleaklsdas",12346,32);
    pruebas.InsertarEnOrden(usuario);
    usuario = Usuario("Pirir","findleaklsdas",12346,24);
    pruebas.InsertarEnOrden(usuario);
    
    pruebas.Imprimir();

    ListaDobleCircular pruebas2;
    Usuario usuario;
    usuario = Usuario("Segundo","Dos",20000,2); 
    pruebas2.Insertar(usuario);
    usuario = Usuario("Cuarto","Cuatro",40000,4);
    pruebas2.Insertar(usuario);
    usuario = Usuario("Primero","Uno",10000,1);
    pruebas2.Insertar(usuario);
    usuario = Usuario("Tercero","Tres",30000,3);
    pruebas2.Insertar(usuario);
    usuario = Usuario("Septimo","Siete",70000,7);
    pruebas2.Insertar(usuario);
    usuario = Usuario("Quinto","Cinco",50000,5);
    pruebas2.Insertar(usuario);
    usuario = Usuario("Sexto","Seis",60000,6);
    pruebas2.Insertar(usuario);
    pruebas2.ImprimirIF();
    pruebas2.GenerarGrafo();
    */
/*
    ListaDeListas pruebas3;
    pruebas3.InsertarCategoria("Hierro");
    pruebas3.InsertarCategoria("Bronce");
    pruebas3.InsertarCategoria("Plata");
    pruebas3.InsertarCategoria("Oro");
    

    pruebas3.InsertarArticulo("Hierro","Pala3",10.85,"Hola1","askldjalskjdjasdjaslkdj.com");
    pruebas3.InsertarArticulo("Hierro","Pala45",1085,"Hola200","qweqweqwe.com");
    pruebas3.InsertarArticulo("Hierro","Pala155",10850,"Hola5000","qweqwevzdvzcvzvcvxcvxqwe.com");
    pruebas3.ImprimirArticulos();
    pruebas3.GenerarGrafo();*/
    /*
    string s = "contrasenia";
    SHA256 sha;
    sha.update(s);
    uint8_t * digest = sha.digest();

    std::cout << SHA256::toString(digest) << std::endl;

    delete[] digest; // Don't forget to free the digest!

    std::ifstream f("input.json");
    json data = json::parse(f);
    string edad1 = data.at("usuarios")[0].at("edad");
    string nick = data.at("usuarios")[0].at("nick");
    int edad = stoi(edad1);
    
    
    std::cout <<"\n"<< edad << std::endl;
    std::cout <<"\n"<< nick << std::endl;
    std::cout <<data.at("usuarios").size()<< std::endl;
    */
   Cola pruebas4;
   pruebas4.Insertar(50,50);
   pruebas4.Insertar(10,5);
   pruebas4.Insertar(4,15);
   pruebas4.Insertar(40,18);
   pruebas4.Insertar(5,32);
   pruebas4.Mostrar();
   pruebas4.Peek();
   return 0;
}
