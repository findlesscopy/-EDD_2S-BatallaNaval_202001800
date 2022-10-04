#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "Estructuras/SHA256.cpp"
#include "Estructuras/ListaDobleCircular.cpp"
#include "Estructuras/ArbolB.cpp"

using namespace std;

int main(){
    ArbolB* prueba = new ArbolB;
    Usuario usuario;
    usuario = Usuario(1234,"Hola","Adios",55,5);
    prueba->insertar(usuario);
    usuario = Usuario(666,"asdasd","ereret",55,3);
    prueba->insertar(usuario);
    usuario = Usuario(768776,"werwerqw","uioui",55,7);
    prueba->insertar(usuario);
    usuario = Usuario(56456,"Hola","Adios",55,5);
    prueba->insertar(usuario);
    usuario = Usuario(34234,"asdasd","ereret",55,3);
    prueba->insertar(usuario);
    usuario = Usuario(57,"werwerqw","uioui",55,7);
    prueba->insertar(usuario);
    usuario = Usuario(678,"Hola","Adios",55,5);
    prueba->insertar(usuario);
    usuario = Usuario(456456,"asdasd","ereret",55,3);
    prueba->insertar(usuario);
    usuario = Usuario(89089,"werwerqw","uioui",55,7);
    prueba->insertar(usuario);
    
    

    
    delete prueba;
    //prueba->Grafo();

    /*
    prueba.Ordenar();
    cout<<prueba.ImprimirIF();
    cout<<prueba.ImprimirFI();
    if(prueba.BuscarUsuarioLogin("Hola","Adios")){
        cout<<"Si";
    }else{
        cout<<"No";
    }
    if(prueba.BuscarUsuarioLogin("Hola","AAAAAAAAAAAAAA")){
        cout<<"Si";
    }else{
        cout<<"No";
    }*/

    return 0;
}