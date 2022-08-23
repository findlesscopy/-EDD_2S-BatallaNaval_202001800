
#include <cstdlib>
#include <iostream>

#include "ListaDobleCircular.cpp"
using namespace std;

/*
 * 
 */
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
*/
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
    return 0;
}
