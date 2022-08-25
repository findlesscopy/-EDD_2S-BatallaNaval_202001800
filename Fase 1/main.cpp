#include <iostream>
#include <cstdlib>


#include "helpers.cpp"

using namespace std;

int opcion;
string dir;
string nick, password;
int edad;
int main(){

    do{
        cout << "--------=====Menu=====--------"<<endl;
        cout << "| 1. Carga masiva            |"<<endl;
        cout << "| 2. Registrar Usuario       |"<<endl;
        cout << "| 3. Login                   |"<<endl;
        cout << "| 4. Reportes                |"<<endl;
        cout << "| 5. Salir del Juego         |"<<endl;
        cout << "--------==============--------"<<endl;
        cin >> opcion;
        switch(opcion){
            case 1 : 
                cout <<"Ingrese la ruta del archivo: "<<endl;
                cin>> dir;
                //cout<<dir;
                CargaMasiva(dir);
                system("pause");
                break;
            case 2 :
                cout <<"Ingrese el nick:"<<endl;
                cin>> nick;
                cout<<"Ingrese su contrasenia"<<endl;
                cin>>password;
                cout<<"Ingrese su edad"<<endl;
                cin>>edad;

                RegistroUsuario(nick,password,0,edad);
                system("pause");
                
                break;
            case 3 :
                cout <<"Ingrese su nick"<<endl;
                cin>> nick;
                cout <<"Ingrese su contrasenia"<<endl;
                cin>> password;
                Login(nick,password);
                system("pause");
                break;
            case 4 :
                cout << "Reportes"<<endl;
                Reportes();
                system("pause");
                break;
            default :
                cout << "Opcion no valida"<<endl;
                system("pause");
                break;
        }
        system("cls");
    }while (opcion<=4);
    return 0;
}