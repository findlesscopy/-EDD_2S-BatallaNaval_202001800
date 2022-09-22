#include <cstdlib>

#include "Estructuras/ArbolB.cpp"
#include "Estructuras/AVL.cpp"
#include <windows.h> 
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    /*
    Usuario user;
    ArbolB pruebas;
    user = Usuario("Hola","Hola",1,1);
    pruebas.insertar(user);
    user = Usuario("Adios","Adios",8,8);
    pruebas.insertar(user);
    user = Usuario("JAJA","JAJA",4,4);
    pruebas.insertar(user);
    user = Usuario("LALALALA","LALALALA",3,3);
    pruebas.insertar(user);
    
    user = Usuario("TTTT","TTTT",1,1);
    pruebas.insertar(user);
    user = Usuario("YY","YY",8,8);
    pruebas.insertar(user);
    user = Usuario("KIKI","KIKI",4,4);
    pruebas.insertar(user);
    user = Usuario("RT","RT",3,3);
    pruebas.insertar(user);
    //        pruebas.insertar(1);
    //        pruebas.insertar(2);
    //        pruebas.insertar(3);
    //        pruebas.insertar(4);
    //        pruebas.insertar(5);
    //        pruebas.insertar(6);
    //        pruebas.insertar(7);
    //        pruebas.insertar(8);
    //        pruebas.insertar(9);
    //        pruebas.insertar(10);
    //        pruebas.insertar(11);
    //        pruebas.insertar(12);
    //        pruebas.insertar(13);
    //        pruebas.insertar(14);
    //        pruebas.insertar(15);
    //        pruebas.insertar(16);
    //        pruebas.insertar(17);
   
    pruebas.Grafo();
*/
    
    Compra compra;


    AVL pruebas;
    compra = Compra("25","hola",2);
    pruebas.insertar(compra);
    compra = Compra("45","adios",58);
    pruebas.insertar(compra);
    compra = Compra("7777asd","kk",96);
    pruebas.insertar(compra);
    compra = Compra("45asd654ad654","a",0);
    pruebas.insertar(compra);
    compra = Compra("798qwe798","ttttttttt",88);
    pruebas.insertar(compra);
    compra = Compra("465654asdasasd","kru",7777);
    pruebas.insertar(compra);
    compra = Compra("123789adj","r7777",222);
    pruebas.insertar(compra);
    compra = Compra("wrwwww43224","y",50);
    pruebas.insertar(compra);

    pruebas.graficar();
    
    return 0;
}
